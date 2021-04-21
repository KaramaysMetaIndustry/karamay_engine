#pragma once
#include "Core/Camera/CameraBase.h"

class Camera_OpenGL : public CameraBase
{
public:
	Camera_OpenGL();
	virtual ~Camera_OpenGL();
};

class CameraFactory_OpenGL : public CameraFactory
{
public:
	virtual CameraBase* Create()
	{
		return new Camera_OpenGL();
	}
};

