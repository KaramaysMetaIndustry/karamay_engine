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

void gl_transform_feedback::associate_buffer(std::uint32_t index, std::shared_ptr<gl_buffer> buffer)
{
	if (index < GL_MAX_TRANSFORM_FEEDBACK_BUFFERS && buffer)
	{
		glTransformFeedbackBufferBase(_handle, static_cast<GLuint>(index), buffer->get_handle());
	}
}

void gl_transform_feedback::associate_buffer(std::uint32_t index, std::shared_ptr<gl_buffer> buffer, std::int64_t offset, std::int64_t size)
{
	if (index < GL_MAX_TRANSFORM_FEEDBACK_BUFFERS && buffer)
	{
		glTransformFeedbackBufferRange(_handle, index, buffer->get_handle(), offset, size);
	}
}
