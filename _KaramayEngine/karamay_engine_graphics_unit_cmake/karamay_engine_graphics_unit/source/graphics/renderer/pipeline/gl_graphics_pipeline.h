#ifndef GRAPHICS_PIPELINE_H
#define GRAPHICS_PIPELINE_H

#include "base/gl_pipeline.h"
#include "graphics/renderer/pipeline/base/resource/buffers/common_buffer/gl_element_array_buffer.h"

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
    CLEAR = GL_CLEAR, // set all values to 0
    SET = GL_SET, // set all values to 1
    COPY = GL_COPY, // src
    COPY_INVERTED = GL_COPY_INVERTED, // ~ src
    NOOP = GL_NOOP, // dst
    INVERT = GL_INVERT, // ~ dst
    AND = GL_AND, // src & dst
    NAND = GL_NAND, // ~ (src & dst)
    OR = GL_OR, // src | dst
    NOR = GL_NOR, // ~ (src | dst)
    XOR = GL_XOR, // src ^ dst
    EQUIV = GL_EQUIV, // ~ (src ^ dst)
    AND_REVERSE = GL_AND_REVERSE, // src & ~ dst
    AND_INVERTED = GL_AND_INVERTED, // ~ src & dst
    OR_REVERSE = GL_OR_REVERSE, // src | ~ dst
    OR_INVERTED = GL_OR_INVERTED // ~ src | dst
};
enum class gl_face : GLenum
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
enum class gl_blend_equation_mode : GLenum
{
    FUNC_ADD = GL_FUNC_ADD, // default
    FUNC_SUBTRACT = GL_FUNC_SUBTRACT,
    FUNC_REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT,
    FUNC_MAX = GL_MAX,
    FUNC_MIN = GL_MIN
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
    LINE = GL_LINE,
    FILL = GL_FILL
};

struct gl_draw_arrays_indirect_command {
    uint32  count;
    uint32  primCount;
    uint32  first;
    uint32  baseInstance;
};

struct gl_draw_elements_indirect_command {
    uint32 count; // 顶点数
    uint32 primCount; // 图元的顶点数
    uint32 firstIndex; // 
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

    gl_render_target() :
        _framebuffer(nullptr)
    {}

    gl_render_target(const gl_render_target&) = delete;
    gl_render_target& operator=(const gl_render_target&) = delete;

    ~gl_render_target() = default;

public:

    void set_default() { _framebuffer = nullptr; }

    void set_framebuffer(gl_framebuffer* framebuffer) { _framebuffer = framebuffer; }

    gl_framebuffer* get_framebuffer() const { return _framebuffer; }

public:

    void bind() noexcept
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
class gl_graphics_pipeline final : public gl_pipeline
{
public:
    gl_graphics_pipeline(glsl_graphics_pipeline_program* graphics_pipeline_program)
    {
        _program.reset(graphics_pipeline_program);
    }

    gl_graphics_pipeline(const gl_graphics_pipeline&) = delete;
    gl_graphics_pipeline& operator=(const gl_graphics_pipeline&) = delete;

    ~gl_graphics_pipeline() = default;

public:

    bool load(const std::string& pipeline_dir) noexcept override;

    void enable() noexcept override;

    void disable() noexcept override;

public:

    glsl_graphics_pipeline_program& program() { return *_program; }

    gl_vertex_launcher& vertex_launcher() { return *_vertex_launcher; }

    gl_render_target& render_target() { return *_render_target; }

private:

    std::unique_ptr<glsl_graphics_pipeline_program> _program = {};

    std::unique_ptr<gl_vertex_launcher> _vertex_launcher = {};

    std::unique_ptr<gl_render_target> _render_target = {};

    /*std::unique_ptr<gl_transform_feedback> _transform_feedback = {};*/

public:

    bool _enable_debug_output = false;
    bool _enable_debug_output_synchronous = false;

    bool _enable_depth_clamp = false;
    bool _enable_clip_distance0 = false;

    bool _enable_texture_cube_map_sampless = false;

    struct gl_vertex_postprocessor
    {
        // flat var output to fragment shader
        // 将整个图元的数据都变为指定顶点的数据
        // 是否起效取决于 vertex shader/tessellation shader/geometry shader output data 是否使用了 flat 指示
        gl_provoke_mode provoke_mode;
        // 
        struct gl_viewport
        {
            uint32 index;
            uint32 x, y;
            uint32 width, height;
            gl_viewport() :
                index(0),
                x(0), y(0), width(0), height(0)
            {}
        } viewport;

