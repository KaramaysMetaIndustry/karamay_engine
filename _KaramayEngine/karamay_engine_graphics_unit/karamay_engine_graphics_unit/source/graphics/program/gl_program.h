#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/shader/gl_shader.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/transform_feedback/gl_transform_feedback.h"
#include "graphics/variable/gl_variable.h"
#include "graphics/buffer/gl_buffer.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/buffer/customization/gl_uniform_buffer.h"
#include "graphics/buffer/customization/gl_shader_storage_buffer.h"
#include "graphics/buffer/customization/gl_atomic_counter_buffer.h"
#include "graphics/texture/gl_texture.h"
#include "graphics/framebuffer/gl_framebuffer.h"
#include "graphics/framebuffer/gl_default_framebuffer.h"

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

	/**
	 * once you install these component, you have no chance to remove or add them until the program destroyed
	 * 
	 */
	void construct(const std::vector<std::string>& shader_paths);

public:

	void set_vertex_array(std::shared_ptr<gl_vertex_array> vertex_array);

	void set_element_array_buffer(std::shared_ptr<gl_element_array_buffer> element_array_buffer);

	void set_transform_feedback(std::shared_ptr<gl_transform_feedback> transform_feedback);

	void add_uniform_buffers(const std::vector<std::shared_ptr<gl_uniform_buffer>>& uniform_buffers);

	void add_uniform_buffer(std::shared_ptr<gl_uniform_buffer> uniform_buffer);

	void add_shader_storage_buffers(const std::vector<std::shared_ptr<gl_shader_storage_buffer>>& shader_storage_buffers);

	void add_shader_storage_buffer(std::shared_ptr<gl_shader_storage_buffer> shader_storage_buffer);

	void add_atomic_counter_buffers(const std::vector<std::shared_ptr<gl_atomic_counter_buffer>>& atomic_counter_buffers);

	void add_atomic_counter_buffer(std::shared_ptr<gl_atomic_counter_buffer> atomic_counter_buffer);

	void set_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer = nullptr);

	void set_commands(std::function<void(void)> commands_lambda);

public:

	std::shared_ptr<gl_vertex_array> get_vertex_array();

	std::shared_ptr<gl_element_array_buffer> get_element_array_buffer();

	std::shared_ptr<gl_transform_feedback> get_transform_feedback();

	std::shared_ptr<gl_uniform_buffer> get_uniform_buffer(std::uint32_t index);

	std::shared_ptr<gl_shader_storage_buffer> get_shader_storage_buffer(std::uint32_t index);

	std::shared_ptr<gl_atomic_counter_buffer> get_atomic_counter_buffer(std::uint32_t index);

	std::shared_ptr<gl_framebuffer> get_framebuffer();

public:

	/**
	 * start render processing
	 */
	void render(std::float_t delta_time);

private:

	std::vector<std::shared_ptr<gl_shader>> _shaders;

	std::shared_ptr<gl_vertex_array> _vertex_array;
	
	std::shared_ptr<gl_element_array_buffer> _element_array_buffer;
	
	std::shared_ptr<gl_transform_feedback> _transform_feedback;
	
	std::vector<std::shared_ptr<gl_uniform_buffer>> _uniform_buffers;
	
	std::vector<std::shared_ptr<gl_shader_storage_buffer>> _shader_storage_buffers;
	
	std::vector<std::shared_ptr<gl_atomic_counter_buffer>> _atomic_counter_buffers;
	
	std::shared_ptr<gl_framebuffer> _framebuffer;
	
	static std::shared_ptr<gl_default_framebuffer> _default_framebuffer;
	
	std::function<void(void)> _commands_lambda;

private:
	//~ render begin
	void _tick_objects();
	void _install();
	void _enable();
	void _call_commands();
	void _disable();
	void _uninstall();
	//~ render end
private:

	// set only once time (when you first time setting the transform feedback)
	void _set_transform_feedback_varyings();

	// bind these persistent data to context (context is public)
	void _bind_vertex_array();
	void _bind_element_array_buffer();
	void _bind_transform_feedback();
	void _bind_uniform_buffers();
	void _bind_shader_storage_buffers();
	void _bind_atomic_counter_buffers();
	void _bind_framebuffer();
	void _bind_textures();

	void _launch_uniforms();

	// unbind these persistent data from context (you can not ensure that slots your have used will be overriden by next program)
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
		// clear all unifrom buffer binding is too expensive
		// use the stored ids
		for (std::int32_t i = 0; i < _uniform_buffers.size(); ++i)
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, i, 0);
		}
	}
	void _unbind_shader_storage_buffers()
	{
		for (std::int32_t i = 0; i < _shader_storage_buffers.size(); ++i)
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i, 0);
		}
	}
	void _unbind_atomic_counter_buffers()
	{
		for (std::uint32_t i = 0; i < _atomic_counter_buffers.size(); ++i)
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i, 0);
		}
	}
	void _unbind_framebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void _unbind_textures() {}


