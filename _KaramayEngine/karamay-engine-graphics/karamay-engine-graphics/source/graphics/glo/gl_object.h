#pragma once
#include "public/opengl.h"
#include "public/stl.h"

class gl_object
{
public:
	gl_object();

	virtual ~gl_object();

public:
	unsigned int get_handle() const;


protected:
	unsigned int _handle;

};

