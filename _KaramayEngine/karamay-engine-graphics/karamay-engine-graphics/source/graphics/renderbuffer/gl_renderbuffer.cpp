#include "gl_renderbuffer.h"

void gl_renderbuffer::allocate(gl_renderbuffer_enum::internal_format internal_format, unsigned int width, unsigned int height)
{
	if (width > GL_MAX_RENDERBUFFER_SIZE || height > GL_MAX_RENDERBUFFER_SIZE) return;
	glNamedRenderbufferStorage(_handle, static_cast<GLenum>(internal_format), static_cast<GLsizei>(width), static_cast<GLsizei>(height));

	_width = width;
	_height = height;
	_internal_format = internal_format;
}

void gl_renderbuffer::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, _handle);
}

void gl_renderbuffer::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

