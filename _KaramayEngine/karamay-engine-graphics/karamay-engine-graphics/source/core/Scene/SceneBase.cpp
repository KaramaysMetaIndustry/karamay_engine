#include "SceneBase.h"
#include "Core/SpicesRendererGlobal.h"

void SceneBase::AddRenderableObject(RenderableObjectBase* RenderableObject)
{
	if (RenderableObject)
	{
		auto It = RenderableObjects.find(RenderableObject->GetClassName());
		if (It == RenderableObjects.end())
		{
			RenderableObjects.emplace(RenderableObject->GetClassName(), std::vector<RenderableObjectBase*>());
			It = RenderableObjects.find(RenderableObject->GetClassName());
		}		
		It->second.push_back(RenderableObject);
		RenderableObject->OwnedScene = this;
	}
}

void SceneBase::RemoveRenderableObject(RenderableObjectBase* RenderableObject)
{
	if (RenderableObject)
	{
	}
}

void SceneBase::Tick(float DeltaTime)
{
	for (auto Camera : Observers)
	{
		if (Camera)
		{
			Camera->Tick(DeltaTime);
		}
	}

	auto It = SceneData->Lights.find("point_light");
	if (It != SceneData->Lights.end())
	{
		auto PointLight = dynamic_cast<PointLightBase*>(It->second.at(0));
		PointLight->Position.x += 0.05f;
	}
}

CameraBase* SceneBase::GetDefaultCamera()
{
	return Observers.size() > 0 ? Observers[0] : nullptr;
}

std::vector<CameraBase*>& SceneBase::GetAllCameras()
{
	return Observers;
}

SceneBase::SceneBase()
{
	// set default camera
	auto DefaultCamera = CameraCreator->Create();
	DefaultCamera->Pitch = glm::radians(0.0f); // -30 ~ 30 top - down
	DefaultCamera->Yaw = glm::radians(180.0f); // 150 - 210 left - right
	DefaultCamera->Roll = glm::radians(0.0f);
	DefaultCamera->Position = glm::vec3(0.0f, 0.0f, 2.0f);
	Observers.push_back(DefaultCamera);

	SceneData = SceneRenderingDataCreator->Create();

	DirectionalLightBase* DirecLight = DirectionalLightCreator->Create();
	PointLightBase* PointLight0 = PointLightCreator->Create();
	PointLightBase* PointLight1 = PointLightCreator->Create();
	SpotLightBase* SpotLight = SpotLightCreator->Create();

	PointLight0->Position = glm::vec3(-2.0f, 0.0f, 5.0f);
	PointLight0->Color = glm::vec3(10.0f, 10.0f, 10.0f);
	PointLight0->Constant = 1.0f;
	PointLight0->Linear = 0.09f;
	PointLight0->Quadratic = 0.0032f;

	PointLight1->Position = glm::vec3(-10.0f, 3.0f, 2.0f);
	PointLight1->Color = glm::vec3(5.0f, 5.0f, 5.0f);
	PointLight1->Constant = 1.0f;
	PointLight1->Linear = 0.09f;
	PointLight1->Quadratic = 0.0032f;
	
	SceneData->AddDirectionalLight(DirecLight);
	SceneData->AddPointLight(PointLight0);
	//SceneData->AddPointLight(PointLight1);
	SceneData->AddSpotLight(SpotLight);
}

SceneBase::~SceneBase()
{
}
