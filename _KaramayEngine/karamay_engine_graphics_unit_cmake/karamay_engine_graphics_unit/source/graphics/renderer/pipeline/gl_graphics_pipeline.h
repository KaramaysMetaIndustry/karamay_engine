#ifndef GRAPHICS_PIPELINE_H
#define GRAPHICS_PIPELINE_H

#include "base/gl_pipeline.h"
#include "base/vertex_launcher/gl_vertex_launcher.h"
#include "base/render_target/gl_render_target.h"

enum class gl_stencil_op : GLenum
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

enum class gl_stencil_func : GLenum
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
    CLEAR = GL_CLEAR,
    SET = GL_SET,
    COPY = GL_COPY,
    COPY_INVERTED = GL_COPY_INVERTED,
    NOOP = GL_NOOP,
    INVERT = GL_INVERT,
    AND = GL_AND,
    NAND = GL_NAND,
    OR = GL_OR,
    NOR = GL_NOR,
    XOR = GL_XOR,
    EQUIV = GL_EQUIV,
    AND_REVERSE = GL_AND_REVERSE,
    AND_INVERTED = GL_AND_INVERTED,
    OR_REVERSE = GL_OR_REVERSE,
    OR_INVERTED = GL_OR_INVERTED
};

enum class gl_depth_func : GLenum
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

enum class gl_provoke_mode : GLenum
{
    first_vertex_convention = GL_FIRST_VERTEX_CONVENTION,
    last_vertex_convention = GL_LAST_VERTEX_CONVENTION
};

enum class gl_clip_control_origin : GLenum
{
    lower_left = GL_LOWER_LEFT,
    upper_left = GL_UPPER_LEFT
};

enum class gl_clip_control_depth_mode : GLenum
{
    negative_one_to_one = GL_NEGATIVE_ONE_TO_ONE,
    zero_to_one = GL_ZERO_TO_ONE
};

/*
 * for dynamical modifying
 * */
