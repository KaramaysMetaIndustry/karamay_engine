#pragma once
#include "graphics/glo/gl_object.h"

enum class gl_shader_type : GLenum
{

};

class gl_shader final : public gl_object
{
public:
	void load_source(gl_shader_type  type);

	void compile();


public:
	gl_shader();

	virtual ~gl_shader();
};

