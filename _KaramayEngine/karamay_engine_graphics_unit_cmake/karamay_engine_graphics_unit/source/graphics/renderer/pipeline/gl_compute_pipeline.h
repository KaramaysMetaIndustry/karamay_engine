#ifndef _GL_COMPUTE_PIPELINE_H_
#define _GL_COMPUTE_PIPELINE_H_

#include "base/gl_pipeline.h"

class gl_compute_pipeline final : public gl_pipeline{
public:
    gl_compute_pipeline(glsl_compute_shader* cs) :
        _program(nullptr)
    {
        _program = new glsl_compute_pipeline_program(cs);
    }

	gl_compute_pipeline(const gl_compute_pipeline&) = delete;
	gl_compute_pipeline& operator=(const gl_compute_pipeline&) = delete;

    ~gl_compute_pipeline()
    {
        delete _program;
    }

public:

    void enable() noexcept
    {
        if (!_program) return;
    }

    void disable() noexcept
    {
        if(_program) return;
    }

public:

	void dispatch(uint32 group_size_x, uint32 group_size_y, uint32 group_size_z) noexcept
	{
	    if(!_program) return;
        glDispatchCompute(group_size_x, group_size_y, group_size_z);
	}

public:

    glsl_compute_pipeline_program& program()
    {
        return *_program;
    }

private:

    glsl_compute_pipeline_program* _program;

};

#endif