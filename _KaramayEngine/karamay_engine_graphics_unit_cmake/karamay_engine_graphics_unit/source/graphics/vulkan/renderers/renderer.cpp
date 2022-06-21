#include "renderer.h"

renderer::renderer(device& dev) : _device(dev)
{
}

renderer::~renderer()
{
}

bool renderer::allocate(device* dev) noexcept
{
	if (!_device.is_valid()) return false;
	
	//auto _buffer = _device.invoke<buffer>();

	return true;
}

void renderer::render(float delta_time) noexcept
{
}

void renderer::deallocate() noexcept
{
}
