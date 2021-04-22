#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_buffer : public gl_texture_base
{
public:
	void associate_buffer(GLenum internal_format, GLuint buffer_handle);
	void associate_sub_buffer(GLenum internal_format, GLuint buffer_handle, GLintptr offset, GLsizeiptr size);

	void bind(unsigned int unit);
	void unbind();

public:
	gl_texture_buffer();
	virtual ~gl_texture_buffer();

};

