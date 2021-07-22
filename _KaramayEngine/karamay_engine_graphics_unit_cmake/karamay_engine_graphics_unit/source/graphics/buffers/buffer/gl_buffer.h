#ifndef H_GL_BUFFER
#define H_GL_BUFFER

#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer_tools.h"
#include "graphics/type/glsl.h"

class gl_buffer final : public gl_object
{
private:

    const static std::int64_t THEORETICAL_MAX_CAPACITY;

    const static std::int64_t HARDWARE_MAX_CAPACITY;

    const static std::int64_t GPU_MAX_CAPACITY;

    const static std::int64_t BUFFER_AVAILABLE_MAX_CAPACITY;

public:

    static std::shared_ptr<gl_buffer> new_buffer(std::int64_t capacity, gl_buffer_storage_options storage_options)
    {
        return std::make_shared<gl_buffer>(capacity, storage_options);
    }

    static std::shared_ptr<gl_buffer> new_buffer(std::int64_t capacity)
    {
        return std::make_shared<gl_buffer>(capacity, gl_buffer_storage_options());
    }

public:

    explicit gl_buffer(std::int64_t capacity, gl_buffer_storage_options storage_options) :
        _capacity(capacity),
        _storage_options(storage_options)
    {
        _allocate_buffer();
    }

    ~gl_buffer() override
    {
        _release_buffer();
    }

private:

    /*
    * 
    */
    void write(std::int64_t offset, const std::uint8_t* byte_stream, std::int64_t byte_stream_size)
    {
        if(
            !_check_object_validation() || 
            !_storage_options.is_dynamic_storage || 
            !byte_stream || offset < 0 || offset + byte_stream_size > _capacity
            ) return;
        glNamedBufferSubData(_handle, offset, byte_stream_size, byte_stream);
    }

public:

    /*
    * conditions:
    * 1) write single value
    * 2) value's type is not concrete enough, otherwise please use the specialized 'write_single'
    */
    void write_single(std::int64_t offset, const glsl_class* value_ptr)
    {
        if(!_check_object_validation() || !_storage_options.is_dynamic_storage || 
            !byte_stream || offset < 0 || offset + byte_stream_size > _capacity
            ) return;

        if(glsl_value)
        {
            glNamedBufferSubData(_handle, offset, glsl_value->stream(), glsl_value->stream_size());
        }
    }

    /*
    * conditions:
    * 1) write single value
    * 2) value's type is concrete enough
    */
    template<typename GLSL_CLASS>
    void write_single_specialized(std::int64_t offset, const GLSL_CLASS& value)
    {}

public:

    /*
    * conditions:
    * 
    */
    void write_sequence(std::int64_t offset, const std::vector<const glsl_class*>& block)
    {
        std::int64_t _size = 0;
        for(const glsl_class* value : values)
        {
            if(!value) return;
            _size += value->stream_size();
        }
        execute_mutable_memory_handler(offset, _size, [&values](std::uint8_t* mapped_memory, std::int64_t size){
            if(mapped_memory)
            {
                for(const glsl_class* _value : values)
                {
                    std::memcpy(mapped_memory, _value, _value->stream_size());
                }
            }
        });
    }

    template<typename GLSL_CLASS>
    void write_sequence_specialized(std::int64_t offset, const std::vector<GLSL_CLASS>& block)
    {}

public:

    void write_point_cloud(const std::vector<pair<std::int64_t, const glsl_class*>>& point_cloud)
    {}

public:

    template<typename GLSL_TRANSPARENT_T>
    void write_dispersed_list(const std::vector<std::pair<std::int64_t, GLSL_TRANSPARENT_T>>& dispersed_list)
    {

        if(dispersed_list.size() < 5) for(const auto& _pair : dispersed_list) write(_pair.first, _pair.second);
        else {
            const std::int64_t _dispersed_list_covered_size = 0;
            const std::int64_t _min_offset = 0;
            if(_min_offset < 0 || _min_offset + _dispersed_list_covered_size > _capacity) return;
            execute_mutable_memory_handler(_min_offset, _dispersed_list_covered_size, [&dispersed_list](std::uint8_t* mapped_memory, std::int64_t mapped_memory_size){
                if(mapped_memory)
                {
                    for(const auto& _pair : dispersed_list)
                    {
                        //std::memcpy(mapped_memory, _pair.second, )
                    }
                }
            });
        }
    }

    void write_dispersed_interracial_list(const std::vector<std::pair<int64_t, const glsl_transparent_class*>>& dispersed_interracial_list)
    {

    }

    template<typename GLSL_TRANSPARENT_T>
    void write_consequent_list(std::int64_t offset, const std::vector<GLSL_TRANSPARENT_T>& consequent_list)
    {
        const std::int64_t _consequent_list_size = consequent_list.size() * sizeof(GLSL_TRANSPARENT_T);
        if(offset < 0 || offset +  _consequent_list_size > _capacity) return;
        glNamedBufferSubData(_handle, offset, _consequent_list_size, reinterpret_cast<const void*>(consequent_list.data()));
    }

    void write_consequent_interracial_list(std::int64_t offset, const std::vector<const glsl_transparent_class*>& consequent_interracial_list)
    {
        std::int64_t _consequent_interracial_list_size = 0;
        for(const auto& _value : consequent_interracial_list) if(_value) _consequent_interracial_list_size += _value->clazz()->class_size;

        if(offset < 0 || _consequent_interracial_list_size < 0 || offset + _consequent_interracial_list_size > _capacity) return;
        {
            auto* _tmp_data = (std::uint8_t*)malloc(_consequent_interracial_list_size);
            std::int64_t _tmp_data_offset = 0;
            for(const auto* _value : consequent_interracial_list)
            {
                if(_tmp_data && _value)
                {
                    std::memcpy(_tmp_data + _tmp_data_offset, _value->stream(), _value->clazz()->class_size);
                    _tmp_data_offset += _value->clazz()->class_size;
                }
            }
            glNamedBufferSubData(_handle, offset, _consequent_interracial_list_size, _tmp_data);
        }

        //
//        {
//            execute_mutable_memory_handler(offset, _consequent_interracial_list_size, [&consequent_interracial_list](std::uint8_t* mapped_memory, std::int64_t mapped_memory_size){
//                if(mapped_memory)
//                {
//                    std::int64_t _offset = 0;
//                    for(const auto& _pair : consequent_interracial_list)
//                    {
//                        std::memcpy(mapped_memory + _offset, _pair.first, _pair.second);
//                        _offset += _pair.second;
//                    }
//                }
//            });
//        }
    }

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
     * Invalidate the whole buffers, data in buffers will become undefined.
     * */
    void invalidate()
    {
        glInvalidateBufferData(_handle);
    }

    /*
     * grab another same buffers storage as new one
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

    std::uint8_t _check_object_validation() const override { return glIsBuffer(_handle) == GL_TRUE; }

    void _allocate_buffer()
    {
        glCreateBuffers(1, &_handle);
        if(_handle == 0) throw std::exception("can not allocate a new buffer");
        std::uint32_t _storage_flags = 0;
        glNamedBufferStorage(_handle, _capacity, nullptr, _storage_flags);
    }

    void _release_buffer()
    {
        glDeleteBuffers(1, &_handle);
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

    std::int64_t _capacity;

    gl_buffer_storage_options _storage_options;
};

#endif
