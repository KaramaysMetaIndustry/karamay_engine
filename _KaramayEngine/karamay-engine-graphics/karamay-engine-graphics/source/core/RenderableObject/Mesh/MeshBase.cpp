#include "MeshBase.h"
#include "Core/SpicesRendererGlobal.h"

void MeshBase::Install()
{
	if (Material && OwnedScene)
	{
		OwnedScene->SceneData->Install();
		Material->Install();
	}
}

void MeshBase::Render(float DeltaTime)
{
	if (Material && OwnedScene && AssociatedPipeline)
	{
		OwnedScene->SceneData->Submit(AssociatedPipeline);	
		Material->Submit(AssociatedPipeline);
	}
}

void MeshBase::Uninstall()
{
	if (Material && OwnedScene)
	{
		OwnedScene->SceneData->Uninstall();
		Material->Uninstall();
	}
}

bool MeshBase::IsRenderable()
{
	return false;
}

void MeshBase::SetIndices(const std::vector<size_t>& Data)
{
	Indices = Data;
}

void MeshBase::SetPositions(const std::vector<float>& Data)
{
	Positions = Data;
}

void MeshBase::SetNormals(const std::vector<float>& Data)
{
	Normals = Data;
}

void MeshBase::SetUVs(const std::vector<float>& Data)
{
	UVs = Data;
}

void MeshBase::SetOffsetPositions(const std::vector<float>& Data)
{
	OffsetPositions = Data;
}

MeshBase::MeshBase()
{
	bEnableGeometryRecombination = false;
	bEnableTessellation = false;
	bEnableGlobalIllumination = false;

	Material = nullptr;
	Material = MaterialCreator->Create();
}

MeshBase::~MeshBase()
{
}
