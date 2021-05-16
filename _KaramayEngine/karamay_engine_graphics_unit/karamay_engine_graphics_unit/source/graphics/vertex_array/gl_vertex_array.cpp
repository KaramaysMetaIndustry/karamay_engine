#include "gl_vertex_array.h"

gl_vertex_array::gl_vertex_array()
{
	glCreateVertexArrays(1, &_handle);
}

gl_vertex_array::~gl_vertex_array()
{
	glDeleteVertexArrays(1, &_handle);
}

void gl_vertex_array::enable_vertex_attributes()
{
	for (const auto index : indices)
	{
		glEnableVertexAttribArray(static_cast<GLuint>(index));
	}
}

void gl_vertex_array::disable_vertex_attributes()
{
	for (const auto index : indices)
	{
		glDisableVertexAttribArray(static_cast<GLuint>(index));
	}
}
