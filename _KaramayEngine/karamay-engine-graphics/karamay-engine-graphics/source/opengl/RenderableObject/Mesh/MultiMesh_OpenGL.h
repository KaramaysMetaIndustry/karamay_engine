#pragma once
#include "Public/OpenGL.h"
#include "Public/STL.h"
#include "Public/GLM.h"
#include "Core/RenderableObject/Mesh/MultiMeshBase.h"

class MultiMesh_OpenGL : public MultiMeshBase
{
public:
	virtual void Install() override;

	virtual void Render(float DeltaTime) override;

	virtual void Uninstall() override;

private:

	GLuint MultiVertexArrayObject;

	GLuint MultiVertexBufferObject, MultiElementBufferObject;
};

