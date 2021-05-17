#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"

class gl_transform_feedback final : public gl_object
{
public:

	gl_transform_feedback();

	virtual ~gl_transform_feedback();

private:
	
	std::vector<const char*> _varyings;

public:

	/**
	 * @index : a transform feedback object has GL_MAX_TRANSFORM_FEEDBACK_BUFFERS slots, range of indices is [0, GL_MAX_TRANSFORM_FEEDBACK_BUFFERS - 1]
	 * you must use [ layout(xfb_buffer = 1) out; ]  to specify which buffer you will write into in glsl
	 * 
	 * @buffer : 
	 * the buffer associated to @index slot
	 */
	void associate_buffer(std::uint32_t index, std::shared_ptr<gl_buffer> buffer);

	/**
	 * @index : location of transform feedback object the buffer will associated to
	 * @buffer : buffer
	 * @offset : (bytes) offset of buffer
	 * @size : (bytes) [offset, offset + size] of buffer will be associate to transform feedback
	 */
	void associate_buffer(std::uint32_t index, std::shared_ptr<gl_buffer> buffer, std::int64_t offset, std::int64_t size);

	
	void set_varyings(const std::vector<const char*>& varyings)
	{
		_varyings = varyings;
	}

	const std::vector<const char*>& get_varyings() { return _varyings; }


public:

	/**
	 * bind transform feedback object to binding in current context
	 */
	void bind()
	{
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _handle);
	}

	/**
	 * unbind transform feedback object from target-binding in current context
	 */
	void unbind()
	{
		GLint handle;
		glGetIntegerv(GL_TRANSFORM_FEEDBACK_BINDING, &handle);
		if(handle == _handle)
		{
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
		}
		
	}

};

