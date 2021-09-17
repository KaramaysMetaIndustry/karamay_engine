#ifndef GL_FRAGMENT_SHADER_H
#define GL_FRAGMENT_SHADER_H
#include "gl_shader.h"

struct gl_fragment_shader_descriptor
{
	std::shared_ptr<gl_shader_parameters> parameters;
};

class gl_fragment_shader : public gl_shader
{

public:

	gl_fragment_shader() = delete;
	gl_fragment_shader(const gl_fragment_shader_descriptor descriptor)
	{}


};

#endif