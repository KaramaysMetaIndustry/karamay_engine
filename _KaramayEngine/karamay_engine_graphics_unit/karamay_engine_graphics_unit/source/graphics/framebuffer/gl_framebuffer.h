#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/texture/gl_texture.h"
#include "graphics/renderbuffer/gl_renderbuffer.h"

class gl_texture_1d;
class gl_texture_1d_array;
class gl_texture_2d;
class gl_texture_2d_multisample;

class gl_texture_2d_array;
class gl_texture_2d_array_multisample;
class gl_texture_3d;
class gl_texture_cube_map;
class gl_texture_cube_map_array;

class gl_renderbuffer;


class gl_framebuffer final : public gl_object
{
public:
	
	gl_framebuffer();

	virtual ~gl_framebuffer();

public:
	/**
	 * attachment_index [0, GL_MAX_COLOR_ATTACHMENTS - 1]
	 */
	void attach_color_texture_1d(std::uint32_t attachment_index, const std::shared_ptr<gl_texture_1d> texture_1d, std::uint32_t mipmap_index)
	{
		if (attachment_index < GL_MAX_COLOR_ATTACHMENTS && texture_1d)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment_index, GL_TEXTURE_1D, texture_1d->get_handle(), mipmap_index);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	void attach_depth_texture_1d(const std::shared_ptr<gl_texture_1d> texture_1d, std::uint32_t mipmap_index)
	{
		if (texture_1d)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture1D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_1D, texture_1d->get_handle(), mipmap_index);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	void attach_stencil_texture_1d(const std::shared_ptr<gl_texture_1d> texture_1d, std::uint32_t mipmap_index)
	{
		if (texture_1d)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture1D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_1D, texture_1d->get_handle(), mipmap_index);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	void attach_depth_stencil_texture_1d(const std::shared_ptr<gl_texture_1d> texture_1d, std::uint32_t mipmap_index)
	{
		if (texture_1d)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture1D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_1D, texture_1d->get_handle(), mipmap_index);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	//void attach_color_texture_1d_array() {}

	void attach_color_texture_2d(std::uint32_t attachment_index, const std::shared_ptr<gl_texture_2d> texture_2d, std::uint32_t mipmap_index)
	{
		if (attachment_index < GL_MAX_COLOR_ATTACHMENTS && texture_2d)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment_index, GL_TEXTURE_2D, texture_2d->get_handle(), mipmap_index);
			//glDrawBuffers()
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	void attach_depth_texture_2d(const std::shared_ptr<gl_texture_2d> texture_2d, std::uint32_t mipmap_index)
	{
		if (texture_2d)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_2d->get_handle(), mipmap_index);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	void attach_stencil_texture_2d(const std::shared_ptr<gl_texture_2d> texture_2d, std::uint32_t mipmap_index)
	{
		if (texture_2d)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture_2d->get_handle(), mipmap_index);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	void attach_depth_stencil_texture_2d(const std::shared_ptr<gl_texture_2d> texture_2d, std::uint32_t mipmap_index)
	{
		if (texture_2d)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture_2d->get_handle(), mipmap_index);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	auto get_color_texture_2d(std::uint32_t attachment_index)
	{
		return std::make_shared<gl_texture_2d>();
	}

	void attach_color_texture_2d_array() 
	{

	}

