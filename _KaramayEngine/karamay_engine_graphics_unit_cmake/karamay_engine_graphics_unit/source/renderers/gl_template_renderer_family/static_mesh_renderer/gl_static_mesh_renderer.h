
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


class gl_static_mesh_renderer final : public gl_renderer 
{
public:

    gl_static_mesh_renderer(const std::string& name):
            gl_renderer(name)
    {}

protected:

    void assembly(gl_renderer_builder& builder) override;

    void pre_render(std::float_t delta_time) override;

    void post_render(std::float_t delta_time) override;

private:

    std::vector<gl_static_mesh> _static_meshes;

public:

    void add_static_mesh(const gl_static_mesh& static_mesh)
    {}

    void add_static_meshes(const std::vector<gl_static_mesh>& static_meshes)
    {}



};

#endif
