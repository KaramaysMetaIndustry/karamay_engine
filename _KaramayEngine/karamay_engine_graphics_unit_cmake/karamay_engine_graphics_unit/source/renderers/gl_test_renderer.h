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

	~gl_test_renderer()
	{}

public:

	void initialize()
	{
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		auto base_color_tex = builder.create_texture_2d("base_color_tex", 8, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		base_color_tex->build_mipmaps();
		auto metallic_tex = builder.create_texture_2d("metallic_tex", 8, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		metallic_tex->build_mipmaps();
		auto emiss_tex = builder.create_texture_2d("emiss_tex", 8, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		emiss_tex->build_mipmaps();
		auto normal_tex = builder.create_texture_2d("normal_tex", 8, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		normal_tex->build_mipmaps();
		auto occlusion_tex = builder.create_texture_2d("occlusion_tex", 8, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		occlusion_tex->build_mipmaps();
		auto sky_box_tex = builder.create_texture_cube("sky_box_tex", 1, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		sky_box_tex->build_mipmaps();
		auto practicle_tex = builder.create_texture_3d("practicle_tex", 1, 1024, 1024, 1024, gl_texture_internal_format::RGBA_F32);
		practicle_tex->build_mipmaps();

		auto _color0_attch = builder.create_renderbuffer("color0_attach", 1920, 1080, gl_renderbuffer_internal_format::RGBA_F32);
		auto _color1_attch = builder.create_renderbuffer("color1_attach", 1920, 1080, gl_renderbuffer_internal_format::RGBA_F32);
		auto _color2_attch = builder.create_renderbuffer("color2_attach", 1920, 1080, gl_renderbuffer_internal_format::RGBA_F32);
		auto _depth_stencil_attach = builder.create_renderbuffer("depth_stencil_attach", 1920, 1080, gl_renderbuffer_internal_format::RGBA_F32);

		auto _framebuffer_0 = builder.create_framebuffer("framebuffer_0", 1920, 1080);

		auto _mesh_pipeline = builder.create_graphics_pipeline("mesh_pipeline");
		auto _deferred_lighting_pipeline = builder.create_graphics_pipeline("deferred_lighting_pipeline");

		_framebuffer_0->set_color_attachment(0, _color0_attch);
		_framebuffer_0->set_color_attachment(1, _color1_attch);
		_framebuffer_0->set_color_attachment(2, _color2_attch);
		_framebuffer_0->set_depth_stencil_attachment(_depth_stencil_attach);
		
		_mesh_pipeline->program()->sampler2D("baseColorMap")->set_texture_2d(base_color_tex);
		_mesh_pipeline->program()->sampler2D("normalMap")->set_texture_2d(normal_tex);
		_mesh_pipeline->program()->sampler2D("occlusionMap")->set_texture_2d(occlusion_tex);
		_mesh_pipeline->program()->sampler2D("metallicMap")->set_texture_2d(metallic_tex);
		_mesh_pipeline->program()->sampler2D("emissiveMap")->set_texture_2d(emiss_tex);
		_mesh_pipeline->program()->image2D("readbackPosition")->set_image_2d(sky_box_tex, gl_cube_face_index::POSITIVE_X, 0);
		_mesh_pipeline->program()->image3D("readbackPosition")->set_image_3d(practicle_tex, 0);


		_mesh_pipeline->render_target()->set_framebuffer(_framebuffer_0);

		//_deferred_lighting_pipeline->program()->sampler2D("inputPositionTex")->set_texture_2d(_color0_attch);

		
	}

	void render(float delta_time)
	{
		auto _mesh_pipeline = builder.graphics_pipeline("mesh_pipeline");
		auto _deferred_lighting_pipeline = builder.graphics_pipeline("deferred_lighting_pipeline");

		if (_mesh_pipeline && _deferred_lighting_pipeline)
		{
			// draw pixels to the framebuffer
			// vertex processing pass
			_mesh_pipeline->enable();
			auto _fence = _mesh_pipeline->draw_arrays(0, 1024); // async task
			_mesh_pipeline->disable();

			// fetch color attachment from framebuffer
			auto _fb0 = _mesh_pipeline->render_target()->get_framebuffer();
			// wait vertex processing pass finished
			_fence->client_wait(0);

			// bind the default framebuffer and clear
			// the next pass will draw pixels to the default framebuffer
			auto _device = gl_default_framebuffer::get_instance();
			_device->bind();
			_device->clear_color_buffer();
			_device->unbind();

			// deferred lighting pass
			_deferred_lighting_pipeline->enable();
			_deferred_lighting_pipeline->draw_arrays(0, 1024);
			_deferred_lighting_pipeline->disable();
		}

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

	bool _exit;
};

#endif