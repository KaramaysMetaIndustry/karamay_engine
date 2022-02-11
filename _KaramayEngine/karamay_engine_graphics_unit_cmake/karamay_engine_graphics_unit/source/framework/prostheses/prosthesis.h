#ifndef PROSTHESIS_H
#define PROSTHESIS_H

#include "public/stl.h"

class avatar;

class prosthesis
{
public:

	prosthesis() = default;

	virtual ~prosthesis() = default;

public:

	std::weak_ptr<avatar> owner;

public:

	virtual void wake();

	virtual void drive(float delta_time);

	virtual void hibernate();

public:


};


#endif