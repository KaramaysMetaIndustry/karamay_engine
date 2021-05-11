#pragma once
#include "material/gl_material.h"
#include "graphics/vertex_array/gl_vertex_array.h"

struct gl_mesh
{
	std::shared_ptr<gl_vertex_array> vertex_array;

	std::shared_ptr<gl_material> material;
};

