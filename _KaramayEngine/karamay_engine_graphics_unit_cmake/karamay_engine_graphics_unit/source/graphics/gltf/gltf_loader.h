#ifndef GLTF_LOADER
#define GLTF_LOADER

#include "gltf_file.h"

class gltf_loader
{
public:

	static sptr<gltf_file> load(const std::string& path)
	{
		return nullptr;
	}

	static std::vector<sptr<gltf_file>> load(const std::vector<std::string>& path)
	{
		std::vector<sptr<gltf_file>> _files;
		return _files;
	}

};

#endif