#ifndef GRAPHICS_PIPELINE_H
#define GRAPHICS_PIPELINE_H

#include "base/gl_pipeline.h"
#include "graphics/renderer/pipeline/base/resource/buffers/common_buffer/gl_element_array_buffer.h"

struct gl_draw_arrays_indirect_command {
    uint32  count;
    uint32  primCount;
    uint32  first;
    uint32  baseInstance;
};

struct gl_draw_elements_indirect_command {
    uint32 count;
    uint32 primCount;
    uint32 firstIndex;
    uint32 baseVertex;
    uint32 baseInstance;
};

struct gl_vertex_launcher_descriptor
{
    gl_primitive_mode primitive_mode;
    uint32 primitive_vertices_num; // IndicesNum % PrimitiveVerticesNum == 0

    gl_vertex_array_descriptor vertex_array_descriptor;
    uint32 elements_num;
};

class gl_vertex_launcher
{
public:
    using vertex_slot_reader = gl_vertex_array::vertex_slot_reader;
    using vertex_slot_writer = gl_vertex_array::vertex_slot_writer;
    using vertex_slot_handler = gl_vertex_array::vertex_slot_handler;
    using instance_attribute_slot_reader = gl_vertex_array::instance_attribute_slot_reader;
    using instance_attribute_slot_writer = gl_vertex_array::instance_attribute_slot_writer;
    using instance_attribute_slot_handler = gl_vertex_array::instance_attribute_slot_handler;
    using element_slot_reader = gl_element_array_buffer::element_buffer_reader;
    using element_slot_writer = gl_element_array_buffer::element_buffer_writer;
    using element_slot_handler = gl_element_array_buffer::element_buffer_handler;

    gl_vertex_launcher(const gl_vertex_launcher_descriptor& descriptor) :
        _primitive_mode(descriptor.primitive_mode),
        _primitive_vertices_num(descriptor.primitive_vertices_num),
        _vertex_array(), _element_array_buffer()
    {
        gl_vertex_array_descriptor _des;
        _vertex_array.reset(new gl_vertex_array(_des));
        _element_array_buffer.reset(new gl_element_array_buffer(gl_element_type::UNSIGNED_BYTE, descriptor.elements_num));
    }

    gl_vertex_launcher(const gl_vertex_launcher&) = delete;
    gl_vertex_launcher& operator=(const gl_vertex_launcher&) = delete;

    ~gl_vertex_launcher() = default;

public:


private:

    void _set_state()
    {
        _enable_primitive_restart ? glEnable(GL_PRIMITIVE_RESTART) : glDisable(GL_PRIMITIVE_RESTART);
        _use_fixed_primitive_restart_index ? glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX) : glDisable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
        //glPrimitiveRestartIndex(0);
        
    }

    bool _enable_primitive_restart;
    bool _use_fixed_primitive_restart_index;

public:

    uint32 get_vertices_num() const { return _vertex_array ? _vertex_array->get_vertices_num() : 0; }

    uint32 get_vertex_size() const { return _vertex_array ? _vertex_array->get_vertex_size() : 0; }

    /*
    * you must describe a vertex size
    * you can only respecify a new VerticesNum, cause VertexSize, Layout can not be modified
    * this action will consume quite time
    */
    void reallocate_vertex_slot(uint32 vertices_num, const void* initial_vertices = nullptr) noexcept
    {
        if (!_vertex_array) return;
        _vertex_array->reallocate_vertex_slot(vertices_num);
    }

    const void* read_vertex_slot(uint32 vertex_offset, uint32 vertices_num)
    {
        return _vertex_array ? _vertex_array->read_vertex_slot(vertex_offset, vertices_num) : nullptr;
    }

    void write_vertex_slot(uint32 vertex_offset, uint32 vertices_num, const void* vertices)
    {
        if (!_vertex_array) return;

        _vertex_array->write_vertex_slot(vertex_offset, vertices_num, vertices);
    }

    void execute_mapped_vertex_slot_reader(uint32 vertex_offset, uint32 vertices_num, const vertex_slot_reader& reader)
    {

    }

    void execute_mapped_vertex_slot_writer(uint32 vertex_offset, uint32 vertices_num, const vertex_slot_writer& writer)
    {}

    void execute_mapped_vertex_slot_handler(uint32 vertex_offset, uint32 vertices_num, const vertex_slot_handler& handler)
    {}

