#pragma once
#include "Public/STL.h"
#include "Public/GLM.h"

#include "Core/PipelineRuntimeData/Abstract/PipelineRuntimeDataBase.h"

class Texture2DBase;
class PipelineBase;


class MaterialBase : public PipelineRuntimeDataBase
{
public:
	virtual void Install() override;
	virtual void Submit(PipelineBase* AssociatedPipeline) override;
	virtual void Uninstall() override;

public:
	virtual void Load(const std::string& Directory);

	virtual void Load(const std::vector<std::string>& FilePathes);

	virtual bool IsMaterialAvaliable();

	virtual void Restore();

	virtual void MergeTextures();

public:
	std::string MaterialName;

	std::string Directory;

protected:
	std::unordered_map<std::string, Texture2DBase*> Maps;

public:
	float Opacity;

	Texture2DBase* AlbedoMap;

	Texture2DBase* NormalMap;

	Texture2DBase* MetalnessMap;

	Texture2DBase* RoughnessMap;

	Texture2DBase* DisplacementMap;
	
	Texture2DBase* AmbientOcclusionMap;

	glm::vec3 AlbedoScale;

	float MetalnessScale;
	
	float RoughnessScale;
	
	float DisplacementScale;
	
	float AmbientOcclusionScale;

public:
	MaterialBase();
	virtual ~MaterialBase();
};

class MaterialFactory
{
public:
	virtual MaterialBase* Create()
	{
		return new MaterialBase();
	}
};

