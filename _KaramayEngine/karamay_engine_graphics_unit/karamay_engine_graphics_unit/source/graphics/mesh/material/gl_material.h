#pragma once

#include "graphics/texture/gl_texture.h"

struct gl_material
{
	std::unordered_map<std::string, std::shared_ptr<gl_texture_2d>> texture_2ds_map;

	std::unordered_map<std::string, std::float_t> float_uniforms_map;

	std::unordered_map<std::string, glm::vec3> vec3s_map;

};

