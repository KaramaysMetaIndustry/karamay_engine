
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
        DEFINE_PROGRAM_PARAMETER_IMAGE(image2DArray, positionImage2DArray)
        DEFINE_PROGRAM_PARAMETER_SAMPLER(sampler2D, albedoMap)
        DEFINE_PROGRAM_PARAMETER_ATOMIC_COUNTER(primitiveCounter)
        DEFINE_PROGRAM_PARAMETER_ATOMIC_COUNTER_ARRAY(primitiveCounters, 5)
        DEFINE_PROGRAM_PARAMETER_UNIFORM_BLOCK(MatricesStruct, matrices)
        DEFINE_PROGRAM_PARAMETER_UNIFORM_BLOCK_ARRAY(MatricesStruct, matricesArray, 10)
        DEFINE_PROGRAM_PARAMETER_SHADER_STORAGE_BLOCK(CachedStruct, swapCache)
        DEFINE_PROGRAM_PARAMETER_SHADER_STORAGE_BLOCK_ARRAY(CachedStruct, swapCacheArray, 10)

        DEFINE_VERTEX_SHADER_PARAMETERS_BEGIN()
            SHADER_PARAMETER_REF(positionImage2D)
            SHADER_PARAMETER_REF(positionImage2Ds)
            SHADER_PARAMETER_REF(matrices)
            SHADER_PARAMETER_REF(swapCacheArray)
        DEFINE_VERTEX_SHADER_PARAMETERS_END()

        DEFINE_TESC_SHADER_PARAMETERS_BEGIN()
        DEFINE_TESC_SHADER_PARAMETERS_END()

        DEFINE_TESE_SHADER_PARAMETERS_BEGIN()
        DEFINE_TESE_SHADER_PARAMETERS_END()

        DEFINE_GEOMETRY_SHADER_PARAMETERS_BEGIN()
        DEFINE_GEOMETRY_SHADER_PARAMETERS_END()

        DEFINE_FRAGMENT_SHADER_PARAMETERS_BEGIN()
            SHADER_PARAMETER_REF(matrices)
            SHADER_PARAMETER_REF(matricesArray)
            SHADER_PARAMETER_REF(swapCache)
            SHADER_PARAMETER_REF(swapCacheArray)
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
        // graphics pipeline desc
        gl_graphics_pipeline_descriptor _graphics_pipeline_desc;
        // fill parameters
        vertex_processing_parameters->albedoMap.generate_token();
        vertex_processing_parameters->albedoMaps[0].generate_token();
        vertex_processing_parameters->positionImage2Ds[2].generate_token();
        // set program parameters
        _graphics_pipeline_desc.parameters = vertex_processing_parameters;
        // set pipeline state
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_x = 0;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_y = 0;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_width = 1024;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_height = 1024;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.flatshading.provoke_mode = gl_provoke_mode::first_vertex_convention;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.primitive_clipping.clip_plane_index = 0;
        _graphics_pipeline_desc.vertex_processing.post_vertex_processing.transform_feedback.semantic_name ="";
        // build graphics pipeline
        _vertex_processing_pipeline = builder.build_graphics_pipeline(_graphics_pipeline_desc);

        gl_compute_shader_descriptor _cs_desc;
        auto _cs = builder.create_compute_shader(_cs_desc);
        // compute pipeline desc
        gl_compute_pipeline_descriptor _compute_pipeline_desc;
        // set program parameters
        _compute_pipeline_desc.parameters = texture_composing_parameters;
        // set pipeline state
        // build compute pipeline
        _texture_composing_pipeline = builder.build_compute_pipeline(_compute_pipeline_desc);

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
