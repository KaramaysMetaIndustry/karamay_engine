#pragma once
#include "graphics/glo/gl_object.h"

namespace gl_renderbuffer_enum
{
	enum class internal_format : GLenum
	{

	};

};


class gl_renderbuffer final : public gl_object
{
public:
	std::shared_ptr<gl_renderbuffer> construct()
	{
		return std::make_shared<gl_renderbuffer>();
	}

	~gl_renderbuffer();

private:
	gl_renderbuffer();

public:
	void allocate(gl_renderbuffer_enum::internal_format internal_format, unsigned int width, unsigned int height)
	{
		if (width > GL_MAX_RENDERBUFFER_SIZE | height > GL_MAX_RENDERBUFFER_SIZE) return;
		glNamedRenderbufferStorage(_handle, static_cast<GLenum>(internal_format), static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	}

public:
	void bind();

	void unbind();



};

