#ifndef GLSL_SHADER_H
#define GLSL_SHADER_H

#include "interface_block/glsl_uniform_block.h"
#include "interface_block/glsl_shader_storage_block.h"
#include "opaque_t/glsl_atomic_counter.h"
#include "opaque_t/glsl_image.h"
#include "opaque_t/glsl_sampler.h"

class glsl_shader{
public:

};

class glsl_graphics_shader : public glsl_shader
{
};


class glsl_vertex_shader : public glsl_graphics_shader{

};

class glsl_tessellation_shader : public glsl_graphics_shader {

};


class glsl_geometry_shader : public glsl_graphics_shader{

};

class glsl_fragment_shader : public glsl_graphics_shader{

};

class glsl_compute_shader : public glsl_shader{

};

#endif
