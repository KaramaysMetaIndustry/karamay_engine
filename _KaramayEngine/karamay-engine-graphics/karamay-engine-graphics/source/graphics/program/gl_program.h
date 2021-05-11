#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/shader/gl_shader.h"
#include "graphics/buffer/gl_buffer.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/texture/gl_texture.h"
#include "graphics/framebuffer/gl_framebuffer.h"

enum class gl_buffer_mode
{
	INTERLEAVED = GL_INTERLEAVED_ATTRIBS,
	SEPARATE_ATTRIBS = GL_SEPARATE_ATTRIBS
};


class gl_program final : public gl_object
{
public:

	gl_program();

	virtual ~gl_program();

private:
	
	std::vector<std::shared_ptr<gl_shader>> shaders;

public:

	void construct(std::vector<std::string> shader_paths)
	{
		for (const auto& path : shader_paths)
		{
			auto shader = std::make_shared<gl_shader>();
			if (shader)
			{
				shader->load(path);
				shader->compile();
				glAttachShader(_handle, shader->get_handle());
				shaders.push_back(shader);
			}
		}

		/*if (is_separable)
			glProgramParameteri(_handle, GL_PROGRAM_SEPARABLE, GL_TRUE);*/

		/*glBindAttribLocation(_handle, 0, "Position");
		glBindFragDataLocation(_handle, 0, "FragColor");*/

		glLinkProgram(_handle);
	}

	// set transform feedback output varyings
	void set_transform_feedback_output_varyings(const std::vector<std::string>& varyings)
	{
		glTransformFeedbackVaryings(_handle, varyings.size(), nullptr, static_cast<GLenum>(gl_buffer_mode::INTERLEAVED));
		glLinkProgram(_handle);
	}

public:
	
