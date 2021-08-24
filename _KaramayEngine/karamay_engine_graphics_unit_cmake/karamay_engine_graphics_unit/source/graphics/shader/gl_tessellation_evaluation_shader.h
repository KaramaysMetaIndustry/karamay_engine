#include "gl_shader.h"
#include "graphics/type/glsl_class/glsl_class.h"


struct gl_tessellation_evaluation_shader_parameters
{

};

class gl_tessellation_evaluation_shader : public gl_shader
{
public:
	gl_tessellation_evaluation_shader() = delete;
	gl_tessellation_evaluation_shader(const gl_tessellation_evaluation_shader_parameters& parameters) :
		parameters(parameters)
	{}

	~gl_tessellation_evaluation_shader() = default;

public:
	const gl_tessellation_evaluation_shader_parameters parameters;


public:

};