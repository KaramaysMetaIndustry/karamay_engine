#ifndef GLSL_SHADER_H
#define GLSL_SHADER_H

#include "graphics/glsl/interface_block/glsl_in_block.h"
#include "graphics/glsl/interface_block/glsl_out_block.h"
#include "graphics/glsl/interface_block/glsl_uniform_block.h"
#include "graphics/glsl/interface_block/glsl_shader_storage_block.h"
#include "graphics/glsl/opaque_t/glsl_atomic_counter.h"
#include "graphics/glsl/opaque_t/glsl_image.h"
#include "graphics/glsl/opaque_t/glsl_sampler.h"

class glsl_shader{
public:
    glsl_shader() = default;

    std::vector<std::shared_ptr<glsl_uniform_block_t>> uniform_blocks;
    std::vector<std::shared_ptr<glsl_shader_storage_block_t>> shader_storage_blocks;
    std::vector<std::shared_ptr<glsl_atomic_counter_t>> atomic_counters;
    std::vector<std::shared_ptr<glsl_sampler_t>> samplers;
    std::vector<std::shared_ptr<glsl_image_t>> images;
};

class glsl_graphics_shader : public glsl_shader
{
    std::shared_ptr<glsl_in_block_t> input;
    std::shared_ptr<glsl_out_block_t> output;
};


class glsl_vertex_shader : public glsl_graphics_shader{

};

class glsl_tessellation_control_shader : public glsl_graphics_shader{

};

class glsl_tessellation_evaluation_shader : public glsl_graphics_shader{

};

class glsl_geometry_shader : public glsl_graphics_shader{

};

class glsl_fragment_shader : public glsl_graphics_shader{

};


class glsl_compute_shader : public glsl_shader{

};

#endif