	void attach_color_texture_rectangle(std::uint32_t attachment_index, const std::shared_ptr<gl_texture_rectangle> texture_rectangle)
	{
		if (attachment_index < GL_MAX_COLOR_ATTACHMENTS && texture_rectangle)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment_index, GL_TEXTURE_RECTANGLE, texture_rectangle->get_handle(), 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	void attach_depth_texture_rectangle(const std::shared_ptr<gl_texture_rectangle> texture_rectangle)
	{
		if (texture_rectangle)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_RECTANGLE, texture_rectangle->get_handle(), 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	void attach_stencil_texture_rectangle(const std::shared_ptr<gl_texture_rectangle> texture_rectangle)
	{
		if (texture_rectangle)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_RECTANGLE, texture_rectangle->get_handle(), 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	void attach_depth_stencil_texture_rectangle(const std::shared_ptr<gl_texture_rectangle> texture_rectangle)
	{
		if (texture_rectangle)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _handle);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_RECTANGLE, texture_rectangle->get_handle(), 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	void attach_color_texture_3d_piece(std::uint32_t attachment_index, const std::shared_ptr<gl_texture_3d> texture_3d, std::uint32_t depth_index, std::uint32_t mipmap_index)
	{
		if (attachment_index < GL_MAX_COLOR_ATTACHMENTS && texture_3d)
		{

			glFramebufferTextureLayer(_handle, GL_COLOR_ATTACHMENT0 + attachment_index, texture_3d->get_handle(), mipmap_index, depth_index);
		}

	}
	void attach_depth_texture_3d_piece(const std::shared_ptr<gl_texture_3d> texture_3d, std::uint32_t depth_index, std::uint32_t mipmap_index)
	{
		if (texture_3d)
		{
			glFramebufferTextureLayer(_handle, GL_DEPTH_ATTACHMENT, texture_3d->get_handle(), mipmap_index, depth_index);
		}
	}
	void attach_stencil_texture_3d_piece(const std::shared_ptr<gl_texture_3d> texture_3d, std::uint32_t depth_index, std::uint32_t mipmap_index)
	{
		if (texture_3d)
		{
			glFramebufferTextureLayer(_handle, GL_STENCIL_ATTACHMENT, texture_3d->get_handle(), mipmap_index, depth_index);
		}
	}
	void attach_depth_stencil_texture_3d_piece(const std::shared_ptr<gl_texture_3d> texture_3d, std::uint32_t depth_index, std::uint32_t mipmap_index)
	{
		if (texture_3d)
		{
			glFramebufferTextureLayer(_handle, GL_DEPTH_STENCIL_ATTACHMENT, texture_3d->get_handle(), mipmap_index, depth_index);
		}
	}

	void attach_color_texture_2d_array_element(std::uint32_t attachment_index, std::shared_ptr<gl_texture_2d_array> texture_2d_array, std::uint32_t element_index, std::uint32_t mipmap_index)
	{
		if (attachment_index < GL_MAX_COLOR_ATTACHMENTS && texture_2d_array)
		{
			glNamedFramebufferTextureLayer(_handle, GL_COLOR_ATTACHMENT0 + attachment_index, texture_2d_array->get_handle(), mipmap_index, element_index);
		}
	}
	void attach_depth_texture_2d_array_element(std::shared_ptr<gl_texture_2d_array> texture_2d_array, std::uint32_t element_index, std::uint32_t mipmap_index)
	{
		if (texture_2d_array)
		{
			glNamedFramebufferTextureLayer(_handle, GL_DEPTH_ATTACHMENT, texture_2d_array->get_handle(), mipmap_index, element_index);
		}
	}
	void attach_stencil_texture_2d_array_element(std::shared_ptr<gl_texture_2d_array> texture_2d_array, std::uint32_t element_index, std::uint32_t mipmap_index)
	{
		if (texture_2d_array)
		{
			glNamedFramebufferTextureLayer(_handle, GL_STENCIL_ATTACHMENT, texture_2d_array->get_handle(), mipmap_index, element_index);
		}
	}
	void attach_depth_stencil_texture_2d_array_element(std::shared_ptr<gl_texture_2d_array> texture_2d_array, std::uint32_t element_index, std::uint32_t mipmap_index)
	{
		if (texture_2d_array)
		{
			glNamedFramebufferTextureLayer(_handle, GL_DEPTH_STENCIL_ATTACHMENT, texture_2d_array->get_handle(), mipmap_index, element_index);
		}
	}

	void attach_color_texture_cube_face(std::uint32_t attachment_index, const std::shared_ptr<gl_texture_cube> texture_cube, std::uint32_t face_index, std::uint32_t mipmap_index)
	{
		if (attachment_index < GL_MAX_COLOR_ATTACHMENTS && face_index < 6 && texture_cube)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment_index, GL_TEXTURE_CUBE_MAP_POSITIVE_X + face_index, texture_cube->get_handle(), mipmap_index);
			//glNamedFramebufferTextureLayer(_handle, GL_COLOR_ATTACHMENT0 + attachment_index, texture_cube->get_handle(), mipmap_index, face_index);
		}
	}
	void attach_depth_texture_cube_face(const std::shared_ptr<gl_texture_cube> texture_cube, std::uint32_t face_index, std::uint32_t mipmap_index)
	{
		if (texture_cube && face_index < 6)
		{
			glNamedFramebufferTextureLayer(_handle, GL_DEPTH_ATTACHMENT, texture_cube->get_handle(), mipmap_index, face_index);
		}
	}
	void attach_stencil_texture_cube_face(const std::shared_ptr<gl_texture_cube> texture_cube, std::uint32_t face_index, std::uint32_t mipmap_index)
	{
		if (texture_cube && face_index < 6)
		{
			glNamedFramebufferTextureLayer(_handle, GL_STENCIL_ATTACHMENT, texture_cube->get_handle(), mipmap_index, face_index);
		}
	}
	void attach_depth_stencil_texture_cube_face(const std::shared_ptr<gl_texture_cube> texture_cube, std::uint32_t face_index, std::uint32_t mipmap_index)
	{
		if (texture_cube && face_index < 6)
		{
			glNamedFramebufferTextureLayer(_handle, GL_DEPTH_STENCIL_ATTACHMENT, texture_cube->get_handle(), mipmap_index, face_index);
		}
	}

	void attach_color_texture_cube_array_element_face(std::uint32_t attachment_index, const std::shared_ptr<gl_texture_cube_array> texture_cube_array, std::uint32_t element_index, std::uint32_t face_index, std::uint32_t mipmap_index)
	{
		if (attachment_index < GL_MAX_COLOR_ATTACHMENTS && face_index < 6 && texture_cube_array)
		{
			glNamedFramebufferTextureLayer(_handle, GL_COLOR_ATTACHMENT0 + attachment_index, texture_cube_array->get_handle(), mipmap_index, element_index + face_index);
		}
	}
	void attach_depth_texture_cube_array_element_face(const std::shared_ptr<gl_texture_cube_array> texture_cube_array, std::uint32_t element_index, std::uint32_t face_index, std::uint32_t mipmap_index) 
	{
		if (face_index < 6 && texture_cube_array)
		{
			glNamedFramebufferTextureLayer(_handle, GL_DEPTH_ATTACHMENT, texture_cube_array->get_handle(), mipmap_index, element_index + face_index);
		}
	}
	void attach_stencil_texture_cube_array_element_face(const std::shared_ptr<gl_texture_cube_array> texture_cube_array, std::uint32_t element_index, std::uint32_t face_index, std::uint32_t mipmap_index)
	{
		if (face_index < 6 && texture_cube_array)
		{
			glNamedFramebufferTextureLayer(_handle, GL_STENCIL_ATTACHMENT, texture_cube_array->get_handle(), mipmap_index, element_index + face_index);
		}
	}
	void attach_depth_stencil_texture_cube_array_element_face(const std::shared_ptr<gl_texture_cube_array> texture_cube_array, std::uint32_t element_index, std::uint32_t face_index, std::uint32_t mipmap_index)
	{
		if (face_index < 6 && texture_cube_array)
		{
			glNamedFramebufferTextureLayer(_handle, GL_DEPTH_STENCIL_ATTACHMENT, texture_cube_array->get_handle(), mipmap_index, element_index + face_index);
		}
	}
	
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

