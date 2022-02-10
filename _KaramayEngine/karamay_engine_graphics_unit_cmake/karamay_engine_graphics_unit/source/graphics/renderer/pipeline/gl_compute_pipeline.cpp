#include "gl_compute_pipeline.h"

bool gl_compute_pipeline::load(const std::string& pipeline_dir) noexcept
{
    if (!_program->load(pipeline_dir))
    {
        return false;
    }
    
    return true;
}

void gl_compute_pipeline::enable() noexcept
{
    _program->enable();
}

void gl_compute_pipeline::disable() noexcept
{
    _program->disable();
}
