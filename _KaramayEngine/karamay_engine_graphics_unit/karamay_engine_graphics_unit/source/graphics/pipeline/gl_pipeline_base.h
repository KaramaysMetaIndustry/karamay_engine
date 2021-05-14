#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/program/gl_program.h"
#include "graphics/buffer/customization/gl_uniform_buffer.h"
#include "graphics/buffer/customization/gl_shader_storage_buffer.h"
#include "graphics/buffer/customization/gl_atomic_count_buffer.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/context/gl_context.h"

class gl_pipeline_base : public gl_object
{
public:
	
	gl_pipeline_base();
	
	virtual ~gl_pipeline_base();

private:

	std::shared_ptr<gl_context> _context;

	std::shared_ptr<gl_program> _program;

	std::unordered_map<std::string, std::shared_ptr<gl_pipeline_base>> _pipelines;

public:

	/**
	 * construct your pipeline 
	 * @shader_paths
	 * 
	 */
	gl_pipeline_base& construct(std::vector<std::string> shader_paths)
	{
		if (_program)
		{
			_program->construct(shader_paths);
		}

		return *this;
	}

	gl_pipeline_base& operator[] (const std::string& name) {}
	gl_pipeline_base& operator[] (std::vector<std::pair<std::string, std::string>>) {}

public:
	
	gl_pipeline_base& transform_feedback_varyings(const std::vector<std::string>& varyings)
	{
		
	}
	gl_pipeline_base& add_transform_feedback(std::shared_ptr<gl_transform_feedback> transform_feedback, const std::vector<std::string>& varyings)
	{}
	gl_pipeline_base& add_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer = nullptr)
	{
	}
	gl_pipeline_base& add_vertex_kit(std::shared_ptr<gl_vertex_array> vertex_array = nullptr, std::shared_ptr<gl_element_array_buffer> element_array_buffer = nullptr)
	{
	}
	gl_pipeline_base& add_element_array_buffer(std::shared_ptr<gl_element_array_buffer> element_array_buffer) 
	{}
	gl_pipeline_base& add_uniform_buffers(std::vector<std::shared_ptr<gl_uniform_buffer>> uniform_buffers)
	{
		if (uniform_buffer && _program)
		{
			auto buffer = std::make_shared<gl_buffer>();
			buffer->fill(0, uniform_buffer->_size, uniform_buffer->_data);
		}
	}
	gl_pipeline_base& add_shader_storage_buffers(std::vector<std::shared_ptr<gl_shader_storage_buffer>> shader_storage_buffers)
	{}
	gl_pipeline_base& add_atomic_count_buffers(std::vector<std::shared_ptr<gl_atomic_count_buffer>> atomic_count_buffers)
	{

	}

	gl_pipeline_base& add_texture_2ds(std::vector<std::shared_ptr<gl_texture_2d>> texture_2ds) {}

public:

	void enable()
	{
		if (_program)
		{
			_program->install();
			_program->enable();
		}
	}

	void run() {}

	void disable()
	{
		if (_program)
		{
			_program->disable();
			_program->uninstall();
		}
	}

};

