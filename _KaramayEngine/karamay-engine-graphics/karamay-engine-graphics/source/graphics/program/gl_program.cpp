#include "gl_program.h"


void gl_program::link(bool is_separable)
{
	if(is_separable)
		glProgramParameteri(_handle, GL_PROGRAM_SEPARABLE, GL_TRUE);

	/*glBindAttribLocation(_handle, 0, "Position");
	glBindFragDataLocation(_handle, 0, "FragColor");*/

	glLinkProgram(_handle);
}

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
