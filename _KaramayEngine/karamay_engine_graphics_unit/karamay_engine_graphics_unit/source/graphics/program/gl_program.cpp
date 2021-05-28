#include "gl_program.h"
#include "graphics/texture/gl_texture.h"

gl_program::gl_program()
{
	_handle = glCreateProgram();
}

gl_program::~gl_program()
{
	glDeleteProgram(_handle);
}

void gl_program::construct(const std::vector<std::string>& shader_paths)
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

void gl_program::set_vertex_array(std::shared_ptr<gl_vertex_array> vertex_array)
{
	_vertex_array = vertex_array;
}

void gl_program::set_element_array_buffer(std::shared_ptr<gl_element_array_buffer> element_array_buffer)
{
	_element_array_buffer = element_array_buffer;
}

void gl_program::set_transform_feedback(std::shared_ptr<gl_transform_feedback> transform_feedback)
{
	_transform_feedback = transform_feedback;
	_set_transform_feedback_varyings();
}

void gl_program::add_uniform_buffers(const std::vector<std::shared_ptr<gl_uniform_buffer>>& uniform_buffers)
{
	if (uniform_buffers.size() < 1) return;
	_uniform_buffers.insert(_uniform_buffers.cend(), uniform_buffers.cbegin(), uniform_buffers.cend());
}

void gl_program::add_uniform_buffer(std::shared_ptr<gl_uniform_buffer> uniform_buffer)
{
	if (uniform_buffer)
		_uniform_buffers.push_back(uniform_buffer);
}

void gl_program::add_shader_storage_buffers(const std::vector<std::shared_ptr<gl_shader_storage_buffer>>& shader_storage_buffers)
{
	if (shader_storage_buffers.size() < 1) return;
	_shader_storage_buffers.insert(_shader_storage_buffers.cend(), shader_storage_buffers.cbegin(), shader_storage_buffers.cend());
}

void gl_program::add_shader_storage_buffer(std::shared_ptr<gl_shader_storage_buffer> shader_storage_buffer)
{
	if (shader_storage_buffer)
		_shader_storage_buffers.push_back(shader_storage_buffer);
}

void gl_program::add_atomic_counter_buffers(const std::vector<std::shared_ptr<gl_atomic_counter_buffer>>& atomic_counter_buffers)
{
	if (atomic_counter_buffers.size() < 1) return;
	_atomic_counter_buffers.insert(_atomic_counter_buffers.cend(), atomic_counter_buffers.cbegin(), atomic_counter_buffers.cend());
}

void gl_program::add_atomic_counter_buffer(std::shared_ptr<gl_atomic_counter_buffer> atomic_counter_buffer)
{
	if (atomic_counter_buffer)
		_atomic_counter_buffers.push_back(atomic_counter_buffer);
}

void gl_program::set_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer)
{
	_framebuffer = framebuffer;
}

void gl_program::set_commands(std::function<void(void)> commands_lambda)
{
	_commands_lambda = commands_lambda;
}

std::shared_ptr<gl_vertex_array> gl_program::get_vertex_array()
{
	return _vertex_array;
}

std::shared_ptr<gl_element_array_buffer> gl_program::get_element_array_buffer()
{
	return _element_array_buffer;
}

std::shared_ptr<gl_transform_feedback> gl_program::get_transform_feedback()
{
	return _transform_feedback;
}

std::shared_ptr<gl_uniform_buffer> gl_program::get_uniform_buffer(std::uint32_t index)
{
	return index < _uniform_buffers.size() ? _uniform_buffers.at(index) : nullptr;
}

std::shared_ptr<gl_shader_storage_buffer> gl_program::get_shader_storage_buffer(std::uint32_t index)
{
	return index < _shader_storage_buffers.size() ? _shader_storage_buffers.at(index) : nullptr;
}

std::shared_ptr<gl_atomic_counter_buffer> gl_program::get_atomic_counter_buffer(std::uint32_t index)
{
	return index < _atomic_counter_buffers.size() ? _atomic_counter_buffers.at(index) : nullptr;
}

std::shared_ptr<gl_framebuffer> gl_program::get_framebuffer()
{
	return _framebuffer;
}

void gl_program::render(std::float_t delta_time)
{
	_install();
	_enable();
	_call_commands();
	_disable();
	_uninstall();
}

void gl_program::_tick_objects()
{
}

void gl_program::_install()
{
	_bind_vertex_array();
	_bind_element_array_buffer();
	_bind_transform_feedback();
	_bind_uniform_buffers();
	_bind_shader_storage_buffers();
	_bind_atomic_counter_buffers();
	_bind_framebuffer();
	_bind_textures(); 
	// must launch uniforms after textures bound
	_launch_uniforms();
}

void gl_program::_enable()
{
	glUseProgram(_handle);
}

void gl_program::_call_commands()
{
	_commands_lambda();
}

void gl_program::_disable()
{
	glUseProgram(0);
}

void gl_program::_uninstall()
{
	_unbind_framebuffer();
	_unbind_vertex_array();
	_unbind_element_array_buffer();
	_unbind_transform_feedback();
	_unbind_uniform_buffers();
	_unbind_shader_storage_buffers();
	_unbind_atomic_counter_buffers();
}

