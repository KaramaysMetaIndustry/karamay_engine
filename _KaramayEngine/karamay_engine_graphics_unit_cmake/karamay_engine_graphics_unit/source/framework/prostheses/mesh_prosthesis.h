#ifndef MESH_PROSTHESIS_H
#define MESH_PROSTHESIS_H
#include "entity_prosthesis.h"

class mesh_prosthesis : public entity_prosthesis
{
public:

	mesh_prosthesis(avatar* owner, const std::string_view& name) : entity_prosthesis(owner, name) {}
	mesh_prosthesis(const mesh_prosthesis&) = delete;
	mesh_prosthesis& operator=(const mesh_prosthesis&) = delete;

	virtual ~mesh_prosthesis() = default;

public:


};


#endif