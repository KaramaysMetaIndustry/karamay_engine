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

	gl_pipeline_base(const std::string& xml_path) :
		_program(std::make_shared<gl_program>())
	{
		// parse xml
	}

	gl_pipeline_base(const std::vector<std::string>& shaders, 
		const std::shared_ptr<gl_vertex_array_descriptor>& va_desc,
		const std::shared_ptr<gl_element_array_buffer>& eab_desc,
		const std::shared_ptr<gl_transform_feedback_descriptor>& tf_desc,
		const std::vector<std::shared_ptr<gl_uniform_buffer_descriptor>>& ub_descs,
		const std::vector<std::shared_ptr<gl_shader_storage_buffer_descriptor>>& ssb_descs,
		const std::vector<std::shared_ptr<gl_atomic_counter_buffer_descriptor>>& acb_descs,
		const std::shared_ptr<gl_framebuffer>& framebuffer,
		const std::function<void(void)>& commands_lambda) :
		_program(std::make_shared<gl_program>())
	{

	}

	virtual ~gl_pipeline_base() {}

protected:

	std::shared_ptr<gl_program> _program;


protected:

	auto& set_shaders(const std::vector<std::string>& shaders)
	{
		if (_program)
		{
			_program->assembly(shaders);

			//_is_assembled = true;
		}

		return *this;
	}

	auto& set_vertex_specification(const std::shared_ptr<gl_vertex_array_descriptor>& va_desc, const std::shared_ptr<gl_element_array_buffer_descriptor>& eab_desc = nullptr)
	{
		if (_program && va_desc)
		{
			_program->set_vertex_array(std::make_shared<gl_vertex_array>(va_desc));
			
			if (eab_desc)
			{
				_program->set_element_array_buffer(std::make_shared<gl_element_array_buffer>(eab_desc));
			}
		}
		return *this;
	}

	auto& set_transform_feedback(const std::shared_ptr<gl_transform_feedback_descriptor>& tf_desc)
	{
		if (_program)
		{
			_program->set_transform_feedback(std::make_shared<gl_transform_feedback>(tf_desc));
		}
		return *this;
	}

	auto& add_uniform_buffer(const std::shared_ptr<gl_uniform_buffer_descriptor>& ub_desc)
	{
		if (ub_desc && _program)
		{
			_program->add_uniform_buffer(std::make_shared<gl_uniform_buffer>(ub_desc));
		}

		return *this;
	}

	auto& add_shader_storage_buffer(const std::shared_ptr<gl_shader_storage_buffer_descriptor>& ssb_desc)
	{
		if (ssb_desc && _program)
		{
			_program->add_shader_storage_buffer(std::make_shared<gl_shader_storage_buffer>(ssb_desc));
		}
		
		return *this;
	}

	auto& add_atomic_counter_buffer(const std::shared_ptr<gl_atomic_counter_buffer_descriptor>& acb_desc)
	{
		if (acb_desc && _program)
		{
			_program->add_atomic_counter_buffer(std::make_shared<gl_atomic_counter_buffer>(acb_desc));
		}

		return *this;
	}

	template<typename T>
	auto& add_uniform(const T& value)
	{
		if (_program)
		{
			_program->add_uniform(value);
		}

		return *this;
	}
	
	template<typename T>
	auto& add_texture(const std::shared_ptr<T>& texture)
	{
		if (texture && _program)
		{
			_program->add_texture(texture);
		}
	}

	auto& set_framebuffer(const std::shared_ptr<gl_framebuffer>& framebuffer = nullptr)
	{
		if (_program)
		{
			if(framebuffer)
				_program->set_framebuffer(framebuffer);
			_program->set_framebuffer();
		}

		return *this;
	}

	void set_commands(const std::function<void(void)>& commands_lambda)
	{
		if (_program)
		{
			_program->set_commands(commands_lambda);
		}
	}

public:

	template<typename T>
	bool update_uniform_buffer_item(const std::string& block_name, const std::string item_name, const T& value)
	{}

	template<typename T>
	bool update_shader_storage_buffer_item(const std::string& block_name, const std::string& item_name, const T& value)
	{}

	template<typename T>
	bool update_atomic_counter_buffer_item(const std::string& block_name, const std::string& item_name, const T& value)
	{}

	template<typename T>
	bool update_uniform(const std::string& name, const T& value)
	{}

	template<typename T>
	bool update_texture(const std::string& name, const std::shared_ptr<T>& texture)
	{}




};