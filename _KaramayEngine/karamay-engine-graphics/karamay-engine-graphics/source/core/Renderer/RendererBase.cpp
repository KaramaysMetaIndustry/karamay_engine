#include "RendererBase.h"
#include "Core/SpicesRendererGlobal.h"

void RendererBase::Render(float DeltaTime)
{
	if (CurrentScene)
		CurrentScene->Tick(DeltaTime);

	for (auto It = PipelineMap.begin(); It != PipelineMap.end(); ++It)
	{
		auto Pipeline = It->second;
		if (Pipeline)
		{
			Pipeline->PipelineRender(DeltaTime);
		}
	}
}

void RendererBase::LoadContext()
{
}

void RendererBase::AddScene(SceneBase* Scene)
{
	if (Scene)
	{
		SceneMap.emplace(Scene->SceneName, Scene);
		for (auto Pair : Scene->RenderableObjects)
		{
			auto& Group = Pair.second;
			for (auto RenderableObject : Group)
			{
				if (RenderableObject)
					RenderableObject->AssociatedRenderer = this;
			}
		}
	}
}

void RendererBase::RemoveScene(SceneBase* Scene)
{
	if (Scene)
	{
		for (auto Pair : Scene->RenderableObjects)
		{
			auto& Group = Pair.second;
			for (auto RenderableObject : Group)
			{
				if (RenderableObject)
					RenderableObject->AssociatedRenderer = this;
			}
		}
		SceneMap.erase(Scene->SceneName);
	}
}

void RendererBase::SetViewport(size_t Width, size_t Height)
{
	FramebufferWidth = Width;
	FramebufferHeight = Height;
}

void RendererBase::SetViewDistance(float Distance)
{
	if (Distance >= 20.0f && Distance <= 1000.0f)
		ViewDistance = Distance;
}

void RendererBase::SetViewField(float Field)
{
	if (Field >= 45.0f && Field <= 90.0f) // 40.0  45.0  90.0
		ViewField = Field;
}

void RendererBase::SwitchScene(const std::string& SceneName)
{
	auto It = SceneMap.find(SceneName);
	if (It != SceneMap.end())
	{
		if (CurrentScene)
			UnregisterScene(CurrentScene);

		RegisterScene(It->second);
	}
}

void RendererBase::RegisterScene(SceneBase* Scene)
{
	if (Scene)
	{
		//std::cout << "Renderer get a new scene, start to register." << std::endl;
		auto& RenderableObjects = Scene->RenderableObjects;
		//std::cout << "Start parsing renderable objects and try to construct associated pipelines." << std::endl;
		for (auto It = RenderableObjects.begin(); It != RenderableObjects.end(); ++It)
		{
			auto& RenderableObjectsGroup = It->second;
			for (auto RenderableObject : RenderableObjectsGroup)
			{
				if (RenderableObject)
				{
					auto PipelineAssemblageInfo = RenderableObject->PipelineAssemblageInfo;
					if (PipelineAssemblageInfo)
					{
						std::string PipelineName = PipelineAssemblageInfo->PipelineName;
						auto ItFind = PipelineMap.find(PipelineName);
						// create association between objects and pipelines
						if (ItFind == PipelineMap.end())
						{
							//std::cout << "Can not find an available pipeline, we try to create a new one." << std::endl;
							PipelineBase* NewPipeline = PipelineCreator->CreatePipeline();
							NewPipeline->Assembly(PipelineAssemblageInfo);
							NewPipeline->AssociateTo(RenderableObject);
							RenderableObject->AssociatedPipeline = NewPipeline;
							PipelineMap.emplace(PipelineName, NewPipeline); // add the finished pipeline
						}
						else {
							//std::cout << "Find an available pipeline, we try to associate to it." << std::endl;
							auto OldPipeline = ItFind->second;
							if (OldPipeline)
							{
								OldPipeline->AssociateTo(RenderableObject);
								RenderableObject->AssociatedPipeline = OldPipeline;
								RenderableObject->AssociatedRenderer = this;
							}
						}
					}
					// install object to context
					RenderableObject->Install();
				}
			}
		}
		CurrentScene = Scene;
		//std::cout << "The new scene has been successfully registered." << std::endl;
	}
}

void RendererBase::UnregisterScene(SceneBase* Scene)
{
	if (Scene)
	{
		auto& RenderableObjects = Scene->RenderableObjects;
		for (auto It = RenderableObjects.begin(); It != RenderableObjects.end(); ++It)
		{
			auto RenderableObjectGroup = It->second;
			for (auto RenderableObject : RenderableObjectGroup)
			{
				if (RenderableObject)
				{
					auto RelatedPipeline = RenderableObject->AssociatedPipeline;
					if (RelatedPipeline)
					{
						// destory association between objects and pipeline
						RelatedPipeline->UnassociateTo(RenderableObject);
						RenderableObject->AssociatedPipeline = nullptr;
					}
					// uninstall objects from context
					RenderableObject->Uninstall();
				}
			}
		}
		CurrentScene = nullptr;
	}
}

glm::mat4 RendererBase::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(ViewField), (float)FramebufferWidth / (float)FramebufferHeight, 0.1f, ViewDistance);
}

RendererBase::RendererBase()
{
	Allocator = RendererAllocatorCreator->Create();

	ViewDistance = 100.0f;
	ViewField = 45.0f;
}

RendererBase::~RendererBase()
{
}



