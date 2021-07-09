#include "gl_program.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/shader/gl_shader.h"
#include "graphics/transform_feedback/gl_transform_feedback.h"

gl_program::gl_program()
{
	_handle = glCreateProgram();

	_update_uniform_funcs_map.emplace("float", &gl_program::_update_uniform_float);
	_update_uniform_funcs_map.emplace("vec2", &gl_program::_update_uniform_vec2);
	_update_uniform_funcs_map.emplace("vec3", &gl_program::_update_uniform_vec3);
	_update_uniform_funcs_map.emplace("vec4", &gl_program::_update_uniform_vec4);
	_update_uniform_funcs_map.emplace("double", &gl_program::_update_uniform_double);
	_update_uniform_funcs_map.emplace("dvec2", &gl_program::_update_uniform_dvec2);
	_update_uniform_funcs_map.emplace("dvec3", &gl_program::_update_uniform_dvec3);
	_update_uniform_funcs_map.emplace("dvec4", &gl_program::_update_uniform_dvec4);
	_update_uniform_funcs_map.emplace("int", &gl_program::_update_uniform_int);
	_update_uniform_funcs_map.emplace("ivec2", &gl_program::_update_uniform_ivec2);
	_update_uniform_funcs_map.emplace("ivec3", &gl_program::_update_uniform_ivec3);
	_update_uniform_funcs_map.emplace("ivec4", &gl_program::_update_uniform_ivec4);
	_update_uniform_funcs_map.emplace("uint", &gl_program::_update_uniform_uint);
	_update_uniform_funcs_map.emplace("uvec2", &gl_program::_update_uniform_uvec2);
	_update_uniform_funcs_map.emplace("uvec3", &gl_program::_update_uniform_uvec3);
	_update_uniform_funcs_map.emplace("uvec4", &gl_program::_update_uniform_uvec4);
												
	_update_uniform_funcs_map.emplace("mat2", &gl_program::_update_uniform_mat2);
	_update_uniform_funcs_map.emplace("mat3", &gl_program::_update_uniform_mat3);
	_update_uniform_funcs_map.emplace("mat4", &gl_program::_update_uniform_mat4);
	_update_uniform_funcs_map.emplace("mat2x3", &gl_program::_update_uniform_mat2x3);
	_update_uniform_funcs_map.emplace("mat2x4", &gl_program::_update_uniform_mat2x4);
	_update_uniform_funcs_map.emplace("mat3x2", &gl_program::_update_uniform_mat3x2);
	_update_uniform_funcs_map.emplace("mat3x4", &gl_program::_update_uniform_mat3x4);
	_update_uniform_funcs_map.emplace("mat4x2", &gl_program::_update_uniform_mat4x2);
	_update_uniform_funcs_map.emplace("mat4x3", &gl_program::_update_uniform_mat4x3);

	_update_uniform_funcs_map.emplace("dmat2", &gl_program::_update_uniform_dmat2);
	_update_uniform_funcs_map.emplace("dmat3", &gl_program::_update_uniform_dmat3);
	_update_uniform_funcs_map.emplace("dmat4", &gl_program::_update_uniform_dmat4);
	_update_uniform_funcs_map.emplace("dmat2x3", &gl_program::_update_uniform_dmat2x3);
	_update_uniform_funcs_map.emplace("dmat2x4", &gl_program::_update_uniform_dmat2x4);
	_update_uniform_funcs_map.emplace("dmat3x2", &gl_program::_update_uniform_dmat3x2);
	_update_uniform_funcs_map.emplace("dmat3x4", &gl_program::_update_uniform_dmat3x4);
	_update_uniform_funcs_map.emplace("dmat4x2", &gl_program::_update_uniform_dmat4x2);
	_update_uniform_funcs_map.emplace("dmat4x3", &gl_program::_update_uniform_dmat4x3);
												  
}

gl_program::~gl_program()
{
	glDeleteProgram(_handle);
}

void gl_program::construct(const std::vector<std::string>& shader_paths)
{
	for (const auto& path : shader_paths)
	{
		auto shader = std::make_shared<gl_shader>(path);
		if (shader)
		{
			glAttachShader(_handle, shader->get_handle());
			_shaders.push_back(shader);
		}
	}

	/*if (is_separable)
		glProgramParameteri(_handle, GL_PROGRAM_SEPARABLE, GL_TRUE);*/

		/*glBindAttribLocation(_handle, 0, "Position");
		glBindFragDataLocation(_handle, 0, "FragColor");*/

	glLinkProgram(_handle);

	GLint logLength = 0;
	GLint success;
	char infoLog[512];
	glGetProgramiv(_handle, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_handle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "[program is linked.]" << std::endl;
	}

	glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		char* log = (char*)malloc(logLength);
		glGetProgramInfoLog(_handle, NULL, &logLength, log);
		printf("============log: %s\n", log);
		free(log);
	}
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
	// must launch uniforms after program enabled
	_launch_uniforms();
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
}

