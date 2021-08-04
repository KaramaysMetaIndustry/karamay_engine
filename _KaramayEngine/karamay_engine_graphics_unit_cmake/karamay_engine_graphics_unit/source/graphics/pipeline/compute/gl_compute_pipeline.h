#pragma once
#include "graphics/pipeline/base/gl_pipeline_base.h"

struct gl_compute_pipeline_descriptor
{
	std::shared_ptr<gl_shader> compute_shader;
};

class gl_compute_pipeline final : public gl_pipeline_base
{
private:

	gl_compute_pipeline() = default;

public:

	explicit gl_compute_pipeline(const gl_compute_pipeline_descriptor& descriptor) :
		_descriptor(descriptor)
	{}

	~gl_compute_pipeline() = default;

private:

	const gl_compute_pipeline_descriptor _descriptor;

public:

	/*
	* Buffered Interface Block, which shaders can only read
	* layout(binding = 0) uniform MyUniformBlock
	* {
	*		....
	* }
	*
	*/
	void add_uniform_blocks();

	/*
	* Bufferred Inteface Block, which shaders can read and write
	* layout(binding = 0) buffer MyShaderStorageBlock
	* {
	*		...
	* }
	* 
	*/
	void add_shader_storage_blocks();

public:

	void install();

public:

	/*
	* Dispatch the compute pipeline
	* 
	*/
	void dispatch(std::uint32_t group_size_x, std::uint32_t group_size_y, std::uint32_t group_size_z)
	{
		glDispatchCompute(group_size_x, group_size_y, group_size_z);
	}

};

