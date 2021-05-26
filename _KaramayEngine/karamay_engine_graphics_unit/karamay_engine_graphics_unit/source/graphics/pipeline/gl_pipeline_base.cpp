#include "gl_pipeline_base.h"
#include "graphics/program/gl_program.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/transform_feedback/gl_transform_feedback.h"
#include "graphics/buffer/customization/gl_uniform_buffer.h"
#include "graphics/buffer/customization/gl_shader_storage_buffer.h"
#include "graphics/buffer/customization/gl_atomic_counter_buffer.h"


gl_pipeline_base::gl_pipeline_base()
{
	_program = std::make_shared<gl_program>();
}

gl_pipeline_base::~gl_pipeline_base()
{

}

gl_pipeline_base& gl_pipeline_base::construct(std::vector<std::string> shader_paths)
{
	if (_program)
	{
		_program->construct(shader_paths);
	}

	return *this;
}

gl_pipeline_base& gl_pipeline_base::set_vertex_array(std::shared_ptr<gl_vertex_array> vertex_array)
{
	if (_program)
	{
		_program->set_vertex_array(vertex_array);
	}

	return *this;
}

gl_pipeline_base& gl_pipeline_base::set_element_array(std::shared_ptr<gl_element_array_buffer> element_array_buffer)
{
	if (_program)
	{
		_program->set_element_array_buffer(element_array_buffer);
	}

	return *this;
}

gl_pipeline_base& gl_pipeline_base::set_transform_feedback(std::shared_ptr<gl_transform_feedback> transform_feedback)
{
	if (_program)
	{
		_program->set_transform_feedback(transform_feedback);
	}

	return *this;
}

gl_pipeline_base& gl_pipeline_base::add_uniform_buffers(const std::vector<std::shared_ptr<gl_uniform_buffer>>& uniform_buffers)
{
	if (_program)
	{
		_program->add_uniform_buffers(uniform_buffers);
	}

	return *this;
}

gl_pipeline_base& gl_pipeline_base::add_shader_storage_buffers(const std::vector<std::shared_ptr<gl_shader_storage_buffer>>& shader_storage_buffers)
{
	if (_program)
	{
		_program->add_shader_storage_buffers(shader_storage_buffers);
	}

	return *this;
}

gl_pipeline_base& gl_pipeline_base::add_atomic_counter_buffers(const std::vector<std::shared_ptr<gl_atomic_counter_buffer>>& atomic_counter_buffers)
{
	if (_program)
	{
		_program->add_atomic_counter_buffers(atomic_counter_buffers);
	}

	return *this;
}

gl_pipeline_base& gl_pipeline_base::set_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer)
{
	if (_program)
	{
		_program->set_framebuffer(framebuffer);
	}

	return *this;
}

gl_pipeline_base& gl_pipeline_base::set_commands(std::function<void(void)> commands_lambda)
{
	if (_program)
	{
		_program->set_commands(commands_lambda);
	}

	return *this;
}

void gl_pipeline_base::render(std::float_t delta_time)
{
	if (_program)
	{
		_program->update(delta_time);
		_program->render(delta_time);
	}
}
