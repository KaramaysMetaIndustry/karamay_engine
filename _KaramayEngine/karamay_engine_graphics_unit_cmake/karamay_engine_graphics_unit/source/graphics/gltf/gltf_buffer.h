#ifndef GLTF_BUFFER_H
#define GLTF_BUFFER_H

#include "public/nlohmann_json.h"

class gltf_buffer
{
public:

	gltf_buffer(const nlohmann::json& object)
	{
		object.at("byteLength").get_to(_byte_length);
		object.at("uri").get_to(_uri);
	}


private:

	std::uint32_t _byte_length;
	std::string _uri;

};

#endif