public:

    uint32 get_instance_attributes_num(const std::string& attribute_name) const {}

    uint32 get_instance_attribute_size(const std::string& attribute_name) const {}

    void reallocate_instance_attribute_slot(const std::string& attribute_name, uint32 attributes_num, uint32 divisor, const void* initial_attributes) noexcept
    {
        if (!_vertex_array) return;
        _vertex_array->reallocate_instance_attribute_slot(0, attributes_num, divisor, initial_attributes);
    }

    const void* read_instance_attribute_slot() {}

    void write_instance_attribute_slot() {}

    void execute_mapped_instance_attribute_slot_reader(const std::string& attribute_name, uint32 attribute_offset, uint32 attributes_num, const instance_attribute_slot_reader& reader)
    {}

    void execute_mapped_instance_attribute_slot_writer(const std::string& attribute_name, uint32 attribute_offset, uint32 attributes_num, const instance_attribute_slot_writer& writer)
    {}

    void execute_mapped_instance_attribute_slot_handler(const std::string& attribute_name, uint32 attribute_offset, uint32 attributes_num, const instance_attribute_slot_handler& handler)
    {}

public:

    uint32 get_elements_num() const { return _element_array_buffer ? _element_array_buffer->get_elements_num() : 0; }

    uint32 get_element_size() const { return _element_array_buffer ? _element_array_buffer->get_element_size() : 0; }

    gl_element_type get_element_type() const { return _element_array_buffer ? _element_array_buffer->get_element_type() : gl_element_type::NONE; }

    /*
    * Indices only associates to PrimitiveMode
    * PrimitiveMode will never change once lancher constructed
    * IndicesNum % PrimitiveVerticesNum = 0
    */
    void reallocate_element_slot(uint32 elements_num, const void* initial_elements = nullptr) noexcept
    {
        if (!_element_array_buffer) return;
        if (elements_num % _primitive_vertices_num != 0) return;

        _element_array_buffer->reallocate(elements_num, initial_elements);
    }

    void execute_mapped_element_slot_reader(uint32 element_offset, uint32 elements_num, const element_slot_reader& reader)
    {
        if (!_element_array_buffer) return;
        _element_array_buffer->execute_mapped_element_buffer_reader(element_offset, elements_num, reader);
    }

    void execute_mapped_element_slot_writer(uint32 element_offset, uint32 elements_num, const element_slot_writer& writer)
    {
        if (!_element_array_buffer) return;
        _element_array_buffer->execute_mapped_element_buffer_writer(element_offset, elements_num, writer);
    }

    void execute_mapped_element_slot_handler(uint32 element_offset, uint32 elements_num, const element_slot_handler& handler)
    {
        if (!_element_array_buffer) return;
        _element_array_buffer->execute_mapped_element_buffer_handler(element_offset, elements_num, handler);
    }

    void set_primitive_restart_flag_element(uint32 element_offset)
    {
        if (!_element_array_buffer) return;
        _element_array_buffer->set_primitive_restart_flag_element(element_offset);
    }

    const std::vector<uint32>& get_primitive_restart_flag_element_indices() const
    {
    }

public:

    void bind() const noexcept
    {
        if (_vertex_array) _vertex_array->bind();
        if (_element_array_buffer) _element_array_buffer->bind();
    }

    void unbind() const noexcept
    {
        if (_vertex_array) _vertex_array->unbind();
        if (_element_array_buffer) _element_array_buffer->unbind();
    }

public:

    gl_primitive_mode get_primitive_mode() const { return _primitive_mode; }

private:

    gl_primitive_mode _primitive_mode;

    uint32 _primitive_vertices_num;

    std::unique_ptr<gl_vertex_array> _vertex_array;

    std::unique_ptr<gl_element_array_buffer> _element_array_buffer;

};

class gl_render_target
{
public:

    gl_render_target() : _framebuffer(nullptr)
    {}

    gl_render_target(const gl_render_target&) = delete;
    gl_render_target& operator=(const gl_render_target&) = delete;

    ~gl_render_target() {}

public:

    void set_framebuffer(gl_framebuffer* framebuffer) { _framebuffer = framebuffer; }

    gl_framebuffer* get_framebuffer() const { return _framebuffer; }

    void set_default() { _framebuffer = nullptr; }

public:

    void bind()
    {
        if (_framebuffer)
        {
            _framebuffer->bind();
        }
        else {
            gl_default_framebuffer::get_instance()->bind();
        }
    }

    void unbind()
    {
        if (_framebuffer)
        {
            _framebuffer->unbind();
        }
        else {
            gl_default_framebuffer::get_instance()->unbind();
        }
    }

private:

