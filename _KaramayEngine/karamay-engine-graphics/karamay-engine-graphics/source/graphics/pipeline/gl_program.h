#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/shader/gl_shader.h"
#include "graphics/buffer/gl_uniform_buffer.h"

class gl_program final : public gl_object
{
public:
	void attach_shader(const std::shared_ptr<gl_shader> shader);

	void link(bool is_separable);

	void detach_all_shaders();

public:
	void enable();

	void disable();

public:
	void set_uniform_block(const GLchar* block_name, std::vector<const GLchar*> attrib_names)
	{
		// fetch the block info
		GLuint block_index = glGetUniformBlockIndex(_handle,block_name);
		GLint block_size;
		glGetActiveUniformBlockiv(_handle, block_index, GL_UNIFORM_BLOCK_DATA_SIZE, &block_size);
		GLbyte* block_buffer;

		// pepare data
		//const GLchar* names[] = { "inner_color", "outer_color","radius_innes","raduis_outer" };
		GLuint attrib_num = attrib_names.size();
		std::vector<GLuint> indices(attrib_num);
		std::vector<GLint> offsets(attrib_num);
		glGetUniformIndices(_handle, attrib_num, attrib_names.data(), indices.data());
		glGetActiveUniformsiv(_handle, 4, indices.data(), GL_UNIFORM_OFFSET, offsets.data());
		
		// create ubo an fill it with data
		gl_uniform_buffer ubo;
		
		// bind the buffer to the block
		glBindBufferBase(GL_UNIFORM_BUFFER, block_index, ubo.get_handle());
	}

	void set_uniform1f(const GLchar* name, GLfloat value)
	{
		glUniform1f(glGetAttribLocation(_handle, name), value);
	}

private:
	std::vector<GLuint> shader_handles;

public:
	gl_program();
	
	virtual ~gl_program();
};

