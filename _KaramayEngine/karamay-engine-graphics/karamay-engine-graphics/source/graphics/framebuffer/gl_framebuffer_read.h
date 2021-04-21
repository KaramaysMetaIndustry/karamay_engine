#pragma once
#include "graphics/glo/gl_object.h"

class gl_framebuffer_read final : public gl_object
{
public:

	void attach_color_buffer();
	void attach_depth_buffer();
	void attach_stencil_buffer(); 

public:
	void read_color(unsigned int attachment_index, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
	void read_depth(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);
	void read_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);
	void read_depth_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);

public:
	void bind();
	void unbind();

public:
	gl_framebuffer_read();
	virtual ~gl_framebuffer_read();
};

