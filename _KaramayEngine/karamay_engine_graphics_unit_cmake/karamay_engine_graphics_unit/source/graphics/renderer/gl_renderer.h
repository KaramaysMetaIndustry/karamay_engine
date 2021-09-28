#ifndef H_RENDERER
#define H_RENDERER

#include "public/stl.h"
#include "graphics/pipeline/graphics/gl_graphics_pipeline.h"
#include "graphics/pipeline/compute/gl_compute_pipeline.h"
#include "graphics/texture/gl_texture.h"

class gl_graphics_pipeline;
class gl_vertex_processing_pipeline;
class gl_compute_pipeline;

class gl_renderer_builder{
public:
    gl_renderer_builder() = default;

public:

    std::shared_ptr<gl_graphics_pipeline> build_graphics_pipeline(const gl_graphics_pipeline_descriptor& descriptor)
    {
        return std::make_shared<gl_graphics_pipeline>(descriptor);
    }

    std::shared_ptr<gl_compute_pipeline> build_compute_pipeline(const gl_compute_pipeline_descriptor& descriptor)
    {
        return std::make_shared<gl_compute_pipeline>(descriptor);
    }

};

/*
* Every Renderer's resource refs must be dependent to each other.
* 
* 
*/
class gl_renderer
{
public:

    gl_renderer(){}

    ~gl_renderer() = default;

public:

    void build(gl_renderer_builder& builder);

    void render(std::float_t delta_time);

protected:

    virtual void _implementation_build(gl_renderer_builder& builder) = 0;

    virtual void _implementation_render(std::float_t delta_time) = 0;

protected:

    void initialize()
    {
        // assembly all program resources
        //assembly(_renderer_builder);
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

    bool _check_dir(const std::string& dir);

    void _initialize_renderer();

    void _compile(); 

    static std::string _global_renderers_dir;


};


#define DEFINE_RENDERER_CONSTRUCTOR(RENDERER_NAME)\
public:\
    static std::shared_ptr<RENDERER_NAME> _instance;\
    RENDERER_NAME() = default;\
    RENDERER_NAME(const gl_static_mesh_renderer&) = delete;\
    RENDERER_NAME& operator=(const RENDERER_NAME&) = delete;\
    ~RENDERER_NAME() = default;\
public:\
    static std::shared_ptr<RENDERER_NAME> invoke()\
    {\
        if (!_instance)\
        {\
            _instance = std::make_shared<RENDERER_NAME>();\
        }\
        return _instance;\
    }\


#define IMPLEMENTATION_FUNC_BUILD()\
protected:\
void _implementation_build(gl_renderer_builder& builder) override\

#define IMPLEMENTATION_FUNC_RENDER()\
protected:\
void _implementation_render(std::float_t delta_time) override\


#define DEFINE_RENDERER_BEGIN(RENDERER_NAME)\
class RENDERER_NAME final : protected gl_renderer{\
DEFINE_RENDERER_CONSTRUCTOR(RENDERER_NAME)\

#define DEFINE_RENDERER_END()\
};\










#endif

