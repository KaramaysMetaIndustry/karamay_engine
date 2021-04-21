#pragma once
#include "Core/Shader/ShaderBase.h"
#include "Public/OpenGL.h"
#include "Public/STL.h"

class Shader_OpenGL : public ShaderBase
{
public:
	virtual void Assembly(ShaderAssemblageInfoBase* Info) override;

public:
	GLuint GetShaderObj() { return shaderObj; }

private:
	GLuint shaderObj;

	const GLchar* sourceCode;

	GLenum shaderType;

};

class ShaderFactory_OpenGL : public ShaderFactory
{
public:
	virtual ShaderBase* CreateShader()
	{
		return new Shader_OpenGL();
	}
};

