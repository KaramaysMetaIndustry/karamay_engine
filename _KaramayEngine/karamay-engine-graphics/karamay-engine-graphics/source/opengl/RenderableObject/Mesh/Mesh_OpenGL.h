#pragma once
#include "Public/OpenGL.h"
#include "Public/GLM.h"
#include "Public/STL.h"
#include "Core/RenderableObject/Mesh/MeshBase.h"

class Mesh_OpenGL : public MeshBase
{
public:
	virtual void Install() override;

	virtual void Render(float DeltaTime) override;
	
	virtual void Uninstall() override;

private:
	GLuint vertexArrayObject;
	
	std::vector<GLuint> vertexBufferObjects;

	GLuint elementBufferObject, instanceBufferObject;

public:
	Mesh_OpenGL();
	virtual ~Mesh_OpenGL();
};


class MeshFactory_OpenGL : public MeshFactory
{
public:
	virtual MeshBase* Create() override
	{
		return new Mesh_OpenGL();
	}
};

