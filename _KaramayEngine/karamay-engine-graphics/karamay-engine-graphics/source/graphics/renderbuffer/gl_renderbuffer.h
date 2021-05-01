#pragma once
#include "graphics/glo/gl_object.h"

namespace gl_renderbuffer_enum
{
	enum class internal_format : GLenum
	{
		NONE
	};

};


class gl_renderbuffer final : public gl_object
{
public:

	static std::shared_ptr<gl_renderbuffer> construct()
	{
		return std::make_shared<gl_renderbuffer>();
	}

	virtual ~gl_renderbuffer()
	{
		glDeleteRenderbuffers(1, &_handle);
	}

private:
	
	gl_renderbuffer() :
		_width(0), _height(0),
		_internal_format(gl_renderbuffer_enum::internal_format::NONE)
	{
		glCreateRenderbuffers(1, &_handle);
	}
	
	unsigned int _width, _height;

	gl_renderbuffer_enum::internal_format _internal_format;

public:

	void allocate(gl_renderbuffer_enum::internal_format internal_format, unsigned int width, unsigned int height);

	void bind();

	void unbind();

};

