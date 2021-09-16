
#ifndef H_GL_STATIC_MESH_RENDERER
#define H_GL_STATIC_MESH_RENDERER
#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)

    // define graphics pipeline parameters
    DEFINE_GRAPHICS_PIPELINE_PARAMETERS(vertex_processing)
    {
		struct MatricesStruct {};
		struct CachedStruct {};

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



    DEFINE_COMPUTE_PIPELINE_PARAMETERS_BEGIN(texture_composing)
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
                glsl_vec3 position0{ item_register };
                glsl_vec3 position1{ item_register };
                glsl_vec3 position2{ item_register };
            } memory[10];


        } _ublock0{ uniform_block_register };
    DEFINE_COMPUTE_PIPELINE_PARAMETERS_END(texture_composing)



    std::shared_ptr<gl_graphics_pipeline> _vertex_processing_pipeline;
    std::shared_ptr<gl_compute_pipeline> _texture_composing_pipeline;


    IMPLEMENTATION_FUNC_BUILD()
    {

        _texture_composing_parameters->compute_shader_parameters._ublock0.memory[0].position0;
        _texture_composing_parameters->compute_shader_parameters._ublock0.memory[0].position1;
        _texture_composing_parameters->compute_shader_parameters._ublock0.memory[0].position2;
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
        _compute_pipeline_desc.parameters;
        _texture_composing_pipeline = builder.create_compute_pipeline(_compute_pipeline_desc);
        if(_texture_composing_pipeline)
        {
            // ..
        }


//        _graphics_pipeline->draw_triangles();
//        _compute_pipeline->dispatch(2, 2, 2);

    }

    IMPLEMENTATION_FUNC_RENDER()
    {
        if(_vertex_processing_pipeline && _texture_composing_pipeline)
        {
            _vertex_processing_pipeline->
        }
    }



public:

    void calculate() {}


DEFINE_RENDERER_END()

#endif
