#include "avatar.h"
#include "framework/prostheses/singularity_prosthesis.h"
#include "framework/prostheses/entity_prosthesis.h"
#include "framework/prostheses/mesh_prosthesis.h"
#include "renderer_framework/std_scene_framework/std_scene_framework.h"
#include "framework/world/world.h"

avatar::avatar(world* owner, const std::string_view& name) :
    _owner(owner), _name(name)
{
}

prosthesis* avatar::invoke(const std::string_view& name) const noexcept
{
    auto _it = _name_to_prosthesis_map.find(name);
    if (_it == _name_to_prosthesis_map.cend())
    {
        return nullptr;
    }
    return _it->second.get();
}

void avatar::invoke_all(std::vector<prosthesis*>& out) const noexcept
{
    out.reserve(_singularities.size() + _entities.size());

    for (auto _singularity : _singularities)
    {
        auto _prosthesis = dynamic_cast<prosthesis*>(_singularity);
        if (_prosthesis)
        {
            out.push_back(_prosthesis);
        }
    }

    for (auto _entity : _entities)
    {
        auto _prosthesis = dynamic_cast<prosthesis*>(_entity);
        if (_prosthesis)
        {
            out.push_back(_prosthesis);
        }
    }

}

singularity_prosthesis* avatar::invoke_singularity(uint64 index) const noexcept
{
    if(index >= _singularities.size())
        return nullptr;
    return _singularities[index];
}

void avatar::invoke_singularities_all(std::vector<singularity_prosthesis*>& out_singularities) const noexcept
{
    out_singularities.reserve(_singularities.size());
    out_singularities.insert(out_singularities.cend(), _singularities.cbegin(), _singularities.cend());
}

entity_prosthesis* avatar::invoke_entity(uint64 index) const noexcept
{
    if(index >= _entities.size())
        return nullptr;
    return _entities[index];
}

entity_prosthesis* avatar::invoke_entity_root() const noexcept
{
    return _entity_root;
}

void avatar::displace_entity_root(entity_prosthesis* insurgent, entity_prosthesis* old_root_recipient) noexcept
{
    if (!_entity_root || !insurgent) return;

}

void avatar::destroy(const std::string_view& prosthesis_name) noexcept
{
}

void avatar::destroy_entity(uint64 index) noexcept
{
}

void avatar::destroy_entity(entity_prosthesis* entity) noexcept
{
}

void avatar::destroy_singularity(uint64 index) noexcept
{
}

void avatar::destroy_singularity(singularity_prosthesis* singularity) noexcept
{
}

void avatar::invoke_entities_all(std::vector<entity_prosthesis*>& out_entities) const noexcept
{
    out_entities.reserve(_entities.size());
    out_entities.insert(out_entities.cend(), _entities.cbegin(), _entities.cend());
}

void avatar::wake() noexcept
{
    
}

void avatar::heartbeat(float delta_time) noexcept
{
    invoke_entity(1);
    
    
}

void avatar::hibernate() noexcept
{
    
}

bool avatar::is_awake() const noexcept
{
    return false;
}


