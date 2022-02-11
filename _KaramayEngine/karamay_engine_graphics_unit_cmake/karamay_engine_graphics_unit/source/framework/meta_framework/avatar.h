#ifndef AVATAR_H
#define AVATAR_H
#include "public/stl.h"

class prosthesis;

class avatar
{
public:

	virtual void wake();

	virtual void heartbeat(float delta_time);

	virtual void hibernate();

public:

	bool attach_prothesis(prosthesis* component);

protected:

	std::vector<prosthesis*> _prosthesises;

};

#endif