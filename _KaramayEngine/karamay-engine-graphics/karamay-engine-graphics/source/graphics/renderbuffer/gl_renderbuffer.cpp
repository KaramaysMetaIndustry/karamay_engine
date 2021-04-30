#include "gl_renderbuffer.h"

void gl_renderbuffer::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, _handle);
}

void gl_renderbuffer::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, _handle);
}

gl_renderbuffer::gl_renderbuffer()
{
	glCreateRenderbuffers(1, &_handle);
}

gl_renderbuffer::~gl_renderbuffer()
{
	glDeleteRenderbuffers(1, &_handle);
}
