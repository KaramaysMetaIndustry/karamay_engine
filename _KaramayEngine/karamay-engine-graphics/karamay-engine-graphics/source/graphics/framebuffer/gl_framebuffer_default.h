#pragma once
#include "graphics/glo/gl_object.h"

class gl_framebuffer_default final : public gl_object
{
public:
	static void read_color(GLenum mode, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
	{
		glReadBuffer(mode);
		glReadPixels(x, y, width, height, format, type, pixels);
	}

	static void read_depth(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
	static void read_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);


	static void set_draw_color_targets()
	{
		glDrawBuffer(GL_BACK_LEFT);
	}

	static void clear_all_color_buffers(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	static void clear_depth_buffer(double depth)
	{
		glClearDepth(depth);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	static void clear_stencil_buffer(int s)
	{
		glClearStencil(s);
		glClear(GL_STENCIL_BUFFER_BIT);
	}

	static void draw()
	{
		glDrawPixels()
	}
};

