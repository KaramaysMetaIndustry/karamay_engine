#include "gl_transform_feedback.h"

gl_transform_feedback::gl_transform_feedback()
{
	glCreateTransformFeedbacks(1, &_handle);
}

gl_transform_feedback::~gl_transform_feedback()
{
	glDeleteTransformFeedbacks(1, &_handle);
}

void gl_transform_feedback::bind()
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _handle);
}

void gl_transform_feedback::unbind()
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

void gl_transform_feedback::associate_buffer(std::uint32_t index, std::shared_ptr<gl_buffer> array_buffer)
{
	if (array_buffer && array_buffer->is(gl_buffer_enum::type::ARRAY_BUFFER))
	{
		glTransformFeedbackBufferBase(_handle, static_cast<GLuint>(index), array_buffer->get_handle());
	}
}

void gl_transform_feedback::associate_buffer(std::uint32_t index, std::shared_ptr<gl_buffer> array_buffer, std::uint32_t offset, std::uint32_t size)
{
	if (array_buffer && array_buffer->is(gl_buffer_enum::type::ARRAY_BUFFER))
	{
		glTransformFeedbackBufferRange(_handle, index, array_buffer->get_handle(), offset, size);
	}
}
