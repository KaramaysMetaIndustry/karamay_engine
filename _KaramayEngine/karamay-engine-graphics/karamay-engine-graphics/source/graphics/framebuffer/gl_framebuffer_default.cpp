#include "gl_framebuffer_default.h"

void gl_framebuffer_default::read_depth(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
	glReadPixels(x, y, width, height, GL_DEPTH_COMPONENT, type, pixels);
}

void gl_framebuffer_default::read_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
	glReadPixels(x, y, width, height, GL_STENCIL_INDEX, type, pixels);
}
