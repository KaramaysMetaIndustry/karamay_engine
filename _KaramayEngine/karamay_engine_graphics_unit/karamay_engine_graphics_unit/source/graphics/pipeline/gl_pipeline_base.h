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

public:

	/**
	 * construct your pipeline 
	 * @shader_paths
	 * 
	 */
	void construct(std::vector<std::string> shader_paths)
	{
		if (_program)
		{
			_program->construct(shader_paths);
		}
	}

public:
	
	/**
	 * 
	 */
	void set_transform_feedback_varyings(const std::vector<std::string>& varyings)
	{
		
	}

	void set_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer = nullptr)
	{
		_framebuffer = framebuffer;
	}

	void set_vertex_array(std::shared_ptr<gl_vertex_array> vertex_array) 
	{
		_vertex_array = vertex_array;
	}

	void set_element_array_buffer(std::shared_ptr<gl_element_array_buffer> element_array_buffer) 
	{}

	void set_uniform_buffer(std::shared_ptr<gl_uniform_buffer> uniform_buffer)
	{
		if (uniform_buffer && _program)
		{
			auto buffer = std::make_shared<gl_buffer>();
			buffer->fill(0, uniform_buffer->_size, uniform_buffer->_data);
		}
	}

	void set_uniform_buffers(const std::vector<std::shared_ptr<gl_uniform_buffer>>& uniform_buffers)
	{}

	void set_shader_storage_buffers(std::shared_ptr<gl_shader_storage_buffer> shader_storage_buffer)
	{}

	void set_shader_storage_buffers(const std::vector<std::shared_ptr<gl_shader_storage_buffer>>& shader_storage_buffers)
	{}

	void set_atomic_count_buffer(std::shared_ptr<gl_atomic_count_buffer> atomic_count_buffer)
	{

	}

public:

	void install()
	{
		
	}

	void enable()
	{
		if (_program)
		{
			_program->enable();
		}
	}

	void disable()
	{
		if (_program)
		{
			_program->disable();
		}
	}

