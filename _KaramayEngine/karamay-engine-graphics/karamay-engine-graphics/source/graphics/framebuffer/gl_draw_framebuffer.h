#pragma once
#include "graphics/glo/gl_object.h"

class gl_draw_framebuffer final : public gl_object
{
public:
	static std::shared_ptr<gl_draw_framebuffer> construct()
	{
		return std::make_shared<gl_draw_framebuffer>();
	}

	~gl_draw_framebuffer();

private:
	gl_draw_framebuffer();


public:
	void bind();

	void unbind();

};

