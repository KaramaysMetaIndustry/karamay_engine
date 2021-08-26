#include "gl_shader.h"


struct gl_compute_shader_descriptor
{
	std::shared_ptr<gl_shader_parameters> parameters;
};

class gl_compute_shader : public gl_shader
{
public:
	
	gl_compute_shader() = delete;
	gl_compute_shader(const gl_compute_shader_descriptor& descriptor) :
		descriptor(descriptor)
	{}

	gl_compute_shader(const gl_compute_shader&) = default;
	gl_compute_shader& operator=(const gl_compute_shader&) = default;

	~gl_compute_shader() override = default;

private:

	gl_compute_shader_descriptor descriptor;

public:

	const std::string& get_shader_glsl_template() const override
	{}

public:
	
	void load_source(const std::string& glsl_file_path)
	{}

};