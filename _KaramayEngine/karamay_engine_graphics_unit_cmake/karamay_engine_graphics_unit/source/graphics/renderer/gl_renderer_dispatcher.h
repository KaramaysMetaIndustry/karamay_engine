#include "gl_renderer.h"

class gl_renderer_dispatcher final
{
public:
	
	gl_renderer_dispatcher() = default;

	~gl_renderer_dispatcher() = default;

public:

	std::vector<std::shared_ptr<gl_renderer>> renderers;

	void tick(std::float_t delta_time)
	{
		renderers[0]->render(delta_time);
	}

};