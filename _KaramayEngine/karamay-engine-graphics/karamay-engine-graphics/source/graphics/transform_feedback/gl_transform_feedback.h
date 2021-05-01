#pragma once
#include "graphics/glo/gl_object.h"

class gl_transform_feedback final : public gl_object
{
public:
	
	static std::shared_ptr<gl_transform_feedback> construct()
	{
		return std::make_shared<gl_transform_feedback>();
	}

	virtual ~gl_transform_feedback()
	{
		glDeleteTransformFeedbacks(1, &_handle);
	}

private:

	gl_transform_feedback()
	{
		glCreateTransformFeedbacks(1, &_handle);
	}

public:
	
	void bind();

	void unbind();

public:

	static void begin()
	{
		glBeginTransformFeedback(GL_PATCHES);
	}

	static void end(){
		glEndTransformFeedback();
	}

	static void pause() {
		glPauseTransformFeedback();
	}

	static void resume() {
		glResumeTransformFeedback();
	}

	static void draw()
	{
	}

};

