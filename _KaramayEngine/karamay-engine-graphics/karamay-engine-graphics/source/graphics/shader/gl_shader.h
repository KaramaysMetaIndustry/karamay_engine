#pragma once
#include "graphics/glo/gl_object.h"

namespace gl_shader_enum
{
	enum class type : GLenum
	{

	};
}

class gl_shader final : public gl_object
{
public:

	gl_shader();
	
	virtual ~gl_shader();

public:

	void load(const std::string& path)
	{
		auto suffix = path.substr(path.find_last_of('.'));
		GLenum type;
		if (suffix == ".vert")
		{
			type = GL_VERTEX_SHADER;
		}
		if (suffix == ".tesc")
		{
			type = GL_TESS_CONTROL_SHADER;
		}
		if (suffix == ".tese")
		{
			
			type = GL_TESS_EVALUATION_SHADER;
		}
		if (suffix == ".geom")
		{
			type = GL_GEOMETRY_SHADER;
		}
		if (suffix == ".frag")
		{
			type = GL_FRAGMENT_SHADER;
		}
		if (suffix == ".comp")
		{
			type = GL_COMPUTE_SHADER;
		}



		// load bytes - FilePath
		std::ifstream file;
		std::string content;
		file.exceptions(std::fstream::failbit | std::fstream::badbit);
		try {
			file.open(path);
			std::stringstream sstream;
			sstream << file.rdbuf();
			file.close();
			content = sstream.str();
		}
		catch (const std::exception& e) {
			std::cout << "Exception: [ " << e.what() << " ]" << std::endl;
		}
		auto source = content.c_str();

		
		_handle = glCreateShader(type);
		glShaderSource(_handle, 1, &source, NULL);
		
	}

	void compile()
	{
		glCompileShader(_handle);

		GLint result;
		char info[512];
		glGetShaderiv(_handle, GL_COMPILE_STATUS, &result);
		if (result != GL_TRUE) {
			glGetShaderInfoLog(_handle, 512, NULL, info);
			std::cout << "shader compile fail : " << info << std::endl;
		}
	}
};

