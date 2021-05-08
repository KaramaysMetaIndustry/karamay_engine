#include "gl_renderbuffer.h"

gl_renderbuffer::~gl_renderbuffer()
{
	glDeleteRenderbuffers(1, &_handle);
}

void gl_renderbuffer::allocate(gl_renderbuffer_enum::internal_format internal_format, std::uint32_t width, std::uint32_t height)
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

