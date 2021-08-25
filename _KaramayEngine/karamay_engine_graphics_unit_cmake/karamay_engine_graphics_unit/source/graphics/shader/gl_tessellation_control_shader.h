#include "gl_shader.h"
#include "graphics/type/glsl_class.h"

struct gl_tessellation_control_shader_descriptor
{
	std::shared_ptr<glsl_tesc_shader_in_block_t> input;
	std::vector<std::shared_ptr<glsl_image_t>> images;
	std::vector<std::shared_ptr<glsl_sampler_t>> samplers;
	std::vector<std::shared_ptr<glsl_atomic_uint>> atomic_counters;
	std::vector<std::shared_ptr<glsl_uniform_block_t>> uniform_blocks;
	std::vector<std::shared_ptr<glsl_shader_storage_block_t>> shader_storage_blocks;
	std::shared_ptr<glsl_tesc_shader_out_block_t> output;
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