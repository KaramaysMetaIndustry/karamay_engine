#ifndef H_GL_BUFFER_BASE
#define H_GL_BUFFER_BASE

#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer_tools.h"


struct gl_buffer_pool_element
{
    std::uint32_t handle;
    std::int64_t capacity;
    gl_buffer_storage_options storage_options;
    std::uint32_t storage_flags;

    gl_buffer_pool_element(const gl_buffer_pool_element& other)
    {
    }
};

/*
 * [You must trust clients who will use your class.]
 * gl_buffer which can only accept glsl_type and bytes
 *
 * */
class gl_buffer : public gl_object
{
public:

    const static std::int64_t THEORETICAL_MAX_CAPACITY;
    const static std::int64_t HARDWARE_MAX_CAPACITY;
    const static std::int64_t GPU_MAX_CAPACITY;
    const static std::int64_t BUFFER_AVAILABLE_MAX_CAPACITY;

public:

    explicit gl_buffer(std::int64_t required_capacity, gl_buffer_storage_options storage_options) :
        _required_capacity(required_capacity),
        _storage_options(storage_options),
        _capacity(0),
        _storage_flags(0)
    {
        reallocate(required_capacity, storage_options);

        auto value = glsl_transparent_class::create("vec3", {"1.0f", "1.0f", "1.0f"});
        auto _value = dynamic_cast<glsl_vec3*>(value);
        if(_value)
        {
            
        }
    }

    ~gl_buffer() override
    {
        //_buffer_pool.insert_after(_buffer_pool.end(), gl_buffer_pool_element{_handle, _storage_options, _capacity});
    }

public:

    /*
     * Description: immediately write << bytes stream >> into [offset, offset + byte_stream_size)
     *
     * */
    void write(std::int64_t offset, const std::uint8_t* byte_stream, std::int64_t byte_stream_size)
    {
        if(!byte_stream || offset < 0 || offset + byte_stream_size > _capacity) return;
        glNamedBufferSubData(_handle, offset, byte_stream_size, byte_stream);
    }

public:

    /*
     * Description: immediately write << single abstract type value >> into [offset, offset + sizeof(GLSL_TRANSPARENT_T))
     * */
    void write(std::int64_t offset, const glsl_transparent_type* value)
    {
        if(!value || offset < 0 || offset + value->meta().type_size > _capacity) return;
        glNamedBufferSubData(_handle, offset, value->meta().type_size, value->data());
    }

    /*
     * Description: immediately write << single exact type value >> into [offset, offset + sizeof(GLSL_TRANSPARENT_T))
     *
     * */
    template<typename GLSL_TRANSPARENT_T>
    void write(int64_t offset, const GLSL_TRANSPARENT_T& value)
    {
        static_assert(std::is_base_of<glsl_transparent_type, GLSL_TRANSPARENT_T>::value, "type must derived from glsl_transparent_type");
        const std::int64_t _value_size = sizeof(GLSL_TRANSPARENT_T);
        if(offset < 0 || offset + _value_size > _capacity) return;
        glNamedBufferSubData(_handle, offset, _value_size, reinterpret_cast<const void*>(&value));
    }

public:

    /*
     * Description: immediately write << consequent abstract type values >> into [offset, offset + )
     * */
    void write(std::int64_t offset, const std::vector<glsl_transparent_type*>& consequent_values)
    {
        std::int64_t _total_size = 0;
        for(auto _value : consequent_values)
        {
            if(_value)  _total_size += _value->meta().type_size;
        }

        execute_mutable_memory_handler(offset, _total_size, [&consequent_values](std::uint8_t* memory, std::int64_t size){
            std::int64_t _offset = 0;
            for(auto _value : consequent_values)
            {
                if(_value) std::memcpy(memory + _offset, _value->data(), _value->meta().type_size);
            }
        });
    }

    /*
     * Description: immediately write << consequent exact type values >> into [offset, offset + sizeof(GLSL_TRANSPARENT_T) * num)
     * */
    template<typename GLSL_TRANSPARENT_T>
    void write(std::int64_t offset, const std::vector<GLSL_TRANSPARENT_T>& consequent_values)
    {
        static_assert(std::is_base_of<glsl_transparent_type, GLSL_TRANSPARENT_T>::value, "type must derived from glsl_transparent_type");

        const std::int64_t _consequent_values_size = sizeof(GLSL_TRANSPARENT_T) * consequent_values.size();
        if(offset < 0 || offset +  _consequent_values_size > _capacity) return;
        glNamedBufferSubData(_handle, offset, _consequent_values_size, reinterpret_cast<const void*>(consequent_values.data()));
    }

public:

    /*
     * Description: async write << dispersed abstract type values >> into [)
     * */
    void write(const std::vector<std::pair<std::int64_t, const glsl_transparent_type*>>& dispersed_values)
    {
        std::int64_t _min_offset, _max_offset;
        _min_offset = _max_offset = 0;
    }

private:

    static std::forward_list<gl_buffer_pool_element> _buffer_pool;

public:

