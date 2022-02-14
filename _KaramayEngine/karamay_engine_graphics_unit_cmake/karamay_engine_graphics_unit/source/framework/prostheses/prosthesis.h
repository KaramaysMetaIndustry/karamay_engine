#ifndef PROSTHESIS_H
#define PROSTHESIS_H

#include "public/stl.h"

class avatar;

class prosthesis
{
public:
	prosthesis() = delete;
	prosthesis(avatar* owner, const std::string_view& name);
	prosthesis(const prosthesis&) = delete;
	prosthesis& operator=(const prosthesis&) = delete;
	
	virtual ~prosthesis() = default;

private:

	avatar* _owner = nullptr;

	prosthesis* _parent = nullptr;

	std::string_view _name = {};

	std::vector<prosthesis*> _children = {};

	bool _is_awake = false;

public:

	virtual void wake();

	virtual void drive(float delta_time);

	virtual void hibernate();

};


#endif