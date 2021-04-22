#pragma once
#include "Public/STL.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

class LightBase;
class SceneRenderingDataBase;
class RenderableObjectBase;
class CameraBase;

class SceneBase : public MetaObject
{
public:
	virtual void AddRenderableObject(RenderableObjectBase* RenderableObject);

	virtual void RemoveRenderableObject(RenderableObjectBase* RenderableObject);

	virtual void Tick(float DeltaTime);

	virtual CameraBase* GetDefaultCamera();

	virtual std::vector<CameraBase*>& GetAllCameras();

protected:
	std::vector<CameraBase*> Observers;

public:
	std::string SceneName;

	SceneRenderingDataBase* SceneData;

	std::unordered_map<std::string, std::vector<RenderableObjectBase*>> RenderableObjects;

public:
	SceneBase();
	virtual ~SceneBase();
};

class SceneFactory
{
public:
	virtual SceneBase* Create()
	{
		return nullptr;
	}
};

