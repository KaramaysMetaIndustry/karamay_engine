#ifndef GL_COMPUTE_PIPELINE_H
#define GL_COMPUTE_PIPELINE_H
#include "gl_pipeline.h"
#include "graphics/glsl/program/glsl_compute_pipeline_program.h"

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

private:

    std::unique_ptr<glsl_compute_pipeline_program> _program = {};

public:

    glsl_compute_pipeline_program& program() noexcept { return *_program; }

public:

    bool load(const std::string& pipeline_dir) noexcept override;

    void enable() noexcept override;

    void disable() noexcept override;

public:

    /*
    * dispatch the compute program.
    * x : group size x
    * y : group size y
    * z : group size z
    */
    void dispatch(uint32 x, uint32 y, uint32 z) noexcept;

};

#endif