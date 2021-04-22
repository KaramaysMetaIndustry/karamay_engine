#pragma once
#include "graphics/glo/gl_object.h"

class gl_renderbuffer final : public gl_object
{
public:
	void allocate(GLenum internal_format, GLsizei width, GLsizei height);

public:
	gl_renderbuffer();
	virtual ~gl_renderbuffer();
};

