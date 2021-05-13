#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_cube final : public gl_texture_base
{
public:
	void allocate(GLenum internal_format, int width, int mipmaps_num);

	void fill_base_mipmap(GLenum format, GLenum type, const void* data, e_cube_face face_index);
	void fill_base_sub_mipmap(GLenum format, GLenum type, const void* data, e_cube_face face_index, int x_offset, int y_offset, int width, int height);
	void fill_miniature_mipmap(GLenum format, GLenum type, const void* data, e_cube_face face_index, int mipmap_index);
	void fill_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, e_cube_face face_index, int mipmap_index, int x_offset, int y_offset, int width, int height);

	void fill_cube_miniature_mipmaps();

	void set() {
		fill_base_mipmap(GL_RGBA, GL_UNSIGNED_BYTE, nullptr, e_cube_face::positive_x);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

private:
	int _width;

	int _internal_format;

	int _mipmaps_num;

public:
	gl_texture_cube();
	virtual ~gl_texture_cube();
};

