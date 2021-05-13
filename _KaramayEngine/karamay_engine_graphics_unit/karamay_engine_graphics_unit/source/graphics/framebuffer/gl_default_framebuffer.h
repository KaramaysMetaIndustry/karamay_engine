#pragma once
#include "graphics/glo/gl_object.h"

namespace gl_default_framebuffer_enum
{
	enum class draw_target : GLenum
	{

	};
}

class gl_default_framebuffer
{
private:

	gl_default_framebuffer(){}

	virtual ~gl_default_framebuffer() {}

public:

	void set_draw_color_targets()
	{
		glDrawBuffer(GL_BACK_LEFT);
	}


	void read_color(GLenum mode, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
	{
		glReadBuffer(mode);
		glReadPixels(x, y, width, height, format, type, pixels);
	}

	void read_depth(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
	
	void read_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);


	

	void clear_all_color_buffers(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void clear_depth_buffer(double depth)
	{
		glClearDepth(depth);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void clear_stencil_buffer(int s)
	{
		glClearStencil(s);
		glClear(GL_STENCIL_BUFFER_BIT);
	}


public:

	void bind() 
	{ 
		glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	}

	void unbind() 
	{}

};

