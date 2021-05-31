#pragma once

#include "public/opengl.h"
#include "public/stl.h"

template<typename T>
class gl_variable
{

private:

	std::string _name;

	T _value;

public:

	gl_variable(const std::string& name, const T& value)
	{
		_name = name;
		_value = value;
	}

public:

	const std::string& get_name() const
	{
		return _name;
	}

	const T& get_value() const
	{
		return _value;
	}
};