#define DEF_ADD_UNIFORMS(TYPE)\
private:\
std::vector<std::shared_ptr<gl_variable<glm::##TYPE##>>> _##TYPE##_uniforms;\
public:\
inline void add_uniforms(const std::vector<std::shared_ptr<gl_variable<glm::##TYPE##>>>& TYPE##_uniforms)\
{\
	_##TYPE##_uniforms.insert(_##TYPE##_uniforms.cend(), TYPE##_uniforms.cbegin(), TYPE##_uniforms.cend());\
}\
inline void add_uniform(std::shared_ptr<gl_variable<glm::##TYPE##>> TYPE##_uniform)\
{\
	_##TYPE##_uniforms.push_back(TYPE##_uniform);\
}\

	DEF_ADD_UNIFORMS(float32)
	DEF_ADD_UNIFORMS(vec2)
	DEF_ADD_UNIFORMS(vec3)
	DEF_ADD_UNIFORMS(vec4)
	DEF_ADD_UNIFORMS(float64)
	DEF_ADD_UNIFORMS(dvec2)
	DEF_ADD_UNIFORMS(dvec3)
	DEF_ADD_UNIFORMS(dvec4)
	DEF_ADD_UNIFORMS(int32)
	DEF_ADD_UNIFORMS(ivec2)
	DEF_ADD_UNIFORMS(ivec3)
	DEF_ADD_UNIFORMS(ivec4)
	DEF_ADD_UNIFORMS(uint32)
	DEF_ADD_UNIFORMS(uvec2)
	DEF_ADD_UNIFORMS(uvec3)
	DEF_ADD_UNIFORMS(uvec4)
	DEF_ADD_UNIFORMS(mat2)
	DEF_ADD_UNIFORMS(mat3)
	DEF_ADD_UNIFORMS(mat4)
	DEF_ADD_UNIFORMS(mat2x3)
	DEF_ADD_UNIFORMS(mat2x4)
	DEF_ADD_UNIFORMS(mat3x2)
	DEF_ADD_UNIFORMS(mat3x4)
	DEF_ADD_UNIFORMS(mat4x2)
	DEF_ADD_UNIFORMS(mat4x3)

#define DEF_ADD_TEXTURES(TYPE)\
private:\
	std::vector<std::shared_ptr<gl_##TYPE##>> _##TYPE##s;\
public:\
	inline void add_textures(const std::vector<std::shared_ptr<gl_##TYPE##>>& TYPE##s)\
	{\
		_##TYPE##s.insert(_##TYPE##s.cend(), TYPE##s.cbegin(), TYPE##s.cend());\
	}\
	inline void add_texture(std::shared_ptr<gl_##TYPE##> TYPE)\
	{\
		_##TYPE##s.push_back(TYPE);\
	}\

	DEF_ADD_TEXTURES(texture_1d)
	DEF_ADD_TEXTURES(texture_1d_array)
	DEF_ADD_TEXTURES(texture_2d)
	DEF_ADD_TEXTURES(texture_2d_array)
	DEF_ADD_TEXTURES(texture_2d_multisample)
	DEF_ADD_TEXTURES(texture_2d_array_multisample)
	DEF_ADD_TEXTURES(texture_rectangle)
	DEF_ADD_TEXTURES(texture_3d)
	DEF_ADD_TEXTURES(texture_cube)
	DEF_ADD_TEXTURES(texture_cube_array)
	DEF_ADD_TEXTURES(texture_buffer)

private:
	//~ helper function
	inline void _update_uniform(const std::string& name, glm::float32 value)
	{
		glUniform1f(glGetUniformLocation(_handle, name.c_str()), value);
	}
	inline void _update_uniform(const std::string& name, glm::vec2 value)
	{
		glUniform2fv(glGetUniformLocation(_handle, name.c_str()), 2, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::vec3 value)
	{
		glUniform3fv(glGetUniformLocation(_handle, name.c_str()), 3, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::vec4 value)
	{
		glUniform4fv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::float64 value)
	{
		glUniform1d(glGetUniformLocation(_handle, name.c_str()), value);
	}
	inline void _update_uniform(const std::string& name, glm::dvec2 value)
	{
		glUniform2dv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::dvec3 value)
	{
		glUniform3dv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::dvec4 value)
	{
		glUniform4dv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::int32 value)
	{
		glUniform1i(glGetUniformLocation(_handle, name.c_str()), value);
	}
	inline void _update_uniform(const std::string& name, glm::ivec2 value)
	{
		glUniform2iv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::ivec3 value)
	{
		glUniform3iv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::ivec4 value)
	{
		glUniform4iv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::uint32 value)
	{
		glUniform1ui(glGetUniformLocation(_handle, name.c_str()), value);
	}
	inline void _update_uniform(const std::string& name, glm::uvec2 value)
	{
		glUniform2uiv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::uvec3 value)
	{
		glUniform3uiv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::uvec4 value)
	{
		glUniform4uiv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::mat2 value)
	{
		glUniformMatrix2fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::mat3 value)
	{
		glUniformMatrix3fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::mat4 value)
	{
		glUniformMatrix4fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::mat2x3 value)
	{
		glUniformMatrix2x3fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::mat2x4 value)
	{
		glUniformMatrix2x4fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::mat3x2 value)
	{
		glUniformMatrix3x2fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::mat3x4 value)
	{
		glUniformMatrix3x4fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::mat4x2 value)
	{
		glUniformMatrix4x2fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glm::mat4x3 value)
	{
		glUniformMatrix4x3fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

};
