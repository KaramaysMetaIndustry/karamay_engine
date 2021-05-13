#pragma once
#include "graphics/glo/gl_object.h"

namespace gl_multisample_renderbuffer_enum
{
	enum class internal_format : GLenum
	{
		NONE
	};
}

class gl_multisample_renderbuffer final : public gl_object
{
public:
	
	gl_multisample_renderbuffer()
	{
		glCreateRenderbuffers(1, &_handle);
	}

	virtual ~gl_multisample_renderbuffer()
	{
		glDeleteRenderbuffers(1, &_handle);
	}

private:

	

	unsigned int _samples_num;

	unsigned int _width, _height;

	gl_multisample_renderbuffer_enum::internal_format _internal_format;

public:
	
	void allocate(unsigned int samples_num, gl_multisample_renderbuffer_enum::internal_format internal_format, unsigned int width, unsigned int height);  

	void bind();

	void unbind();

};

