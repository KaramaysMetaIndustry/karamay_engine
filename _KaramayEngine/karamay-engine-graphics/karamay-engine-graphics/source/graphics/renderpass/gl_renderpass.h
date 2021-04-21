#pragma once
#include "public/stl.h"
#include "gl_sub_renderpass.h"

class gl_renderpass final
{

public:
	void add_sub_renderpass(std::shared_ptr<gl_sub_renderpass> sub_renderpass);

private:
	std::vector<std::shared_ptr<gl_sub_renderpass>> sub_renderpasses;


public:
	gl_renderpass();

	virtual ~gl_renderpass();
};

