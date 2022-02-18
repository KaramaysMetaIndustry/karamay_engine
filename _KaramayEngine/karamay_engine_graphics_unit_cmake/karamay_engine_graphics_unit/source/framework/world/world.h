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

	std::unordered_map<std::string, std::unique_ptr<avatar>> _name_to_avatar_map = {};

	std::vector<avatar*> _avatars = {};

public:

	template<class avatar_t>
	avatar_t* create(const std::string& name) noexcept
	{
		if (_name_to_avatar_map.find(name) != _name_to_avatar_map.cend())
			return nullptr;

		auto _avatar = std::make_unique<avatar_t>(this, name);
		auto _raw_avatar = _avatar.get();
		_name_to_avatar_map.emplace(name, std::move(_avatar));
		_avatars.push_back(_raw_avatar);
		return _raw_avatar;
	}

	avatar* invoke_avatar(const std::string& name) const noexcept;

	avatar* invoke_avatar(uint64 index) const noexcept;
	
	void invoke_avatars_all(std::vector<avatar*>& out_avatars) noexcept;


	void destroy(const std::string& name) noexcept;

	void destroy(avatar* invoked_avatar) noexcept;

	void destroy_all(const std::vector<avatar*>& invoked_avatars) noexcept;


	void fetch_avatar_names(std::vector<std::string>& out_avatar_names) const noexcept;

	uint64 num_of_avatars() const { return _avatars.size(); }

};

#endif