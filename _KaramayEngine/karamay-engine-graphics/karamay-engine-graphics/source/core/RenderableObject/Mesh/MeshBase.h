#pragma once
#include "Public/STL.h"
#include "Core/RenderableObject/Abstract/RenderableObjectBase.h"

class MaterialBase;

class MeshBase : public RenderableObjectBase
{
public:
	bool bEnableGeometryRecombination : 1;

	bool bEnableTessellation : 1;

	bool bEnableGlobalIllumination : 1;

public:
	/** A mesh can only have one material. */
	MaterialBase* Material;

public:
	/** Optional setting. */
	void SetIndices(const std::vector<size_t>& Data);

	/** Required setting. Every point's local position. */
	void SetPositions(const std::vector<float>& Data);
	
	/** Required setting. To fetch texels. */
	void SetUVs(const std::vector<float>& Data);
	
	/** Optional setting. You can also fetch these from normal_map. */
	void SetNormals(const std::vector<float>& Data);
	
	/** Optional setting. If you do not set this, we'll use a default value and only render one instance. */
	void SetOffsetPositions(const std::vector<float>& Data);

protected:
	std::vector<size_t> Indices;

	std::vector<float> Positions;
	const size_t PositionSize = 3;

	std::vector<float> UVs;
	const size_t UVSize = 2;

	std::vector<float> Normals;
	const size_t NormalSize = 3;

	std::vector<float> OffsetPositions;
	const size_t OffsetPositionSize = 3;

public:
	//~ begin override
	virtual void Install() override;
	virtual void Render(float DeltaTime) override;
	virtual void Uninstall() override;
	virtual bool IsRenderable() override;
	//~ end override

public:
	MeshBase();
	virtual ~MeshBase();
};

class MeshFactory
{
public:
	virtual MeshBase* Create()
	{
		return new MeshBase();
	}
};

