#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"

#define attribute_offset(offset) (const GLvoid*)(offset * sizeof(GLfloat))


namespace gl_vertex_array_enum
{

}


struct gl_vertex_attribute_layout
{
	std::uint32_t total_size;
	std::uint32_t attribute_size;
	std::uint32_t components_num;
	std::uint32_t components_type;
	std::uint32_t divisor;
};

class gl_vertex_array_descriptor final
{

public:
	
	gl_vertex_array_descriptor()
	{

	}
	
	~gl_vertex_array_descriptor()
	{

	}

	void add_attributes(const std::vector<glm::vec3>& attributes)
	{
		const std::uint8_t* _tmp_data = (std::uint8_t*)attributes.data();
		const std::size_t _tmp_size = attributes.size() * sizeof(glm::vec3);

		for (std::size_t i = 0; i < _tmp_size; ++i)
		{
			_data.push_back(_tmp_data[i]);
		}

		gl_vertex_attribute_layout _layout;
		_layout.components_num = glm::vec3::length();
		_layout.components_type = _get_component_type<glm::vec3::value_type>();
		_layout.attribute_size = sizeof(glm::vec3);
		_layouts.push_back(_layout);
	}

	template<typename T>
	void add_attributes(const std::vector<T>& attributes)
	{
		const std::uint8_t* _tmp_data = (std::uint8_t*)attributes.data();
		const std::size_t _tmp_size = attributes.size() * sizeof(glm::vec3);

		for (std::size_t i = 0; i < _tmp_size; ++i)
		{
			_data.push_back(_tmp_data[i]);
		}

		gl_vertex_attribute_layout _layout;
		_layout.components_num = T::length();
		_layout.components_type = _get_component_type<T::value_type>();
		_layout.attribute_size = sizeof(T);
		_layouts.push_back(_layout);
	}

	template<typename T>
	std::uint32_t _get_component_type()
	{
		return 0;
	}

	template<>
	std::uint32_t _get_component_type<float>()
	{
		return GL_FLOAT;
	}

	template<>
	std::uint32_t _get_component_type<unsigned int>()
	{
		return GL_UNSIGNED_INT;
	}

	const void* get_data() const
	{
		return _data.data();
	}

	const std::size_t get_data_size() const
	{
		return _size;
	}

	const std::vector<gl_vertex_attribute_layout> get_layouts() const
	{
		return _layouts;
	}

private:

	std::vector<std::uint8_t> _data;

	std::size_t _size;

	std::vector<gl_vertex_attribute_layout> _layouts;

};


class gl_vertex_array : public gl_object
{
public:

	gl_vertex_array();

	virtual ~gl_vertex_array();

public:
	
	void set(std::shared_ptr<gl_vertex_array_descriptor> descriptor)
	{
		_descriptor = descriptor;
	}

	void update(std::float_t delta_time)
	{
		_fill();
	}

private:

	std::shared_ptr<gl_vertex_array_descriptor> _descriptor;

	std::shared_ptr<gl_buffer> _buffer;

	std::vector<std::uint32_t> _indices;



	void _fill()
	{

#define ATTRIBUTE_OFFSET(offset) (const GLvoid*)(offset * sizeof(GLfloat))
		
		if (_descriptor)
		{
			// fill the buffer
			const size_t _alloc_size = _descriptor->get_data_size();
			_buffer = std::make_shared<gl_buffer>();
			_buffer->allocate(_alloc_size);
			_buffer->fill(0, _alloc_size, _descriptor->get_data());

			// set pointers
			const std::vector<gl_vertex_attribute_layout>& layouts = _descriptor->get_layouts();
			std::uint32_t offset = 0;
			for (std::uint32_t i = 0; i < layouts.size(); ++i)
			{
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, 
					layouts[i].components_num, 
					layouts[i].components_type, GL_FALSE, 
					layouts[i].attribute_size, ATTRIBUTE_OFFSET(offset));
				offset += layouts[i].total_size;
			}
		}
	}


public:
	
	void bind()
	{
		glBindVertexArray(_handle);
	}

	void unbind()
	{
		glBindVertexArray(0);
	}

	void enable_vertex_attributes()
	{
		if (_descriptor)
		{
			const auto& _layouts = _descriptor->get_layouts();
			for (std::uint32_t i = 0; i < _layouts.size(); ++i)
			{
				glEnableVertexAttribArray(i);
			}
		}
	}

	void disable_vertex_attributes()
	{
		if (_descriptor)
		{
			const auto& _layouts = _descriptor->get_layouts();
			for (std::uint32_t i = 0; i < _layouts.size(); ++i)
			{
				glDisableVertexAttribArray(i);
			}
		}
	}

};

