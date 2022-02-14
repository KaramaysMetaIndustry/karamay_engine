#include "prosthesis.h"

prosthesis::prosthesis(avatar* owner, const std::string_view& name) :
	_owner(owner), _name(name)
{
}

void prosthesis::wake()
{
	if (_is_awake)
	{
		return;
	}

	_is_awake = true;
}

void prosthesis::drive(float delta_time)
{


}

void prosthesis::hibernate()
{
	if (!_is_awake)
	{
		return;
	}

	_is_awake = false;
}
