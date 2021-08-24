
#ifndef H_GL_STATIC_MESH_RENDERER
#define H_GL_STATIC_MESH_RENDERER

#include "graphics/renderer/gl_renderer.h"



class gl_static_mesh_renderer final : public gl_renderer 
{
public:

    gl_static_mesh_renderer(const std::string& name);

public:

    void assembly(gl_renderer_builder& builder) override;

    void render(std::float_t delta_time) override;

};

#endif
