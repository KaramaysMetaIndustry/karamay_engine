#ifndef GL_MATERIAL_H
#define GL_MATERIAL_H

#include "graphics/resource/texture/gl_texture.h"

class gl_material
{
	gl_texture_2d* base_color_tex;

	glm::vec4 base_color_factor;

	gl_texture_2d* metallic_roughness_tex;

	float metallic_factor; // 1.0f

	float roughness_factor; // 0.0f

	gl_texture_2d* normal_tex;

	gl_texture_2d* occlusion_tex;

	gl_texture_2d* emissive_tex;

	glm::vec3 emissive_factor;

};


#endif
