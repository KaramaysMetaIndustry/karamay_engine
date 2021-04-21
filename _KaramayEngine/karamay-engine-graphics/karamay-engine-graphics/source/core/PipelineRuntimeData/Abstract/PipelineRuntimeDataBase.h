#pragma once
#include "Public/STL.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

class RendererBase;
class PipelineBase;

class PipelineRuntimeDataBase : public MetaObject
{
public:
	virtual void Install() = 0;

	virtual void Submit(PipelineBase* AssociatedPipeline) = 0;

	virtual void Uninstall() = 0;

public:
	std::string PrefixAttributeName;

public:
	PipelineRuntimeDataBase();
	virtual ~PipelineRuntimeDataBase();
};

