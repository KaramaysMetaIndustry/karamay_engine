#include "gl_renderbuffer.h"

gl_renderbuffer::gl_renderbuffer()
{
	glCreateRenderbuffers(1, &_handle);
}

gl_renderbuffer::~gl_renderbuffer()
{
	glDeleteRenderbuffers(1, &_handle);
}
