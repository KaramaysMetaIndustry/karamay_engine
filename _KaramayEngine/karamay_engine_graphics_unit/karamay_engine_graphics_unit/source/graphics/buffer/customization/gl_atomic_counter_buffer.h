#pragma once
#include "graphics/buffer/gl_buffer.h"

struct gl_atomic_counter_buffer_binding_info
{
	std::string block_name;

	std::shared_ptr<gl_buffer> buffer;

	std::size_t offset;

	std::size_t size;
};

class gl_atomic_counter_buffer
{
public:

	gl_atomic_counter_buffer();
	
	virtual ~gl_atomic_counter_buffer();

private:

	std::shared_ptr<gl_buffer> _ref_buffer;

	std::size_t _offset;

	std::size_t _size;

	std::string _template_code;

public:

	void fill(const std::vector<std::string>& variable_names)
	{
		// fill buffer
		_size = sizeof(GLuint) * variable_names.size();
		_ref_buffer->fill(_offset, _size, nullptr);
		
		//_generate_template_code(variable_names);
	}

	void bind(std::uint32_t binding)
	{
		glBindBufferRange(GL_ATOMIC_COUNTER_BUFFER, binding, _ref_buffer->get_handle(), 0, 100);
	}

	void bind()
	{

	}

private:

	//void _generate_template_code(const std::vector<std::string>& variable_names)
	//{
	//	// generate template code
	//	const std::regex pattern("layout (binding = @, offset = $) uniform atomic_uint *;");
	//	std::vector<std::string> code_lines;
	//	std::uint32_t binding = 0;
	//	for (size_t i = 0; i < variable_names.size(); ++i)
	//	{
	//		std::uint32_t offset = 4 * i;
	//		variable_names[i];

	//		code_lines.push_back("");
	//	}
	//}


};

