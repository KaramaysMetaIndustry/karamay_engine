#pragma once
#include "Public/STL.h"
#include "Public/GLM.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

class RendererAllocatorBase;
class WindowBase;
class CameraBase;
class SceneBase;
class PipelineBase;

class RendererBase : public MetaObject
{
public:
	RendererAllocatorBase* Allocator;

public:
	/** Load the renderer context. (Lazy loading)*/
	virtual void LoadContext();
	
	/** Add a scene, and create association between renderer and renderable objects. */
	virtual void AddScene(SceneBase* Scene);
	
	/** Remove a scene, and destory association between renderer and renderable objects. */
	virtual void RemoveScene(SceneBase* Scene);
	
	/** Switch current scene, create new association between pipelines and renderable objects.*/
	virtual void SwitchScene(const std::string& SceneName);
	
	/** Core rendering. */
	virtual void Render(float DeltaTime);

public:
	/** Set viewport size with framebuffer size. */
	virtual void SetViewport(size_t Width, size_t Height);
	
	/** Set the max view distance. 20 <= VD <= 1000 */
	virtual void SetViewDistance(float Distance);
	
	/** Set the field of view. 45 <= FOV <= 90*/
	virtual void SetViewField(float Field);

private:
	/** Associate renderable objects to pipelines. */
	void RegisterScene(SceneBase* Scene);
	
	/** Unassociate renderable objects to pipelines. */
	void UnregisterScene(SceneBase* Scene);

protected:
	SceneBase* CurrentScene;

	std::unordered_map<std::string, SceneBase*> SceneMap;

	std::unordered_map<std::string, PipelineBase*> PipelineMap;

	size_t FramebufferWidth, FramebufferHeight;

	float ViewDistance;

	float ViewField;

public:
	glm::mat4 GetProjectionMatrix();

public:
	RendererBase();
	virtual ~RendererBase();
};

class RendererFactory
{
public:
	virtual RendererBase* Create()
	{
		return nullptr;
	}
};

