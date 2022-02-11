#include "world.h"
#include "framework/avatars/avatar.h"

void world::initialize()
{
	std::shared_ptr<avatar> s;
	std::weak_ptr<avatar> ws(s);
}

void world::tick(float delta_time)
{
	for (auto _avatar : _avatars)
	{
		if (_avatar) _avatar->heartbeat(delta_time);
	}
}
