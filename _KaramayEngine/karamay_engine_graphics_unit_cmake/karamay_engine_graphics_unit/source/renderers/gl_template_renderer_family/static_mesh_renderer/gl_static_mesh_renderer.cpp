#include "gl_static_mesh_renderer.h"
#include "graphics/pipeline/gl_graphics_pipeline.h"
#include "graphics/pipeline/gl_compute_pipeline.h"
#include "graphics/program/gl_program.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/framebuffer/gl_framebuffer.h"
#include "graphics/texture/texture_2d/gl_texture_2d.h"

void gl_static_mesh_renderer::assembly(gl_renderer_builder& builder)
{   

    auto _graphics_pip = builder.create_graphics_pipeline();
    auto _compute_pip = builder.create_compute_pipeline();

    auto _render_target = builder.create_texture_2d();


    _add_pass("RenderSimplePixels", [=]() {
        _graphics_pip->draw_triangles();
        });

    _add_pass("PostProcessing", [=]() {
        _compute_pip->dispatch(64, 1, 1);
        });

    _add_pass("ReadbackFinalPixels", []() {

        });
    
}

void gl_static_mesh_renderer::pre_render(std::float_t delta_time)
{
}

void gl_static_mesh_renderer::post_render(std::float_t delta_time)
{
}
