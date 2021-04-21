#pragma once
#include "Public/STL.h"
#include "Public/GLM.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

class SceneBase;
class PipelineAssemblageInfoBase;
class PipelineBase;
class RendererBase;

enum class EPrimitiveMode : size_t
{
	Points,
	Triangles,
	TriangleStrip,
	Patches
};

class RenderableObjectBase : public MetaObject
{
public:
	/** The object world position. */
	glm::vec3 Position;

	/** The object rotation. */
	float Pitch, Yaw, Roll;

public:
	/** Scene the object owned by. It will be fed back by scene when adding. */
	SceneBase* OwnedScene;

	/** Associated pipeline's asseblage info. */
	PipelineAssemblageInfoBase* PipelineAssemblageInfo;
	
	/** It will be fed back by renderer when registering. */
	PipelineBase* AssociatedPipeline;

	/** It will be fed back by renderer when registering. */
	RendererBase* AssociatedRenderer;

public:
	/** Prepare data and install them at context. 
	*These data's change won't work until next call. 
	*/
	virtual void Install() = 0;

	/** Call per frame, these data' change will be updated per call. */
	virtual void Render(float DeltaTime) = 0;
	
	/** Clear these data from context. */
	virtual void Uninstall() = 0;

	/** Is object renderable now. */
	virtual bool IsRenderable() = 0;

protected:
	glm::mat4 GenerateModelMatrix() const;

protected:
	EPrimitiveMode PrimitiveMode;

	size_t PrimitivePointNum;

public:
	void SetPrimitiveMode(EPrimitiveMode Mode, size_t PointNum = 0);

protected:
	RenderableObjectBase();
	virtual ~RenderableObjectBase();
};

class RenderableObjectFactory : public MetaObject
{
public:
	virtual RenderableObjectBase* Create()
	{
		return nullptr;
	}
};