void gl_program::_enable()
{
	glUseProgram(_handle);

	std::cout << "[program is enabled.]" << std::endl;
}

void gl_program::_call_commands()
{
	_commands_lambda();
	std::cout << "[commands are launched.]" << std::endl;
}

void gl_program::_disable()
{
	glUseProgram(0);

	std::cout << "[program is disabled.]" << std::endl;
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
			//glTransformFeedbackVaryings(_handle, static_cast<GLsizei>(varyings.size()), varyings.data(), static_cast<GLenum>(gl_buffer_mode::INTERLEAVED));
			glLinkProgram(_handle);
		}
	}
}

inline void gl_program::_bind_vertex_array()
{
	if (_vertex_array) {
		// bind it into context
		_vertex_array->bind();

#ifdef _DEBUG
		std::cout << "[vertex array is bound.]" << std::endl;
#endif
		// enable all vertex attribute pointers
		_vertex_array->enable_pointers();
		
#ifdef _DEBUG
		std::cout << "[vertex array pointers are enabled.]" << std::endl;
#endif
		
	}
}

inline void gl_program::_bind_element_array_buffer()
{
	if (_element_array_buffer) {
		// bind it into context
		_element_array_buffer->bind();

#ifdef _DEBUG
		std::cout << "[element array buffer is bound.]" << std::endl;
#endif
	}
}

inline void gl_program::_bind_transform_feedback()
{
	if (_transform_feedback)
	{
		// bind transform feedback to context
		_transform_feedback->bind();

#ifdef _DEBUG
		std::cout << "[transform feedback is bound.]" << std::endl;
#endif
		
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
				uniform_buffer->bind(i);

				const std::string& block_name = uniform_buffer->get_block_name();
				const auto _index = glGetUniformBlockIndex(_handle, block_name.c_str());
				glUniformBlockBinding(_handle, _index, i);

#ifdef _DEBUG
				std::cout << "[ " << _index << " uniform buffer is bound.]" << std::endl;
#endif

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
				const GLuint _index = glGetProgramResourceIndex(_handle, GL_SHADER_STORAGE_BLOCK, shader_storage_buffer->get_descriptor()->get_block_name().c_str());
				glShaderStorageBlockBinding(_handle, _index, i);
				
#ifdef _DEBUG
				std::cout << "[ " << i << " shader storage buffer is bound.]" << std::endl;
#endif // DEBUG	
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
#ifdef _DEBUG
				std::cout << "[ " << i << " atomic counter buffer is bound.]" << std::endl;
#endif // DEBUG
				
			}
		}
	}
}

inline void gl_program::_bind_framebuffer()
{
	if (_framebuffer) // bind customized framebuffer
	{
		_framebuffer->bind();

#ifdef _DEBUG
		std::cout << "[custom framebuffer is bound.]" << std::endl;
#endif

	}
	else // bind default framebuffer
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

#ifdef _DEBUG
		std::cout << "[default framebuffer is bound.]" << std::endl;
#endif

	}
		
}

inline void gl_program::_bind_textures()
{
#define BIND_TEXTURES(TYPE)\
for (std::uint32_t i = 0; i < _##TYPE##s.size(); ++i)\
{\
	_##TYPE##s[i]->bind(i);\
	std::cout<<"[texture is bound.]"<<std::endl;\
}\

	// bind textures to context
	// and prepare to launch it's unit index as a uniform 
	BIND_TEXTURES(texture_1d)
	BIND_TEXTURES(texture_1d_array)
	BIND_TEXTURES(texture_2d)
	BIND_TEXTURES(texture_2d_multisample)
	BIND_TEXTURES(texture_2d_array)
	BIND_TEXTURES(texture_2d_array_multisample)
	BIND_TEXTURES(texture_rectangle)
	BIND_TEXTURES(texture_3d)
	BIND_TEXTURES(texture_cube)
	BIND_TEXTURES(texture_cube_array)
	BIND_TEXTURES(texture_buffer)
}

void gl_program::_launch_uniforms()
{
	for (const auto& uniform : _uniforms)
	{
		if (uniform)
		{
			auto _iterator =
				_update_uniform_funcs_map.find(uniform->get_type());

			if (_iterator != _update_uniform_funcs_map.cend())
			{
				_iterator->second(this, uniform);
			}
		}
	}
}
