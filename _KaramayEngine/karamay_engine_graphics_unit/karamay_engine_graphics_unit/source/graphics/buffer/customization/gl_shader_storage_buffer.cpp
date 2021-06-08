#include "gl_shader_storage_buffer.h"
#include "graphics/program/gl_program.h"

gl_shader_storage_buffer::~gl_shader_storage_buffer()
{
}

void gl_shader_storage_buffer::set_descriptor(std::shared_ptr<gl_shader_storage_buffer_descriptor> descriptor)
{
	_descriptor = descriptor;
}

std::shared_ptr<gl_shader_storage_buffer_descriptor> gl_shader_storage_buffer::get_descriptor()
{
	return _descriptor;
}

void gl_shader_storage_buffer::bind(std::uint32_t binding)
{
	glBindBufferRange(GL_SHADER_STORAGE_BUFFER, binding, _buffer->get_handle(), 0, _buffer->get_size());
	_binding = binding;
}
