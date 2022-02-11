#include "avatar.h"
#include "prosthesis.h"

void avatar::wake()
{
    for (auto _prosthesis : _prosthesises)
    {
        if (_prosthesis) _prosthesis->wake();
    }
}

void avatar::heartbeat(float delta_time)
{
    for (auto _prosthesis : _prosthesises)
    {
        if (_prosthesis) _prosthesis->drive(delta_time);
    }
}

void avatar::hibernate()
{
    for (auto _prosthesis : _prosthesises)
    {
        if (_prosthesis) _prosthesis->hibernate();
    }
}

bool avatar::attach_prothesis(prosthesis* component)
{
    if (!component) return false;
    component->wake();
    _prosthesises.push_back(component);
    return true;
}
