#include "gl_shader.h"

gl_shader::gl_shader()
{
}

gl_shader::~gl_shader()
{
	glDeleteShader(_handle);
}
