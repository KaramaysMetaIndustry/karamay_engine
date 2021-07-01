#ifndef H_GL_VARIABLE
#define H_GL_VARIABLE

#include "public/_glew.h"
#include "public/stl.h"
#include "graphics/variable/glu_types.h"


class gl_variable final
{
public:

	gl_variable(const std::string& type, const std::string& name, const std::vector<std::uint8_t>& stream) :
		_type(type),
		_name(name),
		_size(10),
		_stream(stream)
	{

	}


	gl_variable(const std::string& type, const std::string& name, const std::size_t size) :
		_type(type),
		_name(name),
		_size(_get_type_size(type))
	{}
	
private:

	const std::string _type;

	const std::string _name;

	const std::size_t _size;

	std::vector<std::uint8_t> _stream;

public:

	const std::string& get_type() const { return _type; }

	const std::string& get_name() const { return _name; }

	const std::vector<std::uint8_t>& get_value() const { return _stream; }

	void set_value(const std::vector<std::uint8_t>& stream) 
	{ 
		if (stream.size() != _size) throw std::exception("stream size is not legal");

		_stream = stream;
	}

private:

	std::size_t _get_type_size(const std::string& type)
	{
		if (type == "int") return sizeof glm::ivec1;
		if (type == "ivec2") return sizeof glm::ivec2;
		if (type == "ivec3") return sizeof glm::ivec3;
		if (type == "ivec4") return sizeof glm::ivec4;

		if (type == "uint") return sizeof glm::uvec1;
		if (type == "uvec2") return sizeof glm::uvec2;
		if (type == "uvec3") return sizeof glm::uvec3;
		if (type == "uvec4") return sizeof glm::uvec4;

		if (type == "float") return sizeof glm::vec1;
		if (type == "vec2") return sizeof glm::vec2;
		if (type == "vec3") return sizeof glm::vec3;
		if (type == "vec4") return sizeof glm::vec4;
		
		if (type == "mat2") return sizeof glm::mat2;
		if (type == "mat3") return sizeof glm::mat3;
		if (type == "mat4") return sizeof glm::mat4;
		if (type == "mat2x3") return sizeof glm::mat2x3;
		if (type == "mat2x4") return sizeof glm::mat2x4;
		if (type == "mat3x2") return sizeof glm::mat3x2;
		if (type == "mat3x4") return sizeof glm::mat3x4;
		if (type == "mat4x2") return sizeof glm::mat4x2;
		if (type == "mat4x3") return sizeof glm::mat4x3;

		if (type == "double") return sizeof glm::dvec1;
		if (type == "dvec2") return sizeof glm::vec2;
		if (type == "dvec3") return sizeof glm::vec3;
		if (type == "dvec4") return sizeof glm::vec4;

		if (type == "dmat2") return sizeof glm::dmat2;
		if (type == "dmat3") return sizeof glm::dmat3;
		if (type == "dmat4") return sizeof glm::dmat4;
		if (type == "dmat2x3") return sizeof glm::dmat2x3;
		if (type == "dmat2x4") return sizeof glm::dmat2x4;
		if (type == "dmat3x2") return sizeof glm::dmat3x2;
		if (type == "dmat3x4") return sizeof glm::dmat3x4;
		if (type == "dmat4x2") return sizeof glm::dmat4x2;
		if (type == "dmat4x3") return sizeof glm::dmat4x3;
	}

public:

	~gl_variable() {}

};

#endif







