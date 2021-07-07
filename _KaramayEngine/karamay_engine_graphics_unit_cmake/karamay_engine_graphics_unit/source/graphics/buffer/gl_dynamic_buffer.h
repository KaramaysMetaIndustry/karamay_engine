//
// Created by Regicide Ji on 2021/7/1.
//

#ifndef GL_DYNAMIC_BUFFER_H
#define GL_DYNAMIC_BUFFER_H

#include "gl_buffer_base.h"

enum class gl_dynamic_buffer_usage : GLenum
{
    STREAM_DRAW = GL_STREAM_DRAW, // draw
    STREAM_READ = GL_STREAM_READ, // read
    STREAM_COPY = GL_STREAM_COPY, // copy

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

    gl_dynamic_buffer(std::int32_t capacity, gl_dynamic_buffer_usage usage) :
            gl_buffer_base(capacity),
            _usage(usage)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, capacity, nullptr, static_cast<GLenum>(usage));
        _capacity = capacity;

        rapidly_fill();
    }

public:

    /*
     * specify a new capacity and a new usage
     * */
    void reallocate(std::int32_t new_capacity, gl_dynamic_buffer_usage new_usage);

    /*
     * specify a new capacity and keep the old usage
     * */
    void reallocate(std::int32_t new_capacity);

private:

    gl_dynamic_buffer_usage _usage;

};

#endif
