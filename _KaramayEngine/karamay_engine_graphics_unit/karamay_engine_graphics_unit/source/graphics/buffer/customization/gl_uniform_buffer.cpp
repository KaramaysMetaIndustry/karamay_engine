#include "gl_uniform_buffer.h"

gl_uniform_buffer::gl_uniform_buffer()
{
}

gl_uniform_buffer::~gl_uniform_buffer()
{
}

void gl_uniform_buffer::update(std::float_t delta_time)
{
	if (_descriptor && _descriptor->is_dirty())
	{
		if (_descriptor->get_memory_layout() == gl_uniform_buffer_enum::layout::std140)
		{
			_fill_std140();
		}
		else
		{
			_fill_shared_packed();
		}
	}
}

void gl_uniform_buffer::_fill_std140()
{
	// must ensure the buffer was never used
	if (_descriptor && !_buffer)
	{
		_buffer = std::make_shared<gl_buffer>();
		_buffer->allocate(_descriptor->get_data_size());
		_buffer->fill(0, _descriptor->get_data_size(), _descriptor->get_data());
	}
}

void gl_uniform_buffer::_fill_shared_packed()
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
