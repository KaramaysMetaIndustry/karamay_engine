#pragma once
#include "graphics/pipeline/base/gl_pipeline.h"
#include "graphics/shader/gl_compute_shader.h"
#include "graphics/glsl/glsl_class.h"

class gl_compute_pipeline_parameters
{

};

struct gl_compute_pipeline_descriptor
{
	struct gl_compute_shading
	{
		std::shared_ptr<gl_compute_shader> shader;
	} compute_shading;

	std::shared_ptr<gl_compute_pipeline_parameters> parameters;
};

class gl_compute_pipeline final : public gl_pipeline
{
public:

	explicit gl_compute_pipeline(const gl_compute_pipeline_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		_initialize_compute_pipeline();
	}
	
	gl_compute_pipeline(const gl_compute_pipeline&) = delete;
	gl_compute_pipeline& operator=(const gl_compute_pipeline&) = delete;
	~gl_compute_pipeline() = default;


public:

	bool ouput_pipeline_glsl_template(const std::string& renderer_dir) const override
	{
//		const gl_compute_shader* _compute_shader = _descriptor.compute_shading.shader.get();
//		if (_compute_shader)
//		{
//			const std::string& _template = _compute_shader->get_shader_glsl_template();
//			std::fstream _compute_shader_glsl_file(renderer_dir + _pipeline_name + "\\" + _pipeline_name + ".comp");
//			_compute_shader_glsl_file.write(_template.c_str(), _template.size());
//		}
		return false;
	}

private:

	const gl_compute_pipeline_descriptor _descriptor;

	void _initialize_compute_pipeline();

	inline void _install() {}

	inline void _uninstall() {}

public:
	/*
	* Dispatch compute shader
	*/
	inline void dispatch(std::uint32_t group_size_x, std::uint32_t group_size_y, std::uint32_t group_size_z)
	{
		_install();
		glDispatchCompute(group_size_x, group_size_y, group_size_z);
		_uninstall();
	}

};