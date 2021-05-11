#include "gl_program.h"

void gl_program::enable()
{
	glUseProgram(_handle);
}

void gl_program::disable()
{
	glUseProgram(0);
}

gl_program::gl_program()
{
	_handle = glCreateProgram();
}

gl_program::~gl_program()
{
	glDeleteProgram(_handle);
}
