//
// Created by Regicide Ji on 2021/7/1.
//

#ifndef KARAMAY_ENGINE_GRAPHICS_UNIT_GL_MUTABLE_BUFFER_H
#define KARAMAY_ENGINE_GRAPHICS_UNIT_GL_MUTABLE_BUFFER_H

#include "graphics/glo/gl_object.h"

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


class gl_mutable_buffer : public gl_object {

public:

    gl_mutable_buffer(gl_mutable_buffer_usage usage, std::int32_t capacity)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, capacity, nullptr, static_cast<GLenum>(usage));
    }

    void reallocate(std::int32_t new_capacity, gl_mutable_buffer_usage usage)
    {
        glNamedBufferData(_handle, new_capacity, nullptr, static_cast<GLenum>(usage));
    }

    void fill(std::int32_t offset, std::int32_t size, const std::uint8_t* data)
    {
        glNamedBufferSubData(_handle, offset, size, reinterpret_cast<const void*>(data));
    }


};


#endif //KARAMAY_ENGINE_GRAPHICS_UNIT_GL_MUTABLE_BUFFER_H
