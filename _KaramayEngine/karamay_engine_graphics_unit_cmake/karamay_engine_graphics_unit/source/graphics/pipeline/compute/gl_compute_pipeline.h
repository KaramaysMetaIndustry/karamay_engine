#ifndef _GL_COMPUTE_PIPELINE_H_
#define _GL_COMPUTE_PIPELINE_H_

#include "graphics/glsl/glsl_class.h"
#include "graphics/glsl/glsl_shader.h"
#include "graphics/resource/program/gl_program.h"

struct glsl_compute_pipeline_parameters{
    std::vector<std::shared_ptr<glsl_sampler_t>> samplers;
    std::vector<std::shared_ptr<glsl_image_t>> images;
    std::vector<std::shared_ptr<glsl_atomic_counter_t>> atomic_counters;
    std::vector<std::shared_ptr<glsl_uniform_block_t>> uniform_blocks;
    std::vector<std::shared_ptr<glsl_shader_storage_block_t>> shader_storage_blocks;
};

struct gl_compute_pipeline_descriptor{
    std::shared_ptr<glsl_compute_pipeline_parameters> parameters;
    std::shared_ptr<glsl_compute_shader> compute_shader;
};

class gl_compute_pipeline final{
public:

    gl_compute_pipeline() = delete;
	explicit gl_compute_pipeline(const gl_compute_pipeline_descriptor& descriptor)
    {
        _program = std::make_unique<gl_program>();
        if(_program)
        {
            //_program->construct()
        }
    }
	gl_compute_pipeline(const gl_compute_pipeline&) = delete;
	gl_compute_pipeline& operator=(const gl_compute_pipeline&) = delete;

	~gl_compute_pipeline() = default;

public:

    void enable() noexcept
    {
        if(_program)
        {
            // enable the program, otherwise all resource binding will not work
            _program->enable();
            // bind resource
        }
    }

    void disable() noexcept
    {
        if(_program) return;
        _program->disable();
    }

	void dispatch(std::uint32_t group_size_x, std::uint32_t group_size_y, std::uint32_t group_size_z) noexcept
	{
	    if(!_program) return;

        glDispatchCompute(group_size_x, group_size_y, group_size_z);
	}

private:

    std::unique_ptr<gl_program> _program;

};

#endif