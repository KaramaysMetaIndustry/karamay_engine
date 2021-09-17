#ifndef H_GRAPHICS_PIPELINE
#define H_GRAPHICS_PIPELINE

#include "graphics/pipeline/base/gl_pipeline.h"
#include "graphics/shader/gl_vertex_shader.h"
#include "graphics/shader/gl_tessellation_control_shader.h"
#include "graphics/shader/gl_tessellation_evaluation_shader.h"
#include "graphics/shader/gl_geometry_shader.h"
#include "graphics/shader/gl_fragment_shader.h"
#include "graphics/type/glsl_class.h"

enum gl_stencil_op : GLenum
{
	so_keep = GL_KEEP, // keep current val
	so_zero = GL_ZERO, // set val to 0
	so_replace = GL_REPLACE, //set val to ref specified by glStencilFunc
	so_incr = GL_INCR, // 
	so_incr_wrap = GL_INCR_WRAP,
	so_decr = GL_DECR,
	so_decr_wrap = GL_DECR_WRAP,
	so_invert = GL_INVERT
};

enum gl_stencil_func : GLenum
{
	sf_never = GL_NEVER,
	sf_always = GL_ALWAYS,
	sf_less = GL_LESS,
	sf_less_equal = GL_LEQUAL,
	sf_greater = GL_GREATER,
	sf_greater_equal = GL_GEQUAL,
	sf_equal = GL_EQUAL,
	sf_not_equeal = GL_NOTEQUAL
};

enum class gl_logic_op : GLenum
{
    clear = GL_CLEAR,
    set = GL_SET,
    copy = GL_COPY,
    copy_inverted = GL_COPY_INVERTED,
    noop = GL_NOOP,
    invert = GL_INVERT,
    and = GL_AND,
    nand = GL_NAND,
    or = GL_OR,
    nor = GL_NOR,
    xor = GL_XOR,
    equiv = GL_EQUIV,
    and_reverse = GL_AND_REVERSE,
    and_inverted = GL_AND_INVERTED,
    or_reverse = GL_OR_REVERSE,
    or_inverted = GL_OR_INVERTED
};

enum gl_depth_func : GLenum
{
    df_never = GL_NEVER,
    df_less = GL_LESS,
    df_equeal = GL_EQUAL,
    df_less_equal = GL_LEQUAL,
    df_greater = GL_GREATER,
    df_not_equal = GL_NOTEQUAL,
    df_greater_equal = GL_GEQUAL,
    df_always = GL_ALWAYS
};

enum gl_provoke_mode : GLenum
{
    first_vertex_convention = GL_FIRST_VERTEX_CONVENTION,
    last_vertex_convention = GL_LAST_VERTEX_CONVENTION
};

enum gl_clip_control_origin : GLenum
{
    lower_left = GL_LOWER_LEFT,
    upper_left = GL_UPPER_LEFT
};

enum gl_clip_control_depth_mode : GLenum
{
    negative_one_to_one = GL_NEGATIVE_ONE_TO_ONE,
    zero_to_one = GL_ZERO_TO_ONE
};

class gl_graphics_pipeline_parameters{};

struct gl_graphics_pipeline_descriptor
{
    struct gl_vertex_assembly
    {
       struct gl_vertex_specification{} specification;
       struct gl_primitive_restart
        {
            bool enabled;
            bool use_fixed_restart_primitive_index;
            std::uint32_t restart_primitive_index;
        } primitive_restart;
    } vertex_assembly; // organize vertex stream
    struct gl_vertex_processing
    {
        struct gl_vertex_shading
        {
            std::shared_ptr<gl_vertex_shader> shader;
        }vertex_shading;
        struct gl_tessellation
        {
            std::shared_ptr<gl_tessellation_control_shader> control_shader;
            std::shared_ptr<gl_tessellation_evaluation_shader> evaluation_shader;
        } tessellation;
        struct gl_geometry_shading
        {
            std::shared_ptr<gl_geometry_shader> shader;
        } geometry_shading;
		struct gl_post_vertex_processing
		{
			struct gl_transform_feedback
			{
				
