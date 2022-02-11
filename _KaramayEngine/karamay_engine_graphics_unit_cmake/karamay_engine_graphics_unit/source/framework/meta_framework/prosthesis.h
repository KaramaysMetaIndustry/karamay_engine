#ifndef PROSTHESIS_H
#define PROSTHESIS_H

class prosthesis
{
public:

	virtual void wake();

	virtual void drive(float delta_time);

	virtual void hibernate();

public:



};

#endif