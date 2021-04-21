#include "SceneRenderingData_OpenGL.h"
#include "OpenGL/Implement_OpenGL.h"

void SceneRenderingData_OpenGL::Install()
{
}

void SceneRenderingData_OpenGL::Submit(PipelineBase* AssociatedPipeline)
{
	if (AssociatedPipeline)
	{
		auto Submitter = dynamic_cast<Pipeline_OpenGL*>(AssociatedPipeline)->CommonTool;
		auto It = Lights.find("directional_light");

		if (It != Lights.end())
		{
			auto DirectionalLights = It->second;
			for (size_t i = 0; i < DirectionalLights.size(); ++i)
			{
				DirectionalLights[i]->PrefixAttributeName
					= "en_lights.directional_lights[" + std::to_string(i) + "]";
			}
			Submitter->UpdateUniform1i("en_lights.directional_lights_num", DirectionalLights.size());
		}

		It = Lights.find("point_light");
		if (It != Lights.end())
		{
			
			auto PointLights = It->second;
			for (size_t i = 0; i < PointLights.size(); ++i)
			{
				PointLights[i]->PrefixAttributeName
					= "en_lights.point_lights[" + std::to_string(i) + "]";
			}
			Submitter->UpdateUniform1i("en_lights.point_lights_num", PointLights.size());
		}

		It = Lights.find("spot_light");
		if (It != Lights.end())
		{
			auto SpotLights = It->second;
			for (size_t i = 0; i < SpotLights.size(); ++i)
			{
				SpotLights[i]->PrefixAttributeName
					= "en_lights.spot_lights[" + std::to_string(i) + "]";
			}
			Submitter->UpdateUniform1i("en_lights.spot_lights_num", SpotLights.size());
		}

		Submitter->UpdateUniform3f("en_lights.ambient_light", glm::vec3(0.5f, 0.5f, 0.5f));
	}

	SceneRenderingDataBase::Submit(AssociatedPipeline);
}

void SceneRenderingData_OpenGL::Uninstall()
{
}
