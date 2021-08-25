#include "gl_shader.h"


struct gl_compute_shader_descriptor
{
	std::vector<std::shared_ptr<glsl_uniform_block_t>> referenced_uniform_blocks;
	std::vector<std::shared_ptr<glsl_shader_storage_block_t>> referenced_shader_storage_blocks;
	std::vector<std::shared_ptr<glsl_image_t>> referenced_images;
	std::vector<std::shared_ptr<glsl_sampler_t>> referenced_samplers;
	std::vector<std::shared_ptr<glsl_atomic_uint>> referenced_atomic_uints;
};

class gl_compute_shader : public gl_shader
{
public:
	
	gl_compute_shader() = delete;

	explicit gl_compute_shader(const gl_compute_shader_descriptor& descriptor) :
		descriptor(descriptor)
	{

	}

	gl_compute_shader(const gl_compute_shader&) = default;
	gl_compute_shader& operator=(const gl_compute_shader&) = default;
	~gl_compute_shader() override = default;

private:

	gl_compute_shader_descriptor descriptor;

public:

	const std::string& get_shader_glsl_template() const override
	{

	}

public:
	
	void load_source(const std::string& glsl_file_path)
	{

	}

};