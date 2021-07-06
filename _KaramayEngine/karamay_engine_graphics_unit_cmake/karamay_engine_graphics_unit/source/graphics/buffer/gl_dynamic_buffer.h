//
// Created by Regicide Ji on 2021/7/1.
//

#ifndef GL_DYNAMIC_BUFFER_H
#define GL_DYNAMIC_BUFFER_H

#include "gl_buffer_base.h"

enum class gl_dynamic_buffer_usage : GLenum
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

class gl_dynamic_buffer final : public gl_buffer_base
{
public:

    gl_dynamic_buffer(gl_dynamic_buffer_usage usage, std::int32_t capacity) :
            gl_buffer_base(capacity),
            _usage(usage)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, capacity, nullptr, static_cast<GLenum>(usage));
        _capacity = capacity;
        clear();
    }

    gl_dynamic_buffer& operator=(const gl_dynamic_buffer& other)
    {
        if(other.get_capacity() == _capacity)
        {
            glCopyNamedBufferSubData(other.get_handle(), _handle, 0, 0, _capacity);
        }

        return *this;
    }

private:

    gl_dynamic_buffer_usage _usage;

public:

    void reallocate(std::int32_t new_capacity, gl_dynamic_buffer_usage usage)
    {
        if(!_check_capacity(new_capacity)) return;

        glNamedBufferData(_handle, new_capacity, nullptr, static_cast<GLenum>(usage));
        _throw_errors("glNamedBufferData: ");
        _capacity = new_capacity;
        _usage = usage;
        clear();
    }

};

#endif
