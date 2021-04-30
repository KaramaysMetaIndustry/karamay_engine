#include "gl_draw_framebuffer.h"

void gl_draw_framebuffer::bind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _handle);
}

void gl_draw_framebuffer::unbind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

gl_draw_framebuffer::gl_draw_framebuffer()
{
}

gl_draw_framebuffer::~gl_draw_framebuffer()
{
}
