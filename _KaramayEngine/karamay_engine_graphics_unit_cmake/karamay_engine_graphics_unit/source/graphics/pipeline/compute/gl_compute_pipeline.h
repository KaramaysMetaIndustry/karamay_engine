#ifndef _GL_COMPUTE_PIPELINE_H_
#define _GL_COMPUTE_PIPELINE_H_

#include "graphics/glsl/glsl_program.h"
#include "graphics/resource/program/gl_program.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_uniform_buffer.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_shader_storage_buffer.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_atomic_counter_buffer.h"

struct gl_compute_pipeline_descriptor{
    // pipeline name
    std::string name;
    // renderer dir
    std::string owner_renderer_dir;
    // program body
    std::shared_ptr<glsl_compute_pipeline_program> program;
};

/*
* 
*/
class gl_compute_pipeline final{
public:
    gl_compute_pipeline() = delete;
	explicit gl_compute_pipeline(const gl_compute_pipeline_descriptor& descriptor)
    {
        _construct(descriptor);
    }
	gl_compute_pipeline(const gl_compute_pipeline&) = delete;
	gl_compute_pipeline& operator=(const gl_compute_pipeline&) = delete;

	~gl_compute_pipeline() = default;

public:

    void enable() noexcept
    {
        if (!_program) return;
        _program->enable();
        _bind_resources();
    }

    void disable() noexcept
    {
        if(_program) return;
        _program->disable();
        _unbind_resources();
    }

public:

	void dispatch(std::uint32_t group_size_x, std::uint32_t group_size_y, std::uint32_t group_size_z) noexcept
	{
	    if(!_program) return;

        glDispatchCompute(group_size_x, group_size_y, group_size_z);
	}

private:

    std::unique_ptr<gl_program> _program;

    std::unique_ptr<gl_uniform_buffer> _uniform_buffer;

    std::unique_ptr<gl_shader_storage_buffer> _shader_storage_buffer;

    std::unique_ptr<gl_atomic_counter_buffer> _atomic_counter_buffer;

private:

    void _construct(const gl_compute_pipeline_descriptor& descriptor)
    {
        _program = std::make_unique<gl_program>(); if (!_program) return;

        const auto _glsl_compute_shader = descriptor.program->compute_shader;
        if (_glsl_compute_shader)
        {
            const std::string _path(descriptor.owner_renderer_dir + descriptor.name + ".cs");
            auto _compute_shader = std::make_shared<gl_shader>(gl_shader_type::COMPUTE_SHADER, _path);
            if (_program->construct({ _compute_shader }))
            {

            }
        }
    }

    void _bind_resources()
    {
        if (_uniform_buffer) _uniform_buffer->bind();
        if (_shader_storage_buffer) _shader_storage_buffer->bind();
        if (_atomic_counter_buffer) _atomic_counter_buffer->bind();
    }

    void _unbind_resources()
    {

    }

};

#define DECLARE_COMPUTE_PIPELINE_PROGRAM(PIPELINE_NAME)\
struct glsl_compute_pipeline_program_PIPELINE : glsl_compute_pipeline_program\
{\
\
};\

#endif