	/**
	 * set target framebuffer the pipeline will render to in new pass
	 */
	void bind_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer)
	{
		if (framebuffer) {
			framebuffer->bind();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	/**
	 * set vertex array for pipeline, it will be pulled by [pipeline vertex puller] when draw commands sent out
	 */
	void bind_vertex_array(std::shared_ptr<gl_vertex_array> vertex_array)
	{
		if (vertex_array) {
			vertex_array->bind();
			vertex_array->enable_vertex_attributes();
		}
	}

	// set element array buffer
	void bind_element_array_buffer(std::shared_ptr<gl_buffer> element_array_buffer)
	{
		if (element_array_buffer) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_array_buffer->get_handle());
		}
	}

	// set uniform buffer
	void bind_uniform_buffer(std::uint32_t binding, const std::string& block_name, std::shared_ptr<gl_buffer> buffer)
	{
		if (buffer)
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, buffer->get_handle());
			glUniformBlockBinding(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), binding);
		}
	}

	// layout (binding = 0, std430) buffer [block_name]
	void bind_shader_storage_buffer(std::uint32_t binding, const std::string& block_name, std::shared_ptr<gl_buffer> buffer)
	{
		if (buffer)
		{
			GLuint block_index = glGetProgramResourceIndex(_handle, GL_SHADER_STORAGE_BLOCK, block_name.c_str());
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, buffer->get_handle());
			glShaderStorageBlockBinding(_handle, block_index, binding);
		}
	}

	// layout (binding = 0, offset = 0) uniform atomic_uint [name]
	void bind_atomic_count_buffer(std::uint32_t binding, std::shared_ptr<gl_buffer> buffer)
	{
		glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, binding, buffer->get_handle());
	}

	// set texture
	void bind_texture_1d(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_1d> texture_1d)
	{
		if (texture_1d) {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_1D, texture_1d->get_handle());
			update_uniform_1ui(name, unit);
		}
	}
	void bind_texture_1d_array(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_1d_array> texture_1d_array)
	{
		if (texture_1d_array) {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_1D_ARRAY, texture_1d_array->get_handle());
			update_uniform_1ui(name, unit);
		}
	}
	void bind_texture_2d(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_2d> texture_2d)
	{
		if (texture_2d) {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, texture_2d->get_handle());
			update_uniform_1ui(name, unit);
		}
	}
	void bind_texture_2d_array(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_2d_array> texture_2d_array)
	{
		if (texture_2d_array) {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D_ARRAY, texture_2d_array->get_handle());
			update_uniform_1ui(name, unit);
		}
	}
	void bind_texture_3d(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_3d> texture_3d)
	{
		if (texture_3d) {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_3D, texture_3d->get_handle());
			update_uniform_1ui(name, unit);
		}
	}
	void bind_texture_cube(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_cube> texture_cube)
	{
		if (texture_cube) {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture_cube->get_handle());
			update_uniform_1ui(name, unit);
		}
	}
	void bind_texture_cube_array(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_cube_array> texture_cube_array)
	{
		if (texture_cube_array) {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, texture_cube_array->get_handle());
			update_uniform_1ui(name, unit);
		}
	}
	void bind_texture_buffer(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_buffer> texture_buffer)
	{
		if (texture_buffer) {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_BUFFER, texture_buffer->get_handle());
			update_uniform_1ui(name.c_str(), unit);
		}
	}

	// set uniform vec and matrix
	void update_uniform_1f(const std::string& name, glm::vec1 value)
	{
		glUniform1fv(glGetAttribLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	void update_uniform_2f(const std::string& name, glm::vec2 value)
	{
		glUniform2fv(glGetAttribLocation(_handle, name.c_str()), 2, glm::value_ptr(value));
	}
	void update_uniform_3f(const std::string& name, glm::vec3 value)
	{
		glUniform3fv(glGetAttribLocation(_handle, name.c_str()), 3, glm::value_ptr(value));
	}
	void update_uniform_4f(const std::string& name, glm::vec4 value)
	{
		glUniform4fv(glGetAttribLocation(_handle, name.c_str()), 4, glm::value_ptr(value));
	}
		 
	void update_uniform_1f(const std::string& name, std::float_t value) {}
	void update_uniform_2f(const std::string& name, std::float_t value0, std::float_t value1) {}
	void update_uniform_3f(const std::string& name, std::float_t value0, std::float_t value1, std::float_t value2) {}
	void update_uniform_4f(const std::string& name, std::float_t value0, std::float_t value1, std::float_t value2, std::float_t value3) {}
		 
	void update_uniform_1d(const std::string& name, glm::dvec1 value)
	{
		glUniform1dv(glGetAttribLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	void update_uniform_2d(const std::string& name, glm::dvec2 value)
	{
		glUniform2dv(glGetAttribLocation(_handle, name.c_str()), 2, glm::value_ptr(value));
	}
	void update_uniform_3d(const std::string& name, glm::dvec3 value)
	{
		glUniform3dv(glGetAttribLocation(_handle, name.c_str()), 3, glm::value_ptr(value));
	}
	void update_uniform_4d(const std::string& name, glm::dvec4 value)
	{
		glUniform4dv(glGetAttribLocation(_handle, name.c_str()), 4, glm::value_ptr(value));
	}
	
	void update_uniform_1d(const std::string& name, std::double_t value)
	{
		glUniform1d(glGetAttribLocation(_handle, name.c_str()), value);
	}
	void update_uniform_2d(const std::string& name, std::double_t value0, std::double_t value1)
	{
		glUniform2d(glGetAttribLocation(_handle, name.c_str()), value0, value1);
	}
	void update_uniform_3d(const std::string& name, std::double_t value0, std::double_t value1, std::double_t value2)
	{
		glUniform3d(glGetAttribLocation(_handle, name.c_str()), value0, value1, value2);
	}
	void update_uniform_4d(const std::string& name, std::double_t value0, std::double_t value1, std::double_t value2, std::double_t value3)
	{
		glUniform4d(glGetAttribLocation(_handle, name.c_str()), value0, value1, value2, value3);
	}

	void update_uniform_1i(const std::string& name, glm::ivec1 value)
	{
		glUniform1iv(glGetAttribLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	void update_uniform_2i(const std::string& name, glm::ivec2 value)
	{
		glUniform2iv(glGetAttribLocation(_handle, name.c_str()), 2, glm::value_ptr(value));
	}
	void update_uniform_3i(const std::string& name, glm::ivec3 value)
	{
		glUniform3iv(glGetAttribLocation(_handle, name.c_str()), 3, glm::value_ptr(value));
	}
	void update_uniform_4i(const std::string& name, glm::ivec4 value)
	{
		glUniform4iv(glGetAttribLocation(_handle, name.c_str()), 4, glm::value_ptr(value));
	}
		 
	void update_uniform_1i(const std::string& name, std::int32_t value) {}
	void update_uniform_2i(const std::string& name, std::int32_t value0, std::int32_t value1) {}
	void update_uniform_3i(const std::string& name, std::int32_t value0, std::int32_t value1, std::int32_t value2) {}
	void update_uniform_4i(const std::string& name, std::int32_t value0, std::int32_t value1, std::int32_t value2, std::int32_t value3) {}

	void update_uniform_1ui(const std::string& name, glm::uvec1 value)
	{
		glUniform1uiv(glGetAttribLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	void update_uniform_2ui(const std::string& name, glm::uvec2 value)
	{
		glUniform2uiv(glGetAttribLocation(_handle, name.c_str()), 2, glm::value_ptr(value));
	}
	void update_uniform_3ui(const std::string& name, glm::uvec3 value)
	{
		glUniform3uiv(glGetAttribLocation(_handle, name.c_str()), 3, glm::value_ptr(value));
	}
	void update_uniform_4ui(const std::string& name, glm::uvec4 value)
	{
		glUniform4uiv(glGetAttribLocation(_handle, name.c_str()), 4, glm::value_ptr(value));
	}

	void update_uniform_1ui(const std::string& name, std::uint32_t value) {}
	void update_uniform_2ui(const std::string& name, std::uint32_t value0, std::uint32_t value1) {}
	void update_uniform_3ui(const std::string& name, std::uint32_t value0, std::uint32_t value1, std::uint32_t value2) {}
	void update_uniform_4ui(const std::string& name, std::uint32_t value0, std::uint32_t value1, std::uint32_t value2, std::uint32_t value3) {}

	void update_uniform_matrix_4x4f(const std::string& name, glm::fmat4x4 value)
	{
		glUniformMatrix4fv(glGetAttribLocation(_handle, name.c_str()), 16, GL_TRUE, glm::value_ptr(value));
	}
	void update_uniform_matrix_3x3f() {}
	void update_uniform_matrix_2x2f() {}

	void set_uniform_block(const GLchar* block_name, std::vector<const GLchar*> attrib_names)
	{
		// fetch the block info
		GLuint block_index = glGetUniformBlockIndex(_handle, block_name);
		GLint block_size;
		glGetActiveUniformBlockiv(_handle, block_index, GL_UNIFORM_BLOCK_DATA_SIZE, &block_size);
		GLbyte* block_buffer;

		//const GLchar* names[] = { "inner_color", "outer_color","radius_innes","raduis_outer" };
		GLuint attrib_num = attrib_names.size();
		std::vector<GLuint> indices(attrib_num);
		std::vector<GLint> offsets(attrib_num);
		glGetUniformIndices(_handle, attrib_num, attrib_names.data(), indices.data());
		glGetActiveUniformsiv(_handle, 4, indices.data(), GL_UNIFORM_OFFSET, offsets.data());

		// create ubo an fill it with data
		gl_buffer ubo;

		// bind the buffer to the block
		glBindBufferBase(GL_UNIFORM_BUFFER, block_index, ubo.get_handle());
	}

public:
	void reset_all_bindings()
	{

	}

public:

	void enable();

	void disable();

public:
	
	void render(std::float_t delta_time)
	{

	}
};