struct gl_graphics_pipeline_state
{
    struct gl_vertex_assembly
    {
        struct gl_primitive_restart
        {
            bool enabled;
            bool use_fixed_restart_primitive_index;
            std::uint32_t restart_primitive_index;
        } primitive_restart;
    } vertex_assembly; // organize vertex stream
    struct gl_vertex_processing
    {
        struct gl_post_vertex_processing
        {
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
    struct gl_rasterisation
    {

    } rasterisation; // the stage generate fragments from primitives (points, lines, polygons)
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
            } additional_multisample_fragment_operations;
        } post_fragment_operations;
    } fragment_processing; // process fragments

    void set()
    {
        // vertex specification
        {
            glEnable(GL_PRIMITIVE_RESTART);
            glPrimitiveRestartIndex(0);
            // or
            glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);// 2^N - 1
        }

        // vertex process
        {
            //shading

            // flatshading
            glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

            // clipping
            glEnable(GL_CLIP_DISTANCE0); // [0, GL_MAX_CLIP_DISTANCES-1]
            glClipControl(GL_LOWER_LEFT, GL_NEGATIVE_ONE_TO_ONE);
            // glEnable(GL_DEPTH_CLAMP);
            glDepthRange(1.0l, 1.1l);
            //glDepthRangeArrayv();
            //glDepthRangef();
//            glViewport();
//            glDepthRangeIndexed();
//            glViewportArrayv();
//            glViewportIndexedf();
//            glViewportIndexedfv();


        }

        // primitive assmebly
        {

        }
        // rasterization
        {
            // 到达光栅化之前抛弃所有图元, 使得光栅化包括光栅化之后的阶段全部失效
            if (true)
                glEnable(GL_RASTERIZER_DISCARD);
            else
                glDisable(GL_RASTERIZER_DISCARD);

            // multisampling
            glEnable(GL_MULTISAMPLE);
            glEnable(GL_SAMPLE_SHADING);
            //            glMinSampleShading();
            //            glGetMultisamplefv();

                        // points
            glEnable(GL_PROGRAM_POINT_SIZE);
            glDisable(GL_PROGRAM_POINT_SIZE);
            glPointSize(0);
            //            glPointParameteri();
            //            glPointParameteriv();
            //            glPointParameterf();
            //            glPointParameterfv();

                        // line segments
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(1.0f);

            // polygons
            glEnable(GL_POLYGON_SMOOTH);

            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CCW);
            glCullFace(GL_FRONT_AND_BACK);

            // polygon rast & depth offset
            glEnable(GL_POLYGON_OFFSET_FILL);
            glEnable(GL_POLYGON_OFFSET_LINE);
            glEnable(GL_POLYGON_OFFSET_POINT);
            glEnable(GL_POLYGON_SMOOTH);
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            //glPolygonOffsetClamp();
            glPolygonOffset(1.2f, 0);

        }

        // pre frag operations
        {

            // scissor test
            glEnable(GL_SCISSOR_TEST);
            glDisable(GL_SCISSOR_TEST);

            glEnablei(GL_SCISSOR_TEST, 0);
            glDisablei(GL_SCISSOR_TEST, 0);
            glScissor(0, 0, 0, 0);
            glScissorArrayv(0, 100, nullptr);
            //glScissorIndexed();
            //glScissorIndexedv();

            // multisample fragment ops

        }

        // fragment shading
        {

        }

        glEnable(GL_SAMPLE_COVERAGE);

        // alpha to coverage
        {
            glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
            glEnable(GL_SAMPLE_ALPHA_TO_ONE); // or
        }
        // Stencil test
        {
            // do stencil test and update the stencil buffer
            glEnable(GL_STENCIL_TEST);
            gl_stencil_func _stencil_func;
            //glStencilFunc(_stencil_func, 0, 1); // set front-face and back-face function and
            glStencilFuncSeparate(static_cast<GLenum>(_stencil_func), static_cast<GLenum>(_stencil_func), 0, 1);

            gl_stencil_op _stencil_op;
            // stencil test fail , stencil stencil test pass but depth test fail, both pass
           // glStencilOpSeparate(GL_FRONT, _stencil_op, _stencil_op, _stencil_op);
           // glStencilOpSeparate(GL_BACK, _stencil_op, _stencil_op, _stencil_op);
           // glStencilOpSeparate(GL_FRONT_AND_BACK, _stencil_op, _stencil_op, _stencil_op);
            //glStencilOp(_stencil_op, _stencil_op, _stencil_op);
            glStencilMaskSeparate(GL_FRONT, 1);
            glStencilMaskSeparate(GL_BACK, 1);
            glStencilMaskSeparate(GL_FRONT_AND_BACK, 1);
            //glStencilMask(1);
        }
        // Depth test
        {
            glEnable(GL_DEPTH_TEST);
            //glDepthFunc(df_never);
        }
        // occlusion queries
        {

        }
        // blending
        {
            glEnable(GL_BLEND);
            //            glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
            //            glBlendFunc();
            //            glBlendFuncSeparate();
            //            glBlendFunci();
            //            glBlendFuncSeparatei();
            //            glBlendEquation();
            //            glBlendEquationi();
            //            glBlendEquationSeparate();
            //            glBlendEquationSeparatei();
        }
        // sRGB Conversion
        {
            glEnable(GL_FRAMEBUFFER_SRGB);

        }
        //Dithering
        {
            glEnable(GL_DITHER);
        }
        // color logic operations
        {

            gl_logic_op _logic_op;
            glEnable(GL_COLOR_LOGIC_OP);
            glDisable(GL_COLOR_LOGIC_OP);
            glLogicOp(static_cast<GLenum>(_logic_op));
        }
        // additional multisample fragment operations
        {
            glEnable(GL_MULTISAMPLE);
            //glSampleCoverage();
        }

        glEnable(GL_SAMPLE_MASK);
        //glSampleMaski();

        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    }

};

/*
 * graphics pipeline : 
 * vertex shader [+ tessellation control shader + tessellation evaluation shader] [+ geometry shader] + fragment shader
 * */
class gl_graphics_pipeline : public gl_pipeline
{
public:
    gl_graphics_pipeline(glsl_vertex_shader* vs, glsl_fragment_shader* fs) :
        _program(nullptr)
    {
        gl_vertex_launcher_descriptor _descriptor;
        _vertex_launcher = new gl_vertex_launcher(_descriptor);
        _program = new glsl_graphics_pipeline_program(vs, fs);
        _render_target = new gl_render_target();
        _program->load();
    }

    gl_graphics_pipeline(glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_fragment_shader* fs) 
    {
        gl_vertex_launcher_descriptor _descriptor;
        _vertex_launcher = new gl_vertex_launcher(_descriptor);
        _program = new glsl_graphics_pipeline_program(vs, ts, fs);
        _render_target = new gl_render_target();
        _program->load();
    }

    gl_graphics_pipeline(glsl_vertex_shader* vs, glsl_geometry_shader* gs, glsl_fragment_shader* fs) 
    {
        gl_vertex_launcher_descriptor _descriptor;
        _vertex_launcher = new gl_vertex_launcher(_descriptor);
        _program = new glsl_graphics_pipeline_program(vs, gs, fs);
        _render_target = new gl_render_target();
        _program->load();
    }

