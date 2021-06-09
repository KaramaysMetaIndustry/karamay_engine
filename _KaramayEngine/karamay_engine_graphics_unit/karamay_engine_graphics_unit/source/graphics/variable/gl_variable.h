#pragma once

#include "public/opengl.h"
#include "public/stl.h"
#include "graphics/variable/glu_types.h"

class gl_variable final
{
public:

	gl_variable(const std::string& type, const std::string& name, const std::vector<std::uint8_t>& stream) :
		_type(type),
		_name(name),
		_stream(stream)
	{

	}
	
private:

	std::string _type;

	std::string _name;

	std::vector<std::uint8_t> _stream;

public:

	inline const std::string& get_type() const { return _type; }

	inline const std::string& get_name() const { return _name; }

	inline const std::vector<std::uint8_t>& get_value() const { return _stream; }

	inline void set_name(const std::string& name) { _name = name; }

	inline void set_value(const std::vector<std::uint8_t>& stream) { _stream = stream; }

public:

	~gl_variable() {}
};







