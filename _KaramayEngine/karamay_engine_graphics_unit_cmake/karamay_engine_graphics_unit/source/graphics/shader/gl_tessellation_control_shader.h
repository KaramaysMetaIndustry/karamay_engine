#include "gl_shader.h"
#include "graphics/glsl/glsl_class.h"

struct gl_tessellation_control_shader_descriptor
{
	std::shared_ptr<gl_shader_parameters> parameters;
};

class gl_tessellation_control_shader : public gl_shader
{
public:
	gl_tessellation_control_shader() = delete;
	gl_tessellation_control_shader(const gl_tessellation_control_shader_descriptor& descriptor) :
		descriptor(descriptor)
	{}

public:

	const gl_tessellation_control_shader_descriptor descriptor;

	const std::string& get_shader_glsl_template() const override
	{
		return "";
	}

};