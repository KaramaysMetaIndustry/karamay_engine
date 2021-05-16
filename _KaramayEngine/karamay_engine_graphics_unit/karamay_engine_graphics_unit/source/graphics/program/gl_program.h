#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/shader/gl_shader.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/transform_feedback/gl_transform_feedback.h"
#include "graphics/uniform/gl_uniform.h"
#include "graphics/buffer/gl_buffer.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/buffer/customization/gl_uniform_buffer.h"
#include "graphics/buffer/customization/gl_shader_storage_buffer.h"
#include "graphics/buffer/customization/gl_atomic_count_buffer.h"
#include "graphics/texture/gl_texture.h"
#include "graphics/framebuffer/gl_framebuffer.h"

enum class gl_buffer_mode
{
	INTERLEAVED = GL_INTERLEAVED_ATTRIBS,
	SEPARATE_ATTRIBS = GL_SEPARATE_ATTRIBS
};


/**
 * [Fixed] you must call this func at some time
 * [Optional] you call choose to call this func and remember to call all associated funcs
 * 
 * opengl org obj, which include diff shader stages
 * and in our logic, we do not choose a multiprogram solution
 * 
 * 
 */
class gl_program final : public gl_object
{
public:

	gl_program();

	virtual ~gl_program();

public:

	void construct(const std::vector<std::string>& shader_paths)
	{
		for (const auto& path : shader_paths)
		{
			auto shader = std::make_shared<gl_shader>();
			if (shader)
			{
				shader->load(path);
				shader->compile();
				glAttachShader(_handle, shader->get_handle());
				_shaders.push_back(shader);
			}
		}

		/*if (is_separable)
			glProgramParameteri(_handle, GL_PROGRAM_SEPARABLE, GL_TRUE);*/

		/*glBindAttribLocation(_handle, 0, "Position");
		glBindFragDataLocation(_handle, 0, "FragColor");*/

		glLinkProgram(_handle);
	}

private:

	std::vector<std::shared_ptr<gl_shader>> _shaders;

public:

	void set_vertex_kit(std::shared_ptr<gl_vertex_array> vertex_array, std::shared_ptr<gl_element_array_buffer> element_array_buffer = nullptr)
	{
		_vertex_array = vertex_array;
		_element_array_buffer = element_array_buffer;
	}

	void set_transform_feedback(std::shared_ptr<gl_transform_feedback> transform_feedback, const std::vector<const GLchar*>& varyings)
	{
		if (_transform_feedback)
		{
			_transform_feedback = transform_feedback;

			if (varyings.size() > 0)
			{
				glTransformFeedbackVaryings(_handle, varyings.size(), varyings.data(), static_cast<GLenum>(gl_buffer_mode::INTERLEAVED));
				glLinkProgram(_handle);
			}
		}
	}

	template<typename T>
	void add_immediate_uniforms(const std::vector<std::shared_ptr<gl_uniform<T>>>& uniforms)
	{
		
	}

	template<typename T>
	void add_immediate_uniform_textures(const std::vector<std::shared_ptr<T>>& uniform_textures)
	{

	}

	void add_uniform_buffers(const std::vector<std::shared_ptr<gl_uniform_buffer>>& uniform_buffers) 
	{}

	void add_shader_storage_buffers(const std::vector<std::shared_ptr<gl_shader_storage_buffer>>& shader_storage_buffers) {}

	void add_atomic_count_buffers(const std::vector<std::shared_ptr<gl_atomic_count_buffer>>& atomic_count_buffers) {}

	void set_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer = nullptr)
	{
		_framebuffer = framebuffer;
	}

	void push_commands(std::function<void(void)> commands_lambda)
	{
		_commands_lambda = commands_lambda;
	}

public:

	void render(std::float_t delta_time)
	{
		_install();
		_enable();
		_call_commands();
		_disable();
		_uninstall();
	}

private:

	void _install()
	{
		_bind_framebuffer();
		_bind_vertex_array();
		_bind_element_array_buffer();
		_bind_transform_feedback();
		_bind_uniform_buffers();
		_bind_shader_storage_buffers();
		_bind_atomic_count_buffers();
	}

	void _enable()
	{
		glUseProgram(_handle);
	}

	void _call_commands()
	{
		_commands_lambda();
	}

	void _disable()
	{
		glUseProgram(0);
	}

	void _uninstall()
	{
		_unbind_framebuffer();
		_unbind_vertex_array();
		_unbind_element_array_buffer();
		_unbind_transform_feedback();
		_unbind_uniform_buffers();
		_unbind_shader_storage_buffers();
		_unbind_atomic_count_buffers();
	}

private:
	
	std::shared_ptr<gl_vertex_array> _vertex_array;

	std::shared_ptr<gl_element_array_buffer> _element_array_buffer;

	std::shared_ptr<gl_transform_feedback> _transform_feedback;

	std::vector<std::shared_ptr<gl_uniform_buffer>> _uniform_buffers;

	std::vector<std::shared_ptr<gl_shader_storage_buffer>> _shader_storage_buffers;

	std::vector<std::shared_ptr<gl_atomic_count_buffer>> _atomic_count_buffers;

	std::shared_ptr<gl_framebuffer> _framebuffer;

	std::function<void(void)> _commands_lambda;

