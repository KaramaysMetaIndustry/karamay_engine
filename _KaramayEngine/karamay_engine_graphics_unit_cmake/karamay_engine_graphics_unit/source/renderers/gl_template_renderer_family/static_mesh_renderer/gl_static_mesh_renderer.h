
#ifndef H_GL_STATIC_MESH_RENDERER
#define H_GL_STATIC_MESH_RENDERER


#include "graphics/renderer/gl_renderer.h"
#include "graphics/type/glsl_types.h"


struct gl_material
{

};

struct gl_static_mesh
{
    std::vector<glsl_vec4> colors;
    std::vector<glsl_vec3> positions;
    std::vector<glsl_vec2> uvs;

    gl_material material;
};


class gl_static_mesh_renderer : public gl_renderer {

public:

    void assembly() override;

    void render(std::float_t delta_time) override;

private:

    std::vector<std::shared_ptr<gl_program>> _passes;

public:

    std::vector<std::shared_ptr<gl_static_mesh>> _static_meshes;

};

#endif
