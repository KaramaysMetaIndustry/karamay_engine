#ifndef GL_RENDERER_FRAMEWORK_H
#define GL_RENDERER_FRAMEWORK_H
#include "graphics/opengl/renderer/gl_renderer.h"

class gl_renderer_framework
{
public:

	virtual bool initialize() noexcept = 0;

	virtual void tick(float delta_time) noexcept = 0;

	virtual bool set_state(bool enable) noexcept = 0;

	virtual bool is_active() const noexcept = 0;

};

#endif