#include "gl_renderer.h"

bool gl_renderer::_check_dir(const std::string& dir)
{
	if (std::filesystem::is_directory(dir))
	{

	}

	return false;
}

void gl_renderer::_initialize_renderer()
{
	static const std::string renderers_root_path = "/renderers/";
	bool validate = _check_dir(renderers_root_path + name);


}
