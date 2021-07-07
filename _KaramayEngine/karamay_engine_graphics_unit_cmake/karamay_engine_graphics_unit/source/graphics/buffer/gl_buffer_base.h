#ifndef H_GL_BUFFER_BASE
#define H_GL_BUFFER_BASE

#include "graphics/glo/gl_object.h"

enum class gl_buffer_storage_flag : GLenum
{
    MAP_READ_BIT = GL_MAP_READ_BIT,
    MAP_WRITE_BIT = GL_MAP_WRITE_BIT,

    DYNAMIC_STORAGE_BIT = GL_DYNAMIC_STORAGE_BIT,
    CLIENT_STORAGE_BIT = GL_CLIENT_STORAGE_BIT,

    MAP_PERSISTENT_BIT = GL_MAP_PERSISTENT_BIT,
    MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT
};

struct gl_buffer_storage_options
{
    std::uint8_t is_map_read;
    std::uint8_t is_map_write;
    std::uint8_t is_dynamic_storage;
    std::uint8_t is_client_storage;
    std::uint8_t is_map_persistent;
    std::uint8_t is_map_coherent;
};

enum class gl_buffer_map_access_flag : GLenum
{
    MAP_READ_BIT = GL_MAP_READ_BIT,
    MAP_WRITE_BIT = GL_MAP_WRITE_BIT,
    MAP_PERSISTENT = GL_MAP_PERSISTENT_BIT,
    MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT,
    MAP_INVALIDATE_RANGE_BIT = GL_MAP_INVALIDATE_RANGE_BIT,
    MAP_INVALIDATE_BUFFER_BIT = GL_MAP_INVALIDATE_BUFFER_BIT,
    MAP_FLUSH_EXPLICIT_BIT = GL_MAP_FLUSH_EXPLICIT_BIT,
    MAP_UNSYNCHRONIZED_BIT = GL_MAP_UNSYNCHRONIZED_BIT
};

class gl_buffer_base : public gl_object
{
public:

    const static std::int64_t THEORETICAL_MAX_CAPACITY;
    const static std::int64_t HARDWARE_MAX_CAPACITY;
    const static std::int64_t GPU_MAX_CAPACITY;
    const static std::int64_t BUFFER_AVAILABLE_MAX_CAPACITY;

public:

    explicit gl_buffer_base(std::int64_t capacity, gl_buffer_storage_options storage_options) :
        _capacity(capacity),
        _size(0),
        _storage_flags(0)
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

    ~gl_buffer_base() override = default;

public:

    [[nodiscard]] std::int64_t get_capacity() const { return _capacity; }

    [[nodiscard]] std::int64_t get_size() const { return _size; }

    [[nodiscard]] std::uint32_t get_storage_flags() const { return _storage_flags; }

public:

    void reserve(std::int64_t capacity);

    void shrink_to_fit()
    {
        if(_size < _capacity)
        {
            _reallocate(_size);
        }
    };

public:

    void push_back(const std::uint8_t* data, std::int64_t data_size)
    {
        if(!data || data_size < 0 || _size < 0) return;

        if(_size + data_size > _capacity)  _reallocate(_size + data_size);

        glNamedBufferSubData(_handle, _size, data_size, reinterpret_cast<const void*>(data));

        _size += data_size;
    }

    template<typename GLM_T>
    inline void push_back(const GLM_T& data)
    {
        push_back(reinterpret_cast<const std::uint8_t*>(glm::value_ptr(data)), sizeof (GLM_T));
    }

    template<typename GLM_T>
    inline void push_back(const std::vector<GLM_T>& data_collection)
    {
        push_back(reinterpret_cast<const std::uint8_t*>(data_collection.data()), data_collection.size() * sizeof(GLM_T));
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
    template<typename GLM_T>
    inline void overwrite(std::int64_t offset, const GLM_T& data)
    {
        overwrite(offset, reinterpret_cast<const std::uint8_t*>(glm::value_ptr(data)), static_cast<std::int64_t>(sizeof(GLM_T)));
    }

    /*
     * Pure [Client -> Server]
     * offset > 0 && data_size > 0 &&
     * offset + data_size <= _capacity &&
     * data's length == data_size
     * */
    template<typename GLM_T>
    inline void overwrite(std::int64_t offset, const std::vector<GLM_T>& data_collection)
    {
        overwrite(offset, reinterpret_cast<const std::uint8_t*>(data_collection.data()), static_cast<std::int64_t>(data_collection.size() * sizeof(GLM_T)));
    }

public:


public:

    /*
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     * */
    void rapidly_overwrite(std::uint8_t data_mask = 0);

    template<typename GLM_T>
    inline void rapidly_overwrite(const GLM_T& data_mask)
    {
    }

public:

    /*
     * grab another same buffer storage as new one
     * */
    void invalidate(std::int64_t offset, std::int64_t size);

    void invalidate()
    {
        glInvalidateBufferData(_handle);
    }

public:
    /*
     * Pure [Server -> Server]
     * */
    void output_data_to_buffer(std::int64_t self_offset, int64_t output_size, gl_buffer_base& target, std::int64_t target_offset);

    /*
     * Pure [Server -> Server]
     * */
    void output_data_to_buffer(gl_buffer_base& target_buffer);

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

    [[nodiscard]] std::int64_t get_buffer_size() const
    {
        std::int64_t _buffer_size = 0;
        glGetNamedBufferParameteri64v(_handle, GL_BUFFER_SIZE, &_buffer_size);
        return _buffer_size;
    }

    [[nodiscard]] std::uint8_t is_mapped() const
    {
        std::int32_t _is_mapped = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_MAPPED, &_is_mapped);
        return _is_mapped == GL_TRUE;
    }

    [[nodiscard]] std::int32_t get_access() const
    {
        std::int32_t _buffer_access = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_ACCESS, &_buffer_access);
        return _buffer_access;
    }

    [[nodiscard]] std::int32_t get_usage() const
    {
        std::int32_t _buffer_usage = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_USAGE, &_buffer_usage);
        return _buffer_usage;
    }

protected:

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

//    void asynchronous(){}
//
//    void synchronous(){}
//
//    void synchronized(){}

private:

    std::int64_t _capacity, _size;

    std::uint32_t _storage_flags;

private:

    void _reallocate(std::int64_t new_capacity);

};

#endif
