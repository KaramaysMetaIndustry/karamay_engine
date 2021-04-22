#pragma once
#include "Core/Scene/SceneBase.h"

class Scene_OpenGL : public SceneBase
{
};

class SceneFactory_OpenGL : public SceneFactory
{
public:
	virtual SceneBase* Create() override
	{
		return new Scene_OpenGL();
	}
};

