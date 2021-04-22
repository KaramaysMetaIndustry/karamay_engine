#pragma once
#include "graphics/texture/base/gl_texture_base.h"

enum class e_cube_face : GLenum {
	positive_x = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	negative_x = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	positive_y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	negative_y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	positive_z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	negative_z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};

class gl_texture_cube_array final : public gl_texture_base
{
public:
	void allocate(GLenum internal_format, int width, int mipmaps_num, int num) {
		glTextureStorage3D(GL_TEXTURE_CUBE_MAP_ARRAY, mipmaps_num, internal_format, width, width, num * 6);
	}

	void fill_element_face_sub_miniature_mipmap(int index, e_cube_face cube_face, int mipmap_index, int x_offset, int y_offset, int width, int height, GLenum format, GLenum type, const void* pixels) {
		glTexSubImage3D(static_cast<GLenum>(cube_face), mipmap_index, x_offset, y_offset, 0, width, height, (index + 1) * 6 - 1, format, type, pixels);
	}

public:
	gl_texture_cube_array();
	virtual ~gl_texture_cube_array();
};

