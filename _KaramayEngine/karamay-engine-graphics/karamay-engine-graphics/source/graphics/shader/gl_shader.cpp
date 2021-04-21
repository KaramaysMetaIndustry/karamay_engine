#include "gl_shader.h"

void gl_shader::load_source(gl_shader_type type)
{
	_handle = glCreateShader(static_cast<GLenum>(type));
	char* source;
	int* lengths = {};
	glShaderSource(_handle, 1, &source, lengths);
}

void gl_shader::compile()
{
	glCompileShader(_handle);
}

gl_shader::gl_shader()
{
	
}

gl_shader::~gl_shader()
{
	glDeleteShader(_handle);
}
