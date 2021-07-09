#include "gl_static_mesh_renderer.h"
#include "graphics/program/gl_program.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/framebuffer/gl_framebuffer.h"

#define DEFINE_RENDERER(RENDERER_NAME)
#define END_DEFINE_RENDERER()
#define DEFINE_PASS(PASS_NAME) \
_passes.push_back(std::make_shared<gl_program>())\

#define REFER_PASS(PASS_NAME)\


void gl_static_mesh_renderer::assembly()
{
    _passes.push_back(std::make_shared<gl_program>());


}

void gl_static_mesh_renderer::render(std::float_t delta_time)
{
    _passes[0]->get_vertex_array() = _passes[1]->get_vertex_array();

    _passes[0]->render(delta_time);

    _passes[1]->render(delta_time);


}
