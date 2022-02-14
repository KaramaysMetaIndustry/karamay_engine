#include "entity_prosthesis.h"

entity_prosthesis::entity_prosthesis(avatar* owner) :
	prosthesis(owner)
{
}

void entity_prosthesis::collect(entity_prosthesis* entity) noexcept
{
	_children.push_back(entity);
}

void entity_prosthesis::attach_to(entity_prosthesis* parent_entity) noexcept
{
}

void entity_prosthesis::release(entity_prosthesis* entity) noexcept
{
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
