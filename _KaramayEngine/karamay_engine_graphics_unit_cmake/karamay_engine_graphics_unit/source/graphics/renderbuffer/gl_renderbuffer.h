#ifndef H_GL_RENDERBUFFER
#define H_GL_RENDERBUFFER

#include "graphics/glo/gl_object.h"

namespace gl_renderbuffer_enum
{
	enum class internal_format : GLenum
	{
		NONE
	};

};


class gl_renderbuffer final : public gl_object
{
public:

	gl_renderbuffer() :
		_width(0), _height(0),
		_internal_format(gl_renderbuffer_enum::internal_format::NONE)
	{
		glCreateRenderbuffers(1, &_handle);
	}

	virtual ~gl_renderbuffer();

private:
	
	std::uint32_t _width, _height;

	gl_renderbuffer_enum::internal_format _internal_format;

public:

	void allocate(gl_renderbuffer_enum::internal_format internal_format, std::uint32_t width, std::uint32_t height);

	void bind();

	void unbind();

};

#endif