inline void gl_program::_set_transform_feedback_varyings()
{
	if (_transform_feedback)
	{
		// set program's transform feedback output vars, then relink program
		const auto& varyings = _transform_feedback->get_varyings();
		if (varyings.size() > 0)
		{
			glTransformFeedbackVaryings(_handle, static_cast<GLsizei>(varyings.size()), varyings.data(), static_cast<GLenum>(gl_buffer_mode::INTERLEAVED));
			glLinkProgram(_handle);
		}
	}
}

inline void gl_program::_bind_vertex_array()
{
	if (_vertex_array) {
		// bind it into context
		_vertex_array->bind();
		// enable all vertex attribute pointers
		_vertex_array->enable_pointers();
	}
}

inline void gl_program::_bind_element_array_buffer()
{
	if (_element_array_buffer) {
		// bind it into context
		_element_array_buffer->bind();
	}
}

inline void gl_program::_bind_transform_feedback()
{
	if (_transform_feedback)
	{
		// bind transform feedback to context
		_transform_feedback->bind();
	}
}

inline void gl_program::_bind_uniform_buffers()
{
	const std::size_t max_i = _uniform_buffers.size() > GL_MAX_UNIFORM_BUFFER_BINDINGS 
		? GL_MAX_UNIFORM_BUFFER_BINDINGS : _uniform_buffers.size();

	for (std::int32_t i = 0; i < max_i; ++i)
	{
		if (auto uniform_buffer = _uniform_buffers[i])
		{
			if (uniform_buffer)
			{
				// bind buffer to context
				uniform_buffer->bind(i);
				// bind program to context
				const std::string& block_name = uniform_buffer->get_descriptor()->get_block_name();
				glUniformBlockBinding(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), i);
			}
		}
	}
}

inline void gl_program::_bind_shader_storage_buffers()
{
	const std::size_t max_i = _shader_storage_buffers.size() > GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 
		? GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS : _shader_storage_buffers.size();

	for (std::int32_t i = 0; i < max_i; ++i)
	{
		if (auto shader_storage_buffer = _shader_storage_buffers[i])
		{
			if (shader_storage_buffer)
			{
				// bind buffer to context
				shader_storage_buffer->bind(i);
				// bind program to context
				glShaderStorageBlockBinding(_handle, glGetProgramResourceLocation(_handle, GL_SHADER_STORAGE_BLOCK, shader_storage_buffer->get_descriptor()->get_block_name().c_str()), i);
			}
		}
	}
}

inline void gl_program::_bind_atomic_counter_buffers()
{
	const std::size_t max_i
		= _atomic_counter_buffers.size() > GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS ? GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS : _atomic_counter_buffers.size();

	for (std::int32_t i = 0; i < max_i; ++i)
	{
		if (auto atomic_counter_buffer = _atomic_counter_buffers[i])
		{
			if (atomic_counter_buffer)
			{
				// bind buffer to context
				atomic_counter_buffer->bind(i);
			}
		}
	}
}

inline void gl_program::_bind_framebuffer()
{
	if (_framebuffer) // bind customized framebuffer
		_framebuffer->bind();
	else // bind default framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

inline void gl_program::_bind_textures()
{
#define BIND_TEXTURES(TYPE)\
for (std::uint32_t i = 0; i < _##TYPE##s.size(); ++i)\
{\
	_##TYPE##s[i]->bind(i);\
	add_uniforms({ std::make_shared<gl_variable<glm::uint32>>(_##TYPE##s[i]->get_name(), i) });\
}\

	// bind textures to context
	// and prepare to launch it's unit index as a uniform 
	BIND_TEXTURES(texture_1d)
	BIND_TEXTURES(texture_2d)
	BIND_TEXTURES(texture_2d_multisample)
	BIND_TEXTURES(texture_2d_array)
	BIND_TEXTURES(texture_2d_array_multisample)
	BIND_TEXTURES(texture_3d)
	BIND_TEXTURES(texture_cube)
	BIND_TEXTURES(texture_cube_array)
	BIND_TEXTURES(texture_buffer)
}

void gl_program::_launch_uniforms()
{

#define UPDATE_UNIFORMS(TYPE)\
for (auto uniform : _##TYPE##_uniforms)\
{\
	if (uniform)\
		_update_uniform(uniform->name, uniform->value);\
}\

	// launch all uniforms (include common uniforms and texture units)
	UPDATE_UNIFORMS(float32)
	UPDATE_UNIFORMS(vec2)
	UPDATE_UNIFORMS(vec3)
	UPDATE_UNIFORMS(vec4)

	UPDATE_UNIFORMS(float64)
	UPDATE_UNIFORMS(dvec2)
	UPDATE_UNIFORMS(dvec3)
	UPDATE_UNIFORMS(dvec4)

	UPDATE_UNIFORMS(int32)
	UPDATE_UNIFORMS(ivec2)
	UPDATE_UNIFORMS(ivec3)
	UPDATE_UNIFORMS(ivec4)

	UPDATE_UNIFORMS(uint32)
	UPDATE_UNIFORMS(uvec2)
	UPDATE_UNIFORMS(uvec3)
	UPDATE_UNIFORMS(uvec4)

	UPDATE_UNIFORMS(mat2)
	UPDATE_UNIFORMS(mat3)
	UPDATE_UNIFORMS(mat4)

	UPDATE_UNIFORMS(mat2x3)
	UPDATE_UNIFORMS(mat2x4)
	UPDATE_UNIFORMS(mat3x2)
	UPDATE_UNIFORMS(mat3x4)
	UPDATE_UNIFORMS(mat4x2)
	UPDATE_UNIFORMS(mat4x3)
}
