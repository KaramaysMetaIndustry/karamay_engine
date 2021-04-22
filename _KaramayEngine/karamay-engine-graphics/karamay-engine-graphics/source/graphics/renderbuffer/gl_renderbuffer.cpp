#include "gl_renderbuffer.h"

void gl_renderbuffer::allocate(GLenum internal_format, GLsizei width, GLsizei height)
{
	glNamedRenderbufferStorage(_handle, internal_format, width, height);
}

gl_renderbuffer::gl_renderbuffer()
{
	glCreateRenderbuffers(1, &_handle);
}

gl_renderbuffer::~gl_renderbuffer()
{
	glDeleteRenderbuffers(1, &_handle);
}
