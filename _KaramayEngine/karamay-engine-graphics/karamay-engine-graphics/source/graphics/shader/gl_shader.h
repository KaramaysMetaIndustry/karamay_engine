#pragma once
#include "graphics/glo/gl_object.h"

enum class gl_shader_type : GLenum
{

};

class gl_shader final : public gl_object
{
public:
	static std::shared_ptr<gl_shader> construct()
	{
		return std::make_shared<gl_shader>();
	}

	~gl_shader()
	{}

private:
	gl_shader()
	{}

public:
	void load_source(gl_shader_type  type);

	void compile();
};

