#include "world.h"
#include "framework/avatars/avatar.h"

void world::initialize()
{
}

void world::tick(float delta_time)
{
	std::cout << "world tick" << std::endl;
	for (const auto& _avatar : _avatars)
	{
		if (_avatar) _avatar->heartbeat(delta_time);
	}
}

avatar* world::invoke_avatar(const std::string& name) const noexcept

{
	auto _it = _name_to_avatar_map.find(name);
	if (_it == _name_to_avatar_map.cend())
	{
		return nullptr;
	}
	return _it->second;
}
