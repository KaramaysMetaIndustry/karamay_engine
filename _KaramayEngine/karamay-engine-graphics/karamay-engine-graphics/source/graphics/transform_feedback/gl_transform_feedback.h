#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"

class gl_transform_feedback final : public gl_object
{
public:

	gl_transform_feedback();

	virtual ~gl_transform_feedback();

public:
	
	void bind();

	void unbind();

	void associate_buffer(std::uint32_t index, std::shared_ptr<gl_buffer> buffer);

	void associate_buffer(std::uint32_t index, std::shared_ptr<gl_buffer> buffer, std::uint32_t offset, std::uint32_t size)
	{
		glTransformFeedbackBufferRange(_handle, index, buffer->get_handle(), offset, size);
	}

};

