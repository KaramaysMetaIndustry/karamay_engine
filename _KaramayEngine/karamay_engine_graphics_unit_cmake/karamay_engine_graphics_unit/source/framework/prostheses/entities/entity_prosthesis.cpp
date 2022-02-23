#include "entity_prosthesis.h"

entity_prosthesis::entity_prosthesis(avatar* owner, const std::string_view& name) :
	prosthesis(owner, name)
{
}

void entity_prosthesis::collect(entity_prosthesis* entity) noexcept
{
	_invoked_children.push_back(entity);
}

void entity_prosthesis::collect(const std::vector<entity_prosthesis*>& entities) noexcept
{
	_invoked_children.reserve(entities.size());
	_invoked_children.insert(_invoked_children.cend(), entities.cbegin(), entities.cend());
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
	out.reserve(_invoked_children.size());
	out.insert(out.cend(), _invoked_children.cbegin(), _invoked_children.cend());
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