    gl_framebuffer* _framebuffer;

};

enum class gl_stencil_op : GLenum
{
	KEEP = GL_KEEP, 
	ZERO = GL_ZERO,
	REPLACE = GL_REPLACE,
	INCR = GL_INCR,
	INCR_WRAP = GL_INCR_WRAP,
	DECR = GL_DECR,
    DECR_WRAP = GL_DECR_WRAP,
	INVERT = GL_INVERT
};
enum class gl_stencil_func : GLenum
{
	NEVER = GL_NEVER, // fail
	ALWAYS = GL_ALWAYS, // pass
	LESS = GL_LESS, // <
	LEQUAL = GL_LEQUAL, // <=
	GREATER = GL_GREATER, // >
	GEQUAL = GL_GEQUAL, // >=
	EQUAL = GL_EQUAL, // ==
	NOTEQUAL = GL_NOTEQUAL // !=
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
enum class gl_cull_face : GLenum
{
    FRONT = GL_FRONT, 
    BACK = GL_BACK, // default
    FRONT_AND_BACK = GL_FRONT_AND_BACK
};
enum class gl_depth_func : GLenum
{
    NEVER = GL_NEVER, // fail
    ALWAYS = GL_ALWAYS, // pass
    LESS = GL_LESS, // <
    EQUAL = GL_EQUAL, // ==
    LEQUAL = GL_LEQUAL, // <=
    GREATER = GL_GREATER, // >
    NOTEQUAL = GL_NOTEQUAL, // !=
    GEQUAL = GL_GEQUAL // >=
};
enum class gl_blend_func_factor : GLenum
{
    ZERO = GL_ZERO,
    ONE = GL_ONE,
    SRC_COLOR = GL_SRC_COLOR,
    ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
    DST_COLOR = GL_DST_COLOR,
    ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
    SRC_ALPHA = GL_SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
    DST_ALPHA = GL_DST_ALPHA,
    ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
    CONSTANT_COLOR = GL_CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
};
enum class gl_clip_control_origin : GLenum
{
    LOWER_LEFT = GL_LOWER_LEFT,
    UPPER_LEFT = GL_UPPER_LEFT
};
enum class gl_clip_control_depth_mode : GLenum
{
    NEGATIVE_ONE_TO_ONE = GL_NEGATIVE_ONE_TO_ONE,
    ZERO_TO_ONE = GL_ZERO_TO_ONE
};
enum class gl_provoke_mode : GLenum
{
    FIRST_VERTEX_CONVENTION = GL_FIRST_VERTEX_CONVENTION,
    LAST_VERTEX_CONVENTION = GL_LAST_VERTEX_CONVENTION
};
enum class gl_front_face_mode : GLenum
{
    CW = GL_CW,
    CCW = GL_CCW
};
enum class gl_polygon_mode : GLenum
{
    POINT = GL_POINT,
    LINE = GL_POINT,
    FILL = GL_FILL
};

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
                gl_clip_control_origin clip_control_origin{ gl_clip_control_origin::LOWER_LEFT };
                gl_clip_control_depth_mode clip_control_depth_mode{};
                double near_clipping_distance, far_clipping_distance;
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

};


/*
 * graphics pipeline : 
 * vertex shader + fragment shader
 * vertex shader + tessellation control shader + tessellation evaluation shader + fragment shader
 * vertex shader + geometry shader + fragment shader
 * vertex shader + tessellation control shader + tessellation evaluation shader + geometry shader + fragment shader
 * 
 * vertex shader
 * vertex shader + tessellation control shader + tessellation evaluation shader
 * vertex shader + geometry shader
 * vertex shader + tessellation control shader + tessellation evaluation shader + geometry shader
 * */
class gl_graphics_pipeline : public gl_pipeline
{
public:
    gl_graphics_pipeline(glsl_vertex_shader* vs, glsl_fragment_shader* fs) :
        _program(nullptr),
        _vertex_launcher(nullptr),
        _render_target(nullptr),
        _transform_feedback(nullptr)
    {
        _program = new glsl_graphics_pipeline_program(vs, fs);
        _program->load();

        gl_vertex_launcher_descriptor _descriptor;
        _vertex_launcher = new gl_vertex_launcher(_descriptor);

        _render_target = new gl_render_target();
    }

    gl_graphics_pipeline(glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_fragment_shader* fs) :
        _program(nullptr),
        _vertex_launcher(nullptr),
        _render_target(nullptr),
        _transform_feedback(nullptr)
    {
        _program = new glsl_graphics_pipeline_program(vs, ts, fs);
        _program->load();

        gl_vertex_launcher_descriptor _descriptor;
        _vertex_launcher = new gl_vertex_launcher(_descriptor);
        
        _render_target = new gl_render_target();
    }