        gl_clip_control_origin origin;
        gl_clip_control_depth_mode depth_mode;
        bool discard;

        gl_vertex_postprocessor() :
            provoke_mode(gl_provoke_mode::LAST_VERTEX_CONVENTION),
            viewport(),
            origin(gl_clip_control_origin::LOWER_LEFT), depth_mode(gl_clip_control_depth_mode::NEGATIVE_ONE_TO_ONE),
            discard(false)
        {}
    } vertex_postprocessor = {};

    struct gl_rasterizer
    {
        bool enable_multisample;
        bool enable_sample_shading;
        float sample_shading_rate;

        // point rasterization
        bool enable_program_point_size;
        // line reasterization
        bool enable_line_smooth;
        bool rasterized_line_smooth;
        // triangle rasterization
        bool enable_polygon_smooth; //  polygon antialiasing
        gl_front_face_mode front_face_mode; // polygon face mode CCW
        struct gl_cull_face
        {
            bool enable;
            gl_face face;
            gl_cull_face() :
                enable(true),
                face(gl_face::FRONT)
            {}
        } cull_face; // specify cull face front/back/front_back

        bool enable_polygon_offset_fill;
        bool enable_polygon_offset_line;
        bool enable_polygon_offset_point;
        gl_polygon_mode polygon_mode;

        gl_rasterizer() :
            enable_multisample(false),
            enable_sample_shading(false),
            sample_shading_rate(1.0f),
            enable_program_point_size(false),
            enable_line_smooth(false),
            polygon_mode(gl_polygon_mode::FILL),
            front_face_mode(gl_front_face_mode::CCW) // 逆时针
        {}
    } rasterizer = {};

    struct gl_fragment_preprocessor 
    {
        struct gl_scissor_test
        {
            bool enable;
            struct gl_rectangle
            {
                uint32 index;
                uint32 x, y;
                uint32 width, height;
            } rectangle;
        } scissor_test; // early
        struct gl_multisample_fragment_operations
        {
            bool enable_sample_coverage;
            float sample_coverage_value;
            bool inverted;
            bool enable_sample_mask;
            uint32 mask_index;
            uint32 mask_bitfield;
        } multisample_fragment_operations; // early
    } fragment_preprocessor = {};

    struct gl_fragment_postprocessor 
    {
        struct gl_alpha_to_coverage_operations
        {
            bool enable_sample_alpha_to_coverage;
            bool enable_sample_alpha_to_one;
        } alpha_to_coverage_operations;
        // The ref​ defines the fragment's stencil value for all fragments generated for the given facing (src)
        // if ( ref & mask ) < ( stencil & mask ) do { stencil_op }
        struct gl_stencil_test
        {
            bool enable;
            gl_stencil_func front_face_func;
            uint32 front_face_ref, front_face_mask;
            gl_stencil_op front_face_sfail_operation;
            gl_stencil_op front_face_dpfail_operation;
            gl_stencil_op front_face_dppass_operation;
            gl_stencil_func back_face_func;
            uint32 back_face_ref, back_face_mask;
            gl_stencil_op back_face_sfail_operation;
            gl_stencil_op back_face_dpfail_operation;
            gl_stencil_op back_face_dppass_operation;

            gl_stencil_test() :
                enable(false),
                front_face_func(gl_stencil_func::ALWAYS), front_face_ref(0), front_face_mask(1),
                front_face_sfail_operation(gl_stencil_op::KEEP),
                front_face_dpfail_operation(gl_stencil_op::KEEP),
                front_face_dppass_operation(gl_stencil_op::KEEP),
                
