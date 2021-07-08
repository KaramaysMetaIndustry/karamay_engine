#include "gl_transform_feedback.h"
#include "graphics/buffer/gl_buffer.h"

gl_transform_feedback::~gl_transform_feedback()
{
	glDeleteTransformFeedbacks(1, &_handle);
}

void gl_transform_feedback::associate_buffer(std::uint32_t index, const std::shared_ptr<gl_buffer>& buffer)
{
	if (index < GL_MAX_TRANSFORM_FEEDBACK_BUFFERS && buffer)
	{
		glTransformFeedbackBufferBase(_handle, static_cast<GLuint>(index), buffer->get_handle());
	}
}

void gl_transform_feedback::associate_buffer(std::uint32_t index, const std::shared_ptr<gl_buffer>& buffer, std::int64_t offset, std::int64_t size)
{
	if (index < GL_MAX_TRANSFORM_FEEDBACK_BUFFERS && buffer)
	{
		glTransformFeedbackBufferRange(_handle, index, buffer->get_handle(), offset, size);
	}
}

gl_transform_feedback::gl_transform_feedback(const std::shared_ptr<gl_transform_feedback_descriptor> &descriptor)
{
    glCreateTransformFeedbacks(1, &_handle);
}

void gl_transform_feedback::bind()
{
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _handle);
}

void gl_transform_feedback::unbind()
{
    GLint handle;
    glGetIntegerv(GL_TRANSFORM_FEEDBACK_BINDING, &handle);
    if(handle == _handle)
    {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
    }
}

std::shared_ptr<const gl_buffer> gl_transform_feedback::get_output_buffer() const
{
    return _output_buffer;
}



