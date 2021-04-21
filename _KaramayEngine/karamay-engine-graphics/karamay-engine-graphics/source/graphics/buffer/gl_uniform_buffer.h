#pragma once
#include "graphics/glo/gl_object.h"

class gl_uniform_buffer final : public gl_object
{

public:
	void associate(GLuint program_handle, const char* uniform_block_name);

	

public:
	gl_uniform_buffer();

	virtual ~gl_uniform_buffer();
};

