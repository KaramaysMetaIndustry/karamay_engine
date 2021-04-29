#include "gl_transform_feedback.h"

gl_transform_feedback::~gl_transform_feedback()
{
}

void gl_transform_feedback::bind()
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _handle);
}

void gl_transform_feedback::unbind()
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}
