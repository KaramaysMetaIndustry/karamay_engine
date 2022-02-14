#ifndef PROSTHESIS_H
#define PROSTHESIS_H

#include "public/stl.h"

class avatar;

class prosthesis
{
public:

	prosthesis(avatar* owner);
	
	virtual ~prosthesis() = default;

private:

	avatar* _owner = nullptr;

	prosthesis* _parent = nullptr;

	std::vector<prosthesis*> _children = {};

	bool _is_awake = false;

public:

	virtual void wake();

	virtual void drive(float delta_time);

	virtual void hibernate();

public:


};


#endif