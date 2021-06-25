#ifndef H_GL_TEXTURE_3D
#define H_GL_TEXTURE_3D

#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_3d final: public gl_texture_base
{
public:

	void allocate(GLenum internal_format, int width, int height, int depth, int mipmaps_num);

	void fill_base_mipmap(GLenum format, GLenum type, const void* data);
	void fill_miniature_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index);

	void fill_base_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int y_offset, int z_offset, int width, int height, int depth);
	void fill_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index, int x_offset, int y_offset, int z_offset, int width, int height, int depth);

	void bind(unsigned int unit);
	void unbind();

private:

	int _width, _height, _depth;

	int _internal_format;

	int _mipmaps_num;

public:

    gl_texture_3d();

	virtual ~gl_texture_3d();
};

#endif