				std::string semantic_name;
			} transform_feedback;
            struct gl_flatshading
            {
                gl_provoke_mode provoke_mode;
            } flatshading;
			struct gl_primitive_clipping
			{
                std::uint32_t clip_plane_index{0};
                gl_clip_control_origin clip_control_origin{ gl_clip_control_origin::lower_left };
                gl_clip_control_depth_mode clip_control_depth_mode{};
                // 0, 1
                std::double_t near_clipping_distance, far_clipping_distance;
			} primitive_clipping;
			struct gl_coordinate_transformations
			{
                std::int32_t viewport_x, viewport_y;
                std::uint32_t viewport_width, viewport_height; // glViewport
			} coordinate_transformations;
		} post_vertex_processing;
    } vertex_processing; // vertex shading, tessellation, geometry shading, transform feedback, clipping, coordinates transformation
    struct gl_primitive_assembly 
    {
        bool discard_all_primitives; // discard all primitives, if true the pipeline wont go head
    } primitive_assembly; // collect primitives or discard all of them
    struct gl_rasterization
    {
        
    } rasterization; // the stage generate fragments from primitives (points, lines, polygons)
    struct gl_fragment_processing
    {
        /*
        * Once fragments are produced by rasterization, a number of per-fragment operations
        * are performed prior to fragment shader execution.
        * If a fragment is discarded during any of these operations, it will not be processed by any subsequent stage,
        * including fragment shader execution.
        * Three fragment operations are performed,
        * and a further three are optionally performed on each fragment.
        * (stencil_test, depth_test, occlusion_queries after fragment shading)
        * (which need to specify "early_fragment_tests layout" Qualifier in fs)
        */
        struct gl_pre_fragment_operations
        {
            struct gl_pixel_ownship_test {} pixel_ownship_test;
            struct gl_scissor_test
            {
                bool enabled;
            } scissor_test;
            struct gl_multisample_fragment_operations {} multisample_fragment_operations;
        } pre_fragment_operations;
        struct gl_fragment_shading
        {
            std::shared_ptr<gl_fragment_shader> shader;
        } fragment_shading;
        struct gl_post_fragment_operations
        {
            struct gl_alpha_to_coverage
            {
                bool enabled;

            } alpha_to_coverage;
            struct gl_advanceable_operations
            {
                struct gl_stencil_test
                {
                    bool enabled;
                    gl_stencil_func front_face_func;
                    gl_stencil_func back_face_func;
                    gl_stencil_op front_face_op;
                    gl_stencil_op back_face_op;
                } stencil_test; // can be advanced before fragment shading
                struct gl_depth_test
                {
                    bool enabled;
                    gl_depth_func func;
                    bool clamp_enabled;
                    std::double_t near_val, far_val;
                } depth_test; // can be advanced before fragment shading
                struct gl_occlusion_queries
                {

                } occlusion_queries; // can be advanced before fragment shading
                bool advanced;
            } advanceable_operations;
            struct gl_blending
            {

            } blending;
            struct gl_srgb_conversion
            {

            } srgb_conversion;
            struct gl_dithering
            {
                bool enabled;
            } dithering;
            struct gl_logical_operation
            {
                bool enabled;
                gl_logic_op op;
            } logical_operation;
            struct gl_addtional_multisample_fragment_operations
            {
                bool enabled;
                std::float_t sample_coverage_value;
                bool inverted;
            } addtional_multisample_fragment_operations;
        } post_fragment_operations;
    } fragment_processing; // process fragments
    struct gl_render_target
    {
        std::shared_ptr<gl_framebuffer> framebuffer;
    } render_target;
    std::shared_ptr<gl_graphics_pipeline_parameters> parameters;
};

class gl_graphics_pipeline : public gl_pipeline
{
public:

    gl_graphics_pipeline() = delete;
    gl_graphics_pipeline(const gl_graphics_pipeline_descriptor& descriptor) :
        _descriptor(descriptor)
    {}
    gl_graphics_pipeline(const gl_graphics_pipeline&) = delete;
    gl_graphics_pipeline& operator=(const gl_graphics_pipeline&) = delete;

    ~gl_graphics_pipeline() = default;

private:
    
    const gl_graphics_pipeline_descriptor _descriptor;

public:

    enum class shader_combination_flag : std::uint8_t
    {
        _vs,
        _vs_tescs_teses,
        _vs_tescs_teses_gs,
        
        _vs_fs,
        _vs_gs_fs,
        _vs_tescs_teses_fs,
        _vs_tescs_teses_gs_fs,
        
    };

