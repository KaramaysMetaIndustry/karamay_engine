#include "gl_compute_pipeline.h"
#include "engine/karamay_engine.h"
#include "base/resource/glo/gl_object.h"

bool gl_compute_pipeline::load(const std::string& pipeline_dir) noexcept
{
    if (!_program->load(karamay_engine::get_engine_root() + pipeline_dir))
    {
        return false;
    }
    
    return true;
}

void gl_compute_pipeline::enable() noexcept
{
    if (_program)
    {
        _program->enable();
    }
}

void gl_compute_pipeline::disable() noexcept
{
    if (_program)
    {
        _program->disable();
    }
}

void gl_compute_pipeline::dispatch(uint32 x, uint32 y, uint32 z) noexcept
{
    glDispatchCompute(x, y, z);

#ifdef _DEBUG
    gl_object::_throw_errors(__FUNCTION__);
#endif // _DEBUG
}
