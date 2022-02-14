#include "prosthesis.h"

prosthesis::prosthesis(avatar* owner) :
	_owner(owner)
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