    void initialize()
    {
        auto& _vs = _descriptor.vertex_processing.vertex_shading.shader;
        auto& _tescs = _descriptor.vertex_processing.tessellation.control_shader;
        auto& _teses = _descriptor.vertex_processing.tessellation.evaluation_shader;
        auto& _gs = _descriptor.vertex_processing.geometry_shading.shader;
        auto& _fs = _descriptor.fragment_processing.fragment_shading.shader;

        shader_combination_flag _combination_flag;
        std::uint8_t _flag = 0;

        if (_vs)
        {
            _flag |= 0;
        }
        if (_tescs)
        {

        }

        // check the shaders combination invalidation
        switch (_combination_flag)
        {
        case gl_graphics_pipeline::shader_combination_flag::_vs:
        {
            if (!_descriptor.primitive_assembly.discard_all_primitives)
            {
                std::cout << "You must specify a fragment shader otherwise enable the option 'discard_all_primitives'" << std::endl;
                return;
            }

            // generate pipeline shaders template
            const auto& _vs_template = _vs->get_shader_glsl_template();

            //_program->construct();

        }
            break;
        case gl_graphics_pipeline::shader_combination_flag::_vs_tescs_teses:
        {
            if (!_descriptor.primitive_assembly.discard_all_primitives)
            {
                std::cout << "You must specify a fragment shader otherwise enable the option 'discard_all_primitives'" << std::endl;
                return;
            }
        }
            break;
        case gl_graphics_pipeline::shader_combination_flag::_vs_tescs_teses_gs:
        {
            if (!_descriptor.primitive_assembly.discard_all_primitives)
            {
                std::cout << "You must specify a fragment shader otherwise enable the option 'discard_all_primitives'" << std::endl;
                return;
            }


        }
            break;
        case gl_graphics_pipeline::shader_combination_flag::_vs_fs:
            break;
        case gl_graphics_pipeline::shader_combination_flag::_vs_gs_fs:
            break;
        case gl_graphics_pipeline::shader_combination_flag::_vs_tescs_teses_fs:
            break;
        case gl_graphics_pipeline::shader_combination_flag::_vs_tescs_teses_gs_fs:
            break;
        default:
            break;
        }






        std::vector<std::shared_ptr<gl_shader>> _shaders;
        if (const auto& _vs = _descriptor.vertex_processing.vertex_shading.shader)
        {
            _shaders.push_back(_vs);
        }
        if (const auto& _gs = _descriptor.vertex_processing.geometry_shading.shader)
        {
            _shaders.push_back(_gs);
        }

        // check dir

        // generate shader templates
        for (const auto& _shader : _shaders)
        {
            _shader->get_shader_glsl_template();
        }

        // load source code and compile  
    }

    bool ouput_pipeline_glsl_template(const std::string& renderer_dir) const override
    {
        const std::string _pipeline_dir = renderer_dir + _name + "\\";
        if (std::filesystem::create_directory(_pipeline_dir))
        {

        }
    }

    std::vector<std::shared_ptr<gl_shader>> _shaders;

    void generate_pipeline_dir(const std::string& renderer_dir)
    {
        if (std::filesystem::exists(renderer_dir)) // check the renderer dir
        {
            std::string _pipeline_dir = renderer_dir + _name + "\\";
            if (std::filesystem::create_directory(_pipeline_dir))
            {
                for (const auto& _shader : _shaders)
                {
                    std::ofstream _file(_pipeline_dir + _name + ".ext");
                    _file.open(_pipeline_dir + _name + ".ext", 1, 2);
                    _file.write(_shader->get_shader_glsl_template().c_str(), _shader->get_shader_glsl_template().length());
                    _file.close();
                }
                //std::ofstream _xml_file;
                //_xml_file.open(_pipeline_dir + _name + ".xml");
                //_xml_file.write();
                //_xml_file.close();
            }
        }
    }

public:

    void set_primitive_clipping(gl_clip_control_origin origin, gl_clip_control_depth_mode depth_mode)
    {
        /*_descriptor.vertex_processing.post_vertex_processing.primitive_clipping.clip_control_origin = origin;
        _descriptor.vertex_processing.post_vertex_processing.primitive_clipping.clip_control_depth_mode = depth_mode;*/
    }

    void set_viewport(std::int32_t x, std::int32_t y, std::uint32_t width, std::uint32_t height)
    {
        /*_descriptor.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_x = x;
        _descriptor.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_y = y;
        _descriptor.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_width = width;
        _descriptor.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_height = height;*/
    }

private:

    bool _check_shader_ext(const std::string& path, const std::string& ext)
    {
        return path.substr(path.find_first_of('.')) == ext;
    }

    void _install();

    void _uninstall();

public:

    inline void draw_points(std::int32_t first, std::uint32_t count)
    {
        glDrawArrays(GL_POINTS, 0, 100);
    }

    inline void draw_lines() {}

    inline void draw_triangles() {}

    inline void draw_triangle_strips() {}

    inline void draw_rectangles() {}

};

#define DEFINE_GRAPHICS_PIPELINE_PARAMETERS(PIPELINE_NAME)\
struct gl_##PIPELINE_NAME##_graphics_pipeline_parameters : public gl_graphics_pipeline_parameters\



