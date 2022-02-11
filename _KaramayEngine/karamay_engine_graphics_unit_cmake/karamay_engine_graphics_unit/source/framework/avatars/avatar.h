#ifndef AVATAR_H
#define AVATAR_H
#include "public/stl.h"

class world;
class prosthesis;

class avatar
{
public:

	std::weak_ptr<world> owner;

public:

	/*
	* wake the avatar
	* when the avatar first be loaded into the world, would be called.
	*/
	virtual void wake() noexcept;

	/*
	* heartbeat the avatar
	*/
	virtual void heartbeat(float delta_time) noexcept;

	/*
	* hibernate the avatar
	*/
	virtual void hibernate() noexcept;

	/*
	* check whether the avatar is awake
	*/
	virtual bool is_awake() const noexcept;

public:

	bool attach(prosthesis* pro) noexcept;

	bool detach(prosthesis* pro) noexcept;

	bool detach(const std::string& name) noexcept;

	prosthesis* get_prothesis() noexcept;

protected:

	std::vector<prosthesis*> _prostheses;

protected:

	void _register_entity_prostheses();
	void _unregister_entity_prostheses();

};


#endif

