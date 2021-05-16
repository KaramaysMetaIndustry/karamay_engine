#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/program/gl_program.h"
#include "graphics/buffer/customization/gl_uniform_buffer.h"
#include "graphics/uniform/gl_uniform.h"
#include "graphics/buffer/customization/gl_shader_storage_buffer.h"
#include "graphics/buffer/customization/gl_atomic_count_buffer.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/context/gl_context.h"

class gl_pipeline_base : public gl_object
{
public:

	gl_pipeline_base();

	virtual ~gl_pipeline_base();

public:

	gl_pipeline_base& construct(std::vector<std::string> shader_paths);

public:

	gl_pipeline_base& set_vertex_kit(std::shared_ptr<gl_vertex_array> vertex_array, std::shared_ptr<gl_element_array_buffer> element_array_buffer = nullptr);
	
	gl_pipeline_base& set_transform_feedback(std::shared_ptr<gl_transform_feedback> transform_feedback, const std::vector<std::string>& varyings);
	
	template<typename T>
	gl_pipeline_base& add_immediate_uniforms(const std::vector<gl_uniform<T>>& uniforms);
	
	template<typename T>
	gl_pipeline_base& add_immediate_uniform_textures(const std::vector<std::shared_ptr<T>>& uniform_textures)
	{
		if (_program)
		{
			_program->add_immediate_uniform_textures(uniform_textures);
		}
		return *this;
	}
	
	gl_pipeline_base& add_uniform_buffers(const std::vector<std::shared_ptr<gl_uniform_buffer>>& uniform_buffers);
	
	gl_pipeline_base& add_shader_storage_buffers(const std::vector<std::shared_ptr<gl_shader_storage_buffer>>& shader_storage_buffers)
	{
		if (_program)
		{
			_program->add_shader_storage_buffers(shader_storage_buffers);
		}
		return *this;
	}
	
	gl_pipeline_base& add_atomic_count_buffers(const std::vector<std::shared_ptr<gl_atomic_count_buffer>>& atomic_count_buffers)
	{
		if (_program)
		{
			_program->add_atomic_count_buffers(atomic_count_buffers);
		}
		return *this;
	}	
	
	gl_pipeline_base& set_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer = nullptr)
	{
		return *this;
	}
	
	gl_pipeline_base& set_commands(std::function<void(void)> commands)
	{
		if (_program)
		{
			
		}
		return *this;
	}

public:

	void render(std::float_t delta_time);

private:

	std::shared_ptr<gl_program> _program;

};

template<typename T>
inline gl_pipeline_base& gl_pipeline_base::add_immediate_uniforms(const std::vector<gl_uniform<T>>& uniforms)
{
	if (_program)
	{
		_program->add_immediate_uniforms(uniforms);
	}
	return *this;
}