#define DEFINE_PROGRAM_PARAMETER_IMAGE(GLSL_IMAGE_T, V_NAME) \
glsl_##GLSL_IMAGE_T V_NAME;\

#define DEFINE_PROGRAM_PARAMETER_IMAGE_ARRAY(GLSL_IMAGE_T, V_NAME, ARRAY_SIZE)\
glsl_##GLSL_IMAGE_T V_NAME[ARRAY_SIZE]; \

#define DEFINE_PROGRAM_PARAMETER_SAMPLER(GLSL_SAMPLER_T, V_NAME)\
glsl_##GLSL_SAMPLER_T V_NAME;\

#define DEFINE_PROGRAM_PARAMETER_SAMPLER_ARRAY(GLSL_SAMPLER_T, V_NAME, ARRAY_SIZE)\
glsl_##GLSL_SAMPLER_T V_NAME[ARRAY_SIZE]; \

#define DEFINE_PROGRAM_PARAMETER_ATOMIC_COUNTER(V_NAME)\
glsl_atomic_uint V_NAME;\

#define DEFINE_PROGRAM_PARAMETER_ATOMIC_COUNTER_ARRAY(V_NAME, ARRAY_SIZE)\
glsl_atomic_uint V_NAME[ARRAY_SIZE];\

#define DEFINE_PROGRAM_PARAMETER_UNIFORM_BLOCK(GLSL_UNIFORM_BLOCK_T, V_NAME)\
GLSL_UNIFORM_BLOCK_T V_NAME;

#define DEFINE_PROGRAM_PARAMETER_UNIFORM_BLOCK_ARRAY(GLSL_UNIFORM_BLOCK_T, V_NAME, ARRAY_SIZE)\
GLSL_UNIFORM_BLOCK_T V_NAME[ARRAY_SIZE];\

#define DEFINE_PROGRAM_PARAMETER_SHADER_STORAGE_BLOCK(GLSL_SHADER_STORAGE_BLOCK_T, V_NAME)\
GLSL_SHADER_STORAGE_BLOCK_T V_NAME; \

#define DEFINE_PROGRAM_PARAMETER_SHADER_STORAGE_BLOCK_ARRAY(GLSL_SHADER_STORAGE_BLOCK_T, V_NAME, ARRAY_SIZE)\
GLSL_SHADER_STORAGE_BLOCK_T V_NAME[ARRAY_SIZE];\


// Shader Parameters Definition
#define DEFINE_VERTEX_SHADER_PARAMETERS_BEGIN()
#define DEFINE_VERTEX_SHADER_PARAMETERS_END()

#define DEFINE_TESC_SHADER_PARAMETERS_BEGIN()
#define DEFINE_TESC_SHADER_PARAMETERS_END()

#define DEFINE_TESE_SHADER_PARAMETERS_BEGIN()
#define DEFINE_TESE_SHADER_PARAMETERS_END()

#define DEFINE_GEOMETRY_SHADER_PARAMETERS_BEGIN()
#define DEFINE_GEOMETRY_SHADER_PARAMETERS_END()

#define DEFINE_FRAGMENT_SHADER_PARAMETERS_BEGIN()
#define DEFINE_FRAGMENT_SHADER_PARAMETERS_END()


// Shader Stream Definition
#define DEFINE_STREAM_INPUT_BEGIN()
#define DEFINE_STREAM_INPUT_END()
#define DEFINE_VERTEX_FRAGMENT_STREAM_BEGIN()
#define DEFINE_VERTEX_FRAGMENT_STREAM_END()
#define DEFINE_VERTEX_TESC_STREAM_BEGIN()
#define DEFINE_VERTEX_TESC_STREAM_END()
#define DEFINE_VERTEX_GEOMETRY_STREAM_BEGIN()
#define DEFINE_VERTEX_GEOMETRY_STREAM_END()
#define DEFINE_TESC_TESE_STREAM_BEGIN()
#define DEFINE_TESC_TESE_STREAM_END()
#define DEFINE_TESE_GEOMETRY_STREAM_BEGIN()
#define DEFINE_TESE_GEOMETRY_STREAM_END()
#define DEFINE_TESE_FRAGMENT_STREAM_BEGIN()
#define DEFINE_TESE_FRAGMENT_STREAM_END()
#define DEFINE_GEOMETRY_FRAGMENT_STREAM_BEGIN()
#define DEFINE_GEOMETRY_FRAGMENT_STREAM_END()
#define DEFINE_STREAM_OUTPUT_BEGIN()
#define DEFINE_STREAM_OUTPUT_END()

#endif

