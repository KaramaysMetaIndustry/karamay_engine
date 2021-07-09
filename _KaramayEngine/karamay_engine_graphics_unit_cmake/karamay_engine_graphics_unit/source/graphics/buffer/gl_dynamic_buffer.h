//
// Created by Regicide Ji on 2021/7/1.
//

#ifndef GL_DYNAMIC_BUFFER_H
#define GL_DYNAMIC_BUFFER_H

#include "gl_buffer.h"
//DRAW: The user will be writing data to the buffer, but the user will not read it.
//READ: The user will not be writing data, but the user will be reading it back.
//COPY: The user will be neither writing nor reading the data.

//STATIC: The user will set the data once.
//DYNAMIC: The user will set the data occasionally.
//STREAM: The user will be changing the data after every use. Or almost every use.

enum class gl_dynamic_buffer_usage : GLenum
{
    STATIC_DRAW = GL_STATIC_DRAW,
    STATIC_READ = GL_STATIC_READ,
    STATIC_COPY = GL_STATIC_COPY,

    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    DYNAMIC_READ = GL_DYNAMIC_READ,
    DYNAMIC_COPY = GL_DYNAMIC_COPY,

    STREAM_DRAW = GL_STREAM_DRAW,
    STREAM_READ = GL_STREAM_READ,
    STREAM_COPY = GL_STREAM_COPY
};

class gl_dynamic_buffer final : public gl_buffer
{

};

#endif