    gl_graphics_pipeline(glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_geometry_shader* gs, glsl_fragment_shader* fs) 
    {
        gl_vertex_launcher_descriptor _descriptor;
        _descriptor.primitive_mode = gl_primitive_mode::TRIANGLES;
        _descriptor.primitive_vertices_num = 3;
        _vertex_launcher = new gl_vertex_launcher(_descriptor);
        _program = new glsl_graphics_pipeline_program(vs, ts, gs, fs);
        _render_target = new gl_render_target();
        _program->load();
    }

    gl_graphics_pipeline(const gl_graphics_pipeline&) = delete;
    gl_graphics_pipeline& operator=(const gl_graphics_pipeline&) = delete;

    ~gl_graphics_pipeline()
    {
        if (!_vertex_launcher) delete _vertex_launcher;
        if (!_transform_feedback) delete _transform_feedback;
        if (!_program) delete _program;
        if (!_render_target) delete _render_target;
    }

public:

    /*
    * Make sure all commands for this pipeline can work.
    * Between this range, many commands can be called.
    */
    void enable() noexcept
    {
        if (!_program) return;
        _vertex_launcher->bind();
    }

    /*
    * Make sure all commands for this pipeline can not work.
    * Clear all context.
    */
    void disable() noexcept
    {
        if (!_program) return;
    }

public: // non-draw commands 

    void begin_transform_feedback()
    {
        if (!_vertex_launcher || !_transform_feedback) return;
        gl_primitive_mode _TransformFeedbackPrimitiveMode = _vertex_launcher->get_primitive_mode();
        _transform_feedback->begin_transform_feedback(_TransformFeedbackPrimitiveMode);
    }

    void pause_transform_feedback()
    {
        if (!_vertex_launcher || !_transform_feedback) return;
        _transform_feedback->pause_transform_feedback();
    }

    void resume_transform_feedback()
    {
        if (!_vertex_launcher || !_transform_feedback) return;
        _transform_feedback->resume_transform_feedback();
    }

    void end_transform_feedback()
    {
        if (!_vertex_launcher || !_transform_feedback) return;
        _transform_feedback->end_transform_feedback();
    }

    void begin_conditional_render()
    {
        glBeginConditionalRender(0, GL_QUERY_WAIT);
    }

    void end_conditional_render()
    {
        glEndConditionalRender();
    }

public:

