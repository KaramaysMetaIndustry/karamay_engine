#include "gl_framebuffer.h"
#include "graphics/texture/gl_texture.h"
#include "graphics/renderbuffer/gl_renderbuffer.h"

void gl_framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _handle);
}

void gl_framebuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

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

gl_framebuffer::gl_framebuffer()
{
	glCreateFramebuffers(1, &_handle);
}

gl_framebuffer::~gl_framebuffer()
{
	glDeleteFramebuffers(1, &_handle);
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
