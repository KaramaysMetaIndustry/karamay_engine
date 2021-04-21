#pragma once
#include "graphics/glo/gl_object.h"

class gl_multisample_renderbuffer final : public gl_object
{
public:
	void allocate(GLsizei samples_num, GLenum internal_format, GLsizei width, GLsizei height);  

public:
	gl_multisample_renderbuffer();
	virtual ~gl_multisample_renderbuffer();
};

