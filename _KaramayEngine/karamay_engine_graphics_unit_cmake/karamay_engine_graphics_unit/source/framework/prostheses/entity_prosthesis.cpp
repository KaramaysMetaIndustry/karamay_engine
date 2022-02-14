#include "entity_prosthesis.h"

entity_prosthesis::entity_prosthesis(avatar* owner, const std::string_view& name) :
	prosthesis(owner, name)
{
}

void entity_prosthesis::collect(entity_prosthesis* entity) noexcept
{
	_children.push_back(entity);
}

void entity_prosthesis::collect(const std::vector<entity_prosthesis*>& entities) noexcept
{
	_children.reserve(entities.size());
	_children.insert(_children.cend(), entities.cbegin(), entities.cend());
}

void entity_prosthesis::attach_to(entity_prosthesis* parent_entity) noexcept
{
}

void entity_prosthesis::release(entity_prosthesis* entity) noexcept
{
}

void entity_prosthesis::release(const std::vector<entity_prosthesis*>& entities) noexcept
{
}

void entity_prosthesis::fetch_children_all(std::vector<entity_prosthesis*>& out) const noexcept
{
	out.reserve(_children.size());
	out.insert(out.cend(), _children.cbegin(), _children.cend());
}

void entity_prosthesis::wake()
{
}

void entity_prosthesis::drive(float delta_time)
{
}

void entity_prosthesis::hibernate()
{
}
