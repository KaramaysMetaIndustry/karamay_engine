#include "avatar.h"
#include "renderer_framework/std_scene_framework/std_scene_framework.h"
#include "framework/prostheses/prosthesis.h"

void avatar::wake() noexcept
{
    for (auto _prosthesis : _prostheses)
    {
        if (_prosthesis) _prosthesis->wake();
    }
}

void avatar::heartbeat(float delta_time) noexcept
{
    for (auto _prosthesis : _prostheses)
    {
        if (_prosthesis) _prosthesis->drive(delta_time);
    }
}

void avatar::hibernate() noexcept
{
    for (auto _prosthesis : _prostheses)
    {
        if (_prosthesis) _prosthesis->hibernate();
    }
}

bool avatar::is_awake() const noexcept
{
    return false;
}

bool avatar::attach(prosthesis* component) noexcept
{
    if (!component) return false;
    component->wake();
    _prostheses.push_back(component);
    return true;
}

bool avatar::detach(prosthesis* pro) noexcept
{
    return false;
}

bool avatar::detach(const std::string& name) noexcept
{
    return false;
}

prosthesis* avatar::get_prothesis() noexcept
{
    return nullptr;
}

void avatar::_register_entity_prostheses()
{
}

void avatar::_unregister_entity_prostheses()
{
}


