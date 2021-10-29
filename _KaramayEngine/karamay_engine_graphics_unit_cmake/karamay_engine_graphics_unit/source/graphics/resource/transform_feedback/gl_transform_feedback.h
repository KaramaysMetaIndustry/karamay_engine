#ifndef GL_TRANSFORM_FEEDBACK_H
#define GL_TRANSFORM_FEEDBACK_H

#include "graphics/resource/glo/gl_object.h"
#include "graphics/resource/buffers/indexed_buffer/gl_transform_feedback_buffer.h"

class gl_transform_feedback_descriptor{
public:
    std::vector<std::string> varyings;
};

class gl_transform_feedback final : public gl_object{
public:
	gl_transform_feedback() = delete;
	explicit gl_transform_feedback(const std::shared_ptr<gl_transform_feedback_descriptor>& descriptor) :
		gl_object(gl_object_type::TRANSFORM_FEEDBACK_OBJ)
	{
		glCreateTransformFeedbacks(1, &_handle);
	}
	gl_transform_feedback(const gl_transform_feedback&) = delete;
	gl_transform_feedback& operator=(const gl_transform_feedback&) = delete;

	~gl_transform_feedback() override
	{
		glDeleteTransformFeedbacks(1, &_handle);
	}


public:

	void bind() noexcept
	{
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _handle);
	}

	void unbind() noexcept
	{
		GLint handle;
		glGetIntegerv(GL_TRANSFORM_FEEDBACK_BINDING, &handle);
		if (handle == _handle)
		{
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
		}
	}

public:

	void draw(gl_primitive_mode mode, std::uint32_t stream_index)
	{
		glDrawTransformFeedbackStream(static_cast<GLenum>(mode), _handle, stream_index);
	}

	void draw_instance(gl_primitive_mode mode, std::uint32_t stream_index, std::int32_t instances_count)
	{
		//glDrawTransformFeedback(static_cast<GLenum>(mode), _handle);
		glDrawTransformFeedbackStreamInstanced(static_cast<GLenum>(mode), _handle, stream_index, instances_count);
		//glDrawTransformFeedbackStream()
	}

public:

	void associate_buffer(std::uint32_t index, const std::shared_ptr<gl_buffer>& buffer, std::int64_t offset, std::int64_t size)
	{
		if (index < GL_MAX_TRANSFORM_FEEDBACK_BUFFERS && buffer)
		{
			//glTransformFeedbackBufferRange(_handle, index, buffer->get_handle(), offset, size);
		}
	}

private:

	gl_transform_feedback_descriptor _descriptor;

	std::unique_ptr<gl_transform_feedback_buffer> _transform_feedback_bufffer;

};

#endif
