
#ifndef H_GL_STATIC_MESH_RENDERER
#define H_GL_STATIC_MESH_RENDERER
#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)
    
    DEFINE_GRAPHICS_PIPELINE_PARAMETERS_BEGIN(VertexProcessing)
     
        DEFINE_STREAM_INPUT()

        DEFINE_VERTEX_SHADER_PARAMETERS_BEGIN()
            DEFINE_SHADER_PARAMETER_UNIFORM_BLOCK(MatricesStruct, matrices, [10])
            DEFINE_SHADER_PARAMETER_SHADER_STORAGE_BLOCK(CachedStruct, swapCache)
        DEFINE_VERTEX_SHADER_PARAMETERS_END()

        DEFINE_VERTEX_TESC_STREAM()
        
        DEFINE_TESC_SHADER_PARAMETERS_BEGIN()
            DEFINE_SHADER_PARAMETER_ATOMIC_COUNTER(primitiveCounter)
        DEFINE_TESC_SHADER_PARAMETERS_END()

        DEFINE_TESC_TESE_STREAM()

        DEFINE_TESE_SHADER_PARAMETERS_BEGIN()
            DEFINE_SHADER_PARAMETER_ATOMIC_COUNTER(primitiveCounter)
        DEFINE_TESE_SHADER_PARAMETERS_END()

        DEFINE_TESE_GEOMETRY_STREAM()

        DEFINE_GEOMETRY_SHADER_PARAMETERS_BEGIN()
        DEFINE_GEOMETRY_SHADER_PARAMETERS_END()

        DEFINE_GEOMETRY_FRAGMENT_STREAM()

        DEFINE_FRAGMENT_SHADER_PARAMETERS_BEGIN()
            DEFINE_SHADER_PARAMETER_IMAGE(image2D, positionImage2D)
            DEFINE_SHADER_PARAMETER_SAMPLER(sampler2D, albedoMap)
            DEFINE_SHADER_PARAMETER_ATOMIC_COUNTER(primitiveCounter)
            DEFINE_SHADER_PARAMETER_UNIFORM_BLOCK(MatricesStruct, matrices, [10])
            DEFINE_SHADER_PARAMETER_SHADER_STORAGE_BLOCK(CachedStruct, swapCache)
        DEFINE_FRAGMENT_SHADER_PARAMETERS_END()

        DEFINE_STREAM_OUTPUT()

    DEFINE_GRAPHICS_PIPELINE_PARAMETERS_END()


    IMPLEMENTATION_FUNC_BUILD()
    {
        _render_target = builder.create_texture_2d(1024, 1024, gl_texture_pixel_format::rgba12_ui_nor, 1);
        //builder.create_renderbuffer()
        
        gl_vertex_shader_descriptor _vs_desc;
        
        gl_tessellation_control_shader_descriptor _tesc_desc;
        gl_tessellation_evaluation_shader_descriptor _tese_desc;
        gl_geometry_shader_descriptor _gs_desc;
        gl_fragment_shader_descriptor _fs_desc;

        auto _vs = builder.create_vertex_shader(_vs_desc);
        auto _tesc = builder.create_tessellation_control_shader(_tesc_desc);
        auto _tese = builder.create_tessellation_evaluation_shader(_tese_desc);
        auto _gs = builder.create_geometry_shader(_gs_desc);
        auto _fs = builder.create_fragment_shader(_fs_desc);

        gl_graphics_pipeline_descriptor _graphics_pipeline_desc;
        _graphics_pipeline_desc.parameters;
        _graphics_pipeline_desc.vertex_processing.vertex_shading.shader = _vs;
        _graphics_pipeline_desc.vertex_processing.tessellation.control_shader = _tesc;
        _graphics_pipeline_desc.vertex_processing.tessellation.evaluation_shader = _tese;
        _graphics_pipeline_desc.vertex_processing.geometry_shading.shader = _gs;
        _graphics_pipeline_desc.fragment_processing.fragment_shading.shader = _fs;

        gl_compute_shader_descriptor _cs_desc;
        auto _cs = builder.create_compute_shader(_cs_desc);
        gl_compute_pipeline_descriptor _compute_pipeline_desc;
        _compute_pipeline_desc.compute_shading.shader = _cs;

        auto _graphics_pipeline = builder.create_graphics_pipeline(_graphics_pipeline_desc);
        auto _compute_pipeline = builder.create_compute_pipeline(_compute_pipeline_desc);

        _graphics_pipeline->draw_triangles();
        _compute_pipeline->dispatch(2, 2, 2);

    }

    IMPLEMENTATION_FUNC_RENDER()
    {
        
    }

private:

    std::shared_ptr<gl_texture_2d> _render_target;


public:

    void calculate(); 


DEFINE_RENDERER_END()

#endif
