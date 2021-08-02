#pragma once

#include "graphics/program/gl_program.h"

struct gl_compute_pipeline_descriptor
{
	std::shared_ptr<gl_shader> compute_shader;

};

class gl_compute_pipeline final
{
public:

	gl_compute_pipeline(const gl_compute_pipeline_descriptor& descriptor) :
		_descriptor(descriptor)
	{
	}

	~gl_compute_pipeline() = default;

private:

	gl_compute_pipeline() = default;

	const gl_compute_pipeline_descriptor _descriptor;


	/*
	* Buffered Interface Block, which shaders can only read
	* layout(binding = 0) uniform MyUniformBlock
	* {
	*		....
	* }
	*
	*/
	void set_uniform_blocks();

	/*
	* Bufferred Inteface Block, which shaders can read and write
	* layout(binding = 0) buffer MyShaderStorageBlock
	* {
	*		...
	* }
	* 
	*/
	void set_shader_storage_blocks();


	/*
	* Dispatch the compute pipeline
	* 
	*/
	void dispatch(std::uint32_t group_size_x, std::uint32_t group_size_y, std::uint32_t group_size_z)
	{
		glDispatchCompute(group_size_x, group_size_y, group_size_z);
	}

};

