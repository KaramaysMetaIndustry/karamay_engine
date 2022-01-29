#ifndef GLTF_LOADER_H
#define GLTF_LOADER_H

#include "components/gltf_file.h"

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