#ifndef GLTF_ASSET
#define GLTF_ASSET

class gltf_asset
{
public:
	gltf_asset()
	{

	}

	~gltf_asset() = default;

public:

	bool load(const nlohmann::json& object)
	{
		return true;
	}

};


#endif