    gl_graphics_pipeline(glsl_vertex_shader* vs, glsl_geometry_shader* gs, glsl_fragment_shader* fs) :
        _program(nullptr),
        _vertex_launcher(nullptr),
        _render_target(nullptr),
        _transform_feedback(nullptr)
    {
        _program = new glsl_graphics_pipeline_program(vs, gs, fs);
        _program->load();

        gl_vertex_launcher_descriptor _descriptor;
        _vertex_launcher = new gl_vertex_launcher(_descriptor);
        
        _render_target = new gl_render_target();
    }

    gl_graphics_pipeline(glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_geometry_shader* gs, glsl_fragment_shader* fs) :
        _program(nullptr),
        _vertex_launcher(nullptr),
        _render_target(nullptr),
        _transform_feedback(nullptr)
    {
        _program = new glsl_graphics_pipeline_program(vs, ts, gs, fs);
        _program->load();

        gl_vertex_launcher_descriptor _descriptor;
        _descriptor.primitive_mode = gl_primitive_mode::TRIANGLES;
        _descriptor.primitive_vertices_num = 3;
        _vertex_launcher = new gl_vertex_launcher(_descriptor);

        _render_target = new gl_render_target();
    }

    gl_graphics_pipeline(const gl_graphics_pipeline&) = delete;
    gl_graphics_pipeline& operator=(const gl_graphics_pipeline&) = delete;

    ~gl_graphics_pipeline()
    {
#ifdef _DEBUG
        if (!_program || !_vertex_launcher || !_render_target) throw std::exception("these must not be nullptr");
#endif // !_DEBUG
        delete _program;
        delete _vertex_launcher;
        if (!_transform_feedback) delete _transform_feedback;
        delete _render_target;
    }

public:

    /*
    * Make sure all commands for this pipeline can work.
    * Between this range, many commands can be called.
    */
    void enable()
    {
#ifdef _DEBUG
        if (!_program || !_vertex_launcher || !_render_target)
            throw std::exception("vertex launcher, program, render target must not be nullptr");
#endif // _DEBUG
        _program->enable();
        _vertex_launcher->bind();
        if (_transform_feedback)
        {
            _transform_feedback->bind();
        }
        _render_target->bind();

        _set_pipeline_state();
    }

    /*
    * Make sure all commands for this pipeline can not work.
    * Clear all context.
    */
    void disable()
    {
#ifdef _DEBUG
        if (!_program || !_vertex_launcher || !_render_target)
            throw std::exception("vertex launcher, program, render target must not be nullptr");
#endif // _DEBUG
        _render_target->unbind();
        if (_transform_feedback)
        {
            _transform_feedback->unbind();
        }
        _vertex_launcher->unbind();
        _program->disable();
    }

public:

    /*
    * ref the program body
    * you can dynamic link or unlink program parameters' resource
    */
    glsl_graphics_pipeline_program& program()
    {
#ifdef _DEBUG
        if (!_program) throw std::exception("program must not be nullptr");
#endif
        return *_program;
    }

    /*
    * ref the vertex launcher
    * you should combine and send vertex data to program
    */
    gl_vertex_launcher& vertex_launcher()
    {
#ifdef _DEBUG
        if (!_vertex_launcher) throw std::exception("vertex launcher must not be nullptr");
#endif
        return *_vertex_launcher;
    }

    /*
    * ref the render target
    * you can set final target (device framebuffer / custom framebuffer) the renderer render to
    */
    gl_render_target& render_target()
    {
#ifdef _DEBUG
        if (!_render_target) throw std::exception("render target must not be nullptr");
#endif
        return *_render_target;
    }

private:

