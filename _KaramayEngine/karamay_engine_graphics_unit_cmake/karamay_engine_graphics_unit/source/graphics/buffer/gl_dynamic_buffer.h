//
// Created by Regicide Ji on 2021/7/1.
//

#ifndef KARAMAY_ENGINE_GRAPHICS_UNIT_GL_DYNAMIC_BUFFER_H
#define KARAMAY_ENGINE_GRAPHICS_UNIT_GL_DYNAMIC_BUFFER_H

#include "gl_buffer_base.h"

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

enum class gl_mutable_buffer_usage : GLenum
{
   STREAM_DRAW = GL_STREAM_DRAW,
   STREAM_READ = GL_STREAM_READ,
   STREAM_COPY = GL_STREAM_COPY,
   STATIC_DRAW = GL_STATIC_DRAW,
   STATIC_READ = GL_STATIC_READ,
   STATIC_COPY = GL_STATIC_COPY,
   DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
   DYNAMIC_READ = GL_DYNAMIC_READ,
   DYNAMIC_COPY = GL_DYNAMIC_COPY
};

enum class gl_buffer_map_bit : GLenum
{
    MAP_READ_BIT = GL_MAP_READ_BIT,
    MAP_WRITE_BIT = GL_MAP_WRITE_BIT
};


class gl_dynamic_buffer : public gl_buffer_base {

public:

    gl_dynamic_buffer(gl_mutable_buffer_usage usage, std::int32_t capacity)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, capacity, nullptr, static_cast<GLenum>(usage));
        _capacity = capacity;
        clear();
    }

public:

    /*
     * if new_capacity > max_capacity
     * */
    void reallocate(std::int32_t new_capacity, gl_mutable_buffer_usage usage)
    {
        if(!_check_capacity(new_capacity)) return;

        glNamedBufferData(_handle, new_capacity, nullptr, static_cast<GLenum>(usage));
        _capacity = new_capacity;

        clear();
    }

public:

    /*
     *  fill bytes data
     *  @ offset
     *  @ data
     *  @ data_size
     * */
    void fill(std::int32_t offset, const std::uint8_t* data, std::int32_t data_size) noexcept
    {
        if(!data || offset < 0 || data_size < 0 || (offset + data_size > _capacity)) return;

        glNamedBufferSubData(_handle, offset, data_size, reinterpret_cast<const void*>(data));
        // ** data_size > data real size, it will not case exception
        // because glNamedBufferSubData operation is read-only to data
    }

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
                glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_bit::MAP_READ_BIT))
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


    void asynchronous()
    {
    }

    void synchronous()
    {}

    void synchronized()
    {

    }

    gl_dynamic_buffer& operator=(const gl_dynamic_buffer& other)
    {
        if(other.get_capacity() == _capacity)
        {
            glCopyNamedBufferSubData(other.get_handle(), _handle, 0, 0, _capacity);
        }

        return *this;
    }

    void _check_errors(const std::string& func_name)
    {
        gl_error err;
        while((err = static_cast<gl_error>(glGetError())) != GL_NO_ERROR)
        {
            // Process/log the error.
            switch (err) {

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
    }

};


#endif
