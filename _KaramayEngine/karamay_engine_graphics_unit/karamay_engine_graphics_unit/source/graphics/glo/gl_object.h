#pragma once
#include "public/opengl.h"
#include "public/stl.h"

namespace gl_object_enum
{
	enum class type
	{
		NONE,
		BUFFER_OBJ = GL_BUFFER,
		SHADER_OBJ = GL_SHADER,
		PROGRAM_OBJ = GL_PROGRAM,
		VERTEX_ARRAY_OBJ = GL_VERTEX_ARRAY,
		QUERY_OBJ = GL_QUERY,
		PROGRAM_PIPELINE_OBJ = GL_PROGRAM_PIPELINE,
		TRANSFORM_FEEDBACK_OBJ = GL_TRANSFORM_FEEDBACK,
		SAMPLER_OBJ = GL_SAMPLER,
		TEXTURE_OBJ = GL_TEXTURE,
		RENDERBUFFER_OBJ = GL_RENDERBUFFER,
		FRAMEBUFFER_OBJ = GL_FRAMEBUFFER
	};
}

class gl_object
{
protected:
	
	gl_object():
		_handle(0),
		_type(gl_object_enum::type::NONE)
	{}

	virtual ~gl_object() {}

protected:

	std::uint32_t _handle;

	gl_object_enum::type _type;

public:
	
	const std::uint32_t get_handle() const { return _handle; }

};

