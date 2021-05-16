#pragma once

#include "public/opengl.h"
#include "public/stl.h"

template<typename T>
class gl_uniform
{
private:
	std::string name;

	T value;

public:

	gl_uniform(const std::string& name, T value)
	{

	}
};




