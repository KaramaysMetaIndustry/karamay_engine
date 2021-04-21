#pragma once
#include "Public/STL.h"
#include "Core/PipelineRuntimeData/Texture/Abstract/TextureBase.h"

class Texture2DBase : public TextureBase
{
public:
	virtual void LoadPixels(const std::string& FilePath) override;

public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;

	virtual void Uninstall() override;

public:
	Texture2DBase();
	virtual ~Texture2DBase();
};

class Texture2DFactory
{
public:
	virtual Texture2DBase* Create()
	{
		return nullptr;
	}
};

