#ifndef H_RENDERER
#define H_RENDERER

#include "graphics/pipeline/graphics/gl_graphics_pipeline.h"
#include "graphics/pipeline/graphics/gl_vertex_processing_pipeline.h"
#include "graphics/pipeline/compute/gl_compute_pipeline.h"

#include "graphics/texture/gl_texture.h"

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

/*
* Every Renderer's resource refs must be dependent to each other.
* 
* 
*/
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

    void initialize()
    {
        // assembly all program resources
        assembly(_renderer_builder); 
        // check shaders
            // if not, create template shaders
        // if true, complie shaders
        // if complie success, check resources validation

    }

    

    using _pass_lambda = std::function<void(void)>;
    
    void _add_pass(const std::string& pass_name, const _pass_lambda& pass_lambda)
    {
        _passes.push_back(pass_lambda);
    }

private:

    std::string _renderer_name; 

    gl_renderer_builder _renderer_builder;

    std::vector<std::shared_ptr<gl_pipeline>> _pipelines;

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

    static std::string _global_renderers_dir;

    bool generate_renderer_glsl_template()
    {
        const std::string _renderer_dir = _global_renderers_dir + _renderer_name + "\\";
        bool _generation_result = false;
        if (std::filesystem::create_directory(_renderer_dir))
        {
            for (const auto& _pipeline : _pipelines)
            {
                if (!_pipeline || !_pipeline->ouput_pipeline_glsl_template(_renderer_dir)) 
                    return _generation_result;
            }
            _generation_result = true;
        }
        return _generation_result;
    }

};

#endif

