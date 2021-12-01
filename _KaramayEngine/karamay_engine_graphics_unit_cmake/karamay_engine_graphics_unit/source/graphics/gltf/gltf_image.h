#ifndef GLTF_IMAGE_H
#define GLTF_IMAGE_H

#include "public/nlohmann_json.h"

class gltf_image
{
public:

	gltf_image(const nlohmann::json& object)
	{
		if (object.find("uri") != object.cend()) object.at("uri").get_to(_uri);
	}

private:

	std::string _uri;

};

#endif