    void reallocate(std::int64_t capacity, gl_buffer_storage_options storage_options)
    {
        // search the suitable buffer
        auto _it = std::find_if(_buffer_pool.begin(), _buffer_pool.end(), [&](const gl_buffer_pool_element& element){
            return _check_buffer_validation(capacity, storage_options);
        });

        // do not find one, create a new one
        if(_it == _buffer_pool.end())
        {
            glCreateBuffers(1, &_handle);
            if(_handle != 0)
            {
                if(storage_options.is_map_read) _storage_flags |= GL_MAP_READ_BIT;
                if(storage_options.is_map_write) _storage_flags |= GL_MAP_WRITE_BIT;
                if(storage_options.is_map_persistent) _storage_flags |= GL_MAP_PERSISTENT_BIT;
                if(storage_options.is_map_coherent) _storage_flags |= GL_MAP_COHERENT_BIT;
                if(storage_options.is_client_storage) _storage_flags |= GL_CLIENT_STORAGE_BIT;
                if(storage_options.is_dynamic_storage) _storage_flags |= GL_DYNAMIC_STORAGE_BIT;

                glNamedBufferStorage(_handle, capacity, nullptr, _storage_flags);
                _required_capacity = capacity;
            }
        }else{ // find a suitable buffer
            // fetch
            _handle = _it->handle;
            _required_capacity = capacity;
            _storage_options = _it->storage_options;
            _storage_flags = _it->storage_flags;
            _capacity = _it->capacity;

            //_buffer_pool.remove(*_it);
        }
    }

    void reallocate(std::int64_t capacity)
    {
        reallocate(capacity, _storage_options);
    }

private:

    bool _check_buffer_validation(std::int64_t required_capacity, gl_buffer_storage_options storage_options)
    {

    }

    void _release_all_buffers()
    {


    }

    void _release_isolated_buffers(){}

public:

    /*
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     * */
    void overwrite_by_byte(std::int64_t offset, std::int64_t size);

    template<typename GLSL_T>
    inline void overwrite_by_unit(std::int64_t offset, std::int64_t size, const GLSL_T& unit)
    {
        glClearNamedBufferSubData(_handle, 0, offset, size, 0, 0, reinterpret_cast<const std::uint8_t*>(&unit));
    }

public:

    /*
     * Invalidate the whole buffer, data in buffer will become undefined.
     * */
    void invalidate()
    {
        glInvalidateBufferData(_handle);
    }

    /*
     * grab another same buffer storage as new one
     * */
    void invalidate(std::int64_t offset, std::int64_t size)
    {
        if(offset < 0 || size < 0 || offset + size > _capacity) return; // VALUE_INVALID
        glInvalidateBufferSubData(_handle, offset, size);
    }

public:
    /*
     * Pure [Server -> Server]
     * */
    void output_data_to_buffer(std::int64_t self_offset, int64_t output_size, gl_buffer& target, std::int64_t target_offset);

    /*
     * Pure [Server -> Server]
     * */
    void output_data_to_buffer(gl_buffer& target_buffer);

public:

    /*
     * map a block of immutable memory
     * then execute a handler you specified (can not do any modification)
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * */
    void execute_immutable_memory_handler(std::int64_t offset, std::int64_t size, const std::function<void(const std::uint8_t*, std::int64_t)>& handler);

    /*
     * map a block of mutable memory
     * then execute a handler you specified
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * */
    void execute_mutable_memory_handler(std::int64_t offset, std::int64_t size, const std::function<void(std::uint8_t*, std::int64_t)>& handler);

public:

    [[nodiscard]] std::int64_t get_capacity() const { return _required_capacity; }

    [[nodiscard]] std::uint32_t get_storage_flags() const { return _storage_flags; }

    [[nodiscard]] std::int64_t query_buffer_size() const
    {
        std::int64_t _buffer_size = 0;
        glGetNamedBufferParameteri64v(_handle, GL_BUFFER_SIZE, &_buffer_size);
        return _buffer_size;
    }

    [[nodiscard]] std::uint8_t query_buffer_mapped() const
    {
        std::int32_t _is_mapped = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_MAPPED, &_is_mapped);
        return _is_mapped == GL_TRUE;
    }

    [[nodiscard]] std::int32_t query_buffer_access() const
    {
        std::int32_t _buffer_access = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_ACCESS, &_buffer_access);
        return _buffer_access;
    }

    [[nodiscard]] std::int32_t query_buffer_usage() const
    {
        std::int32_t _buffer_usage = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_USAGE, &_buffer_usage);
        return _buffer_usage;
    }

private:

    [[nodiscard]] inline bool _check_capacity(std::int64_t capacity) const
    {
        return capacity != _capacity && capacity < BUFFER_AVAILABLE_MAX_CAPACITY;
    }

public:

    template<typename T>
    void print()
    {
        execute_immutable_memory_handler(0, _required_capacity, [](const std::uint8_t* data, std::int64_t size){
            const auto _data = reinterpret_cast<const T*>(data);
            if(_data)
            {
                for(std::int32_t _index = 0; _index < size/ sizeof(T); ++_index)
                {
                    std::cout<<": "<<_data[_index] <<std::endl;

                }
            }
        });
    }

private:

    void _reallocate(std::int64_t new_capacity);

private:

    std::int64_t _capacity, _required_capacity;

    std::uint32_t _storage_flags;

    gl_buffer_storage_options _storage_options;


};

#endif
