#ifndef _GL_COMPUTE_PIPELINE_H_
#define _GL_COMPUTE_PIPELINE_H_

#include "base/gl_pipeline.h"

class gl_compute_pipeline final : public gl_pipeline
{
public:
    gl_compute_pipeline(glsl_compute_shader* cs) :
        _program(nullptr)
    {
        _program = new glsl_compute_pipeline_program(cs);
        _program->load();
    }

	gl_compute_pipeline(const gl_compute_pipeline&) = delete;
	gl_compute_pipeline& operator=(const gl_compute_pipeline&) = delete;

    ~gl_compute_pipeline()
    {
        delete _program;
    }

public:

    glsl_compute_pipeline_program& program()
    {
#ifdef _DEBUG
        if(!_program) throw std::exception("program can not be null");
#endif
        return *_program;
    }

public:

    void enable() noexcept
    {
        if (!_program) return;
        _program->enable();
    }

    void disable() noexcept
    {
        if (_program) return;
        _program->disable();
    }

public:

    void dispatch(uint32 num_groups_x, uint32 num_groups_y, uint32 num_groups_z) noexcept
    {
        if (!_program) return;
        glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
    }

private:

    glsl_compute_pipeline_program* _program;

};

#endif