private:
	
	void _bind_framebuffer()
	{
		if (_program)
		{
			_program->bind_framebuffer(_framebuffer);
		}
	}

	void _bind_vertex_array()
	{
		if (_program)
		{
			_program->bind_vertex_array(_vertex_array);
		}
	}

	void _bind_element_array_buffer()
	{
		
	}

	void _bind_transform_feedback()
	{
		
	}

	void _bind_uniform_buffers()
	{
		if (_program)
		{
		}
	}

	void _bind_shader_storage_buffers()
	{
		
	}

	void _bind_atomic_count_buffer()
	{
	
	}

	//~
	void _bind_texture_1d(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_1d> texture_1d)
	{
		if (_program)
		{
			_program->bind_texture_1d(unit, name, texture_1d);
		}
	}
	
	void _bind_texture_1d_array(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_1d_array> texture_1d_array)
	{
		if (_program)
		{
			_program->bind_texture_1d_array(unit, name, texture_1d_array);
		}
	}
	
	void _bind_texture_2d(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_2d> texture_2d)
	{
		if (_program)
		{
			_program->bind_texture_2d(unit, name, texture_2d);
		}
	}
	
	void _bind_texture_2d_array(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_2d_array> texture_2d_array)
	{
		if (_program)
		{
			_program->bind_texture_2d_array(unit, name, texture_2d_array);
		}
	}
	
	void _bind_texture_3d(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_3d> texture_3d)
	{
		if (_program)
		{
			_program->bind_texture_3d(unit, name, texture_3d);
		}
	}
	
	void _bind_texture_cube(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_cube> texture_cube)
	{
		if (_program)
		{
			_program->bind_texture_cube(unit, name, texture_cube);
		}
	}
	
	void bind_texture_cube_array(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_cube_array> texture_cube_array)
	{
		if (_program)
		{
			_program->bind_texture_cube_array(unit, name, texture_cube_array);
		}
	}
	
	void bind_texture_buffer(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_buffer> texture_buffer)
	{
		if (_program)
		{
			_program->bind_texture_buffer(unit, name, texture_buffer);
		}
	}
	
	void update_uniform_1f(const std::string& name, glm::vec1 value)
	{
		if (_program)
		{
			_program->update_uniform_1f(name, value);
		}
	}
	void update_uniform_2f(const std::string& name, glm::vec2 value)
	{
		if (_program)
		{
			_program->update_uniform_2f(name, value);
		}
	}
	void update_uniform_3f(const std::string& name, glm::vec3 value)
	{
		if (_program)
		{
			_program->update_uniform_3f(name, value);
		}
	}
	void update_uniform_4f(const std::string& name, glm::vec4 value)
	{
		if (_program)
		{
			_program->update_uniform_4f(name, value);
		}
	}

	void update_uniform_1d(const std::string& name, glm::dvec1 value)
	{
		if (_program)
		{
			_program->update_uniform_1d(name, value);
		}
	}
	void update_uniform_2d(const std::string& name, glm::dvec2 value)
	{
		if (_program)
		{
			_program->update_uniform_2d(name, value);
		}
	}
	void update_uniform_3d(const std::string& name, glm::dvec3 value)
	{
		if (_program)
		{
			_program->update_uniform_3d(name, value);
		}
	}
	void update_uniform_4d(const std::string& name, glm::dvec4 value)
	{
		if (_program)
		{
			_program->update_uniform_4d(name, value);
		}
	}

	void update_uniform_1i(const std::string& name, glm::ivec1 value)
	{
		if (_program)
		{
			_program->update_uniform_1i(name, value);
		}
	}
	void update_uniform_2i(const std::string& name, glm::ivec2 value)
	{
		if (_program)
		{
			_program->update_uniform_2i(name, value);
		}
	}
	void update_uniform_3i(const std::string& name, glm::ivec3 value)
	{
		if (_program)
		{
			_program->update_uniform_3i(name, value);
		}
	}
	void update_uniform_4i(const std::string& name, glm::ivec4 value)
	{
		if (_program)
		{
			_program->update_uniform_4i(name, value);
		}
	}

	void update_uniform_1ui(const std::string& name, glm::uvec1 value)
	{
		if (_program)
		{
			_program->update_uniform_1ui(name, value);
		}
	}
	void update_uniform_2ui(const std::string& name, glm::uvec2 value)
	{
		if (_program)
		{
			_program->update_uniform_2ui(name, value);
		}
	}
	void update_uniform_3ui(const std::string& name, glm::uvec3 value)
	{
		if (_program)
		{
			_program->update_uniform_3ui(name, value);
		}
	}
	void update_uniform_4ui(const std::string& name, glm::uvec4 value)
	{
		if (_program)
		{
			_program->update_uniform_4ui(name, value);
		}
	}

	void update_uniform_matrix_4x4f(const std::string& name, glm::fmat4x4 value)
	{
		if (_program)
		{
			_program->update_uniform_matrix_4x4f(name, value);
		}
	}
	void update_uniform_matrix_3x3f() {}
	void update_uniform_matrix_2x2f() {}

private:
	
	std::shared_ptr<gl_framebuffer> _framebuffer;

	std::shared_ptr<gl_vertex_array> _vertex_array;

	
	std::shared_ptr<gl_element_array_buffer> _element_array_buffer;

	std::shared_ptr<gl_buffer> _stripped_element_array_buffer;

	
	std::vector<std::shared_ptr<gl_uniform_buffer>> _uniform_buffers;

	std::vector<std::shared_ptr<gl_buffer>> _stripped_uniform_buffers;

	
	std::vector<std::shared_ptr<gl_shader_storage_buffer>> _shader_storage_buffers;

	std::vector<std::shared_ptr<gl_buffer>> _stripped_shader_storage_buffers;

	
	std::shared_ptr<gl_atomic_count_buffer> _atomic_count_buffer;

	std::shared_ptr<gl_buffer> _stripped_atomic_count_buffer;

};

