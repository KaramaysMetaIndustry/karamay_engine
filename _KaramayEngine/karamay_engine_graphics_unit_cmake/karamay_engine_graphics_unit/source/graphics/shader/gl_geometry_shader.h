#include "gl_shader.h"


struct gl_geometry_shader_descriptor
{
	std::shared_ptr<gl_shader_parameters> parameters;
};

class gl_geometry_shader : public gl_shader
{
public:
	gl_geometry_shader() = delete;
	gl_geometry_shader(const gl_geometry_shader_descriptor& descriptor)
	{

	}

};