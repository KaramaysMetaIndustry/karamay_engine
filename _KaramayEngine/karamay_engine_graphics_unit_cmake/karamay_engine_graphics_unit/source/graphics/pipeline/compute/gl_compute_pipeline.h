#pragma once
#include "graphics/pipeline/base/gl_pipeline.h"
#include "graphics/shader/gl_compute_shader.h"
#include "graphics/type/glsl_class.h"

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

	void register_parameters()
	{

	}

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


#define DEFINE_COMPUTE_PIPELINE_PARAMETERS_BEGIN(PIPELINE_NAME)\
struct gl_##PIPELINE_NAME##_graphics_pipeline_parameters\
{\
	class gl_##PIPELINE_NAME##_compute_shader_parameters : public gl_compute_shader_parameters\
	{\
	public:\

#define DEFINE_COMPUTE_PIPELINE_PARAMETERS_END(PIPELINE_NAME)\
	} compute_shader_parameters;\
};\
std::shared_ptr<class gl_##PIPELINE_NAME##_graphics_pipeline_parameters> _##PIPELINE_NAME##_parameters;\


class glsl_pp_uniform_block_t : public glsl_uniform_block_t
{
public:
	glsl_pp_uniform_block_t() = delete;
	glsl_pp_uniform_block_t(std::function<void(const glsl_uniform_block_t& uniform_block)> _register)
	{}

	const std::uint8_t* data() const override
	{
		return reinterpret_cast<const std::uint8_t*>(&memory);
	}

	std::int64_t size() const override
	{
		return sizeof(memory) * 10;
	}

	struct gl_struct
	{
		glsl_vec3 position0{ item_register };
		glsl_vec3 position1{ item_register };
		glsl_vec3 position2{ item_register };
	} memory[10];


} _ublock0{ uniform_block_register };