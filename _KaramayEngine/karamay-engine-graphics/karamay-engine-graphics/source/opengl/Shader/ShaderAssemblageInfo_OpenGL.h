#pragma once
#include "Core/Shader/ShaderAssemblageInfoBase.h"
#include "Public/OpenGL.h"

class ShaderAssemblageInfo_OpenGL : public ShaderAssemblageInfoBase
{
public:
	GLenum GetOpenGLShaderType()
	{
		switch (Type)
		{
		case EShaderType::VertexShader: return GL_VERTEX_SHADER;
		case EShaderType::TessellationControlShader: return GL_TESS_CONTROL_SHADER;
		case EShaderType::TessellationEvaluationShader: return GL_TESS_EVALUATION_SHADER;
		case EShaderType::GeometryShader: return GL_GEOMETRY_SHADER;
		case EShaderType::FragmentShader: return GL_FRAGMENT_SHADER;
		case EShaderType::ComputeShader: return GL_COMPUTE_SHADER;
		default:
			break;
		}
	}
};


class ShaderAssemblageInfoFactory_OpenGL : public ShaderAssemblageInfoFactory
{
public:
	ShaderAssemblageInfoBase* Create() override
	{
		return new ShaderAssemblageInfo_OpenGL();
	}
};

