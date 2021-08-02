#ifndef H_GRAPHICS_PIPELINE
#define H_GRAPHICS_PIPELINE

#include "graphics/program/gl_program.h"

class gl_vertex_shader;
class gl_fragment_shader;
class gl_geometry_shader;
class gl_tessellation_control_shader;
class gl_tessellation_evaluation_shader;

enum class gl_blend_state
{};

enum class gl_rasterizer_state
{};

enum class gl_depth_stencil_state
{};

struct gl_graphics_pipeline_descriptor
{
    struct gl_vertex_specification
    {

    } vertex_specification;

    struct gl_vertex_shading
    {
        std::shared_ptr<gl_vertex_shader> vertex_shader;

    } stage_vertex_shading;

    struct gl_tessellation
    {
        std::shared_ptr<gl_tessellation_control_shader> tessellation_control_shader;
        bool tessellator;
        std::shared_ptr<gl_tessellation_evaluation_shader> tessellation_evaluation_shader;
    } stage_tessellation;

    struct gl_geometry_shading
    {
        std::shared_ptr<gl_geometry_shader> geometry_shader;
    } stage_geometry_shading;

    struct gl_transform_feedback
    {
        std::shared_ptr<gl_buffer> transform_feedback_target;
        std::string semantic_name;

    } stage_transform_feedback;

    struct gl_rasterization
    {
        bool reject_rasterization; // discard all primitives, do not use any
        gl_rasterizer_state rasterizer_state;

    } stage_rasterization;

    struct gl_fragment_shading
    {
        std::shared_ptr<gl_fragment_shader> fragment_shader;

    } stage_fragment_shading;

    struct gl_per_fragment_operations
    {
        gl_blend_state blend_state;
        bool enable_alpha_to_coverage;
        bool enable_stencil_test;
        bool enable_depth_test;


    } stage_per_fragment_operations;

    struct gl_framebuffer
    {
        gl_depth_stencil_state depth_stencil_state;

    } framebuffer;
};

class gl_graphics_pipeline
{
public:
    
    gl_graphics_pipeline() = default;

    explicit gl_graphics_pipeline(const gl_graphics_pipeline_descriptor& descriptor) :
        _descriptor(descriptor)
    {
        _descriptor.vertex_specification;
        _descriptor.stage_vertex_shading;
        _descriptor.stage_tessellation;
        _descriptor.stage_geometry_shading;
        _descriptor.stage_transform_feedback;
        _descriptor.stage_rasterization;
        _descriptor.stage_fragment_shading;
        _descriptor.framebuffer;
    }

    ~gl_graphics_pipeline() = default;

public:

    void install();

public:

    void draw_rectangles();

    void draw_triangles();

    void draw_triangle_strips();

private:

    std::shared_ptr<gl_program> _program;

    gl_graphics_pipeline_descriptor _descriptor;

    std::function<void(void)> _graphics_pipeline_installer;

    void _initialize_graphics_pipeline();

    void _compile_pipeline();

};

#endif

