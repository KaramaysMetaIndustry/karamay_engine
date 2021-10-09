#include "gl_program.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/shader/gl_shader.h"
#include "graphics/transform_feedback/gl_transform_feedback.h"

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

void gl_program::render(std::float_t delta_time)
{
	_install();
    {
        _enable();
        {
            _launch_uniforms();	// must launch uniforms after program enabled
            _call_commands();
        }
        _disable();
    }
	_uninstall();
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
		std::cout << "[element array buffers is bound.]" << std::endl;
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
			    // bind uniform buffers to context binding
				uniform_buffer->bind(i);
				// bind program uniform index to context binding
				std::uint32_t _uniform_block_index = glGetUniformBlockIndex(_handle, uniform_buffer->get_block_name().c_str());
				glUniformBlockBinding(_handle, _uniform_block_index, i);
#ifdef _DEBUG
				std::cout << "[ uniform block index: "<< _uniform_block_index <<".]" << std::endl;
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
				// bind buffers to context
				shader_storage_buffer->bind(i);
				// bind program to context
				const GLuint _index = glGetProgramResourceIndex(_handle, GL_SHADER_STORAGE_BLOCK, shader_storage_buffer->get_descriptor()->get_block_name().c_str());
				glShaderStorageBlockBinding(_handle, _index, i);
				
#ifdef _DEBUG
				std::cout << "[ " << i << " shader storage buffers is bound.]" << std::endl;
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
				// bind buffers to context
				atomic_counter_buffer->bind(i);
#ifdef _DEBUG
				std::cout << "[ " << i << " atomic counter buffers is bound.]" << std::endl;
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
