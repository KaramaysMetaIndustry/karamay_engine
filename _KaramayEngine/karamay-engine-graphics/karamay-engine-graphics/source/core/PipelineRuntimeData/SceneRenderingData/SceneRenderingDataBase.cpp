#include "SceneRenderingDataBase.h"
#include "Core/SpicesRendererGlobal.h"

void SceneRenderingDataBase::AddDirectionalLight(DirectionalLightBase* Light)
{
	auto It = Lights.find("directional_light");
	if (It != Lights.end())
	{
		It->second.push_back(Light);
	}
}

void SceneRenderingDataBase::AddPointLight(PointLightBase* Light)
{
	auto It = Lights.find("point_light");
	if (It != Lights.end())
	{
		It->second.push_back(Light);
	}
}

void SceneRenderingDataBase::AddSpotLight(SpotLightBase* Light)
{
	auto It = Lights.find("spot_light");
	if (It != Lights.end())
	{
		It->second.push_back(Light);
	}
}

void SceneRenderingDataBase::Install()
{
}

void SceneRenderingDataBase::Submit(PipelineBase* AssociatedPipeline)
{
	if (AssociatedPipeline)
	{
		auto It = Lights.find("directional_light");
		if (It != Lights.end())
		{
			for (auto DirectionalLight : It->second)
			{
				DirectionalLight->Submit(AssociatedPipeline);
			}
		}

		It = Lights.find("point_light");
		if (It != Lights.end())
		{
			for (auto PointLight : It->second)
			{
				
				PointLight->Submit(AssociatedPipeline);
			}
		}

		It = Lights.find("spot_light");
		if (It != Lights.end())
		{
			for (auto SpotLight : It->second)
			{
				SpotLight->Submit(AssociatedPipeline);
			}
		}
	}
}

void SceneRenderingDataBase::Uninstall()
{
}

SceneRenderingDataBase::SceneRenderingDataBase()
{
	Lights.emplace("directional_light", std::vector<LightBase*>());
	Lights.emplace("point_light", std::vector<LightBase*>());
	Lights.emplace("spot_light", std::vector<LightBase*>());
}

SceneRenderingDataBase::~SceneRenderingDataBase()
{
}
