#pragma once
#include "graphics/glo/gl_object.h"

class gl_transform_feedback final : public gl_object
{
public:
	static std::shared_ptr<gl_transform_feedback> construct()
	{
		return std::make_shared<gl_transform_feedback>();
	}

	~gl_transform_feedback();

private:
	gl_transform_feedback();

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

