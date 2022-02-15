#ifndef MESH_PROSTHESIS_H
#define MESH_PROSTHESIS_H
#include "entity_prosthesis.h"

class material
{

};

class mesh
{

};

class static_mesh : public mesh
{

};

class dynamic_mesh : public mesh
{

};

class mesh_prosthesis : public entity_prosthesis
{
public:
	mesh_prosthesis() = delete;
	mesh_prosthesis(avatar* owner, const std::string_view& name);
	mesh_prosthesis(const mesh_prosthesis&) = delete;
	mesh_prosthesis& operator=(const mesh_prosthesis&) = delete;

	virtual ~mesh_prosthesis() = default;

private:

	std::unique_ptr<mesh> _mesh = {};

public:

	mesh* invoke_mesh() const noexcept { return _mesh.get(); }

};


#endif