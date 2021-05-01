#include "gl_multisample_renderbuffer.h"

void gl_multisample_renderbuffer::allocate(unsigned int samples_num, gl_multisample_renderbuffer_enum::internal_format internal_format, unsigned int width, unsigned int height)
{
	if (samples_num > GL_MAX_SAMPLES || width > GL_MAX_RENDERBUFFER_SIZE || height > GL_MAX_RENDERBUFFER_SIZE) return;

	glNamedRenderbufferStorageMultisample(_handle, samples_num, static_cast<GLenum>(internal_format), width, height);

	_samples_num = samples_num;
	_width = width;
	_height = height;
	_internal_format = internal_format;
}

void gl_multisample_renderbuffer::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, _handle);
}

void gl_multisample_renderbuffer::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

gl_multisample_renderbuffer::gl_multisample_renderbuffer()
{
	glCreateRenderbuffers(1, &_handle);
}

gl_multisample_renderbuffer::~gl_multisample_renderbuffer()
{
	glDeleteRenderbuffers(1, &_handle);
}
