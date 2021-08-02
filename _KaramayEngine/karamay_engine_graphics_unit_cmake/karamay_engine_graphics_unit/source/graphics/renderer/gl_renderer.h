#ifndef H_RENDERER
#define H_RENDERER

#include "public/stl.h"

class gl_pipeline;
class gl_graphics_pipeline;
class gl_compute_pipeline;
class gl_ray_tracing_pipeline;


class gl_renderer_builder
{
public:

    gl_renderer_builder() = default;

private:

    struct gl_renderer_resource
    {
        std::vector<std::shared_ptr<gl_pipeline>> pipelines;

    } _resource;


public:

    std::shared_ptr<gl_graphics_pipeline> create_graphics_pipeline()
    {
    }

    std::shared_ptr<gl_compute_pipeline> create_compute_pipeline()
    {

    }

    std::shared_ptr<gl_ray_tracing_pipeline> create_ray_tracing_pipeline()
    {

    }

    std::shared_ptr<gl_texture_2d> create_texture_2d()
    {

    }

    std::shared_ptr<gl_texture_2d_array> create_texture_2d_array() {}

    std::shared_ptr<gl_texture_2d_multisample> create_texture_2d_multisample() {}

    std::shared_ptr<gl_texture_2d_array_multisample> create_texture_2d_array_multisample() {}

    std::shared_ptr<gl_texture_3d> create_texture_3d() {}

    std::shared_ptr<gl_texture_cube> create_texture_cube() {}

    std::shared_ptr<gl_texture_cube_array> create_texture_cube_array() {}

    std::shared_ptr<gl_texture_rectangle> create_texture_rectangle() {}

    std::shared_ptr<gl_uniform_buffer> create_uniform_buffer() {}

};


class gl_renderer
{
public:

    gl_renderer()
    {
        assembly(_renderer_builder);
    }

    ~gl_renderer() = default;

private:

    gl_renderer_builder _renderer_builder;

protected:

    
    
    using _pass_lambda = std::function<void(void)>;

private:

    std::unordered_map<std::string, std::shared_ptr<gl_pipeline>> _pipeline_map;
    
    std::vector<_pass_lambda> _passes;

protected:

   
    void _add_pass(const std::string& pass_name, const _pass_lambda& pass_lambda)
    {
        _passes.push_back(pass_lambda);
    }

    void _pre_compile_renderer()
    {
        _generate_glslx_file();
    }

    void _generate_glslx_file() {}

    void _compile_renderer() 
    {
        _pre_compile_renderer();
        
    }

public:

    virtual void assembly(gl_renderer_builder& builder) = 0;

    virtual void pre_render(std::float_t delta_time) = 0;
    virtual void post_render(std::float_t delta_time) = 0;

    virtual void launch_render_task() = 0;


    void render(std::float_t delta_time)
    {
        pre_render(delta_time);
        for (auto& _pass : _passes) _pass();
        post_render(delta_time);
    }

};


#endif

