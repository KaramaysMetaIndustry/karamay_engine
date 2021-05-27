#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/variable/gl_variable.h"
#include "graphics/program/gl_program.h"


class gl_texture_1d;
class gl_texture_2d;
class gl_texture_2d_multisample;
class gl_texture_3d;
class gl_texture_1d_array;
class gl_texture_2d_array;
class gl_texture_2d_array_multisample;

class gl_program;
class gl_vertex_array;
class gl_element_array_buffer;
class gl_uniform_buffer;
class gl_shader_storage_buffer;
class gl_atomic_counter_buffer;
class gl_transform_feedback;
class gl_framebuffer;
class gl_default_framebuffer;



class gl_pipeline_base : public gl_object
{
public:

	gl_pipeline_base();

	virtual ~gl_pipeline_base();

public:

	gl_pipeline_base& construct(std::vector<std::string> shader_paths);

public:

	gl_pipeline_base& set_vertex_array(std::shared_ptr<gl_vertex_array> vertex_array);
	
	gl_pipeline_base& set_element_array(std::shared_ptr<gl_element_array_buffer> element_array_buffer);

	gl_pipeline_base& set_transform_feedback(std::shared_ptr<gl_transform_feedback> transform_feedback);
	
	gl_pipeline_base& add_uniform_buffers(const std::vector<std::shared_ptr<gl_uniform_buffer>>& uniform_buffers);
	
	gl_pipeline_base& add_shader_storage_buffers(const std::vector<std::shared_ptr<gl_shader_storage_buffer>>& shader_storage_buffers);
	
	gl_pipeline_base& add_atomic_counter_buffers(const std::vector<std::shared_ptr<gl_atomic_counter_buffer>>& atomic_counter_buffers);
	
	gl_pipeline_base& set_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer = nullptr);
	
	gl_pipeline_base& set_commands(std::function<void(void)> commands_lambda);

	template<typename T>
	gl_pipeline_base& add_uniforms(const std::vector<std::shared_ptr<gl_variable<T>>>& uniforms)
	{
		if (_program)
		{
			_program->add_uniforms(uniforms);
		}
		return *this;
	}


public:

	void render(std::float_t delta_time);

private:

	std::shared_ptr<gl_program> _program;

};