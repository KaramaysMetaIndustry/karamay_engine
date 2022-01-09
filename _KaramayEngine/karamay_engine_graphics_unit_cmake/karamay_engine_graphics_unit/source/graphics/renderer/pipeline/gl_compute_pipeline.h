#ifndef _GL_COMPUTE_PIPELINE_H_
#define _GL_COMPUTE_PIPELINE_H_

#include "base/gl_pipeline.h"

class gl_compute_pipeline final : public gl_pipeline
{
public:
    gl_compute_pipeline(glsl_compute_pipeline_program* compute_pipeline_program)
    {
        _program.reset(compute_pipeline_program);
    }

	gl_compute_pipeline(const gl_compute_pipeline&) = delete;
	gl_compute_pipeline& operator=(const gl_compute_pipeline&) = delete;

    ~gl_compute_pipeline() = default;

public:

    bool load(const std::string& pipeline_dir) noexcept override
    {
        if (!_program->load(pipeline_dir)) return false;

        return true;
    }

    void enable() noexcept override
    {
        _program->enable();
    }

    void disable() noexcept override
    {
        _program->disable();
    }

private:

    std::unique_ptr<glsl_compute_pipeline_program> _program = {};

public:

    const std::unique_ptr<glsl_compute_pipeline_program>& program() const noexcept { return _program; }

public:

    void dispatch(uint32 num_groups_x, uint32 num_groups_y, uint32 num_groups_z) noexcept
    {
        if (!_program) return;
        glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
    }

};

#endif