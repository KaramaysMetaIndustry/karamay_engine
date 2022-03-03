#include "render_pass.h"

render_pass::render_pass(device& dev) : device_object(dev)
{
}

render_pass::~render_pass()
{
    deallocate();
}

bool render_pass::allocate()
{
    return false;
}

void render_pass::deallocate()
{
}
