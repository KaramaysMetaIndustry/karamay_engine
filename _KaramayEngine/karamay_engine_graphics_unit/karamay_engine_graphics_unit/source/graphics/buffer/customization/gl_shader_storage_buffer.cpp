#include "gl_shader_storage_buffer.h"

gl_shader_storage_buffer::gl_shader_storage_buffer()
{
}

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

void gl_shader_storage_buffer::update(std::float_t delta_time)
{
	
}
