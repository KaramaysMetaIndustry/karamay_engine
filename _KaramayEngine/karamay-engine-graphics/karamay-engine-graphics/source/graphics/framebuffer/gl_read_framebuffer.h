#pragma once
#include "graphics/glo/gl_object.h"

class gl_read_framebuffer final : public gl_object
{
public:
	static std::shared_ptr<gl_read_framebuffer> construct()
	{
		return std::make_shared<gl_read_framebuffer>();
	}

	~gl_read_framebuffer();

private:
	gl_read_framebuffer();


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

};