                back_face_func(gl_stencil_func::ALWAYS), back_face_ref(0), back_face_mask(1),
                back_face_sfail_operation(gl_stencil_op::KEEP),
                back_face_dpfail_operation(gl_stencil_op::KEEP),
                back_face_dppass_operation(gl_stencil_op::KEEP)
            {}
        } stencil_test; // can be early <=> framebuffer
        // gl_Position (rast)=> gl_FragCoord.z
        // if(srcDepth < bufferDepth)
        struct gl_depth_test
        {
            bool enable;
            gl_depth_func func;
            gl_depth_test() :
                enable(false), func(gl_depth_func::ALWAYS)
            {}
        } depth_test; // can be early <=> framebuffer
        // (srcR * src_rgb_factor) rgb_equation (dstR * (1-dst_rgb_factor)) = rR
        // (srcG * src_rgb_factor) rgb_equation (dstG * (1-dst_rgb_factor)) = rG
        // (srcB * src_rgb_factor) rgb_equation (dstB * (1-dst_rgb_factor)) = rB
        // (srcA * src_alpha_factor) alpha_equation (dstA * (1-dst_alpha_factor)) = rA
        struct gl_blend
        {
            bool enable;
            glm::vec4 blend_color;

            gl_blend_func_factor src_rgb_factor;
            gl_blend_func_factor dst_rgb_factor;
            gl_blend_equation_mode rgb_equation;
            gl_blend_func_factor src_alpha_factor;
            gl_blend_func_factor dst_alpha_factor;
            gl_blend_equation_mode alpha_equation;

            gl_blend() :
                enable(false), blend_color(0.0f, 0.0f, 0.0f, 1.0f),
                src_rgb_factor(gl_blend_func_factor::ONE), dst_rgb_factor(gl_blend_func_factor::ZERO), rgb_equation(gl_blend_equation_mode::FUNC_ADD),
                src_alpha_factor(gl_blend_func_factor::ONE), dst_alpha_factor(gl_blend_func_factor::ZERO), alpha_equation(gl_blend_equation_mode::FUNC_ADD)
            {}
        } blend;
        // if format is SRGB, opengl think that is a linear color, and do transformation
        bool enable_framebuffer_srgb;
        // make low precision color looks like more rich
        bool enable_dither;
        // if enable, blend will not work, only work on rgb
        struct gl_logical_operation
        {
            bool enable; // Logicop
            gl_logic_op op;
            gl_logical_operation() :
                enable(false), op(gl_logic_op::COPY)
            {}
        } logical_operation; // <=> framebuffer
    } fragment_postprocessor = {};

public:

    auto syncable_draw_arrays(uint32 vertex_offset, uint32 vertices_num) const -> std::shared_ptr<gl_fence>
    {
        if (!_vertex_launcher || vertex_offset + vertices_num >= _vertex_launcher->get_vertices_num()) return nullptr;
        glDrawArrays(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), vertex_offset, vertices_num);
        return std::make_shared<gl_fence>();
    }
    auto syncable_draw_arrays(uint32 vertex_offset, uint32 vertices_num, uint32 instances_num, uint32 base_instance) const -> std::shared_ptr<gl_fence>
    {
        if (!_vertex_launcher || vertex_offset + vertices_num >= _vertex_launcher->get_vertices_num()) return nullptr;
        if (base_instance >= instances_num) return nullptr;
        glDrawArraysInstancedBaseInstance(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), vertex_offset, vertices_num, instances_num, base_instance);
        return std::make_shared<gl_fence>();
    }
    auto syncable_draw_elements(uint32 element_offset, uint32 elements_num) const -> std::shared_ptr<gl_fence>
    {
        if (element_offset + elements_num >= _vertex_launcher->get_elements_num()) return nullptr;
        glDrawElements(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()),
            (void*)(_vertex_launcher->get_element_size() * element_offset)
        );
        return std::make_shared<gl_fence>();
    }
    auto syncable_draw_elements(uint32 element_offset, uint32 elements_num, uint32 instances_num, uint32 base_instance) const -> std::shared_ptr<gl_fence>
    {
        if (!_vertex_launcher) return nullptr;
        glDrawElementsInstancedBaseInstance(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            instances_num, base_instance
        );
        return std::make_shared<gl_fence>();
    }
    auto syncable_draw_elements(uint32 element_offset, uint32 elements_num, uint32 base_vertex) const -> std::shared_ptr<gl_fence>
    {
        if (!_vertex_launcher) return nullptr;
        glDrawElementsBaseVertex(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            base_vertex
        );
        return std::make_shared<gl_fence>();
    }
    auto syncable_draw_elements(uint32 element_offset, uint32 elements_num, uint32 base_vertex, uint32 instances_num, uint32 base_instance) const -> std::shared_ptr<gl_fence>
    {
        if (!_vertex_launcher) return nullptr;
        glDrawElementsInstancedBaseVertexBaseInstance(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            instances_num, base_vertex, base_instance
        );
        return std::make_shared<gl_fence>();
    }
    auto syncable_draw_range_elements(uint32 element_start, uint32 element_end, uint32 element_offset, uint32 elements_num, uint32 base_vertex) const -> std::shared_ptr<gl_fence>
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
    auto syncable_multi_draw_arrays(const std::vector<uint32>& vertex_offsets, const std::vector<uint32>& vertices_nums) const -> std::shared_ptr<gl_fence>
    {
        if (!_vertex_launcher) return nullptr;
        if (vertex_offsets.size() != vertices_nums.size()) return nullptr;
        glMultiDrawArrays(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            (const int32*)vertex_offsets.data(), (const int32*)vertices_nums.data(), vertex_offsets.size()
        );
        return std::make_shared<gl_fence>();
    }
    auto syncable_multi_draw_elements(const std::vector<uint32>& element_offsets, std::vector<uint32>& elements_nums) const -> std::shared_ptr<gl_fence>
    {
        if (!_vertex_launcher) return nullptr;
        glMultiDrawElements(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), (const int32*)elements_nums.data(),
            static_cast<GLenum>(_vertex_launcher->get_element_type()),
            nullptr, element_offsets.size()
        );
        return std::make_shared<gl_fence>();
    }
    
    auto syncable_indirect_draw_arrays(const gl_draw_arrays_indirect_command& command) const -> std::shared_ptr<gl_fence>
    {
        glDrawArraysIndirect(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), (const void*)&command);
        return std::make_shared<gl_fence>();
    }
    auto syncable_indirect_draw_elements(const gl_draw_elements_indirect_command& command) const -> std::shared_ptr<gl_fence>
    {
        glDrawElementsIndirect(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            static_cast<GLenum>(_vertex_launcher->get_element_type()),
            (const void*)&command
        );
        return std::make_shared<gl_fence>();
    }
    auto syncable_indirect_multi_draw_arrays(const std::vector<gl_draw_arrays_indirect_command>& commands) const -> std::shared_ptr<gl_fence>
    {
        //glMultiDrawArraysIndirect()
        return std::make_shared<gl_fence>();
    }
    auto syncable_indirect_multi_draw_elements(const std::vector<gl_draw_elements_indirect_command>& commands) const -> std::shared_ptr<gl_fence>
    {
        glMultiDrawElementsIndirect(GL_TRIANGLES, 
            static_cast<GLenum>(_vertex_launcher->get_element_type()),
            commands.data(), commands.size(), 
            0
        );
        return std::make_shared<gl_fence>();
    }

    void unsyncable_draw_arrays(uint32 vertex_offset, uint32 vertices_num)
    {
        if (!_vertex_launcher || vertex_offset + vertices_num >= _vertex_launcher->get_vertices_num()) return;
        glDrawArrays(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), vertex_offset, vertices_num);
    }
    void unsyncable_draw_arrays(uint32 vertex_offset, uint32 vertices_num, uint32 instances_num, uint32 base_instance) const
    {
        if (!_vertex_launcher || vertex_offset + vertices_num >= _vertex_launcher->get_vertices_num()) return;
        if (base_instance >= instances_num) return;
        glDrawArraysInstancedBaseInstance(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), vertex_offset, vertices_num, instances_num, base_instance);
    }
    void unsyncable_draw_elements(uint32 element_offset, uint32 elements_num) const
    {
        if (element_offset + elements_num >= _vertex_launcher->get_elements_num()) return;
        glDrawElements(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()),
            (void*)(_vertex_launcher->get_element_size() * element_offset)
        );
    }

    void unsyncable_draw_elements(uint32 element_offset, uint32 elements_num, uint32 instances_num, uint32 base_instance) const
    {
        if (!_vertex_launcher) return;
        glDrawElementsInstancedBaseInstance(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            instances_num, base_instance
        );
    }
    void unsyncable_draw_elements(uint32 element_offset, uint32 elements_num, uint32 base_vertex) const 
    {
        if (!_vertex_launcher) return;
        glDrawElementsBaseVertex(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            base_vertex
        );
    }
    void unsyncable_draw_elements(uint32 element_offset, uint32 elements_num, uint32 base_vertex, uint32 instances_num, uint32 base_instance) const
    {
        if (!_vertex_launcher) return;
        glDrawElementsInstancedBaseVertexBaseInstance(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            instances_num, base_vertex, base_instance
        );
    }
    void unsyncable_draw_range_elements(uint32 element_start, uint32 element_end, uint32 element_offset, uint32 elements_num, uint32 base_vertex) const
    {
        if (!_vertex_launcher) return;
        glDrawRangeElementsBaseVertex(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            element_start, element_end,
            elements_num, static_cast<GLenum>(_vertex_launcher->get_element_type()), (void*)(_vertex_launcher->get_element_size() * element_offset),
            base_vertex
        );
    }
    void unsyncable_multi_draw_arrays(const std::vector<uint32>& vertex_offsets, const std::vector<uint32>& vertices_nums) const
    {
        if (!_vertex_launcher) return;
        if (vertex_offsets.size() != vertices_nums.size()) return;
        glMultiDrawArrays(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            (const int32*)vertex_offsets.data(), (const int32*)vertices_nums.data(), vertex_offsets.size()
        );
    }
    void unsyncable_multi_draw_elements(const std::vector<uint32>& element_offsets, std::vector<uint32>& elements_nums) const
    {
        if (!_vertex_launcher) return;
        glMultiDrawElements(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), (const int32*)elements_nums.data(),
            static_cast<GLenum>(_vertex_launcher->get_element_type()),
            nullptr, element_offsets.size()
        );
    }
    
    void unsyncable_indirect_draw_arrays(const gl_draw_arrays_indirect_command& command) const
    {
        glDrawArraysIndirect(static_cast<GLenum>(_vertex_launcher->get_primitive_mode()), (const void*)&command);
    }
    void unsyncable_indirect_draw_elements(const gl_draw_elements_indirect_command& command) const
    {
        glDrawElementsIndirect(
            static_cast<GLenum>(_vertex_launcher->get_primitive_mode()),
            static_cast<GLenum>(_vertex_launcher->get_element_type()),
            (const void*)&command
        );
    }
    void unsyncable_indirect_multi_draw_arrays(const std::vector<gl_draw_arrays_indirect_command>& commands) const
    {
        //glMultiDrawArraysIndirect()
    }
    void unsyncable_indirect_multi_draw_elements(const std::vector<gl_draw_elements_indirect_command>& commands) const
    {
        glMultiDrawElementsIndirect(GL_TRIANGLES, 
            static_cast<GLenum>(_vertex_launcher->get_element_type()), 
            commands.data(), commands.size(), 
            0
        );
    }

