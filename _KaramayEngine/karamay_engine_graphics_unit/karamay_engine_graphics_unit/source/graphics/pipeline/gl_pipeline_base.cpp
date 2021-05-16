#include "gl_pipeline_base.h"

gl_pipeline_base::gl_pipeline_base()
{
	glCreateProgramPipelines(1, &_handle);
}

gl_pipeline_base::~gl_pipeline_base()
{
	glDeleteProgramPipelines(1, &_handle);
}

gl_pipeline_base& gl_pipeline_base::construct(std::vector<std::string> shader_paths)
{
	if (_program)
	{
		_program->construct(shader_paths);
	}

	return *this;
}

gl_pipeline_base& gl_pipeline_base::set_vertex_kit(std::shared_ptr<gl_vertex_array> vertex_array, std::shared_ptr<gl_element_array_buffer> element_array_buffer)
{
	if (_program)
	{
		_program->set_vertex_kit(vertex_array, element_array_buffer);
	}

	return *this;
}

gl_pipeline_base& gl_pipeline_base::set_transform_feedback(std::shared_ptr<gl_transform_feedback> transform_feedback, const std::vector<std::string>& varyings)
{
	if (_program)
	{
		_program->set_transform_feedback(transform_feedback, varyings);
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

void gl_pipeline_base::render(std::float_t delta_time)
{
	if (_program)
	{
		_program->render(delta_time);
	}

	gl_uniform<glm::mat4> a("actor", glm::mat4(1.0f));
}
