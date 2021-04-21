#include "PipelineCommonTool.h"

void PipelineCommonTool::Initalize(GLuint ProgramObj)
{
	programObj = ProgramObj;
}

void PipelineCommonTool::SetTransformFeedbackVarings(GLsizei Count, const GLchar* const* Varyings, GLenum BufferMode)
{
	glTransformFeedbackVaryings(programObj, Count, Varyings, BufferMode);
	glLinkProgram(programObj);
}

void PipelineCommonTool::UpdateUniform1i(const GLchar* UniformName, GLint UniformValue)
{
	glUniform1i(glGetUniformLocation(programObj, UniformName), UniformValue);
}

void PipelineCommonTool::UpdateUniform2i(const GLchar* UniformName, GLint UniformValue0, GLint UniformValue1)
{
	glUniform2i(glGetUniformLocation(programObj, UniformName), UniformValue0, UniformValue1);
}

void PipelineCommonTool::UpdateUniform3i(const GLchar* UniformName, GLint UniformValue0, GLint UniformValue1, GLint UniformValue2)
{
	glUniform3i(glGetUniformLocation(programObj, UniformName), UniformValue0, UniformValue1, UniformValue2);
}

void PipelineCommonTool::UpdateUniform4i(const GLchar* UniformName, GLint UniformValue0, GLint UniformValue1, GLint UniformValue2, GLint UniformValue3)
{
	glUniform4i(glGetUniformLocation(programObj, UniformName), UniformValue0, UniformValue1, UniformValue2, UniformValue3);
}

void PipelineCommonTool::UpdateUniform1f(const GLchar* UniformName, GLfloat UniformValue)
{
	glUniform1f(glGetUniformLocation(programObj, UniformName), UniformValue);
}

void PipelineCommonTool::UpdateUniform2f(const GLchar* UniformName, GLfloat UniformValue0, GLfloat UniformValue1)
{
	glUniform2f(glGetUniformLocation(programObj, UniformName), UniformValue0, UniformValue1);
}

void PipelineCommonTool::UpdateUniform3f(const GLchar* UniformName, GLfloat UniformValue0, GLfloat UniformValue1, GLfloat UniformValue2)
{
	glUniform3f(glGetUniformLocation(programObj, UniformName), UniformValue0, UniformValue1, UniformValue2);
}

void PipelineCommonTool::UpdateUniform4f(const GLchar* UniformName, GLfloat UniformValue0, GLfloat UniformValue1, GLfloat UniformValue2, GLfloat UniformValue3)
{
	glUniform4f(glGetUniformLocation(programObj, UniformName), UniformValue0, UniformValue1, UniformValue2, UniformValue3);
}

void PipelineCommonTool::UpdateUniform2f(const GLchar* UniformName, glm::vec2 UniformValue)
{
	glUniform2f(glGetUniformLocation(programObj, UniformName), UniformValue.x, UniformValue.y);
}

void PipelineCommonTool::UpdateUniform3f(const GLchar* UniformName, glm::vec3 UniformValue)
{
	glUniform3f(glGetUniformLocation(programObj, UniformName), UniformValue.x, UniformValue.y, UniformValue.z);
}

void PipelineCommonTool::UpdateUniform4f(const GLchar* UniformName, glm::vec4 UniformValue)
{
	glUniform4f(glGetUniformLocation(programObj, UniformName), UniformValue.x, UniformValue.y, UniformValue.z, UniformValue.w);
}

void PipelineCommonTool::UpdateUnifromMatrix3(const GLchar* UniformName, const glm::mat3& Value)
{
}

void PipelineCommonTool::UpdateUniformMatrix4(const GLchar* UniformName, const glm::mat4& UniformValue)
{
	glUniformMatrix4fv(glGetUniformLocation(programObj, UniformName), 1, GL_FALSE, glm::value_ptr(UniformValue));
}

void PipelineCommonTool::UpdateTexture1D(const GLchar* UniformName, GLint Slot)
{
}

void PipelineCommonTool::UpdateTexture2D(const GLchar* UniformName, GLint Slot)
{
	UpdateUniform1i(UniformName, Slot);
}

void PipelineCommonTool::UpdateTexture3D(const GLchar* UniformName, GLint Slot)
{
}