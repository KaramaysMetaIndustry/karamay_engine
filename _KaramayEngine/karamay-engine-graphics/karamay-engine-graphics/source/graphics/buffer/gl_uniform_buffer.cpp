#include "gl_uniform_buffer.h"

void gl_uniform_buffer::associate(GLuint program_handle, const char* uniform_block_name)
{
	GLuint uniform_block_index = glGetUniformBlockIndex(program_handle, uniform_block_name);
	glUniformBlockBinding(program_handle, uniform_block_index, _handle);
}

gl_uniform_buffer::gl_uniform_buffer()
{
}

gl_uniform_buffer::~gl_uniform_buffer()
{
}
