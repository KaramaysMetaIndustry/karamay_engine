#ifndef GL_TRANSFORM_FEEDBACK_H
#define GL_TRANSFORM_FEEDBACK_H

#include "../glo/gl_object.h"
#include "../buffers/indexed_buffer/gl_transform_feedback_buffer.h"
#include "graphics/renderer/pipeline/base/vertex_launcher/gl_vertex_launcher.h"

class gl_transform_feedback final : public gl_object{
public:
	gl_transform_feedback() : gl_object(gl_object_type::TRANSFORM_FEEDBACK_OBJ) {};
	gl_transform_feedback(const std::vector<std::string>& Varings, uint32 AcceptDataFrom) :
		gl_object(gl_object_type::TRANSFORM_FEEDBACK_OBJ), 
		_State(TransformFeedbackState::End)
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

	void bind() const noexcept
	{
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _handle);
	}

	void unbind() const noexcept
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

	void begin_transform_feedback(gl_primitive_mode mode)
	{
		if (_State == TransformFeedbackState::End)
		{
			glBeginTransformFeedback(static_cast<GLenum>(mode));
			_State = TransformFeedbackState::Running;
		}
	}

	void pause_transform_feedback()
	{
		if (_State == TransformFeedbackState::Running)
		{
			glPauseTransformFeedback();
			_State = TransformFeedbackState::Paused;
		}
	}

	void resume_transform_feedback()
	{
		if (_State == TransformFeedbackState::Paused)
		{
			glResumeTransformFeedback();
			_State = TransformFeedbackState::Running;
		}
	}

	void end_transform_feedback()
	{
		if (_State == TransformFeedbackState::Running)
		{
			glEndTransformFeedback();
			_State = TransformFeedbackState::End;
		}
	}

public:

	void draw(gl_primitive_mode mode, uint32 stream_index) const noexcept
	{
		glDrawTransformFeedbackStream(static_cast<GLenum>(mode), _handle, stream_index);
	}

	void draw(gl_primitive_mode mode, uint32 stream_index, uint32 intsances_num) const noexcept
	{
		glDrawTransformFeedbackStreamInstanced(static_cast<GLenum>(mode), _handle, stream_index, intsances_num);
	}

public:

	const std::vector<std::string>& GetVaryings() const noexcept { return _Varyings; }

private:
	
	const std::vector<std::string> _Varyings;

	TransformFeedbackState _State;

	std::vector<std::unique_ptr<gl_transform_feedback_buffer>> _TransformFeedbackBuffers;

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
		for (uint32 Index = 0; Index < _TransformFeedbackBuffers.size(); ++Index)
		{
			//glTransformFeedbackBufferRange(_handle, Index, _TransformFeedbackBuffers[Index].get_handle(), Offset, Size);
		}

	/*	if (Index < GL_MAX_TRANSFORM_FEEDBACK_BUFFERS && buffer)
		{
			
		}*/
	}

};

#endif
