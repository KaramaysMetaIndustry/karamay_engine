
#ifndef H_GL_STATIC_MESH_RENDERER
#define H_GL_STATIC_MESH_RENDERER
#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)

    struct MatricesStruct {};
    struct CachedStruct {};

    // define graphics pipeline parameters
    DEFINE_GRAPHICS_PIPELINE_PARAMETERS(vertex_processing)
    {
        DEFINE_PROGRAM_PARAMETER_IMAGE(image2D, positionImage2D)
        DEFINE_PROGRAM_PARAMETER_IMAGE_ARRAY(image2D, positionImage2Ds, 10)
        DEFINE_PROGRAM_PARAMETER_SAMPLER(sampler2D, albedoMap)
        DEFINE_PROGRAM_PARAMETER_SAMPLER_ARRAY(sampler2D, albedoMaps, 2)
        DEFINE_PROGRAM_PARAMETER_ATOMIC_COUNTER(primitiveCounter)
        DEFINE_PROGRAM_PARAMETER_ATOMIC_COUNTER_ARRAY(primitiveCounters, 5)
        DEFINE_PROGRAM_PARAMETER_UNIFORM_BLOCK(MatricesStruct, matrices)
        DEFINE_PROGRAM_PARAMETER_UNIFORM_BLOCK_ARRAY(MatricesStruct, matricesArray, 10)
        DEFINE_PROGRAM_PARAMETER_SHADER_STORAGE_BLOCK(CachedStruct, swapCache)
        DEFINE_PROGRAM_PARAMETER_SHADER_STORAGE_BLOCK_ARRAY(CachedStruct, swapCacheArray, 10)

        DEFINE_VERTEX_SHADER_PARAMETERS_BEGIN()
        DEFINE_VERTEX_SHADER_PARAMETERS_END()

        DEFINE_TESC_SHADER_PARAMETERS_BEGIN()
        DEFINE_TESC_SHADER_PARAMETERS_END()

        DEFINE_TESE_SHADER_PARAMETERS_BEGIN()
        DEFINE_TESE_SHADER_PARAMETERS_END()

        DEFINE_GEOMETRY_SHADER_PARAMETERS_BEGIN()
        DEFINE_GEOMETRY_SHADER_PARAMETERS_END()

        DEFINE_FRAGMENT_SHADER_PARAMETERS_BEGIN()
        DEFINE_FRAGMENT_SHADER_PARAMETERS_END()
    };

    std::shared_ptr<gl_vertex_processing_graphics_pipeline_parameters> vertex_processing_parameters;



    DEFINE_COMPUTE_PIPELINE_PARAMETERS(texture_composing)
    {
        DEFINE_PROGRAM_PARAMETER_IMAGE(image2D, positionImage2D)
        DEFINE_PROGRAM_PARAMETER_IMAGE_ARRAY(image2D, positionImage2Ds, 10)
        DEFINE_PROGRAM_PARAMETER_SAMPLER(sampler2D, albedoMap)
        DEFINE_PROGRAM_PARAMETER_SAMPLER_ARRAY(sampler2D, albedoMaps, 2)
        DEFINE_PROGRAM_PARAMETER_ATOMIC_COUNTER(primitiveCounter)
        DEFINE_PROGRAM_PARAMETER_ATOMIC_COUNTER_ARRAY(primitiveCounters, 5)
        DEFINE_PROGRAM_PARAMETER_UNIFORM_BLOCK(MatricesStruct, matrices)
        DEFINE_PROGRAM_PARAMETER_UNIFORM_BLOCK_ARRAY(MatricesStruct, matricesArray, 10)
        DEFINE_PROGRAM_PARAMETER_SHADER_STORAGE_BLOCK(CachedStruct, swapCache)
        DEFINE_PROGRAM_PARAMETER_SHADER_STORAGE_BLOCK_ARRAY(CachedStruct, swapCacheArray, 10)
    };

    std::shared_ptr<gl_graphics_pipeline> _vertex_processing_pipeline;
    std::shared_ptr<gl_compute_pipeline> _texture_composing_pipeline;


    IMPLEMENTATION_FUNC_BUILD()
    {
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

        // desc, create graphics pipeline
        gl_graphics_pipeline_descriptor _graphics_pipeline_desc;
        // shaders
        _graphics_pipeline_desc.vertex_processing.vertex_shading.shader = _vs;
        _graphics_pipeline_desc.vertex_processing.tessellation.control_shader = _tesc;
        _graphics_pipeline_desc.vertex_processing.tessellation.evaluation_shader = _tese;
        _graphics_pipeline_desc.vertex_processing.geometry_shading.shader = _gs;
        _graphics_pipeline_desc.fragment_processing.fragment_shading.shader = _fs;
        // parameters
        _graphics_pipeline_desc.parameters = vertex_processing_parameters;
        vertex_processing_parameters->albedoMap.generate_token();
        vertex_processing_parameters->albedoMaps[0].generate_token();
        vertex_processing_parameters->positionImage2Ds[2].generate_token();
        // controls
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_x = 0;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_y = 0;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_width = 1024;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_height = 1024;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.flatshading.provoke_mode = gl_provoke_mode::first_vertex_convention;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.primitive_clipping.clip_plane_index = 0;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.transform_feedback.semantic_name ="";

        _vertex_processing_pipeline = builder.create_graphics_pipeline(_graphics_pipeline_desc);
        if(_vertex_processing_pipeline)
        {
            _vertex_processing_pipeline->initialize();
        }


        gl_compute_shader_descriptor _cs_desc;
        auto _cs = builder.create_compute_shader(_cs_desc);
        // desc, create compute pipeline
        gl_compute_pipeline_descriptor _compute_pipeline_desc;
        _compute_pipeline_desc.compute_shading.shader = _cs;
        // parameters
        _compute_pipeline_desc.parameters = texture_composing_parameters;
        _texture_composing_pipeline = builder.create_compute_pipeline(_compute_pipeline_desc);
        if(_texture_composing_pipeline)
        {
            //
        }

    }

    IMPLEMENTATION_FUNC_RENDER()
    {
        while(delta_time > 0)
        {
            if(_vertex_processing_pipeline && _texture_composing_pipeline)
            {
                _vertex_processing_pipeline->draw_lines();
                _texture_composing_pipeline->dispatch(2, 2, 2);
            }
        }
    }

DEFINE_RENDERER_END()

#endif
