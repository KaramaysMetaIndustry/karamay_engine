#ifndef H_RENDERER
#define H_RENDERER

#include "graphics/pipeline/graphics/gl_graphics_pipeline.h"
#include "graphics/pipeline/compute/gl_compute_pipeline.h"
#include "graphics/texture/gl_texture.h"

class gl_graphics_pipeline;
class gl_vertex_processing_pipeline;
class gl_compute_pipeline;

class gl_renderer_builder
{
public:

    gl_renderer_builder() = default;

public:

    std::shared_ptr<gl_renderbuffer> create_renderbuffer(const gl_renderbuffer_descriptor& descriptor)
    {

    }

    std::shared_ptr<gl_renderbuffer_multisample> create_renderbuffer_multisample(const gl_renderbuffer_multisample_descriptor& descriptor)
    {

    }

public:

    std::shared_ptr<gl_vertex_shader> create_vertex_shader(const gl_vertex_shader_descriptor& descriptor) 
    {
        return std::make_shared<gl_vertex_shader>(descriptor);
    }
    
    std::shared_ptr<gl_tessellation_control_shader> create_tessellation_control_shader(const gl_tessellation_control_shader_descriptor& descriptor) 
    {
        return std::make_shared<gl_tessellation_control_shader>(descriptor);
    }
    
    std::shared_ptr<gl_tessellation_evaluation_shader> create_tessellation_evaluation_shader(const gl_tessellation_evaluation_shader_descriptor& descriptor)
    {
        return std::make_shared<gl_tessellation_evaluation_shader>(descriptor);
    }
    
    std::shared_ptr<gl_geometry_shader> create_geometry_shader(const gl_geometry_shader_descriptor& descriptor)
    {
        return std::make_shared<gl_geometry_shader>(descriptor);
    }
    
    std::shared_ptr<gl_fragment_shader> create_fragment_shader(const gl_fragment_shader_descriptor& descriptor)
    {
        return std::make_shared<gl_fragment_shader>(descriptor);
    }

    std::shared_ptr<gl_compute_shader> create_compute_shader(const gl_compute_shader_descriptor& descriptor)
    {

    }

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

    struct gl_PIP_NAME_graphics_pipeline_parameters : public gl_graphics_pipeline_parameters
    {

        class gl_pp_compute_shader_parameters : public gl_compute_shader_parameters
        {
        public:
            class glsl_pp_uniform_block_t : public glsl_uniform_block_t
            {
            public:
                glsl_pp_uniform_block_t() = delete;
                glsl_pp_uniform_block_t(std::function<void(const glsl_uniform_block_t& uniform_block)> _register)
                {}

                const std::uint8_t* data() const override
                {
                    return reinterpret_cast<const std::uint8_t*>(&memory);
                }

                std::int64_t size() const override
                {
                    return sizeof(memory) * 10;
                }
                
                struct gl_struct
                {
                    glsl_vec3 position0{item_register};
                    glsl_vec3 position1{item_register};
                    glsl_vec3 position2{item_register};
                } memory[10];


            } _ublock0{uniform_block_register};
        } compute_parameters;


    };
    std::shared_ptr<class gl_PIP_NAME_graphics_pipeline_parameters> _parameters;

    void test()
    {
        _parameters->compute_parameters._ublock0.memory[0].position0.client_value = glm::vec3(0.0f);
    }

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




#define CLASS_NAME(__CLASS__)  #__CLASS__





#endif

