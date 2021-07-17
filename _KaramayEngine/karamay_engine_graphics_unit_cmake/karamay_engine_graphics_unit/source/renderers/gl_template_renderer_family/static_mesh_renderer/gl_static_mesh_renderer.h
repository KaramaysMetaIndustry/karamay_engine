
#ifndef H_GL_STATIC_MESH_RENDERER
#define H_GL_STATIC_MESH_RENDERER


#include <utility>

#include "graphics/renderer/gl_renderer.h"
#include "graphics/type/glsl_types.h"


struct gl_material
{

};

struct gl_static_mesh
{
    gl_material material;
};


class gl_static_mesh_renderer final : public gl_renderer {

public:

    gl_static_mesh_renderer(const std::string& name):
            gl_renderer(name)
    {
    }


    std::vector<std::shared_ptr<gl_static_mesh>> _static_meshes;

public:

    void assembly() override;

    void render(std::float_t delta_time) override;

private:

    std::vector<std::shared_ptr<gl_program>> _passes;

};

#endif