    glsl_graphics_pipeline_program* _program;
    gl_vertex_launcher* _vertex_launcher;
    gl_render_target* _render_target;
    gl_transform_feedback* _transform_feedback;

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
    sptr<gl_fence> draw_arrays(uint32 vertex_offset, uint32 vertices_num)
    {
        if (!_vertex_launcher || vertex_offset + vertices_num >= _vertex_launcher->get_vertices_num()) return nullptr;
        glDrawArrays(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), vertex_offset, vertices_num);
        return std::make_shared<gl_fence>();
    }

    /*
    * draw vertex array by vertex_offset and vertices_num
    * draw number of instances, and specify where instance attribute will effect vertex 
    */
    sptr<gl_fence> draw_arrays(uint32 vertex_offset, uint32 vertices_num, uint32 instances_num, uint32 base_instance) const
    {
        if (!_vertex_launcher || vertex_offset + vertices_num >= _vertex_launcher->get_vertices_num()) return nullptr;
        if (base_instance >= instances_num) return nullptr;
        glDrawArraysInstancedBaseInstance(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), vertex_offset, vertices_num, instances_num, base_instance);
        return std::make_shared<gl_fence>();
    }
    
    /*
    * draw vertex array by indrect command
    */
    sptr<gl_fence> draw_arrays(const gl_draw_arrays_indirect_command& command) const
    {
        glDrawArraysIndirect(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), (const void*)&command);
        return std::make_shared<gl_fence>();
    }

    /*
    * multi draw vertex array by vertex_offset and vertices_num pairs
    * multi drawing can not support instanced drawing.
    */
    sptr<gl_fence> multi_draw_arrays(const std::vector<uint32>& vertex_offsets, const std::vector<uint32>& vertices_nums) const
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
    sptr<gl_fence> multi_draw_arrays(const std::vector<gl_draw_arrays_indirect_command>& commands) const
    {
        //glMultiDrawArraysIndirect()
        return std::make_shared<gl_fence>();
    }

    /*
    * draw vertex array according to element array by element_offset and elements_num
    */
    sptr<gl_fence> draw_elements(uint32 element_offset, uint32 elements_num) const
    {
        if (element_offset + elements_num >= _vertex_launcher->get_elements_num()) return nullptr;
        glDrawElements(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()),
            (void*)(_vertex_launcher->get_element_size() * element_offset)
        );
        return std::make_shared<gl_fence>();
    }

    sptr<gl_fence> draw_elements(uint32 element_offset, uint32 elements_num, uint32 instances_num, uint32 base_instance) const
    {
        if (!_vertex_launcher) return nullptr;
        glDrawElementsInstancedBaseInstance(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            instances_num, base_instance
        );
        return std::make_shared<gl_fence>();
    }

    sptr<gl_fence> draw_elements(uint32 element_offset, uint32 elements_num, uint32 base_vertex) const
    {
        if (!_vertex_launcher) return nullptr;
        glDrawElementsBaseVertex(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            base_vertex
        );
        return std::make_shared<gl_fence>();
    }

    sptr<gl_fence> draw_elements(uint32 element_offset, uint32 elements_num, uint32 base_vertex, uint32 instances_num, uint32 base_instance) const
    {
        if (!_vertex_launcher) return nullptr;
        glDrawElementsInstancedBaseVertexBaseInstance(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            instances_num, base_vertex, base_instance
        );
        return std::make_shared<gl_fence>();
    }

    sptr<gl_fence> draw_elements(const gl_draw_elements_indirect_command& command) const
    {
        glDrawElementsIndirect(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            static_cast<GLenum>(_vertex_launcher->get_element_type()),
            (const void*)&command
        );
        return std::make_shared<gl_fence>();
    }

    sptr<gl_fence> draw_range_elements(uint32 element_start, uint32 element_end, uint32 element_offset, uint32 elements_num, uint32 base_vertex) const
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

    sptr<gl_fence> multi_draw_elements(const std::vector<uint32>& element_offsets, std::vector<uint32>& elements_nums) const
    {
        if (!_vertex_launcher) return nullptr;
        glMultiDrawElements(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), (const int32*)elements_nums.data(),
            static_cast<GLenum>(_vertex_launcher->get_element_type()),
            nullptr, element_offsets.size()
        );
        return std::make_shared<gl_fence>();
    }

    sptr<gl_fence> multi_draw_elements(const std::vector<gl_draw_elements_indirect_command>& commands) const
    {
        return std::make_shared<gl_fence>();
    }

    sptr<gl_fence> draw_transform_feedback(uint32 stream_Index = 0)
    {
        if (!_vertex_launcher || !_transform_feedback) return nullptr;
        _transform_feedback->draw(_vertex_launcher->get_primitive_mode(), stream_Index);
        return std::make_shared<gl_fence>();
    }

    sptr<gl_fence> draw_transform_feedback(uint32 stream_index, uint32 instances_num)
    {
        if (!_vertex_launcher || !_transform_feedback) return nullptr;
        gl_primitive_mode _TransformFeedbackPrimitiveMode = _vertex_launcher->get_primitive_mode();
        _transform_feedback->draw(_TransformFeedbackPrimitiveMode, stream_index, instances_num);
        return std::make_shared<gl_fence>();
    }

