#pragma once
#include "graphics/buffer/gl_buffer.h"
#include "graphics/variable/gl_variable.h"

class gl_program;

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
		std140, 
		shared, 
		packed, 
	};

	enum class matrix_layout
	{
		row_major, 
		column_major 
	};

	enum class reference_style
	{
		global,
		instanced,
		array_instanced,
	};

	enum class reference_shader
	{
		vertex_shader,
		tessc_shader,
		tesse_shader,
		geom_shader,
		fragment_shader
	};

}

class gl_uniform_buffer_descriptor
{

public:

	gl_uniform_buffer_descriptor();

public:

	void add_uniform(const std::shared_ptr<gl_variable>& item);

	void add_uniforms(const std::vector<std::shared_ptr<gl_variable>>& items)
	{
		_items.insert(_items.cend(), items.cbegin(), items.cend());
		_is_dirty = true;
	}

	void clear_uniforms();

private:

	gl_uniform_buffer_enum::layout _memory_layout;

	gl_uniform_buffer_enum::matrix_layout _memory_matrix_layout;

	std::string _block_name;

	std::vector<std::shared_ptr<gl_variable>> _items;

	std::uint8_t _is_dirty;

public:
	
	inline const gl_uniform_buffer_enum::layout get_memory_layout() const
	{
		return _memory_layout;
	}

	inline const std::string& get_block_name() const
	{
		return _block_name;
	}

	inline const auto& get_items()
	{
		return _items;
	}

	inline const std::uint8_t is_dirty() const
	{
		return _is_dirty;
	}

	inline void set_dirty(bool dirty) { _is_dirty = dirty; }

	inline void set_block_name(const std::string& block_name) { _block_name = block_name; }

};


class gl_uniform_buffer final
{
public:
	
	gl_uniform_buffer(const std::shared_ptr<gl_uniform_buffer_descriptor>& descriptor);

public:

	void bind(std::int32_t binding, gl_program& program);

	void unbind();

	std::shared_ptr<gl_uniform_buffer_descriptor> get_descriptor()
	{
		return _descriptor;
	}

private:

	std::shared_ptr<gl_uniform_buffer_descriptor> _descriptor;

	std::shared_ptr<gl_buffer> _buffer;

	std::uint32_t _binding;

private:

	void _fill_shared_packed(const gl_program& program);

	void _fill_std140();

public:

	~gl_uniform_buffer();


};