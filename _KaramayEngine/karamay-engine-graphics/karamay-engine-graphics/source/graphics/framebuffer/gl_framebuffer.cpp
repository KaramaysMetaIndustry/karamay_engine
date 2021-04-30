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

void gl_framebuffer::attach_color_buffer_1d(unsigned int attachment_index, const std::shared_ptr<gl_texture_1d> texture_1d, unsigned int mipmap_index)
{
	glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment_index, GL_TEXTURE_1D, texture_1d->get_handle(), mipmap_index);
}

void gl_framebuffer::attach_depth_buffer_1d(const std::shared_ptr<gl_texture_1d> texture_1d, unsigned int mipmap_index)
{
	glFramebufferTexture1D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_1D, texture_1d->get_handle(), mipmap_index);
}

void gl_framebuffer::attach_stencil_buffer_1d(const std::shared_ptr<gl_texture_1d> texture_1d, unsigned int mipmap_index)
{
	glFramebufferTexture1D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_1D, texture_1d->get_handle(), mipmap_index);
}

void gl_framebuffer::attach_depth_stencil_buffer_1d(const std::shared_ptr<gl_texture_1d> texture_1d, unsigned int mipmap_index)
{
	glFramebufferTexture1D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_1D, texture_1d->get_handle(), mipmap_index);
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

void gl_framebuffer::attach_color_buffer(unsigned int attachment_index, gl_renderbuffer renderbuffer)
{
	glNamedFramebufferRenderbuffer(_handle, GL_COLOR_ATTACHMENT0 + attachment_index, GL_RENDERBUFFER, renderbuffer.get_handle());
}

void gl_framebuffer::attach_depth_buffer(gl_renderbuffer renderbuffer)
{
	glNamedFramebufferRenderbuffer(_handle, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.get_handle());
}

void gl_framebuffer::attach_stencil_buffer(gl_renderbuffer renderbuffer)
{
	glNamedFramebufferRenderbuffer(_handle, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.get_handle());
}

void gl_framebuffer::attach_depth_stencil_buffer(gl_renderbuffer renderbuffer)
{
	glNamedFramebufferRenderbuffer(_handle, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.get_handle());
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
