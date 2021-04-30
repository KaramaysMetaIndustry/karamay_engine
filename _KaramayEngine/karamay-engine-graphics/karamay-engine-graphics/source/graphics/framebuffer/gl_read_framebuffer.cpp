#include "gl_framebuffer_read.h"
#include "gl_read_framebuffer.h"

void gl_framebuffer_read::read_color(unsigned int attachment_index, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
	// specify color attachment
	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachment_index);
	// do not clamp the color
	glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE); // GL_FALSE, GL_FIXED_ONLY
	// read pixels
	glReadPixels(x, y, width, height, format, type, pixels);
}

void gl_framebuffer_read::read_depth(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels)
{
	glReadPixels(x, y, width, height, GL_DEPTH_COMPONENT, type, pixels);
}

void gl_framebuffer_read::read_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels)
{
	glReadPixels(x, y, width, height, GL_STENCIL_INDEX, type, pixels);
}

void gl_framebuffer_read::read_depth_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels)
{
	glReadPixels(x, y, width, height, GL_DEPTH_STENCIL, type, pixels);
}

void gl_framebuffer_read::bind()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _handle);
}

void gl_framebuffer_read::unbind()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

gl_framebuffer_read::gl_framebuffer_read()
{
}

gl_framebuffer_read::~gl_framebuffer_read()
{
}

gl_read_framebuffer::~gl_read_framebuffer()
{
}
