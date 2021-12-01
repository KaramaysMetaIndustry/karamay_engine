#include "gl_renderer.h"

class gl_renderer_dispatcher final
{
public:
	
	gl_renderer_dispatcher() = default;

	~gl_renderer_dispatcher() = default;

public:

	std::vector<std::shared_ptr<gl_renderer>> renderers;


};