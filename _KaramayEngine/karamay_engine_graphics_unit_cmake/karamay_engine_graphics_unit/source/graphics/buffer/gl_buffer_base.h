#ifndef H_GL_BUFFER_BASE
#define H_GL_BUFFER_BASE

#include "graphics/glo/gl_object.h"

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

    const static std::int32_t MAX_CAPACITY;

protected:

    explicit gl_buffer_base(std::int32_t capacity) :
        _capacity(capacity)
    {}

    ~gl_buffer_base() override = default;

    std::int32_t _capacity;

public:

    [[nodiscard]] std::int32_t get_capacity() const {return _capacity;}

public:

    /*
     * Pure [Client -> Server]
     * offset > 0 && data_size > 0 &&
     * offset + data_size <= _capacity &&
     * data's length == data_size
     * */
    VALID void fill(std::int32_t offset, const std::uint8_t* data, std::int32_t data_size);

    /*
     * Pure [Client -> Server]
     * offset > 0 && data_size > 0 &&
     * offset + data_size <= _capacity &&
     * data's length == data_size
     * */
    template<typename GLM_T>
    VALID inline void fill(std::int32_t offset, const GLM_T& data)
    {
        fill(offset, reinterpret_cast<const std::uint8_t*>(glm::value_ptr(data)), sizeof(GLM_T));
    }

    /*
     * Pure [Client -> Server]
     * offset > 0 && data_size > 0 &&
     * offset + data_size <= _capacity &&
     * data's length == data_size
     * */
    template<typename GLM_T>
    VALID inline void fill(std::int32_t offset, const std::vector<GLM_T>& data_collection)
    {
        fill(offset, reinterpret_cast<const std::uint8_t*>(data_collection.data()), data_collection.size() * sizeof(GLM_T));
    }

public:

    /*
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     * */
    VALID void rapidly_fill(std::uint8_t data_mask = 0);

    template<typename GLM_T>
    inline void rapidly_fill(const GLM_T& data_mask){}

public:

    /*
     * grab another same buffer storage as new one
     * */
    void invalidate(std::int32_t offset, std::int32_t size);

    void invalidate()
    {
        glInvalidateBufferData(_handle);
        _throw_errors("glInvalidateBufferData");
    }

public:
    /*
     * Pure [Server -> Server]
     * */
    VALID void output_data(std::int32_t self_offset, int32_t output_size, gl_buffer_base* target_buffer, std::int32_t target_buffer_offset);

    /*
     * Pure [Server -> Server]
     * */
    VALID void output_data(gl_buffer_base* target_buffer);

public:

    /*
     * map a block of immutable memory
     * then execute a handler you specified (can not do any modification)
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * */
    VALID void execute_immutable_memory_handler(std::int32_t offset, std::int32_t size, const std::function<void(const std::uint8_t*, std::int32_t)>& handler);

    /*
     * map a block of mutable memory
     * then execute a handler you specified
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * */
    VALID void execute_mutable_memory_handler(std::int32_t offset, std::int32_t size, const std::function<void(std::uint8_t*, std::int32_t)>& handler);

public:

    [[nodiscard]] std::int32_t get_buffer_size() const
    {
        std::int32_t _buffer_size = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_SIZE, &_buffer_size);
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

    [[nodiscard]] bool _check_capacity(std::int32_t capacity) const
    {
        return capacity != _capacity && capacity < MAX_CAPACITY;
    }

    inline void _internal_clear_by_byte_zero()
    {
        std::uint8_t _value = 0;
        glClearNamedBufferData(_handle, GL_R8UI, GL_RED, GL_UNSIGNED_BYTE, &_value);
    }

public:

    template<typename T>
    VALID void print()
    {
        execute_immutable_memory_handler(0, _capacity, [](const std::uint8_t* data, std::int32_t size){
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

};



#endif
