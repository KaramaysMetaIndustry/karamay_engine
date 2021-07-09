#ifndef H_GL_STATIC_BUFFER
#define H_GL_STATIC_BUFFER

#include "gl_buffer.h"

/*
 * The following operations are always valid on immutable buffers regardless of the flags field:
 * (0) Writing to the buffer with any rendering pipeline process. These include Transform Feedback, Image Load Store, Atomic Counter, and Shader Storage Buffer Object. Basically, anything that is part of the rendering pipeline that can write to a buffer will always work.
 * (1) Clearing the buffer. Because this only transfers a few bytes of data, it is not considered "client-side" modification.
 * (2) Copying the buffer. This copies from one buffer to another, so it all happens "server-side".
 * (3) Invalidating the buffer. This only wipes out the contents of the buffer, so it is considered "server-side".
 * (4) Asynchronous pixel transfers into the buffer. This sets the data in a buffer, but only through pure-OpenGL mechanisms.
 * (5) Using glGetBufferSubData to read a part of the buffer back to the CPU. This is not a "server-side" operation, but it's always available regardless
 * */
class gl_static_buffer final : public gl_buffer
{
};


#endif
