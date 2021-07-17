
#ifndef H_GL_INSTANCED_STATIC_MESH_RENDERER
#define H_GL_INSTANCED_STATIC_MESH_RENDERER

#include "graphics/renderer/gl_renderer.h"

class gl_instanced_static_mesh_renderer : public gl_renderer
{
public:

    void assembly() override;

    void render(std::float_t delta_time) override;

};


#endif
