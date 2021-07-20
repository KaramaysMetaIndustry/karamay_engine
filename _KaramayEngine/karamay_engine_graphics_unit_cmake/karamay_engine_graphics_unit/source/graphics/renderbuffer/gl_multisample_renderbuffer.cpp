#include "gl_multisample_renderbuffer.h"


void gl_multisample_renderbuffer::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, _handle);
}

void gl_multisample_renderbuffer::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}