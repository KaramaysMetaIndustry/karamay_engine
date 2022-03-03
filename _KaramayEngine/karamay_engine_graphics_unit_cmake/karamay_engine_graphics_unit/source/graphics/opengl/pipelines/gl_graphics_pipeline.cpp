#include "gl_graphics_pipeline.h"
#include "engine/karamay_engine.h"

bool gl_graphics_pipeline::load(glsl_graphics_pipeline_program* glsl) noexcept
{
    if (!glsl)
    {
        return false;
    }

    _program = std::make_unique<gl_program>();
    if (!_program || _program->load(glsl))
    {
        return false;
    }

    auto _invoked_vert = glsl->invoke_vertex_shader();
    if (!_invoked_vert)
    {
        std::cerr << "a graphics pipeline must have a vertex shader" << std::endl;
        return false;
    }

    const auto& _vert_input = _invoked_vert->input();
    // initialize with vertex input
    gl_vertex_launcher_descriptor _descriptor;
    // primitive mode
    _descriptor.primitive_mode = gl_primitive_mode::TRIANGLES;
    _descriptor.primitive_vertices_num = 3;
    // indices
    _descriptor.elements_num = 99; // 99 / 3 = 33
    // vertices
    _descriptor.vertex_array_descriptor.vertices_num = 47;
    //_allocate_attributes(_descriptor.vertex_array_descriptor.vertex_descriptor.attribute_descriptors);
    // instance attributes
    //_allocate_instance_attributes(_descriptor.vertex_array_descriptor.instance_attribute_descriptors);
    auto _vl = new gl_vertex_launcher(_descriptor);

    auto _invoked_geom = glsl->invoke_geometry_shader();
    auto _invoked_tese = glsl->invoke_tessellation_evaluation_shader();
    
    // feedback stream
    gl_feedback* _fb = nullptr;
    if (_invoked_geom)
    {

    }
    else if(_invoked_tese) {

    }


    //default framebuffer or custom framebuffer
    gl_render_target* _rt = nullptr;
    
    auto _invoked_frag = glsl->invoke_fragment_shader();
    if (!_invoked_frag)
    {

    }
    
    _vertex_launcher.reset(_vl);
    if(_fb) _feedback.reset(_fb);
    if(_render_target) _render_target.reset(_rt);

    return true;
}

void gl_graphics_pipeline::enable() noexcept
{
#ifdef _DEBUG
    if (!_program || !_vertex_launcher || !_render_target)
        throw std::exception("vertex launcher, program, render target must not be nullptr");
#endif // _DEBUG
    _program->enable();
    _vertex_launcher->bind();
    _render_target->bind();
    _set_pipeline_fixed_functions();
}

void gl_graphics_pipeline::disable() noexcept
{
#ifdef _DEBUG
    if (!_program || !_vertex_launcher || !_render_target)
        throw std::exception("vertex launcher, program, render target must not be nullptr");
#endif // _DEBUG
    _render_target->unbind();
    _vertex_launcher->unbind();
    _program->disable();
}
