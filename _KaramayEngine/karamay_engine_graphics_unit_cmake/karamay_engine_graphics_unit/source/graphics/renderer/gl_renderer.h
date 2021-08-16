#ifndef H_RENDERER
#define H_RENDERER

#include "graphics/pipeline/graphics/gl_graphics_pipeline.h"
#include "graphics/pipeline/graphics/gl_vertex_processing_pipeline.h"
#include "graphics/pipeline/compute/gl_compute_pipeline.h"

#include "graphics/texture/gl_texture.h"

class gl_pipeline_base;
class gl_graphics_pipeline;
class gl_vertex_processing_pipeline;
class gl_compute_pipeline;

class gl_renderer_builder
{
public:

    gl_renderer_builder() = default;

private:

    struct gl_renderer_resource
    {
        std::vector<std::shared_ptr<gl_pipeline_base>> pipelines;

    } _resource;


public:

    std::shared_ptr<gl_graphics_pipeline> create_graphics_pipeline(const gl_graphics_pipeline_descriptor& descriptor)
    {
        return std::make_shared<gl_graphics_pipeline>(descriptor);
    }

    std::shared_ptr<gl_compute_pipeline> create_compute_pipeline()
    {

    }


    static std::shared_ptr<gl_texture_2d> create_texture_2d(
        std::int32_t width, std::int32_t height, 
        gl_texture_pixel_format pixel_format,
        std::int32_t mipmaps_count
    )
    {
        if (
            width < 0 || width > GL_MAX_TEXTURE_SIZE || 
            height < 0 || height > GL_MAX_TEXTURE_SIZE || 
            mipmaps_count < 0
            ) return;

        gl_texture_2d_descriptor _desc{ width, height, pixel_format,mipmaps_count };
        return std::make_shared<gl_texture_2d>(_desc);
    }

    static std::shared_ptr<gl_texture_2d_array> create_texture_2d_array(
        std::int32_t elements_count,
        std::int32_t width, std::int32_t height,
        gl_texture_pixel_format pixel_format,
        std::int32_t mipmaps_count
    ) 
    {
        if (
            elements_count < 0 || width < 0 ||
            width > GL_MAX_TEXTURE_SIZE ||
            height < 0 || height > GL_MAX_TEXTURE_SIZE ||
            mipmaps_count < 0
            ) return;
        gl_texture_2d_array_descriptor _desc(elements_count, width, height, pixel_format, mipmaps_count);
        return std::make_shared<gl_texture_2d_array>(_desc);
    }

    static std::shared_ptr<gl_texture_2d_multisample> create_texture_2d_multisample() {}

    static std::shared_ptr<gl_texture_2d_array_multisample> create_texture_2d_array_multisample() {}

    static std::shared_ptr<gl_texture_3d> create_texture_3d() {}

    static std::shared_ptr<gl_texture_cube> create_texture_cube() {}

    static std::shared_ptr<gl_texture_cube_array> create_texture_cube_array() {}

    static std::shared_ptr<gl_texture_rectangle> create_texture_rectangle() {}


};

class gl_renderer
{
public:

    gl_renderer()
    {
        assembly(_renderer_builder);
    }

    ~gl_renderer() = default;

public:

    virtual void assembly(gl_renderer_builder& builder) = 0;

    virtual void render(std::float_t delta_time) = 0;

protected:

    using _pass_lambda = std::function<void(void)>;
    
    void _add_pass(const std::string& pass_name, const _pass_lambda& pass_lambda)
    {
        _passes.push_back(pass_lambda);
    }

private:

    std::string name; 

    gl_renderer_builder _renderer_builder;

    std::vector<std::shared_ptr<gl_pipeline_base>> _pipelines;

    std::vector<_pass_lambda> _passes;

    bool _validate()
    {
        for (auto& _pipeline : _pipelines)
        {
            if (!_pipeline || !_pipeline->validate()) return false;
        }
    }

    bool _check_dir(const std::string& dir);

    void _initialize_renderer();

    void _compile(); 
};

#endif