public:

    void set_blend_enable(bool enable) { _enable_blend = enable; }
    void set_clip_distance0_enable(bool enable) { _enable_clip_distance0 = enable; }
    void set_color_logic_op_enable(bool enable) { _enable_color_logic_op = enable; }
    void set_debug_output_enable(bool enable) { _enable_debug_output = enable; }
    void set_debug_output_synchronous(bool enable) { _enable_debug_output_synchronous = enable; }
    void set_depth_clamp_enable(bool enable) { _enable_depth_clamp = enable; }
    void set_depth_test_enable(bool enable) { _enable_depth_test = enable; }
    void set_dither_enable(bool enable) { _enable_dither = enable; }
    void set_framebuffer_srgb_enable(bool enable) { _enable_framebuffer_srgb = enable; }

    void set_primitive_restart(bool enable) { _enable_primitive_restart = enable; }



    void set_sample_alpha_to_coverage_enable(bool enable) { _enable_sample_alpha_to_coverage = enable; }
    void set_sample_alpha_to_one_enable(bool enable) { _enable_sample_alpha_to_one = enable; }
    void set_sample_coverage_enable(bool enable) { _enable_sample_coverage = enable; }
    void set_sample_mask_enable(bool enable) { _enable_sample_mask = enable; }
    void set_scissor_test_enable(bool enable) { _enable_scissor_test = enable; }
    void set_stencil_test_enable(bool enable) { _enable_stencil_test = enable; }
    void set_texture_cube_map_sampless_enable(bool enable) { _enable_texture_cube_map_sampless = enable; }

public:

    void set_viewport(float x, float y, float width, float height) { _viewport.x = x; _viewport.y = y; _viewport.z = width; _viewport.w = height; }

private:

    bool _enable_texture_cube_map_sampless;

    // debug output
    bool _enable_debug_output;
    bool _enable_debug_output_synchronous;

    // vertex arrays 
    bool _enable_primitive_restart;
    
    // vertex post-processing
    bool _enable_depth_clamp;
    bool _enable_clip_distance0;

    glm::vec4 _viewport;
    gl_clip_control_origin _clip_control_origin;
    gl_clip_control_depth_mode _clip_control_depth_mode;
    gl_provoke_mode _provoke_mode;

    void _set_vertex_post_processing()
    {
        glProvokingVertex(static_cast<GLenum>(_provoke_mode));

        glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
        //glViewportIndexedf();
        //glViewportIndexedfv();
        //glViewportArrayv();
        
        // depth clamp
        if (_enable_depth_clamp)
        {
            glEnable(GL_DEPTH_CLAMP);
            //glDepthRange(1, 2);
            //glDepthRangef(1.1f, 1.2f);
            //glDepthRangeIndexed();
        }
        else {
            glDisable(GL_DEPTH_CLAMP);
        }

        _enable_clip_distance0 ? glEnable(GL_CLIP_DISTANCE0) : glDisable(GL_CLIP_DISTANCE0);

        glClipControl(static_cast<GLenum>(_clip_control_origin), static_cast<GLenum>(_clip_control_depth_mode));

    }

public:
    void set_rasterizer_discard(bool enable) { _enable_rasterizer_discard = enable; }
    void set_multisample_enable(bool enable) { _enable_multisample = enable; }
    void set_sample_shading_enable(bool enable) { _enable_sample_shading = enable; }
    void set_sample_shading_rate(float rate) { _sample_shading_rate = rate; }

    void set_program_point_size_enable(bool enable) { _enable_program_point_size = enable; }
    void set_line_smooth_enable(bool enable) { _enable_line_smooth = enable; }
    void set_rasterized_line_width(float width) { _rasterized_line_width = width; }

    void set_polygon_smooth_enable(bool enable) { _enable_polygon_smooth = enable; }
    
    void set_front_face(gl_front_face_mode face_mode) { _front_face_mode = face_mode; }

    void set_cull_face_enable(bool enable) { _enable_cull_face = enable; }
    void set_cull_face(gl_cull_face face) { _cull_face = face; }

    void set_front_polygon_mode(gl_polygon_mode mode) { _front_polygon_mode = mode; }
    void set_back_polygon_mode(gl_polygon_mode mode) { _back_polygon_mode = mode; }

    void set_polygon_offset_fill_enable(bool enable) { _enable_polygon_offset_fill = enable; }
    void set_polygon_offset_line_enable(bool enable) { _enable_polygon_offset_line = enable; }
    void set_polygon_offset_point_enable(bool enable) { _enable_polygon_offset_point = enable; }

