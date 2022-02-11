#ifndef WORLD_H
#define WORLD_H

#include "public/stl.h"

class avatar;

class world
{

private:

	std::vector<avatar*> _avatars;

public:

	void initialize();

	void tick(float delta_time);

public:

	template<class avatar_t>
	avatar_t* spawn(const std::string& name) noexcept
	{
		auto _avatar = new avatar_t();
		if(_avatar) _avatars.push_back(_avatar);
		return _avatar;
	}

};

#endif