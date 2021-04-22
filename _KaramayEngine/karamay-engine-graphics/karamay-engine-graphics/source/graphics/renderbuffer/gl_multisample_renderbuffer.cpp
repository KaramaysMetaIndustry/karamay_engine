#include "gl_multisample_renderbuffer.h"

void gl_multisample_renderbuffer::allocate(GLsizei samples_num, GLenum internal_format, GLsizei width, GLsizei height)
{
	glNamedRenderbufferStorageMultisample(_handle, samples_num, internal_format, width, height);
}

gl_multisample_renderbuffer::gl_multisample_renderbuffer()
{
	glCreateRenderbuffers(1, &_handle);
}

gl_multisample_renderbuffer::~gl_multisample_renderbuffer()
{
	glDeleteRenderbuffers(1, &_handle);
}
