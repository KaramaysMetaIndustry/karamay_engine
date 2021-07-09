
#ifndef H_GL_PARTICLE_SYSTEM_RENDERER
#define H_GL_PARTICLE_SYSTEM_RENDERER

#include "graphics/renderer/gl_renderer.h"

class gl_particle_system_renderer : public gl_renderer {

    void assembly() override;

    void render(std::float_t delta_time) override;

};


#endif
