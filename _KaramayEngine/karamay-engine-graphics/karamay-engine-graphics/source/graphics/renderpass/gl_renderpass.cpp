#include "gl_renderpass.h"

void gl_renderpass::add_sub_renderpass(std::shared_ptr<gl_sub_renderpass> sub_renderpass)
{
	sub_renderpasses.push_back(sub_renderpass);
}

gl_renderpass::gl_renderpass()
{
}

gl_renderpass::~gl_renderpass()
{
}
