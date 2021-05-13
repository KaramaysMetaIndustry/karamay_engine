#include "gl_pipeline_base.h"

gl_pipeline_base::gl_pipeline_base()
{
	glCreateProgramPipelines(1, &_handle);
}

gl_pipeline_base::~gl_pipeline_base()
{
	glDeleteProgramPipelines(1, &_handle);
}
