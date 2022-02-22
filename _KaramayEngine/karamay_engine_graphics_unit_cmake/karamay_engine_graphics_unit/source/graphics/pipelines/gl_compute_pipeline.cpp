#include "gl_compute_pipeline.h"
#include "engine/karamay_engine.h"
#include "graphics/resource/glo/gl_object.h"

void gl_compute_pipeline::dispatch(uint32 x, uint32 y, uint32 z) noexcept
{
    glDispatchCompute(x, y, z);

#ifdef _DEBUG
    gl_object::_throw_errors(__FUNCTION__);
#endif // _DEBUG
}
