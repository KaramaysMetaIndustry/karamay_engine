#pragma once
#include "Public/OpenGL.h"
#include "Public/GLM.h"
#include "Public/STL.h"

class LightBase;

class PipelineCommonTool
{
public:
	void Initalize(GLuint ProgramObj);


public:
	void SetTransformFeedbackVarings(GLsizei Count, const GLchar* const* Varyings, GLenum BufferMode);

public:
	void UpdateUniform1i(const GLchar* UniformName, GLint UniformValue);
	void UpdateUniform2i(const GLchar* UniformName, GLint UniformValue0, GLint UniformValue1);
	void UpdateUniform3i(const GLchar* UniformName, GLint UniformValue0, GLint UniformValue1, GLint UniformValue2);
	void UpdateUniform4i(const GLchar* UniformName, GLint UniformValue0, GLint UniformValue1, GLint UniformValue2, GLint UniformValue3);

	void UpdateUniform1f(const GLchar* UniformName, GLfloat UniformValue);
	void UpdateUniform2f(const GLchar* UniformName, GLfloat UniformValue0, GLfloat UniformValue1);
	void UpdateUniform3f(const GLchar* UniformName, GLfloat UniformValue0, GLfloat UniformValue1, GLfloat UniformValue2);
	void UpdateUniform4f(const GLchar* UniformName, GLfloat UniformValue0, GLfloat UniformValue1, GLfloat UniformValue2, GLfloat UniformValue3);
	void UpdateUniform2f(const GLchar* UniformName, glm::vec2 UniformValue);
	void UpdateUniform3f(const GLchar* UniformName, glm::vec3 UniformValue);
	void UpdateUniform4f(const GLchar* UniformName, glm::vec4 UniformValue);

	void UpdateUnifromMatrix3(const GLchar* UniformName, const glm::mat3& Value);
	void UpdateUniformMatrix4(const GLchar* UniformName, const glm::mat4& Value);

	void UpdateTexture1D(const GLchar* UniformName, GLint Slot);
	void UpdateTexture2D(const GLchar* UniformName, GLint Slot);
	void UpdateTexture3D(const GLchar* UniformName, GLint Slot);

	void UpdateDirectionalLights(const GLchar* UniformName, std::vector<LightBase*>& DirectionalLights);
	void UpdatePointLights(const GLchar* UniformName, std::vector<LightBase*>& PointLights);
	void UpdateSpotLights(const GLchar* UniformName, std::vector<LightBase*>& SpotLights);

private:
	GLuint programObj;
};

