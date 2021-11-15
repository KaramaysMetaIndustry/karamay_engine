#ifndef GRAPHICS_PIPELINE_H
#define GRAPHICS_PIPELINE_H

#include "graphics/glsl/glsl_program.h"
#include "graphics/resource/program/gl_program.h"
#include "graphics/resource/vertex_launcher/gl_vertex_launcher.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_uniform_buffer.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_shader_storage_buffer.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_atomic_counter_buffer.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_transform_feedback_buffer.h"
#include "graphics/resource/buffers/indirect_buffer/gl_draw_indirect_buffer.h"

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
struct GraphicsPipelineState
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

    void reset();
};

/*
 * descriptor for graphics pipeline construction
 * */
struct GraphicsPipelineDescriptor{
    std::string Name;
    std::string OwnerRendererDir;
    // [must have] vertex stream which input into program by vertex puller
   SharedPtr<VertexLauncher> VertexLauncher;
    // [must have] program body
    SharedPtr<GraphicsPipelineProgram> Program;
    // [optional] transform feedback 
    SharedPtr<TransformFeedback> TransformFeedback;
    // [must have] where program final color output
    SharedPtr<Framebuffer> RenderTarget;
    // [must have] pipeline state
    SharedPtr<GraphicsPipelineState> State;
};

/*
 * graphics pipeline
 * vertex shader [+ tessellation control shader + tessellation evaluation shader] [+ geometry shader] + fragment shader
 * */
class GraphicsPipeline{
public:
    GraphicsPipeline() = default;
    GraphicsPipeline(const GraphicsPipelineDescriptor& Descriptor)
    {
    }
    GraphicsPipeline(const GraphicsPipeline&) = delete;
    GraphicsPipeline& operator=(const GraphicsPipeline&) = delete;

    ~GraphicsPipeline() = default;
   
public:

    /*
    * Make sure all commands for this pipeline can work.
    * Between this range, many commands can be called.
    */
    void Enable() noexcept
    {
        if (!_Program) return;
        _Program->enable();
        _BindResources();
    }

    /*
    * Make sure all commands for this pipeline can not work.
    * Clear all context.
    */
    void Disable() noexcept
    {
        if (!_Program) return;
        _UnbindResources();
        _Program->disable();
    }

public: // non-draw commands 

    void BeginTransformFeedback()
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;
        auto _TransformFeedback = _Descriptor.TransformFeedback;

        if (!_VertexLauncher || !_TransformFeedback) return;
        PrimitiveMode _TransformFeedbackPrimitiveMode = _VertexLauncher->GetPrimitiveMode();
        _TransformFeedback->BeginTransformFeedback(_TransformFeedbackPrimitiveMode);
    }

    void PauseTransformFeedback()
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;
        auto _TransformFeedback = _Descriptor.TransformFeedback;

        if (!_VertexLauncher || !_TransformFeedback) return;
        _TransformFeedback->PauseTransformFeedback();
    }

    void ResumeTransformFeedback()
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;
        auto _TransformFeedback = _Descriptor.TransformFeedback;

        if (!_VertexLauncher || !_TransformFeedback) return;
        _TransformFeedback->ResumeTransformFeedback();
    }

    void EndTransformFeedback()
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;
        auto _TransformFeedback = _Descriptor.TransformFeedback;

        if (!_VertexLauncher || !_TransformFeedback) return;
        _TransformFeedback->EndTransformFeedback();
    }

    void BeginConditionalRender()
    {
        glBeginConditionalRender(0, GL_QUERY_WAIT);
    }

    void EndConditionalRender()
    {
        glEndConditionalRender();
    }

