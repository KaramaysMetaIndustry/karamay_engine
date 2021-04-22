#pragma once
#include "Public/STL.h"
#include "Core/PipelineRuntimeData/Abstract/PipelineRuntimeDataBase.h"

class LightBase;
class DirectionalLightBase;
class PointLightBase;
class SpotLightBase;

class SceneRenderingDataBase : public PipelineRuntimeDataBase
{
public:
	virtual void AddDirectionalLight(DirectionalLightBase* Light);

	virtual void AddPointLight(PointLightBase* Light);

	virtual void AddSpotLight(SpotLightBase* Light);

public:
	std::unordered_map<std::string, std::vector<LightBase*>> Lights;

public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;

	virtual void Uninstall() override;

public:
	SceneRenderingDataBase();
	virtual ~SceneRenderingDataBase();

};

class SceneRenderingDataFactory : public MetaObject
{
public:
	virtual SceneRenderingDataBase* Create()
	{
		return new SceneRenderingDataBase();
	}
};

