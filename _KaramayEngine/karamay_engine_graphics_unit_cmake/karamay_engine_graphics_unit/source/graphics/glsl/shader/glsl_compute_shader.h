#ifndef GLSL_COMPUTE_SHADER_H
#define GLSL_COMPUTE_SHADER_H
#include "glsl_shader.h"

class glsl_compute_shader : public glsl_shader
{
public:
	glsl_compute_shader() = default;

	glsl_compute_shader(const glsl_compute_shader&) = delete;
	glsl_compute_shader& operator=(const glsl_compute_shader&) = delete;

	~glsl_compute_shader() = default;

public:

	bool generate_template(const std::string& path) override
	{
		for (auto _ub_ref : _uniform_block_refs)
		{

		}

		for (auto _ssb_ref : _shader_storage_block_refs)
		{

		}

		for (auto _ac_ref : _atomic_counter_refs)
		{

		}

		return true;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::COMPUTE_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("\\") + 1) + ".comp");
		return false;
	}

};

class glsl_compute_shader_template_parameters final
{

};

class glsl_compute_shader_template final : public glsl_compute_shader
{
public:
	glsl_compute_shader* generate_instance(glsl_compute_shader_template_parameters* parameters) noexcept
	{
		return nullptr;
	}
};

#endif