public: // draw commands

    void DrawArrays(UInt32 VertexOffset, UInt32 VerticesNum) const
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;

        if (!_VertexLauncher) return;
        if (VertexOffset + VerticesNum >= _VertexLauncher->GetVerticesNum()) return;

        glDrawArrays(static_cast<GLenum>(_VertexLauncher->GetPrimitiveMode()), VertexOffset, VerticesNum);
    }

    void DrawArrays(UInt32 VertexOffset, UInt32 VerticesNum, UInt32 InstancesNum, UInt32 InstanceOffset) const
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;

        if (!_VertexLauncher) return;
        if (VertexOffset + VerticesNum >= _VertexLauncher->GetVerticesNum()) return;
        if (InstanceOffset >= InstancesNum) return;

        glDrawArraysInstancedBaseInstance(static_cast<GLenum>(_VertexLauncher->GetPrimitiveMode()), VertexOffset, VerticesNum, InstancesNum, InstanceOffset);
    }

    void MultiDrawArrays(const std::vector<UInt32>& VertexOffsets, const std::vector<UInt32>& VerticesNums) const
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;

        if (!_VertexLauncher) return;
        if (VertexOffsets.size() != VerticesNums.size()) return;

        glMultiDrawArrays(static_cast<GLenum>(_VertexLauncher->GetPrimitiveMode()), 
            (const Int32*)VertexOffsets.data(), (const Int32*)VerticesNums.data(), VertexOffsets.size()
        );
    }

    
    void DrawElements(UInt32 ElementOffset, UInt32 ElementsNum) const
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;

        if (ElementOffset + ElementsNum >= _VertexLauncher->GetElementsNum()) return;

        glDrawElements(
            static_cast<GLenum>(_VertexLauncher->GetPrimitiveMode()),
            ElementsNum, static_cast<GLenum>(_VertexLauncher->GetElementType()), 
            (void*)(_VertexLauncher->GetElementSize() * ElementOffset)
        );
    }

    void DrawElements(UInt32 ElementOffset, UInt32 ElementsNum, UInt32 InstancesNum, UInt32 BaseInstance) const
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;

        glDrawElementsInstancedBaseInstance(
            static_cast<GLenum>(_VertexLauncher->GetPrimitiveMode()),
            ElementsNum, static_cast<GLenum>(_VertexLauncher->GetElementType()), (void*)(_VertexLauncher->GetElementSize() * ElementOffset),
            InstancesNum, BaseInstance
        );
    }

    void DrawElements(UInt32 ElementOffset, UInt32 ElementsNum, UInt32 BaseVertex) const
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;

        glDrawElementsBaseVertex(
            static_cast<GLenum>(_VertexLauncher->GetPrimitiveMode()),
            ElementsNum, static_cast<GLenum>(_VertexLauncher->GetElementType()), (void*)(_VertexLauncher->GetElementSize() * ElementOffset),
            BaseVertex
        );
    }

    void DrawElements(UInt32 ElementOffset, UInt32 ElementsNum, UInt32 BaseVertex, UInt32 InstancesNum, UInt32 BaseInstance) const
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;

        glDrawElementsInstancedBaseVertexBaseInstance(
            static_cast<GLenum>(_VertexLauncher->GetPrimitiveMode()),
            ElementsNum, static_cast<GLenum>(_VertexLauncher->GetElementType()), (void*)(_VertexLauncher->GetElementSize() * ElementOffset),
            InstancesNum, BaseVertex, BaseInstance
        );
    }

    void DrawRangeElements(UInt32 ElementStart, UInt32 ElementEnd, UInt32 ElementOffset, UInt32 ElementsNum, UInt32 BaseVertex) const
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;

        glDrawRangeElementsBaseVertex(
            static_cast<GLenum>(_VertexLauncher->GetPrimitiveMode()),
            ElementStart, ElementEnd,
            ElementsNum, static_cast<GLenum>(_VertexLauncher->GetElementType()), (void*)(_VertexLauncher->GetElementSize() * ElementOffset),
            BaseVertex
        );
    }

    void MultiDrawElements(const std::vector<UInt32>& ElementOffsets, std::vector<UInt32>& ElementsNums) const
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;

        glMultiDrawElements(
            static_cast<GLenum>(_VertexLauncher->GetPrimitiveMode()), (const Int32*)ElementsNums.data(),
            static_cast<GLenum>(_VertexLauncher->GetElementType()),
            nullptr, ElementOffsets.size()
        );
    }

    void MultiDrawElements(UInt32 BaseVertex) const
    {
        //glMultiDrawElementsBaseVertex()
    }


    void DrawArrays(const DrawArraysIndirectCommand& Command) const
    {

    }

    void MultiDrawArrays(const std::vector<DrawArraysIndirectCommand>& Commands) const
    {
        //glMultiDrawArraysIndirect();
    }

    void DrawElements(const DrawElementsIndirectCommand& Command) const
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;

        glDrawElementsIndirect(
            static_cast<GLenum>(_VertexLauncher->GetPrimitiveMode()),
            static_cast<GLenum>(_VertexLauncher->GetElementType()),
            (const void*)&Command
        );
    }

    void MultiDrawElements(const std::vector<DrawElementsIndirectCommand>& Commands) const
    {
        //glMultiDrawElementsIndirect();
    }


    void DrawTransformFeedback(UInt32 StreamIndex = 0)
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;
        auto _TransformFeedback = _Descriptor.TransformFeedback;

        if (!_VertexLauncher || !_TransformFeedback) return;

        PrimitiveMode _TransformFeedbackPrimitiveMode = _VertexLauncher->GetPrimitiveMode();
        _TransformFeedback->Draw(_TransformFeedbackPrimitiveMode, StreamIndex);
    }

    void DrawTransformFeedback(UInt32 StreamIndex, UInt32 InstancesNum)
    {
        auto _VertexLauncher = _Descriptor.VertexLauncher;
        auto _TransformFeedback = _Descriptor.TransformFeedback;

        if (!_VertexLauncher || !_TransformFeedback) return;

        PrimitiveMode _TransformFeedbackPrimitiveMode = _VertexLauncher->GetPrimitiveMode();
        _TransformFeedback->Draw(_TransformFeedbackPrimitiveMode, StreamIndex, InstancesNum);
    }

