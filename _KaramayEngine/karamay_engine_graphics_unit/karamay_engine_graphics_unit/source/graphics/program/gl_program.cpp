#include "gl_program.h"

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
}

void gl_program::add_uniform_buffers(const std::vector<std::shared_ptr<gl_uniform_buffer>>& uniform_buffers)
{
	if (uniform_buffers.size() < 1) return;

	_uniform_buffers.insert(_uniform_buffers.cend(), uniform_buffers.cbegin(), uniform_buffers.cend());
}

void gl_program::add_shader_storage_buffers(const std::vector<std::shared_ptr<gl_shader_storage_buffer>>& shader_storage_buffers)
{
	if (shader_storage_buffers.size() < 1) return;

	_shader_storage_buffers.insert(_shader_storage_buffers.cend(), shader_storage_buffers.cbegin(), shader_storage_buffers.cend());
}

void gl_program::add_atomic_counter_buffers(const std::vector<std::shared_ptr<gl_atomic_counter_buffer>>& atomic_counter_buffers)
{
	if (atomic_counter_buffers.size() < 1) return;

	_atomic_counter_buffers.insert(_atomic_counter_buffers.cend(), atomic_counter_buffers.cbegin(), atomic_counter_buffers.cend());
}

void gl_program::set_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer)
{
	_framebuffer = framebuffer;
}

void gl_program::render(std::float_t delta_time)
{
	_install();
	_enable();
	_call_commands();
	_disable();
	_uninstall();
}

void gl_program::_install()
{
	_bind_vertex_array();
	_bind_element_array_buffer();
	_bind_transform_feedback();
	_update_uniforms();
	_bind_textures();
	_bind_uniform_buffers();
	_bind_shader_storage_buffers();
	_bind_atomic_counter_buffers();
	_bind_framebuffer();
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
