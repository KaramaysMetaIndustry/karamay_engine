//
// Created by Regicide Ji on 2021/7/1.
//

#ifndef KARAMAY_ENGINE_GRAPHICS_UNIT_GL_MUTABLE_BUFFER_H
#define KARAMAY_ENGINE_GRAPHICS_UNIT_GL_MUTABLE_BUFFER_H

#include "gl_buffer_base.h"

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


class gl_mutable_buffer : public gl_buffer_base {

public:

    gl_mutable_buffer(gl_mutable_buffer_usage usage, std::int32_t capacity)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, capacity, nullptr, static_cast<GLenum>(usage));
        _capacity = capacity;
        clear();
    }

public:

    void allocate(gl_mutable_buffer_usage usage, std::int32_t capacity)
    {

    }

    void reallocate(std::int32_t new_capacity, gl_mutable_buffer_usage usage)
    {
        if(!_check_capacity(new_capacity)) return;

        glNamedBufferData(_handle, new_capacity, nullptr, static_cast<GLenum>(usage));
        _capacity = new_capacity;

        clear();
    }

    void fill(std::int32_t offset, std::int32_t size, const std::uint8_t* data)
    {
        if(offset + size > _capacity) throw std::exception("out of bound");
        glNamedBufferSubData(_handle, offset, size, reinterpret_cast<const void*>(data));
    }

public:

    /*
     * map a block memory of the gpu memory, the block has read-only data
     * you can only do read-only operations
     * */
    void launch_immutable_task(std::int32_t offset, std::int32_t size, const std::function<void(const std::uint8_t*, std::int32_t)>& task)
    {
        if(offset + size > _capacity) return;

        const auto* _mapped_memory = reinterpret_cast<const std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_bit::MAP_READ_BIT))
                );

        if(_mapped_memory) task(_mapped_memory, size);

        glUnmapNamedBuffer(_handle);
    }

    /*
     * map a block memory of gpu memory, the block has read-write data
     *
     * */
    void launch_mutable_task(std::int32_t offset, std::int32_t size, const std::function<void(std::uint8_t*, std::int32_t)>& task)
    {
        if(offset + size > _capacity) return;

        auto* _mapped_memory = reinterpret_cast<std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, size, GL_MAP_WRITE_BIT)
                );

        if(_mapped_memory) { task(_mapped_memory, size); glFlushMappedNamedBufferRange(_handle, offset, size); }

        glUnmapNamedBuffer(_handle);
    }

    void asynchronous()
    {
    }

    void synchronous()
    {}

    void synchronized()
    {

    }

    gl_mutable_buffer& operator=(const gl_mutable_buffer& other)
    {
        if(other.get_capacity() == _capacity)
        {
            glCopyNamedBufferSubData(other.get_handle(), _handle, 0, 0, _capacity);
        }

        return *this;
    }

};


#endif
