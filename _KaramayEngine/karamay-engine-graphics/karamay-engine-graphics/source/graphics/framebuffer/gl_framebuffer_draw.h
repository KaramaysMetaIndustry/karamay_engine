#pragma once
#include "graphics/glo/gl_object.h"

class gl_framebuffer_draw final : public gl_object
{
public:
	void bind();

	void unbind();


public:
	gl_framebuffer_draw();
	virtual ~gl_framebuffer_draw();

};

