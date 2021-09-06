
#ifndef H_GL_STATIC_MESH_RENDERER
#define H_GL_STATIC_MESH_RENDERER
#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)

    // define graphics pipeline parameters
    DEFINE_GRAPHICS_PIPELINE_PARAMETERS(vertex_processing)
    {
		struct MatricesStruct {};
		struct CachedStruct {};

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
			DEFINE_SHADER_PARAMETER_IMAGE_ARRAY(image2D, positionImage2D, 10)
			DEFINE_SHADER_PARAMETER_SAMPLER(sampler2D, albedoMap)
			DEFINE_SHADER_PARAMETER_SAMPLER_ARRAY(sampler2D, albedoMap, 2)
			DEFINE_SHADER_PARAMETER_ATOMIC_COUNTER(primitiveCounter)
			DEFINE_SHADER_PARAMETER_UNIFORM_BLOCK(MatricesStruct, matrices)
			DEFINE_SHADER_PARAMETER_UNIFORM_BLOCK_ARRAY(MatricesStruct, matrices, 10)
			DEFINE_SHADER_PARAMETER_SHADER_STORAGE_BLOCK(CachedStruct, swapCache)
			DEFINE_SHADER_PARAMETER_SHADER_STORAGE_BLOCK_ARRAY(CachedStruct, swapCache, 10)
        DEFINE_FRAGMENT_SHADER_PARAMETERS_END()

        DEFINE_STREAM_OUTPUT()
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


    IMPLEMENTATION_FUNC_BUILD()
    {

		gl_texture_cube_array_descriptor _desc(10, 1024, gl_image_format::rgba, 12);
		auto _sky_boxes = std::make_shared<gl_texture_cube_array>(_desc);
		_sky_boxes->fill(0, gl_cube_face_index::negative_x, 0, 0, 0, nullptr, 100, 100);




        _render_target = builder.create_texture_2d(1024, 1024, gl_texture_pixel_format::rgba12_ui_nor, 1);
        //builder.create_renderbuffer()
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

        gl_graphics_pipeline_descriptor _graphics_pipeline_desc;
        // set pipeline parameters
        _graphics_pipeline_desc.parameters = vertex_processing_parameters;
        // set vertex processing shaders
        _graphics_pipeline_desc.vertex_processing.vertex_shading.shader = _vs;
        _graphics_pipeline_desc.vertex_processing.tessellation.control_shader = _tesc;
        _graphics_pipeline_desc.vertex_processing.tessellation.evaluation_shader = _tese;
        _graphics_pipeline_desc.vertex_processing.geometry_shading.shader = _gs;
        // set fragment shader
        _graphics_pipeline_desc.fragment_processing.fragment_shading.shader = _fs;
        auto _graphics_pipeline = builder.create_graphics_pipeline(_graphics_pipeline_desc);


        gl_compute_shader_descriptor _cs_desc;
        auto _cs = builder.create_compute_shader(_cs_desc);
        gl_compute_pipeline_descriptor _compute_pipeline_desc;
        // set compute shader
        _compute_pipeline_desc.compute_shading.shader = _cs;
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
