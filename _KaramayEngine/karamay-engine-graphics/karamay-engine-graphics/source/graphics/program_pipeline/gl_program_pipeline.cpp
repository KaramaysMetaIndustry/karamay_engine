#include "gl_program_pipeline.h"
#include "graphics/program/gl_program.h"

void gl_program_pipeline::attach_program(GLbitfield stages, std::shared_ptr<gl_program> program)
{
	glUseProgramStages(_handle, stages, program->get_handle());
	/*glBindAttribLocation();
	glBindFragDataLocation()*/
}

void gl_program_pipeline::enable_scissor_test()
{
	glEnable(GL_SCISSOR_TEST);
}

void gl_program_pipeline::disable_scissor_test()
{
	glDisable(GL_SCISSOR_TEST);
}

void gl_program_pipeline::set_scissor_box(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glScissor(x, y, width, height);
}

void gl_program_pipeline::set_scissor_box(GLint x, GLint y, GLsizei width, GLsizei height, GLuint viewport_index)
{
	if (viewport_index >= GL_MAX_VIEWPORTS) return;
	glScissorIndexed(viewport_index, x, y, width, height);
}

void gl_program_pipeline::enable_stencil_test()
{
	glEnable(GL_STENCIL_TEST);
}

void gl_program_pipeline::disable_stencil_test()
{
	glDisable(GL_STENCIL_TEST);
}

void gl_program_pipeline::set_stencil_mask(GLuint mask)
{
	glStencilMask(mask);
}

void gl_program_pipeline::set_stencil_function(GLenum func, GLint stencil_value, GLuint mask)
{
	glStencilFunc(func, stencil_value, mask);
}

void gl_program_pipeline::set_stencil_function(GLenum front_func, GLenum back_func, GLint stencil_value, GLuint mask)
{
	glStencilFuncSeparate(front_func, back_func, stencil_value, mask);
}

void gl_program_pipeline::set_stencil_operation(GLenum fail, GLenum z_fail, GLenum z_pass)
{
	glStencilOp(fail, z_fail, z_pass);
}

void gl_program_pipeline::set_stencil_operation(GLenum face, GLenum sfail, GLenum dp_fail, GLenum dp_pass)
{
	glStencilOpSeparate(face, sfail, dp_fail, dp_pass);
}

void gl_program_pipeline::enable_depth_test()
{
	glEnable(GL_DEPTH_TEST);
}

void gl_program_pipeline::disable_depth_test()
{
	glDisable(GL_DEPTH_TEST);
}

void gl_program_pipeline::bind()
{
	glUseProgram(0); // program 优先级高于 program pipeline ，必须确保program当前无绑定
	glBindProgramPipeline(_handle);
}

void gl_program_pipeline::unbind()
{
	glBindProgramPipeline(0);
}

gl_program_pipeline::gl_program_pipeline()
{
	glCreateProgramPipelines(1, &_handle);
}

gl_program_pipeline::~gl_program_pipeline()
{
	glDeleteProgramPipelines(1, &_handle);
}
