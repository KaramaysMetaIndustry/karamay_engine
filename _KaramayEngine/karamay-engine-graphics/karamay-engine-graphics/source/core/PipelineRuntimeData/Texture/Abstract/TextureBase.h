#pragma once
#include "Public/STL.h"
#include "Core/PipelineRuntimeData/Abstract/PipelineRuntimeDataBase.h"

enum class TextureApplicationType : unsigned int
{
	AmbientMap,
	DiffuseMap,
	SpecularMap,

	Null
};

class TextureBase : public PipelineRuntimeDataBase
{
public:
	virtual void LoadPixels(const std::string& FilePath) = 0;

public:
	TextureApplicationType ApplicationType;

protected:
	TextureBase();
	virtual ~TextureBase();
};

