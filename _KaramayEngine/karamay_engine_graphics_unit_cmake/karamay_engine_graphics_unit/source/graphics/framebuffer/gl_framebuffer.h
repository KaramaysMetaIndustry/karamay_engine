#ifndef H_GL_FRAMEBUFFER
#define H_GL_FRAMEBUFFER

#include "graphics/glo/gl_object.h"
#include "graphics/texture/gl_texture.h"
#include "graphics/renderbuffer/gl_renderbuffer.h"

class gl_framebuffer final : public gl_object
{
public:
	
	gl_framebuffer();

	virtual ~gl_framebuffer();

public:
	/**
	 * attachment_index [0, GL_MAX_COLOR_ATTACHMENTS - 1]
	 */

	
public:

	void attach_color_renderbuffer(std::uint32_t attachment_index, std::shared_ptr<gl_renderbuffer> renderbuffer)
	{
		if (renderbuffer && attachment_index <= GL_MAX_COLOR_ATTACHMENTS)
		{
			glNamedFramebufferRenderbuffer(_handle, GL_COLOR_ATTACHMENT0 + attachment_index, GL_RENDERBUFFER, renderbuffer->get_handle());
		}
		
	}
	void attach_depth_renderbuffer(std::shared_ptr<gl_renderbuffer> renderbuffer)
	{
		if (renderbuffer)
		{
			glNamedFramebufferRenderbuffer(_handle, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
		}
	}
	void attach_stencil_renderbuffer(std::shared_ptr<gl_renderbuffer> renderbuffer)
	{
		if (renderbuffer)
		{
			glNamedFramebufferRenderbuffer(_handle, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
		}
		
	}
	void attach_depth_stencil_renderbuffer(std::shared_ptr<gl_renderbuffer> renderbuffer)
	{
		if (renderbuffer)
		{
			glNamedFramebufferRenderbuffer(_handle, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
		}
	}

public:

	void set_drawable_color_components(std::vector<std::uint32_t> color_attachment_indices)
	{
		for (auto& elem : color_attachment_indices)
		{
			elem += GL_COLOR_ATTACHMENT0;
		}

		glDrawBuffers(static_cast<GLsizei>(color_attachment_indices.size()), color_attachment_indices.data());
	}

	void set_readable_color_component(std::uint32_t color_attachment_index) 
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0 + color_attachment_index);
	}

public:

	void read_color(int attachment_index, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
	void read_depth(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);
	void read_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);
	void read_depth_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);

	void draw_color(int attachment_index, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
	void draw_depth(GLsizei width, GLsizei height, GLenum type, const void* pixels);
	void draw_stencil(GLsizei width, GLsizei height, GLenum type, const void* pixels);
	void draw_depth_stencil(GLsizei width, GLsizei height, GLenum type, const void* pixels);

	void check_status()
	{
		glCheckFramebufferStatus(GL_FRAMEBUFFER);
	}

public:

	void bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _handle);
	}

	void unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

private:

	bool is_framebuffer() const
	{
		return glIsFramebuffer(_handle) == GL_TRUE ? true : false;
	}


};

#endif