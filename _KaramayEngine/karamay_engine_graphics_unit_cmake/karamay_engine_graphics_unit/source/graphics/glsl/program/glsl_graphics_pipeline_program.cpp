#include "glsl_graphics_pipeline_program.h"

bool glsl_graphics_pipeline_program::load(const std::string& pipeline_dir)
{
	// load rpc file
	// generate shader code source and compile
	// generate the middle info for program dynamic updating

	for (auto _shader : _shaders)
	{
		_shader->load(pipeline_dir);
	}

	return false;
}

