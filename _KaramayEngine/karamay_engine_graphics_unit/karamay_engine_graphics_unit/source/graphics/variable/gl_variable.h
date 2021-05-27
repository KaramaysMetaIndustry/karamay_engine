#pragma once

#include "public/opengl.h"
#include "public/stl.h"

template<typename T>
class gl_variable
{

public:
	std::string name;

	T value;

public:

	gl_variable()
	{

	}

	gl_variable(const std::string& name, const T& value)
	{
		this->name = name;
		this->value = value;
	}
};




