#include "world.h"
#include "framework/avatars/avatar.h"
#include "framework/prostheses/prosthesis.h"

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

	return nullptr;
}

avatar* world::invoke_avatar(uint64 index) const noexcept
{
	return nullptr;
}

void world::invoke_avatars_all(std::vector<avatar*>& out_avatars) noexcept
{
}

void world::destroy(const std::string& name) noexcept
{
}

void world::destroy(avatar* invoked_avatar) noexcept
{
}

void world::destroy_all(const std::vector<avatar*>& invoked_avatars) noexcept
{
}

void world::fetch_avatar_names(std::vector<std::string>& out_avatar_names) const noexcept
{
	out_avatar_names.reserve(_name_to_avatar_map.size());

	for (const auto& _name_to_avatar : _name_to_avatar_map)
	{
		out_avatar_names.push_back(_name_to_avatar.first);
	}
}
