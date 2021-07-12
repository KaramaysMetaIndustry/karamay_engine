#ifndef H_GL_BUFFER_BASE
#define H_GL_BUFFER_BASE

#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer_tools.h"


/*
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

    explicit gl_buffer(std::int64_t capacity, gl_buffer_storage_options storage_options) :
        _capacity(capacity),
        _size(0),
        _storage_flags(0),
        _storage_options(storage_options)
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
            _capacity = capacity;
        }
    }

    ~gl_buffer() override
    {
        glDeleteBuffers(1, &_handle);
    }

public:

    void reserve(std::int64_t capacity);

    void shrink_to_fit();

public:

    void write(){}

    void write_with_mask()
    {

    }

    void invalidate(){}


public:

    /*
     * [App -> GL]
     * */
    void push_back(const std::uint8_t* stream, std::int64_t stream_size)
    {
        // check the dynamic updating validation
        if(!_storage_options.is_dynamic_storage|| !stream || stream_size < 0 || _size < 0) return;
        // check the rest capacity
        if(_size + stream_size > _capacity)  _reallocate(_size + stream_size);

        glNamedBufferSubData(_handle, _size, stream_size, reinterpret_cast<const void*>(stream));

        _size += stream_size;
    }

    /*
     * Static
     * [App -> GL]
     * 使用情形：离散数据，非离散数据请使用数组更新，会大幅降低上下文开销
     * */
    template<typename GLSL_T>
    inline void push_back(const GLSL_T& data)
    {
        STATIC_ASSERT_GLSL_T();
        push_back(reinterpret_cast<const std::uint8_t*>(glm::value_ptr(data)), sizeof (GLSL_T));
    }

    /*
     * Static
     * [App -> GL]
     * 插入非离散同类数据
     * */
    template<typename GLSL_T>
    inline void push_back(const std::vector<GLSL_T>& data_collection)
    {
        STATIC_ASSERT_GLSL_T();
        push_back(reinterpret_cast<const std::uint8_t*>(data_collection.data()), data_collection.size() * sizeof(GLSL_T));
    }

    /*
     * Dynamic
     * */
    inline void push_back(glsl_type type, std::uint8_t* stream)
    {
        if(!stream) return;
        push_back(stream, get_glsl_type_size(type));
    }

    /*
     * Dynamic
     * */
    inline void push_back(glsl_type type, std::uint32_t num, std::uint8_t* stream)
    {
        if(!stream) return;
        push_back(stream, get_glsl_type_size(type) * num);
    }

    inline void push_back(std::uint8_t data, std::int64_t count)
    {
        std::vector<std::uint8_t> _data(data, count);
        push_back(_data.data(), count);
    }

public:

    /*
     * Pure [Client -> Server]
     * offset > 0 && data_size > 0 &&
     * offset + data_size <= _capacity &&
     * data's length == data_size
     * */
    void overwrite(std::int64_t offset, const std::uint8_t* data, std::int64_t data_size);

    /*
     * Pure [Client -> Server]
     * offset > 0 && data_size > 0 &&
     * offset + data_size <= _capacity &&
     * data's length == data_size
     * */
    template<typename GLSL_T>
    inline void overwrite(std::int64_t offset, const GLSL_T& data)
    {
        STATIC_ASSERT_GLSL_T();
        overwrite(offset, reinterpret_cast<const std::uint8_t*>(&data), static_cast<std::int64_t>(sizeof(GLSL_T)));
    }

    /*
     * Pure [Client -> Server]
     * offset > 0 && data_size > 0 &&
     * offset + data_size <= _capacity &&
     * data's length == data_size
     * */
    template<typename GLSL_T>
    inline void overwrite(std::int64_t offset, const std::vector<GLSL_T>& data_collection)
    {
        STATIC_ASSERT_GLSL_T();
        overwrite(offset, reinterpret_cast<const std::uint8_t*>(data_collection.data()), static_cast<std::int64_t>(data_collection.size() * sizeof(GLSL_T)));
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

    [[nodiscard]] std::int64_t get_capacity() const { return _capacity; }

    [[nodiscard]] std::int64_t get_size() const { return _size; }

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
        execute_immutable_memory_handler(0, _size, [](const std::uint8_t* data, std::int64_t size){
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

    std::int64_t _capacity, _size;

    std::uint32_t _storage_flags;

    gl_buffer_storage_options _storage_options;

    //    void asynchronous(){}
    //    void synchronous(){}
    //    void synchronized(){}


};

#endif
