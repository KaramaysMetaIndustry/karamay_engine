#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"

class gl_transform_feedback_descriptor
{

};


class gl_transform_feedback final : public gl_object
{
public:

	explicit gl_transform_feedback(const gl_transform_feedback_descriptor& descriptor);

	~gl_transform_feedback();

private:

    gl_transform_feedback_descriptor _descriptor;

	std::vector<const char*> _varyings;

public:

	void associate_buffer(std::uint32_t index, std::shared_ptr<gl_buffer> buffer);


	void associate_buffer(std::uint32_t index, std::shared_ptr<gl_buffer> buffer, std::int64_t offset, std::int64_t size);

	
	void set_varyings(const std::vector<const char*>& varyings)
	{
		_varyings = varyings;
	}

public:

	void bind()
	{
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _handle);
	}

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

