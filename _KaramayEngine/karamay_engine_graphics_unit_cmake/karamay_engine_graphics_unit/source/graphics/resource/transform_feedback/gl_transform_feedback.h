#ifndef GL_TRANSFORM_FEEDBACK_H
#define GL_TRANSFORM_FEEDBACK_H

#include "graphics/resource/glo/gl_object.h"
#include "graphics/resource/buffers/indexed_buffer/gl_transform_feedback_buffer.h"
#include "graphics/resource/vertex_launcher/gl_vertex_launcher.h"

class TransformFeedback final : public gl_object{
public:
	TransformFeedback() = delete;
	TransformFeedback(const std::vector<std::string>& Varings, UInt32 AcceptDataFrom) :
		gl_object(gl_object_type::TRANSFORM_FEEDBACK_OBJ), _State(TransformFeedbackState::End)
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
		GLint handle;
		glGetIntegerv(GL_TRANSFORM_FEEDBACK_BINDING, &handle);
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	}

public:

	enum class TransformFeedbackState
	{
		Running,
		Paused,
		End
	};

	void BeginTransformFeedback(PrimitiveMode Mode)
	{
		if (_State == TransformFeedbackState::End)
		{
			glBeginTransformFeedback(static_cast<GLenum>(Mode));
			_State = TransformFeedbackState::Running;
		}
	}

	void PauseTransformFeedback()
	{
		if (_State == TransformFeedbackState::Running)
		{
			glPauseTransformFeedback();
			_State = TransformFeedbackState::Paused;
		}
	}

	void ResumeTransformFeedback()
	{
		if (_State == TransformFeedbackState::Paused)
		{
			glResumeTransformFeedback();
			_State = TransformFeedbackState::Running;
		}
	}

	void EndTransformFeedback()
	{
		if (_State == TransformFeedbackState::Running)
		{
			glEndTransformFeedback();
			_State = TransformFeedbackState::End;
		}
	}

public:

	void Draw(PrimitiveMode Mode, UInt32 StreamIndex) const noexcept
	{
		glDrawTransformFeedbackStream(static_cast<GLenum>(Mode), _handle, StreamIndex);
	}

	void Draw(PrimitiveMode Mode, UInt32 StreamIndex, UInt32 InstancesNum) const noexcept
	{
		glDrawTransformFeedbackStreamInstanced(static_cast<GLenum>(Mode), _handle, StreamIndex, InstancesNum);
	}

public:

	const std::vector<std::string>& GetVaryings() const noexcept { return _Varyings; }

private:
	
	const std::vector<std::string> _Varyings;

	TransformFeedbackState _State;

	std::vector<UniquePtr<TransformFeedbackBuffer>> _TransformFeedbackBuffers;

	void _Allocate()
	{
		for (const auto& _TransformFeedbackBuffer : _TransformFeedbackBuffers)
		{
			//glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0, 0, 1024);
			glTransformFeedbackBufferRange(_handle, 0, 1, 0, 1024);
		}
	}

	void _AssociateBuffer()
	{
		for (UInt32 Index = 0; Index < _TransformFeedbackBuffers.size(); ++Index)
		{
			//glTransformFeedbackBufferRange(_handle, Index, _TransformFeedbackBuffers[Index].get_handle(), Offset, Size);
		}

	/*	if (Index < GL_MAX_TRANSFORM_FEEDBACK_BUFFERS && buffer)
		{
			
		}*/
	}

};

#endif
