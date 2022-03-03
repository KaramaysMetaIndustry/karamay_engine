#include "gl_pipeline.h"

void gl_pipeline::enable() noexcept
{
	if (_program)
	{
		_program->enable();
	}
}

void gl_pipeline::disable() noexcept
{
	if (_program)
	{
		_program->disable();
	}
}
