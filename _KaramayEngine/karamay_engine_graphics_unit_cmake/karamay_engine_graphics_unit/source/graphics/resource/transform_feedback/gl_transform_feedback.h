#ifndef GL_TRANSFORM_FEEDBACK_H
#define GL_TRANSFORM_FEEDBACK_H

#include "graphics/resource/glo/gl_object.h"
#include "graphics/resource/buffers/indexed_buffer/gl_transform_feedback_buffer.h"
#include "graphics/resource/vertex_launcher/gl_vertex_launcher.h"

class TransformFeedback final : public gl_object{
public:
	TransformFeedback() = delete;
	explicit TransformFeedback(const std::vector<std::string>& Varings) :
		gl_object(gl_object_type::TRANSFORM_FEEDBACK_OBJ)
	{
		glCreateTransformFeedbacks(1, &_handle);
	}
	TransformFeedback(const TransformFeedback&) = delete;
	TransformFeedback& operator=(const TransformFeedback&) = delete;

	~TransformFeedback() override
	{
		glDeleteTransformFeedbacks(1, &_handle);
	}

public:

	void Bind() const noexcept
	{
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _handle);
	}

	void Unbind() const noexcept
	{
		//GLint handle;
		//glGetIntegerv(GL_TRANSFORM_FEEDBACK_BINDING, &handle);
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	}

public:

	// if do not have gs, only output stream 0
	void Draw(PrimitiveMode Mode, UInt32 StreamIndex = 0) const noexcept
	{
		glDrawTransformFeedbackStream(static_cast<GLenum>(Mode), _handle, StreamIndex);
	}

	// if do not have gs, only output stream 0
	void DrawInstances(UInt32 InstancesNum, PrimitiveMode Mode, UInt32 StreamIndex = 0) const noexcept
	{
		glDrawTransformFeedbackStreamInstanced(static_cast<GLenum>(Mode), _handle, StreamIndex, InstancesNum);
	}

public:

	const std::vector<std::string>& GetVaryings() const noexcept { return _Varyings; }

private:
	
	const std::vector<std::string> _Varyings;

	std::vector<TransformFeedbackBuffer> _TransformFeedbackBuffers;

	void _Allocate()
	{

	}

	void _AssociateBuffer()
	{
		for (UInt32 Index = 0; Index < _TransformFeedbackBuffers.size(); ++Index)
		{
			glTransformFeedbackBufferRange(_handle, Index, _TransformFeedbackBuffers[Index].get_handle(), Offset, Size);
		}

	/*	if (Index < GL_MAX_TRANSFORM_FEEDBACK_BUFFERS && buffer)
		{
			
		}*/
	}


};

#endif
