#include "gl_vertex_array.h"

gl_vertex_array::gl_vertex_array()
{
	glCreateVertexArrays(1, &_handle);
}

gl_vertex_array::~gl_vertex_array()
{
	glDeleteVertexArrays(1, &_handle);
}