public:

  /*  void begin_transform_feedback()
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
    }*/
    void begin_conditional_render()
    {
        glBeginConditionalRender(0, GL_QUERY_WAIT);
    }
    void end_conditional_render()
    {
        glEndConditionalRender();
    }

    //auto syncable_draw_feedback(uint32 stream_index) const ->std::shared_ptr<gl_fence>
    //{
    //    if (!_vertex_launcher || !_transform_feedback) return nullptr;
    //    _transform_feedback->draw(_vertex_launcher->get_primitive_mode(), stream_index);
    //    return std::make_shared<gl_fence>();
    //}
    //auto syncable_draw_feedback(uint32 stream_index, uint32 instances_num) const ->std::shared_ptr<gl_fence>
    //{
    //    if (!_vertex_launcher || !_transform_feedback) return nullptr;
    //    gl_primitive_mode _TransformFeedbackPrimitiveMode = _vertex_launcher->get_primitive_mode();
    //    _transform_feedback->draw(_TransformFeedbackPrimitiveMode, stream_index, instances_num);
    //    return std::make_shared<gl_fence>();
    //}
    //
    //void unsyncable_draw_feedback(uint32 stream_index) const
    //{
    //    if (!_vertex_launcher || !_transform_feedback) return;
    //    _transform_feedback->draw(_vertex_launcher->get_primitive_mode(), stream_index);
    //}
    //void unsyncable_draw_feedback(uint32 stream_index, uint32 instances_num) const
    //{
    //    if (!_vertex_launcher || !_transform_feedback) return;
    //    gl_primitive_mode _TransformFeedbackPrimitiveMode = _vertex_launcher->get_primitive_mode();
    //    _transform_feedback->draw(_TransformFeedbackPrimitiveMode, stream_index, instances_num);
    //}

