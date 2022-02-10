#include "gl_mesh_pipeline.h"

bool gl_mesh_pipeline::load(const std::string& pipeline_dir) noexcept
{
    if (!_mesh_pipeline_program || !_mesh_pipeline_program->load(pipeline_dir)) return false;
    std::cout << "pipeline : " << long long(this) << " load succuessfully." << std::endl;
    return true;
}

void gl_mesh_pipeline::enable() noexcept
{
    _mesh_pipeline_program->enable();
}

void gl_mesh_pipeline::disable() noexcept
{
    _mesh_pipeline_program->disable();
}
