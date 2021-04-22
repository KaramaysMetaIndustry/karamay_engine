#pragma once
#include "Public/STL.h"
#include "Public/GLM.h"

#include "Core/Abstract/MetaObject/MetaObject.h"

class CameraBase : public MetaObject
{
public:
	virtual void Tick(float DeltaTime);

	virtual glm::mat4 GetViewMatrix();

public:
	glm::vec3 Position;

	float Pitch, Yaw, Roll;

public:
	CameraBase();
	virtual ~CameraBase();
};

class CameraFactory : public MetaObject
{
public:
	virtual CameraBase* Create()
	{
		return nullptr;
	}
};

