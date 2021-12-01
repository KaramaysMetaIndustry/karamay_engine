#ifndef GL_TEST_RENDERER_H
#define GL_TEST_RENDERER_H

#include "graphics/pipeline/graphics/gl_graphics_pipeline.h"
#include "graphics/glsl/opaque_t/glsl_sampler.h"
#include "graphics/gltf/gltf_scene.h"
#include "graphics/renderer/gl_renderer.h"

class gl_test_renderer : public gl_renderer
{
public:
	gl_test_renderer() 
	{
		_exit = false;
	}

	void initialize()
	{
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		auto base_color_tex = builder.texture_2d(8, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		base_color_tex->build_mipmaps();
		auto metallic_tex = builder.texture_2d(8, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		metallic_tex->build_mipmaps();
		auto emiss_tex = builder.texture_2d(8, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		emiss_tex->build_mipmaps();
		auto normal_tex = builder.texture_2d(8, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		normal_tex->build_mipmaps();
		auto occlusion_tex = builder.texture_2d(8, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		occlusion_tex->build_mipmaps();
		auto sky_box_tex = builder.texture_cube(1, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		sky_box_tex->build_mipmaps();
		auto practicle_tex = builder.texture_3d(1, 1024, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		practicle_tex->build_mipmaps();

		auto _baked_vertices_fb = builder.framebuffer(1920, 1080);

		auto _mesh_pipeline = builder.graphics_pipeline();
		auto _materials_combiner = builder.compute_pipeline();

		_mesh_pipeline->vertex_launcher();
		_mesh_pipeline->program()->sampler2D("baseColor")->set_texture_2d(base_color_tex);

		_finish_commands();
		_mesh_pipeline->enable();
		_mesh_pipeline->draw_arrays(0, 2048);
		_mesh_pipeline->draw_elements(0, 48200);
		_mesh_pipeline->disable();
		_flush_commands();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL GL_POINT
		//glFrontFace(GL_CW);//default GL_CW

		//glEnable(GL_COLOR_BUFFER_BIT);
		//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glEnable(GL_ACCUM_BUFFER_BIT);
		//glClearAccum(1.0f, 0.2f, 1.0f, 1.0f);

		// when current frag-z < 1.0, keep it
		// fragShader write its z value before working
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);
		//glDepthMask(GL_TRUE);
		//glClearDepth(1.0f);

		//glEnable(GL_STENCIL_TEST);
		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		//glStencilMask(GL_TRUE);
		//glClearStencil(0);

	}

	void render(float delta_time)
	{
		if (!_mesh_pipeline) return;

		glClear(GL_COLOR_BUFFER_BIT);

		_mesh_pipeline->enable();

		_mesh_pipeline->draw_arrays(0, 1024);

		_mesh_pipeline->disable();
	}

	bool should_exit()
	{
		return _exit;
	}

	void set_exit(bool exit)
	{
		_exit = exit;
	}

private:

	std::unique_ptr<gl_graphics_pipeline> _mesh_pipeline;

	bool _exit;
};

#endif