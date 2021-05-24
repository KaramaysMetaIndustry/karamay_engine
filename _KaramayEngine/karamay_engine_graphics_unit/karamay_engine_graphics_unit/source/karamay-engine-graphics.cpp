#include "window/window.h"


int main()
{
  
	glfw_window* window = new glfw_window();
	window->load_context();

	while (true)
	{
		window->tick(1.0f);
	}

}
