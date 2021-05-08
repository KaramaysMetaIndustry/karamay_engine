#pragma once
#include "graphics/texture/base/gl_texture_base.h"
#include "graphics/buffer/gl_buffer.h"

class gl_texture_buffer : public gl_texture_base
{
public:
	
	gl_texture_buffer();
	
	virtual ~gl_texture_buffer();

public:
	
	void associate_buffer(GLenum internal_format, std::shared_ptr<gl_buffer> buffer)
	{
		if (buffer)
		{
			glTexBuffer(GL_TEXTURE_BUFFER, internal_format, buffer->get_handle());
		}
	}
	
	void associate_sub_buffer(GLenum internal_format, GLuint buffer_handle, GLintptr offset, GLsizeiptr size);

	void bind(std::uint32_t unit);
	
	void unbind();

};

