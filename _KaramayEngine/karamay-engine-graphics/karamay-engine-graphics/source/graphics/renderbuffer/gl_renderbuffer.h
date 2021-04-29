#pragma once
#include "graphics/glo/gl_object.h"

class gl_renderbuffer final : public gl_object
{
public:
	std::shared_ptr<gl_renderbuffer> construct()
	{
		return std::make_shared<gl_renderbuffer>();
	}

	~gl_renderbuffer();

private:

	gl_renderbuffer();

public:
	void allocate(GLenum internal_format, GLsizei width, GLsizei height)
	{
		glNamedRenderbufferStorage(_handle, internal_format, width, height);
	}

public:
	gl_renderbuffer();
	virtual ~gl_renderbuffer();
};