    /*
    * draw vertex array by vertex_offset and vertices_num
    */
    std::shared_ptr<gl_fence> draw_arrays(uint32 vertex_offset, uint32 vertices_num)
    {
        if (!_vertex_launcher || vertex_offset + vertices_num >= _vertex_launcher->get_vertices_num()) return nullptr;
        glDrawArrays(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), vertex_offset, vertices_num);
        return std::make_shared<gl_fence>();
    }

    /*
    * draw vertex array by vertex_offset and vertices_num
    * draw number of instances, and specify where instance attribute will effect vertex 
    */
    std::shared_ptr<gl_fence> draw_arrays(uint32 vertex_offset, uint32 vertices_num, uint32 instances_num, uint32 base_instance) const
    {
        if (!_vertex_launcher || vertex_offset + vertices_num >= _vertex_launcher->get_vertices_num()) return nullptr;
        if (base_instance >= instances_num) return nullptr;
        glDrawArraysInstancedBaseInstance(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), vertex_offset, vertices_num, instances_num, base_instance);
        return std::make_shared<gl_fence>();
    }
    
    /*
    * draw vertex array by indrect command
    */
    std::shared_ptr<gl_fence> draw_arrays(const gl_draw_arrays_indirect_command& command) const
    {
        glDrawArraysIndirect(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), (const void*)&command);
        return std::make_shared<gl_fence>();
    }

    /*
    * multi draw vertex array by vertex_offset and vertices_num pairs
    * multi drawing can not support instanced drawing.
    */
    std::shared_ptr<gl_fence> multi_draw_arrays(const std::vector<uint32>& vertex_offsets, const std::vector<uint32>& vertices_nums) const
    {
        if (!_vertex_launcher) return nullptr;
        if (vertex_offsets.size() != vertices_nums.size()) return nullptr;
        glMultiDrawArrays(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            (const int32*)vertex_offsets.data(), (const int32*)vertices_nums.data(), vertex_offsets.size()
        );
        return std::make_shared<gl_fence>();
    }

    /*
    * multi draw vertex array by indrect command
    */
    std::shared_ptr<gl_fence> multi_draw_arrays(const std::vector<gl_draw_arrays_indirect_command>& commands) const
    {
        //glMultiDrawArraysIndirect()
        return std::make_shared<gl_fence>();
    }

    /*
    * draw vertex array according to element array by element_offset and elements_num
    */
    std::shared_ptr<gl_fence> draw_elements(uint32 element_offset, uint32 elements_num) const
    {
        if (element_offset + elements_num >= _vertex_launcher->get_elements_num()) return nullptr;
        glDrawElements(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()),
            (void*)(_vertex_launcher->get_element_size() * element_offset)
        );
        return std::make_shared<gl_fence>();
    }

    std::shared_ptr<gl_fence> draw_elements(uint32 element_offset, uint32 elements_num, uint32 instances_num, uint32 base_instance) const
    {
        if (!_vertex_launcher) return nullptr;
        glDrawElementsInstancedBaseInstance(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            instances_num, base_instance
        );
        return std::make_shared<gl_fence>();
    }

    std::shared_ptr<gl_fence> draw_elements(uint32 element_offset, uint32 elements_num, uint32 base_vertex) const
    {
        if (!_vertex_launcher) return nullptr;
        glDrawElementsBaseVertex(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            base_vertex
        );
        return std::make_shared<gl_fence>();
    }

    std::shared_ptr<gl_fence> draw_elements(uint32 element_offset, uint32 elements_num, uint32 base_vertex, uint32 instances_num, uint32 base_instance) const
    {
        if (!_vertex_launcher) return nullptr;
        glDrawElementsInstancedBaseVertexBaseInstance(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            instances_num, base_vertex, base_instance
        );
        return std::make_shared<gl_fence>();
    }

    std::shared_ptr<gl_fence> draw_elements(const gl_draw_elements_indirect_command& command) const
    {
        glDrawElementsIndirect(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            static_cast<GLenum>(_vertex_launcher->get_element_type()),
            (const void*)&command
        );
        return std::make_shared<gl_fence>();
    }

    std::shared_ptr<gl_fence> draw_range_elements(uint32 element_start, uint32 element_end, uint32 element_offset, uint32 elements_num, uint32 base_vertex) const
    {
        if (!_vertex_launcher) return nullptr;
        glDrawRangeElementsBaseVertex(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            element_start, element_end,
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            base_vertex
        );
        return std::make_shared<gl_fence>();
    }

    std::shared_ptr<gl_fence> multi_draw_elements(const std::vector<uint32>& element_offsets, std::vector<uint32>& elements_nums) const
    {
        if (!_vertex_launcher) return nullptr;
        glMultiDrawElements(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), (const int32*)elements_nums.data(),
            static_cast<GLenum>(_vertex_launcher->get_element_type()),
            nullptr, element_offsets.size()
        );
        return std::make_shared<gl_fence>();
    }

    std::shared_ptr<gl_fence> multi_draw_elements(const std::vector<gl_draw_elements_indirect_command>& commands) const
    {
        return std::make_shared<gl_fence>();
    }

    std::shared_ptr<gl_fence> draw_transform_feedback(uint32 stream_Index = 0)
    {
        if (!_vertex_launcher || !_transform_feedback) return nullptr;
        _transform_feedback->draw(_vertex_launcher->get_primitive_mode(), stream_Index);
        return std::make_shared<gl_fence>();
    }

    std::shared_ptr<gl_fence> draw_transform_feedback(uint32 stream_index, uint32 instances_num)
    {
        if (!_vertex_launcher || !_transform_feedback) return nullptr;
        gl_primitive_mode _TransformFeedbackPrimitiveMode = _vertex_launcher->get_primitive_mode();
        _transform_feedback->draw(_TransformFeedbackPrimitiveMode, stream_index, instances_num);
        return std::make_shared<gl_fence>();
    }

public:

    gl_vertex_launcher& vertex_launcher() { return *_vertex_launcher; }

    glsl_graphics_pipeline_program& program() { return *_program; }

    gl_render_target& render_target() { return *_render_target; }

private:

    gl_vertex_launcher* _vertex_launcher;

    gl_transform_feedback* _transform_feedback;

    glsl_graphics_pipeline_program* _program;

    gl_render_target* _render_target;

};


#define DEFINE_GRAPHICS_PIPELINE_PARAMETERS(PIPELINE_NAME)\
struct gl_##PIPELINE_NAME##_graphics_pipeline_parameters : public gl_graphics_pipeline_parameters\

#define CLASS_NAME(__CLASS__)  #__CLASS__



#define DEFINE_PROGRAM_PARAMETER_IMAGE(GLSL_IMAGE_T, V_NAME) \
glsl_##GLSL_IMAGE_T V_NAME{CLASS_NAME(V_NAME)};\

#define DEFINE_PROGRAM_PARAMETER_SAMPLER(GLSL_SAMPLER_T, V_NAME)\
glsl_##GLSL_SAMPLER_T V_NAME;\


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
#define SHADER_PARAMETER_REF(TOKEN_NAME)\

#define INPUT_STREAM() \

#define OUTPUT_STREAM() \

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

