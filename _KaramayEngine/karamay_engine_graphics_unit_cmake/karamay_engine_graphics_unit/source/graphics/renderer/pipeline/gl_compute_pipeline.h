#ifndef GL_COMPUTE_PIPELINE_H
#define GL_COMPUTE_PIPELINE_H

#include "base/gl_pipeline.h"

/*
* compute pipeline only need a compute shader to link program
* 
*/
class gl_compute_pipeline final : public gl_pipeline
{
public:
    gl_compute_pipeline(glsl_compute_pipeline_program* program)
    {
        _program.reset(program);
    }

	gl_compute_pipeline(const gl_compute_pipeline&) = delete;
	gl_compute_pipeline& operator=(const gl_compute_pipeline&) = delete;

    ~gl_compute_pipeline() = default;

public:

    bool load(const std::string& pipeline_dir) noexcept override;

    void enable() noexcept override;

    void disable() noexcept override;

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