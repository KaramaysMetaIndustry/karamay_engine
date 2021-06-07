#pragma once

#include "public/opengl.h"
#include "public/stl.h"
#include "graphics/variable/glu_types.h"

template<typename T>
class gl_variable final
{
public:

	gl_variable() :
		_name(),
		_value()
	{}

	gl_variable(const std::string& name, const T& value) :
		_name(name),
		_value(value)
	{}

	~gl_variable() {}

private:

	std::string _name;

	T _value;

public:

	inline const std::string& get_name() const { return _name; }

	inline const T& get_value() const { return _value; }

	inline const char* get_name_c_str() const { return _name.c_str(); }

	inline void set_name(const std::string& name) { _name = name; }

	inline void set_value(const T& value) { _value = value; }

	inline std::size_t get_size() const { return sizeof(T); }

};