private:

    GraphicsPipelineDescriptor _Descriptor;

    UniquePtr<gl_program> _Program;

    struct gl_graphics_pipeline_resource_pool{
        std::unique_ptr<gl_uniform_buffer> uniform_buffer;
        std::unique_ptr<gl_shader_storage_buffer> shader_storage_buffer;
        std::unique_ptr<gl_atomic_counter_buffer> atomic_counter_buffer;
        std::unique_ptr<gl_draw_indirect_buffer> draw_indirect_buffer;
    } _resource_pool;

private:

    void _BindResources()
    {
        if (_Descriptor.VertexLauncher && _Descriptor.Program && _Descriptor.RenderTarget && _Descriptor.State)
        {
            // bind vertex launcher
            _Descriptor.VertexLauncher->Bind();

            // bind program parameters
            const auto& _program_parameters = _Descriptor.Program->parameters();
            for (const auto& _image : _program_parameters.images)
            {
                if(_image) _image->bind();
            }
            for (const auto& _sampler : _program_parameters.samplers)
            {
                if (_sampler) _sampler->bind();
            }
            if (_resource_pool.uniform_buffer)
            {
                _resource_pool.uniform_buffer->bind();
            }
            if (_resource_pool.shader_storage_buffer)
            {
                _resource_pool.shader_storage_buffer->bind();
            }
            if (_resource_pool.atomic_counter_buffer)
            {
                _resource_pool.atomic_counter_buffer->bind();
            }
           
            // bind transform feedback
           

            // bind framebuffer
            _Descriptor.RenderTarget->bind();

            // set state
            _Descriptor.State->set();
        }
 
    }

    void _UnbindResources()
    {

    }

    void FlushResources()
    {
        GLint MaxVertexAtomicCounterBuffers(0);
        GLint MaxControlAtomicCounterBuffers(0);
        GLint MaxEvaluationAtomicCounterBuffers(0);
        GLint MaxGeometryAtomicCounterBuffers(0);
        GLint MaxFragmentAtomicCounterBuffers(0);
        GLint MaxCombinedAtomicCounterBuffers(0);

        glGetIntegerv(GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS, &MaxVertexAtomicCounterBuffers);
        glGetIntegerv(GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS, &MaxControlAtomicCounterBuffers);
        glGetIntegerv(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS, &MaxEvaluationAtomicCounterBuffers);
        glGetIntegerv(GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS, &MaxGeometryAtomicCounterBuffers);
        glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS, &MaxFragmentAtomicCounterBuffers);
        glGetIntegerv(GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS, &MaxCombinedAtomicCounterBuffers);
    }

};


struct gl_vertex_processing_pipeline_state 
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
                std::uint32_t clip_plane_index{ 0 };
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
};

struct gl_vertex_processing_pipeline_descriptor
{
    // pipeline name
    std::string name;
    // renderer dir
    std::string owner_renderer_dir;

    // pipeline state
    std::shared_ptr<gl_vertex_processing_pipeline_state> state;
    // vertex stream which input into program by vertex puller
    std::shared_ptr<VertexLauncher> vertex_launcher;
    // program body
    std::shared_ptr<glsl_vertex_processing_pipeline_program> program;
    // must have transform feedback 
    std::shared_ptr<TransformFeedback> transform_feedback;
};

/*
 * vertex processing pipeline, optimized for vertex processing.
 * fetch data from transform feedback buffer, after vertex processing, all primitives will be discard.
 * vertex shader [+ tessellation control shader + tessellation evaluation shader] [+geometry shader]
 * */
class gl_vertex_processing_pipeline{
public:
    gl_vertex_processing_pipeline() = default;
    gl_vertex_processing_pipeline(const gl_vertex_processing_pipeline_descriptor& descriptor) {}
    gl_vertex_processing_pipeline(const gl_vertex_processing_pipeline&) = delete;
    gl_vertex_processing_pipeline& operator=(const gl_vertex_processing_pipeline&) = delete;

    ~gl_vertex_processing_pipeline() = default;

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