private:
    bool _enable_rasterizer_discard;
    bool _enable_multisample;
    bool _enable_sample_shading;
    bool _enable_program_point_size;
    bool _enable_line_smooth;
    bool _enable_polygon_smooth;
    bool _enable_cull_face;
    bool _enable_polygon_offset_fill;
    bool _enable_polygon_offset_line;
    bool _enable_polygon_offset_point;

    float _sample_shading_rate;
    float _rasterized_line_width = 1.0f;
    gl_front_face_mode _front_face_mode;
    gl_cull_face _cull_face;
    gl_polygon_mode _front_polygon_mode;
    gl_polygon_mode _back_polygon_mode;

    void _set_rasterization()
    {
        // rasterizer discard which make all stages discarded start from rasterization
        _enable_rasterizer_discard ? glEnable(GL_RASTERIZER_DISCARD) : glDisable(GL_RASTERIZER_DISCARD);
        // multisample
        _enable_multisample ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
        // sample shading
        if (_enable_sample_shading)
        {
            glEnable(GL_SAMPLE_SHADING);
            glMinSampleShading(_sample_shading_rate);
        }
        else {
            glDisable(GL_SAMPLE_SHADING);
        }
        // points
        // program point size
        _enable_program_point_size ? glEnable(GL_PROGRAM_POINT_SIZE) : glDisable(GL_PROGRAM_POINT_SIZE);
        // line segments
        // line smooth
        if (_enable_line_smooth)
        {
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(_rasterized_line_width);
        }
        else {
            glDisable(GL_LINE_SMOOTH);
        }
        // polygons
        // polygon smooth
        _enable_polygon_smooth ? glEnable(GL_POLYGON_SMOOTH) : glDisable(GL_POLYGON_SMOOTH);
        glFrontFace(static_cast<GLenum>(_front_face_mode));
        // cull face
        if (_enable_cull_face)
        {
            glEnable(GL_CULL_FACE);
            glCullFace(static_cast<GLenum>(_cull_face));
        }
        else {
            glDisable(GL_CULL_FACE);
        }
        // polygon Rast & Depth Offset
        glPolygonMode(GL_FRONT, static_cast<GLenum>(_front_polygon_mode));
        glPolygonMode(GL_BACK, static_cast<GLenum>(_back_polygon_mode));
        //glPolygonOffset();
        //glPolygonOffsetClamp();
        _enable_polygon_offset_point ? glEnable(GL_POLYGON_OFFSET_POINT) : glDisable(GL_POLYGON_OFFSET_POINT);
        _enable_polygon_offset_line ? glEnable(GL_POLYGON_OFFSET_LINE) : glDisable(GL_POLYGON_OFFSET_LINE);
        _enable_polygon_offset_fill ? glEnable(GL_POLYGON_OFFSET_FILL) : glDisable(GL_POLYGON_OFFSET_FILL);
    }

    // pre-fragment operations
    bool _enable_scissor_test;
    
    bool _enable_sample_coverage;
    bool _enable_sample_mask;
    bool _enable_sample_alpha_to_coverage;
    bool _enable_sample_alpha_to_one;
    
    bool _enable_stencil_test;
    bool _enable_depth_test;
    bool _enable_blend; // blending
    bool _enable_framebuffer_srgb; // SRGB Conversion
    bool _enable_dither; // Dithering
    bool _enable_color_logic_op; // Logicop

    int _scissor_x, _scissor_y, _scissor_width, _scissor_height;
    float _sample_coverage_value;
    bool _inverted;


    gl_stencil_func _front_face_stencil_func = gl_stencil_func::ALWAYS;
    gl_stencil_func _back_face_stencil_func = gl_stencil_func::ALWAYS;
    uint32 _stencil_ref;
    uint32 _stencil_mask;

    enum class gl_stencil_operation : GLenum
    {
        KEEP = GL_KEEP,
        ZERO = GL_ZERO,
        REPLACE = GL_REPLACE,
        INCR = GL_INCR,
        INCR_WRAP = GL_INCR_WRAP,
        DECR = GL_DECR,
        DECR_WRAP = GL_DECR_WRAP,
        INVERT = GL_INVERT
    };

    gl_stencil_operation _sfail_stencil_operation = gl_stencil_operation::KEEP;
    gl_stencil_operation _dpfail_stencil_operation = gl_stencil_operation::KEEP;
    gl_stencil_operation _dppass_stencil_operation = gl_stencil_operation::KEEP;


    void _set_pre_fragment_operation()
    {
        // scissor test
        if (_enable_scissor_test)
        {
            glEnable(GL_SCISSOR_TEST);
            glScissor(_scissor_x, _scissor_y, _scissor_width, _scissor_height);
            //glScissorIndexed();
            //glScissorIndexedv();
            //glScissorArrayv();
        }
        else {
            glDisable(GL_SCISSOR_TEST);
        }

        // sample mask
        if (_enable_sample_mask)
        {
            glEnable(GL_SAMPLE_MASK);
            //glSampleMaski();
        }
        else {
            glDisable(GL_SAMPLE_MASK);
        }

        // sample alpha to coverage
        _enable_sample_alpha_to_coverage ? glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE) : glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        // sample alpha to one
        _enable_sample_alpha_to_one ? glEnable(GL_SAMPLE_ALPHA_TO_ONE) : glDisable(GL_SAMPLE_ALPHA_TO_ONE);

        // sample coverage
        if (_enable_sample_coverage)
        {
            glEnable(GL_SAMPLE_COVERAGE);
            glSampleCoverage(_sample_coverage_value, _inverted);
        }
        else {
            glDisable(GL_SAMPLE_COVERAGE);
        }

        // stencil test
        if (_enable_stencil_test)
        {
            glEnable(GL_STENCIL_TEST);
            glStencilFuncSeparate(
                static_cast<GLenum>(_front_face_stencil_func), 
                static_cast<GLenum>(_back_face_stencil_func), 
                _stencil_ref, _stencil_mask);
            
            glStencilOpSeparate(GL_FRONT, 
                static_cast<GLenum>(_sfail_stencil_operation), 
                static_cast<GLenum>(_dpfail_stencil_operation), 
                static_cast<GLenum>(_dppass_stencil_operation)
            );
            glStencilOpSeparate(GL_BACK,
                static_cast<GLenum>(_sfail_stencil_operation),
                static_cast<GLenum>(_dpfail_stencil_operation),
                static_cast<GLenum>(_dppass_stencil_operation)
            );
            
            glStencilMaskSeparate(GL_FRONT, 1);
            glStencilMaskSeparate(GL_BACK, 1);
        }
        else {
            glDisable(GL_STENCIL_TEST);
        }

        // depth test
        if (_enable_depth_test)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(static_cast<GLenum>(_depth_func));
        }
        else {
            glDisable(GL_DEPTH_TEST);
        }

        // blend
        if (_enable_blend)
        {
            glEnable(GL_BLEND); 
            //glBlendColor();
            //glBlendFuncSeparate();
            //glBlendEquationSeparate();
        }
        else {
            glDisable(GL_BLEND);
        }

        if (_enable_framebuffer_srgb)
        {
            glEnable(GL_FRAMEBUFFER_SRGB);
        }
        else {
            glDisable(GL_FRAMEBUFFER_SRGB);
        }

        // dither
        if (_enable_dither)
        {
            glEnable(GL_DITHER);
        }
        else {
            glDisable(GL_DITHER);
        }

        // logic op
        if (_enable_color_logic_op)
        {
            glEnable(GL_COLOR_LOGIC_OP);
            glLogicOp(static_cast<GLenum>(_logic_op));
        }
        else {
            glDisable(GL_COLOR_LOGIC_OP);
        }
 
    }

    gl_logic_op _logic_op;
    gl_depth_func _depth_func;
    glm::dvec2 _depth_range;
    float _line_wdith;

    void _set_pipeline_state()
    {
        _set_vertex_post_processing();
        _set_rasterization();
        _set_pre_fragment_operation();

        // primitive restart index
        _enable_primitive_restart ? glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX) : glDisable(GL_PRIMITIVE_RESTART_FIXED_INDEX);

        // framebuffer srgb
        if (_enable_framebuffer_srgb)
        {
            glEnable(GL_FRAMEBUFFER_SRGB);
        }
        else {
            glDisable(GL_FRAMEBUFFER_SRGB);
        }

        // texture cube map sampless
        _enable_texture_cube_map_sampless ? glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS) : glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    }


public:

    void set_blend_func(gl_blend_func_factor src_rgb_factor, gl_blend_func_factor dst_rgbfactor)
    {

    }

    void set_blend_func(gl_blend_func_factor src_rgb_factor, gl_blend_func_factor dst_rgbfactor, gl_blend_func_factor src_alpha_factor, gl_blend_func_factor dst_alpha_factor)
    {

    }

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

