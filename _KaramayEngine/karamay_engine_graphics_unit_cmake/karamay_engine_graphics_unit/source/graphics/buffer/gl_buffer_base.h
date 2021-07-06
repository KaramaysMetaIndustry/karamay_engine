//
// Created by jichengcheng on 2021/7/1.
//

#ifndef KARAMAY_ENGINE_GRAPHICS_UNIT_GL_BUFFER_BASE_H
#define KARAMAY_ENGINE_GRAPHICS_UNIT_GL_BUFFER_BASE_H

#define OPTIMIZED

#include "graphics/glo/gl_object.h"



enum gl_error : GLenum
{
    INVALID_ENUM = GL_INVALID_ENUM,
    INVALID_VALUE = GL_INVALID_VALUE,
    INVALID_OPERATION = GL_INVALID_OPERATION,
    STACK_OVERFLOW = GL_STACK_OVERFLOW,
    STACK_UNDERFLOW = GL_STACK_UNDERFLOW,
    OUT_OF_MEMORY = GL_OUT_OF_MEMORY,
    INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION,
    CONTEXT_LOST = GL_CONTEXT_LOST,
    TABLE_TOO_LARGE = GL_TABLE_TOO_LARGE
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
     * */
    void fill(std::int32_t offset, const std::uint8_t* data, std::int32_t data_size);

    template<typename GLM_T>
    void fill(std::int32_t offset, const GLM_T& data)
    {

    }

public:
    /*
     * Mostly [Server -> Server]
     * */
    void clear();

public:
    /*
     * Pure [Server -> Server]
     * */
    void transfer_data(std::int32_t self_offset, int32_t self_size, gl_buffer_base* target_buffer, std::int32_t target_buffer_offset);

    /*
     * Pure [Server -> Server]
     * */
    void transfer_data_to(gl_buffer_base* target_buffer);

public:

    /*
     * map a block of immutable memory
     * then execute a handler you specified (can not do any modification)
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * */
    void execute_immutable_memory_handler(std::int32_t offset, std::int32_t size, const std::function<void(const std::uint8_t*, std::int32_t)>& handler)
    {
        if(offset < 0 || size < 0 || offset + size > _capacity) return;

        const auto* _mapped_memory_block = reinterpret_cast<const std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_READ_BIT))
        );

        if(_mapped_memory_block) handler(_mapped_memory_block, size);

        glUnmapNamedBuffer(_handle);
    }

    /*
     * map a block of mutable memory
     * then execute a handler you specified
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * */
    void execute_mutable_memory_handler(std::int32_t offset, std::int32_t size, const std::function<void(std::uint8_t*, std::int32_t)>& handler)
    {
        if(offset + size > _capacity) return;

        auto* _mapped_memory_block = reinterpret_cast<std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, size, GL_MAP_WRITE_BIT)
        );

        if(_mapped_memory_block)
        {
            handler(_mapped_memory_block, size);
            glFlushMappedNamedBufferRange(_handle, offset, size);
        } // make sure modification pushed to GPU

        glUnmapNamedBuffer(_handle);
    }

public:

    [[nodiscard]] std::int32_t get_buffer_size() const
    {
        std::int32_t _buffer_size = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_SIZE, &_buffer_size);
        return _buffer_size;
    }

    [[nodiscard]] std::int32_t get_access() const
    {
        std::int32_t _buffer_size = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_ACCESS, &_buffer_size);
        return _buffer_size;
    }

    [[nodiscard]] std::int32_t is_mapped() const
    {
        std::int32_t _buffer_size = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_MAPPED, &_buffer_size);
        return _buffer_size;
    }

    [[nodiscard]] std::int32_t get_usage() const
    {
        std::int32_t _buffer_size = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_USAGE, &_buffer_size);
        return _buffer_size;
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

    void _throw_errors(const std::string& func_name)
    {
        std::vector<gl_error> _errors;
        gl_error err;
        while((err = static_cast<gl_error>(glGetError())) != GL_NO_ERROR)
        {
            _errors.push_back(err);
        }
        if(_errors.size())
        {
            std::cout<<func_name<<": ["<<std::endl;
            for(auto _error : _errors)
            {
                std::cout<<"      ";
                switch (_error) {
                    case INVALID_ENUM:std::cout<<"INVALID_ENUM"<<std::endl;
                        break;
                    case INVALID_VALUE:std::cout<<"INVALID_VALUE"<<std::endl;
                        break;
                    case INVALID_OPERATION:std::cout<<"INVALID_OPERATION"<<std::endl;
                        break;
                    case STACK_OVERFLOW:std::cout<<"STACK_OVERFLOW"<<std::endl;
                        break;
                    case STACK_UNDERFLOW:std::cout<<"STACK_UNDERFLOW"<<std::endl;
                        break;
                    case OUT_OF_MEMORY:std::cout<<"OUT_OF_MEMORY"<<std::endl;
                        break;
                    case INVALID_FRAMEBUFFER_OPERATION:std::cout<<"INVALID_FRAMEBUFFER_OPERATION"<<std::endl;
                        break;
                    case CONTEXT_LOST:std::cout<<"CONTEXT_LOST"<<std::endl;
                        break;
                    case TABLE_TOO_LARGE:std::cout<<"TABLE_TOO_LARGE"<<std::endl;
                        break;
                }
            }
            std::cout<<"]"<<std::endl;
        }



    }

public:

    template<typename T>
    void print()
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


    void asynchronous(){}

    void synchronous(){}

    void synchronized(){}

};



#endif
