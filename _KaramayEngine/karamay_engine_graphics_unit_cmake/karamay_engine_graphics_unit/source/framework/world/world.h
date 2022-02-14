#ifndef WORLD_H
#define WORLD_H

#include "public/stl.h"

class avatar;

class world
{

public:

	void initialize();

	void tick(float delta_time);

private:

	std::vector<std::unique_ptr<avatar>> _avatars = {};

	std::unordered_map<std::string, avatar*> _name_to_avatar_map = {};

public:

	avatar* invoke_avatar(const std::string& name) const noexcept;

	template<class avatar_t>
	avatar_t* spawn(const std::string& name) noexcept
	{
		auto _avatar = std::make_unique<avatar_t>(this);
		auto _raw_avatar = _avatar.get();
		_avatars.push_back(std::move(_avatar));
		return _raw_avatar;
	}

	void remove(const std::string& name) noexcept
	{
		auto _it = _name_to_avatar_map.find(name);
		if (_it == _name_to_avatar_map.cend())
		{
			return;
		}

		auto _raw_avatar = _it->second;
		auto _num = _name_to_avatar_map.erase(name);
	}
};

#endif