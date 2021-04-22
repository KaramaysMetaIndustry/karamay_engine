#pragma once
#include "Public/STL.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

enum class EShaderType
{
	VertexShader,
	TessellationControlShader,
	TessellationEvaluationShader,
	GeometryShader,
	FragmentShader,
	ComputeShader
};

class ShaderAssemblageInfoBase : public MetaObject
{
public:
	std::string FilePath;

	EShaderType Type;

public:
	virtual void Fomat();

public:
	ShaderAssemblageInfoBase();
	virtual ~ShaderAssemblageInfoBase();

};

class ShaderAssemblageInfoFactory
{
public:
	virtual ShaderAssemblageInfoBase* Create()
	{
		return nullptr;
	}
};