private:

    void _set_vertex_postprocessor()
    {
        glProvokingVertex(static_cast<GLenum>(vertex_postprocessor.provoke_mode));
        glClipControl(static_cast<GLenum>(vertex_postprocessor.origin), static_cast<GLenum>(vertex_postprocessor.depth_mode));

        // primitive clipping
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

        // coordinate transformations
        glViewportIndexedf(vertex_postprocessor.viewport.index,
            vertex_postprocessor.viewport.x, 
            vertex_postprocessor.viewport.y, 
            vertex_postprocessor.viewport.width, 
            vertex_postprocessor.viewport.height
        );
        vertex_postprocessor.discard ? glEnable(GL_RASTERIZER_DISCARD) : glDisable(GL_RASTERIZER_DISCARD);
    }
    void _set_rasterizer()
    {
        // when this enabled, point/line/polygon smooth will not work
        rasterizer.enable_multisample ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
        if (rasterizer.enable_sample_shading)
        {
            glEnable(GL_SAMPLE_SHADING);
            glMinSampleShading(rasterizer.sample_shading_rate);
        }
        else {
            glDisable(GL_SAMPLE_SHADING);
        }
        rasterizer.enable_program_point_size ? glEnable(GL_PROGRAM_POINT_SIZE) : glDisable(GL_PROGRAM_POINT_SIZE);
        if (rasterizer.enable_line_smooth)
        {
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(rasterizer.rasterized_line_smooth);
        }
        else {
            glDisable(GL_LINE_SMOOTH);
        }

        // specify polygon front face
        glFrontFace(static_cast<GLenum>(rasterizer.front_face_mode));
        // specify polygon mode
        glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(rasterizer.polygon_mode));
        if (rasterizer.cull_face.enable)
        {
            glEnable(GL_CULL_FACE);
            glCullFace(static_cast<GLenum>(rasterizer.cull_face.face));
        }
        else {
            glDisable(GL_CULL_FACE);
        }
        rasterizer.enable_polygon_smooth ? glEnable(GL_POLYGON_SMOOTH) : glDisable(GL_POLYGON_SMOOTH);
        //glPolygonOffset();
        //glPolygonOffsetClamp();
        //glPolygonOffsetClamp();
        //glPolygonOffset();

       rasterizer.enable_polygon_offset_point ? glEnable(GL_POLYGON_OFFSET_POINT) : glDisable(GL_POLYGON_OFFSET_POINT);
       rasterizer.enable_polygon_offset_line ? glEnable(GL_POLYGON_OFFSET_LINE) : glDisable(GL_POLYGON_OFFSET_LINE);
       rasterizer.enable_polygon_offset_fill ? glEnable(GL_POLYGON_OFFSET_FILL) : glDisable(GL_POLYGON_OFFSET_FILL);
    }
    void _set_fragment_preprocessor()
    {
        // fragment preprocessor
        if (fragment_preprocessor.scissor_test.enable)
        {
            //glEnable(GL_SCISSOR_TEST);
            //glScissor(fragment_operations.scissor_test.x, fragment_operations.scissor_test.y, fragment_operations.scissor_test.width, fragment_operations.scissor_test.height);
            glEnablei(GL_SCISSOR_TEST, fragment_preprocessor.scissor_test.rectangle.index);
            glScissorIndexed(fragment_preprocessor.scissor_test.rectangle.index,
                fragment_preprocessor.scissor_test.rectangle.x, 
                fragment_preprocessor.scissor_test.rectangle.y, 
                fragment_preprocessor.scissor_test.rectangle.width,
                fragment_preprocessor.scissor_test.rectangle.height
            );
        }
        else {
            glDisable(GL_SCISSOR_TEST);
        }
        
        // multisample operations
        // frag_coverage & (~coverage_value)
        if (fragment_preprocessor.multisample_fragment_operations.enable_sample_coverage)
        {
            glEnable(GL_SAMPLE_COVERAGE);
            glSampleCoverage(
                fragment_preprocessor.multisample_fragment_operations.sample_coverage_value, 
                fragment_preprocessor.multisample_fragment_operations.inverted
            );
        }
        else {
            glDisable(GL_SAMPLE_COVERAGE);
        }

        if (fragment_preprocessor.multisample_fragment_operations.enable_sample_mask)
        {
            glEnable(GL_SAMPLE_MASK);
            glSampleMaski(fragment_preprocessor.multisample_fragment_operations.mask_index, fragment_preprocessor.multisample_fragment_operations.mask_bitfield);
        }
        else {
            glDisable(GL_SAMPLE_MASK);
        }
    }
    void _set_fragment_postprocessor()
    {
        fragment_postprocessor.alpha_to_coverage_operations.enable_sample_alpha_to_coverage ? glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE) : glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        fragment_postprocessor.alpha_to_coverage_operations.enable_sample_alpha_to_one ? glEnable(GL_SAMPLE_ALPHA_TO_ONE) : glDisable(GL_SAMPLE_ALPHA_TO_ONE);
        
        if (fragment_postprocessor.stencil_test.enable)
        {
            glEnable(GL_STENCIL_TEST);
            glStencilFuncSeparate(
                GL_FRONT,
                static_cast<GLenum>(fragment_postprocessor.stencil_test.front_face_func),
                fragment_postprocessor.stencil_test.front_face_ref, fragment_postprocessor.stencil_test.front_face_mask
            );
            glStencilFuncSeparate(
                GL_BACK,
                static_cast<GLenum>(fragment_postprocessor.stencil_test.front_face_func),
                fragment_postprocessor.stencil_test.back_face_ref, fragment_postprocessor.stencil_test.back_face_mask
            );
            glStencilOpSeparate(GL_FRONT,
                static_cast<GLenum>(fragment_postprocessor.stencil_test.front_face_sfail_operation),
                static_cast<GLenum>(fragment_postprocessor.stencil_test.front_face_dpfail_operation),
                static_cast<GLenum>(fragment_postprocessor.stencil_test.front_face_dppass_operation)
            );
            glStencilOpSeparate(GL_BACK,
                static_cast<GLenum>(fragment_postprocessor.stencil_test.back_face_sfail_operation),
                static_cast<GLenum>(fragment_postprocessor.stencil_test.back_face_dpfail_operation),
                static_cast<GLenum>(fragment_postprocessor.stencil_test.back_face_dppass_operation)
            );
            glStencilMaskSeparate(GL_FRONT, 1);
            glStencilMaskSeparate(GL_BACK, 1);
        }
        else {
            glDisable(GL_STENCIL_TEST);
        }
        if (fragment_postprocessor.depth_test.enable)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(static_cast<GLenum>(fragment_postprocessor.depth_test.func));
        }
        else {
            glDisable(GL_DEPTH_TEST);
        }
        if (fragment_postprocessor.blend.enable)
        {
            glEnable(GL_BLEND);
            glBlendColor(
                fragment_postprocessor.blend.blend_color.r,
                fragment_postprocessor.blend.blend_color.g,
                fragment_postprocessor.blend.blend_color.b,
                fragment_postprocessor.blend.blend_color.a
            );
            glBlendFuncSeparate(
                static_cast<GLenum>(fragment_postprocessor.blend.src_rgb_factor),
                static_cast<GLenum>(fragment_postprocessor.blend.src_alpha_factor),
                static_cast<GLenum>(fragment_postprocessor.blend.dst_rgb_factor),
                static_cast<GLenum>(fragment_postprocessor.blend.dst_alpha_factor)
            );
            glBlendEquationSeparate(
                static_cast<GLenum>(fragment_postprocessor.blend.rgb_equation),
                static_cast<GLenum>(fragment_postprocessor.blend.alpha_equation)
            );
        }
        else {
            glDisable(GL_BLEND);
        }
        fragment_postprocessor.enable_framebuffer_srgb ? glEnable(GL_FRAMEBUFFER_SRGB) : glDisable(GL_FRAMEBUFFER_SRGB);
        fragment_postprocessor.enable_dither ? glEnable(GL_DITHER) : glDisable(GL_DITHER);
        if (fragment_postprocessor.logical_operation.enable)
        {
            glEnable(GL_COLOR_LOGIC_OP);
            glLogicOp(static_cast<GLenum>(fragment_postprocessor.logical_operation.op));
        }
        else {
            glDisable(GL_COLOR_LOGIC_OP);
        }
    }
    void _set_pipeline_fixed_functions()
    {
        _set_vertex_postprocessor();
        _set_rasterizer();
        _set_fragment_preprocessor();
        _set_fragment_postprocessor();
    }

    void _allocate_attributes(std::vector<gl_vertex_attribute_descriptor>& attributes)
    {
        
    }
    void _allocate_instance_attributes(std::vector<gl_instance_attribute_descriptor>& instance_attributes)
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

