#include "gl_framebuffer.h"
#include "graphics/resource/texture/gl_texture.h"
#include "graphics/resource/renderbuffer/gl_renderbuffer.h"

void gl_framebuffer::draw_color(int attachment_index, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachment_index);
	glDrawPixels(width, height, format, type, pixels);
}

void gl_framebuffer::draw_depth(GLsizei width, GLsizei height, GLenum type, const void* pixels)
{
	glDrawPixels(width, height, GL_DEPTH_COMPONENT, type, pixels);
}

void gl_framebuffer::draw_stencil(GLsizei width, GLsizei height, GLenum type, const void* pixels)
{
	glDrawPixels(width, height, GL_STENCIL_INDEX, type, pixels);
}

void gl_framebuffer::draw_depth_stencil(GLsizei width, GLsizei height, GLenum type, const void* pixels)
{
	glDrawPixels(width, height, GL_DEPTH_STENCIL, type, pixels);
}


void gl_framebuffer::read_color(int attachment_index, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachment_index);
	glClampColor(GL_CLAMP_READ_COLOR, GL_TRUE); // GL_FALSE, GL_FIXED_ONLY
	glReadPixels(x, y, width, height, format, type, pixels);
}

void gl_framebuffer::read_depth(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels)
{
	glReadPixels(x, y, width, height, GL_DEPTH_COMPONENT, type, pixels);
}

void gl_framebuffer::read_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels)
{
	glReadPixels(x, y, width, height, GL_STENCIL_INDEX, type, pixels);
}

void gl_framebuffer::read_depth_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels)
{
	glReadPixels(x, y, width, height, GL_DEPTH_STENCIL, type, pixels);
}
