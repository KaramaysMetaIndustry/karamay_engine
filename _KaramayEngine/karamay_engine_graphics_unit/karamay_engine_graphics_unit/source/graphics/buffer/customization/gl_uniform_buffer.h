#pragma once
#include "graphics/buffer/gl_buffer.h"

struct _shader_point_light_std140
{
	// ...
	glm::vec3 position; // Position of the point light
	float __DUMMY_PADDING0__; // This is just needed because of std140 layout padding rules

	glm::vec3 color; // Color of the point light
	float ambientFactor; // Ambient factor (how much this light contributes to the global lighting in any case)

	float constantAttenuation; // Constant attenuation factor of light with rising distance
	float linearAttenuation; // Lienar attenuation factor of light with rising distance
	float exponentialAttenuation; // Constant attenuation factor of light with rising distance
	GLint isOn; // Flag telling, if the light is on
};

namespace gl_uniform_buffer_enum
{
	enum class layout
	{
		shared, // must query ?
		packed, // must query
		std140, // no query
	};

	enum class matrix_layout
	{
		row_major,
		column_major
	};
}

struct gl_uniform_buffer_descriptor
{
	gl_uniform_buffer_enum::layout memory_layout;

	gl_uniform_buffer_enum::matrix_layout memory_matrix_layout;

	std::string block_name;

	void* _data;

	size_t _size;
	
	size_t size;
	
	bool is_dirty;

public:

	template<typename T>
	void add_uniform(T uniform)
	{
		const void* data = (void*)glm::value_ptr(uniform);
		const size_t size = sizeof(T);
		memcpy(_data, data, size);
		_size += size;
	}

	
	gl_uniform_buffer_descriptor() :
		memory_layout(gl_uniform_buffer_enum::layout::std140),
		memory_matrix_layout(gl_uniform_buffer_enum::matrix_layout::row_major),
		is_dirty(true)
	{

	}
};


class gl_uniform_buffer
{

public:
	
	gl_uniform_buffer();
	
	virtual ~gl_uniform_buffer();

public:

	void set_descriptor(std::shared_ptr<gl_uniform_buffer_descriptor> descriptor)
	{
		_descriptor = descriptor;
	}

	std::shared_ptr<gl_uniform_buffer_descriptor> get_descriptor() { return _descriptor; }
	
	void update(std::float_t delta_time);

	void bind(std::int32_t binding)
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, binding, _buffer->get_handle(), 0, _descriptor->size);
	}

	void unbind()
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, _binding, 0, 0, 0);
		_binding = 0;
	}

private:

	std::shared_ptr<gl_uniform_buffer_descriptor> _descriptor;

	std::shared_ptr<gl_buffer> _buffer;

	std::uint32_t _binding;

private:

	void _fill_std140()
	{
		if (_descriptor)
		{
			_buffer = std::make_shared<gl_buffer>();
			_buffer->allocate(_descriptor->size);
			_buffer->fill(0, _descriptor->size, _descriptor->data);
		}
	}

	void _fill_shared_packed()
	{
		if (_descriptor)
		{
			//const std::string& block_name = _descriptor->block_name;
			//
			//GLuint _program; 
			//GLint block_size;
			//GLbyte* block_buffer;
			//const GLchar* names[] = { "inner_color", "outer_color","radius_innes","raduis_outer" };
			////GLuint attrib_num = attrib_names.size();
			//std::vector<GLuint> indices(attrib_num);
			//std::vector<GLint> offsets(attrib_num);

			//// get block size
			//glGetActiveUniformBlockiv(_program, 
			//	glGetUniformBlockIndex(_program, block_name.c_str()), GL_UNIFORM_BLOCK_DATA_SIZE, &block_size);
			//// get block 
			//glGetUniformIndices(_program, attrib_num, attrib_names.data(), indices.data());
			//glGetActiveUniformsiv(_program, 4, indices.data(), GL_UNIFORM_OFFSET, offsets.data());

			////create ubo an fill it with data
			//	gl_buffer ubo;

			////bind the buffer to the block
			//	glBindBufferBase(GL_UNIFORM_BUFFER, block_index, ubo.get_handle());
		}
		
	}

};

