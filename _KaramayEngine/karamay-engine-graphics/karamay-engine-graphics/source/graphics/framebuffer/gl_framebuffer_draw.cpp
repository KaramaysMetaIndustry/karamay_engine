#include "gl_framebuffer_draw.h"

void gl_framebuffer_draw::bind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _handle);
}

void gl_framebuffer_draw::unbind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

gl_framebuffer_draw::gl_framebuffer_draw()
{
}

gl_framebuffer_draw::~gl_framebuffer_draw()
{
}