private:

	void _bind_framebuffer()
	{
		if (_framebuffer)
		{
			_framebuffer->bind_to_context();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	} 
	void _bind_vertex_array()
	{
		if (_vertex_array) {
			_vertex_array->bind_to_context();
			_vertex_array->enable_vertex_attributes();
		}
	}
	void _bind_element_array_buffer()
	{
		if (_element_array_buffer) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _element_array_buffer->get_handle());
		}
	}
	void _bind_transform_feedback()
	{
		if (_transform_feedback)
		{
			_transform_feedback->bind();
		}

	}
	void _bind_uniform_buffers()
	{
		//GL_MAX_UNIFORM_BUFFER_BINDINGS;
		
		for (size_t i = 0; i < _uniform_buffers.size(); ++i)
		{
			if (auto uniform_buffer = _uniform_buffers[i])
			{
				auto binding_info = uniform_buffer->get_binding_info();
				const auto& block_name = binding_info.block_name;
				auto buffer = binding_info.buffer;
				if (buffer)
				{
					glBindBufferBase(GL_UNIFORM_BUFFER, i, buffer->get_handle());
					glUniformBlockBinding(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), i);
				}
			}
		}
		
	}
	void _bind_shader_storage_buffers()
	{
		//GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS;
		
		for (size_t i = 0; i < _shader_storage_buffers.size(); ++i)
		{
			if (auto shader_storage_buffer = _shader_storage_buffers[i])
			{
				auto binding_info = shader_storage_buffer->get_binding_info();
				const auto& block_name = binding_info.block_name;
				auto buffer = binding_info.buffer;
				if (buffer)
				{
					glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i, buffer->get_handle());
					glUniformBlockBinding(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), i);
				}
			}
		}
	}
	void _bind_atomic_count_buffers()
	{
		for (size_t i = 0; i < _atomic_count_buffers.size(); ++i)
		{
			if (auto atomic_count_buffer = _atomic_count_buffers[i])
			{
				auto binding_info = atomic_count_buffer->get_binding_info();
				auto buffer = binding_info.buffer;
				if (buffer)
				{
					glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, i, buffer->get_handle());
				}
			}
		}
	}

	void _unbind_framebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void _unbind_vertex_array()
	{
		glBindVertexArray(0);
	}
	void _unbind_element_array_buffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void _unbind_transform_feedback()
	{
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	}
	void _unbind_uniform_buffers()
	{
		for (size_t i = 0; i < _uniform_buffers.size(); ++i)
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, i, 0);
		}
	}
	void _unbind_shader_storage_buffers()
	{
		for (size_t i = 0; i < _shader_storage_buffers.size(); ++i)
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i, 0);
		}
	}
	void _unbind_atomic_count_buffers()
	{
		for (size_t i = 0; i < _atomic_count_buffers.size(); ++i)
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i, 0);
		}
	}

	// indexed buffer GL_MAX_UNIFORM_BUFFER_BINDINGS
	// indexed buffer GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS
	// indexed buffer GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS
	
	void bind_texture_1d(std::uint32_t unit, const std::string& name, std::shared_ptr<gl_texture_1d> texture_1d)
	{
		if (texture_1d) {
			texture_1d->bind(unit);
			//update_uniform_1ui(name, unit);
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
	// float vectors
	

private:

	void _update_uniform(const std::string& name, glm::vec1 value)
	{
		glUniform1fv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::vec2 value)
	{
		glUniform2fv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::vec3 value)
	{
		glUniform3fv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::vec4 value)
	{
		glUniform4fv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	// double vectors
	
	void _update_uniform(const std::string& name, glm::dvec1 value)
	{
		glUniform1dv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::dvec2 value)
	{
		glUniform2dv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::dvec3 value)
	{
		glUniform3dv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::dvec4 value)
	{
		glUniform4dv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	// int vectors
	
	void _update_uniform(const std::string& name, glm::ivec1 value)
	{
		glUniform1iv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::ivec2 value)
	{
		glUniform2iv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::ivec3 value)
	{
		glUniform3iv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::ivec4 value)
	{
		glUniform4iv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	// uint vectors
	
	void _update_uniform(const std::string& name, glm::uvec1 value)
	{
		glUniform1uiv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::uvec2 value)
	{
		glUniform2uiv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::uvec3 value)
	{
		glUniform3uiv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	void _update_uniform(const std::string& name, glm::uvec4 value)
	{
		glUniform4uiv(glGetUniformLocation(_handle, name.c_str()), glm::value_ptr(value));
	}
	
	void _update_uniform(const std::string& name, glm::mat3 value)
	{}
	void _update_uniform(const std::string& name, glm::mat4 value)
	{
		glUniformMatrix4fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	



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


};

