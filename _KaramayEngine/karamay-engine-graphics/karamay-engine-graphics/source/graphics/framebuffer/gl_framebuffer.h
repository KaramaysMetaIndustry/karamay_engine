#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/texture/gl_texture.h"
#include "graphics/renderbuffer/gl_renderbuffer.h"

class gl_framebuffer final : public gl_object
{
public:
	void bind();

	void unbind();

	/// attach texture_* as buffer
	void attach_color_buffer_1d(unsigned int attachment_index, const std::shared_ptr<gl_texture_1d> texture_1d, unsigned int mipmap_index);
	void attach_depth_buffer_1d(const std::shared_ptr<gl_texture_1d> texture_1d, unsigned int mipmap_index);
	void attach_stencil_buffer_1d(const std::shared_ptr<gl_texture_1d> texture_1d, unsigned int mipmap_index);
	void attach_depth_stencil_buffer_1d(const std::shared_ptr<gl_texture_1d> texture_1d, unsigned int mipmap_index);

	void attach_color_buffer_2d(unsigned int attachment_index, const std::shared_ptr<gl_texture_2d> texture_2d, unsigned int mipmap_index);
	void attach_depth_buffer_2d(const std::shared_ptr<gl_texture_2d> texture_2d, unsigned int mipmap_index);
	void attach_stencil_buffer_2d(const std::shared_ptr<gl_texture_2d> texture_2d, unsigned int mipmap_index);
	void attach_depth_stencil_buffer_2d(const std::shared_ptr<gl_texture_2d> texture_2d, unsigned int mipmap_index);

	void attach_color_buffer_3d(unsigned int attachment_index, const std::shared_ptr<gl_texture_3d> texture_3d, unsigned int mipmap_index);
	void attach_depth_buffer_3d(const std::shared_ptr<gl_texture_3d> texture_3d, unsigned int mipmap_index);
	void attach_stencil_buffer_3d(const std::shared_ptr<gl_texture_3d> texture_3d, unsigned int mipmap_index);
	void attach_depth_stencil_buffer_3d(const std::shared_ptr<gl_texture_3d> texture_3d, unsigned int mipmap_index);

	void attach_color_buffer_cube_face(unsigned int attachment_index, const std::shared_ptr<gl_texture_cube> texture_cube, unsigned int face_index, unsigned int mipmap_index);
	void attach_depth_buffer_cube_face(const std::shared_ptr<gl_texture_cube> texture_cube, unsigned int face_index, unsigned int mipmap_index);
	void attach_stencil_buffer_cube_face(const std::shared_ptr<gl_texture_cube> texture_cube, unsigned int face_index, unsigned int mipmap_index);
	void attach_depth_stencil_buffer_cube_face(const std::shared_ptr<gl_texture_cube> texture_cube, unsigned int face_index, unsigned int mipmap_index);

	/// attach renderbuffer as buffer
	void attach_color_buffer(unsigned int attachment_index, gl_renderbuffer renderbuffer);
	void attach_depth_buffer(gl_renderbuffer renderbuffer);
	void attach_stencil_buffer(gl_renderbuffer renderbuffer);
	void attach_depth_stencil_buffer(gl_renderbuffer renderbuffer);


	void read_color(int attachment_index, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
	void read_depth(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);
	void read_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);
	void read_depth_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);

	void draw_color(int attachment_index, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
	void draw_depth(GLsizei width, GLsizei height, GLenum type, const void* pixels);
	void draw_stencil(GLsizei width, GLsizei height, GLenum type, const void* pixels);
	void draw_depth_stencil(GLsizei width, GLsizei height, GLenum type, const void* pixels);

	void set_draw_targets(std::vector<unsigned int> color_attachment_indices)
	{
		for (auto& elem : color_attachment_indices)
		{
			elem + GL_COLOR_ATTACHMENT0;
		}

		glDrawBuffers(3, color_attachment_indices.data());
	}

public:
	gl_framebuffer();
	virtual ~gl_framebuffer();
};

