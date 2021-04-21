#pragma once
#include "Public/STL.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

class ShaderAssemblageInfoBase;

class PipelineAssemblageInfoBase : public MetaObject
{
public:
	std::vector<ShaderAssemblageInfoBase*> ShaderAssmblageInfos;

	std::string PipelineName;
};

class PipelineAssemblageInfoFactory
{
public:
	virtual PipelineAssemblageInfoBase* Create()
	{
		return nullptr;
	}
};

