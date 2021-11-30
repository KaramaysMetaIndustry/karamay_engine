#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "graphics/resource/glo/gl_object.h"
#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"
#include "gl_pixels.h"

enum class parameter : GLenum
{
	DEPTH_STENCIL_TEXTURE_MODE = GL_DEPTH_STENCIL_TEXTURE_MODE,
	TEXTURE_BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
	TEXTURE_MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
	TEXTURE_SWIZZLE_R = GL_TEXTURE_SWIZZLE_R,
	TEXTURE_SWIZZLE_G = GL_TEXTURE_SWIZZLE_G,
	TEXTURE_SWIZZLE_B = GL_TEXTURE_SWIZZLE_B,
	TEXTURE_SWIZZLE_A = GL_TEXTURE_SWIZZLE_A,
	TEXTURE_SWIZZLE_RGBA = GL_TEXTURE_SWIZZLE_RGBA
};

enum class texture_swizzle_component : GLenum
{
	RED = GL_RED,
	GREEN = GL_GREEN,
	BLUE = GL_BLUE,
	ALPHA = GL_ALPHA,
	ZERO = GL_ZERO,
	ONE = GL_ONE
};

enum class depth_stencil_texture_mode : GLenum{
	STENCIL_INDEX = GL_STENCIL_INDEX,
	DEPTH_COMPONENT = GL_DEPTH_COMPONENT
};

enum class gl_cube_face_index : GLenum {
	POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};

enum class gl_texture_type : GLenum
{
    // no mipmap, buffer data
	TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
	// have mipmaps
	TEXTURE_1D = GL_TEXTURE_1D,
	TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
	TEXTURE_2D = GL_TEXTURE_2D,
	TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
    TEXTURE_3D = GL_TEXTURE_3D,
    TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
    TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
    // one mipmap
	TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
	TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
	TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,

};


enum class gl_texture_internal_format : GLenum
{
	//	F_R16 = GL_R16F,
	//	F_RG16 = GL_RG16F,
	//	F_RGB16 = GL_RGB16F,
	//	F_RGBA16 = GL_RGBA16F,
	F_R32 = GL_R32F, // R + FLOAT
	F_RG32 = GL_RG32F, // RG + FLOAT
	F_RGB32 = GL_RGB32F, // RGB + FLOAT
	F_RGBA32 = GL_RGBA32F, // RGBA + FLOAT

	I_R8 = GL_R8I, // R + BYTE
	I_R16 = GL_R16I, // R + SHORT
	I_R32 = GL_R32I, // R + INT
	I_RG8 = GL_RG8I, // RG + BYTE
	I_RG16 = GL_RG16I, // RG + SHORT
	I_RG32 = GL_RG32I, // RG + INT
	I_RGB8 = GL_RGB8I, // RGB + BYTE
	I_RGB16 = GL_RGB16I, // RGB + SHORT
	I_RGB32 = GL_RGB32I, // RGB + INT
	I_RGBA8 = GL_RGBA8I, // RGBA + BYTE
	I_RGBA16 = GL_RGBA16I, // RGBA + SHORT
	I_RGBA32 = GL_RGBA32I, // RGBA + INT

	UI_R8 = GL_R8UI, // R + UBYTE
	UI_R16 = GL_R16UI, // R + USHORT
	UI_R32 = GL_R32UI, // R + UINT
	UI_RG8 = GL_RG8UI, // RG + UBYTE
	UI_RG16 = GL_RG16UI, // RG + USHORT
	UI_RG32 = GL_RG32UI, // RG + UINT
	UI_RGB8 = GL_RGB8UI,  // RGB + UBYTE
	UI_RGB16 = GL_RGB16UI, // RGB + USHORT
	UI_RGB32 = GL_RGB32UI, // RGB + UINT
	UI_RGBA8 = GL_RGBA8UI, // RGBA + UBYTE
	UI_RGBA16 = GL_RGBA16UI, // RGBA + USHORT
	UI_RGBA32 = GL_RGBA32UI, // RGBA + UINT

	NOR_I_R8 = GL_R8_SNORM, // R + BYTE
	NOR_UI_R8 = GL_R8, // R + UBYTE
	NOR_I_R16 = GL_R16_SNORM, // R + SHORT
	NOR_UI_R16 = GL_R16, // R + USHORT
	NOR_I_RG8 = GL_RG8_SNORM, // RG + BYTE
	NOR_UI_RG8 = GL_RG8, // RG + UBYTE
	NOR_I_RG16 = GL_RG16_SNORM, // RG + SHORT
	NOR_UI_RG16 = GL_RG16, // RG + USHORT
	NOR_I_RGB8 = GL_RGB8_SNORM, // RGB + BYTE
	NOR_UI_RGB8 = GL_RGB8, // RGB + UBYTE
	NOR_I_RGB16 = GL_RGB16_SNORM, // RGB + SHORT
	NOR_UI_RGB16 = GL_RGB16, // RGB + USHORT
	NOR_I_RGBA8 = GL_RGBA8_SNORM, // RGBA + BYTE
	NOR_UI_RGBA8 = GL_RGBA8, // RGBA + UBYTE
	NOR_I_RGBA16 = GL_RGBA16_SNORM, // RGBA + SHORT
	NOR_UI_RGBA16 = GL_RGBA16, // RGBA + USHORT
	

	

	//NOR_UI_RGB4 = GL_RGB4,
	//NOR_UI_RGB5 = GL_RGB5,
	NOR_UI_R5_G6_B5 = GL_RGB565, // RGB + USHORT_5_6_5
	//NOR_UI_RGB10 = GL_RGB10,
	//NOR_UI_RGB12 = GL_RGB12,
	//NOR_UI_RGBA2 = GL_RGBA2,
	NOR_UI_RGBA4 = GL_RGBA4, // RGBA + USHORT_4_4_4_4
	NOR_UI_RGB5_A1 = GL_RGB5_A1, // RGBA + USHORT_5_5_5_1
	NOR_UI_RGB10_A2 = GL_RGB10_A2, // RGBA + UINT_10_10_10_2
	//NOR_UI_RGBA12 = GL_RGBA12,

	NOR_UI_SRGB8 = GL_SRGB8, // 
	NOR_UI_SRGB8_ALPHA8 = GL_SRGB8_ALPHA8, // 
	
	UI_RGB10_A2 = GL_RGB10_A2UI, //
	F_R11_G11_B10 = GL_R11F_G11F_B10F, // 
	RGB9_E5 = GL_RGB9_E5, // 

	// depth stencil
	DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
	DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
	DEPTH_COMPONENT32 = GL_DEPTH_COMPONENT32,
	DEPTH_COMPONENT32F = GL_DEPTH_COMPONENT32F,
	DPETH24_STENCIL8 = GL_DEPTH24_STENCIL8,
	DPETH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
	STENCIL_INDEX1 = GL_STENCIL_INDEX1,
	STENCIL_INDEX4 = GL_STENCIL_INDEX4,
	STENCIL_INDEX8 = GL_STENCIL_INDEX8,
	STENCIL_INDEX16 = GL_STENCIL_INDEX16,

	// compressed format
	COMPRESSED_R = GL_COMPRESSED_RED,
	COMPRESSED_RG = GL_COMPRESSED_RG,
	COMPRESSED_RGB = GL_COMPRESSED_RGB,
	COMPRESSED_RGBA = GL_COMPRESSED_RGBA,
	COMPRESSED_SRGB = GL_COMPRESSED_SRGB,
	COMPRESSED_SRGB_ALPHA = GL_COMPRESSED_SRGB_ALPHA,
	COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1,
	COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
	COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2,
	COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2,
	COMPRESSED_RGBA_BPTC_UNORM = GL_COMPRESSED_RGBA_BPTC_UNORM,
	COMPRESSED_SRGB_ALPHA_BPTC_UNORM = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
	COMPRESSED_RGB_BPTC_SIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
	COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,
	COMPRESSED_RGB8_ETC2 = GL_COMPRESSED_RGB8_ETC2,
	COMPRESSED_SRGB8_ETC2 = GL_COMPRESSED_SRGB8_ETC2,
	COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 = GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,
	COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 = GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,
	COMPRESSED_RGBA8_ETC2_EAC = GL_COMPRESSED_RGBA8_ETC2_EAC,
	COMPRESSED_SRGB8_ALPHA8_ETC2_EAC = GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,
	COMPRESSED_R11_EAC = GL_COMPRESSED_R11_EAC,
	COMPRESSED_SIGNED_R11_EAC = GL_COMPRESSED_SIGNED_R11_EAC,
	COMPRESSED_RG11_EAC = GL_COMPRESSED_RG11_EAC,
	COMPRESSED_SIGNED_RG11_EAC = GL_COMPRESSED_SIGNED_RG11_EAC
};

enum class gl_texture_pixel_format : GLenum
{
	STENCIL_INDEX = GL_STENCIL_INDEX,
	DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
	DEPTH_STENCIL = GL_DEPTH_STENCIL,

	R = GL_RED,
	G = GL_GREEN,
	B = GL_BLUE,
	RG = GL_RG,
	RGB = GL_RGB,
	RGBA = GL_RGBA,
	BGR = GL_BGR,
	BGRA = GL_BGRA,

	R_INTEGER = GL_RED_INTEGER,
	G_INTEGER = GL_GREEN_INTEGER,
	B_INTEGER = GL_BLUE_INTEGER,
	RG_INTEGER = GL_RG_INTEGER,
	RGB_INTEGER = GL_RGB_INTEGER,
	RGBA_INTEGER = GL_RGBA_INTEGER,
	BGR_INTEGER = GL_BGR_INTEGER,
	BGRA_INTEGER = GL_BGRA_INTEGER
};

enum class gl_texture_pixel_type : GLenum
{
	UBYTE = GL_UNSIGNED_BYTE,
	BYTE = GL_BYTE,
	USHORT = GL_UNSIGNED_SHORT,
	SHORT = GL_SHORT,
	UINT = GL_UNSIGNED_INT,
	INT = GL_INT,

	FLOAT = GL_FLOAT,
	
	UBYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
	UBYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,

	USHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
	USHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
	
	USHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
	USHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
	
	USHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
	USHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
	
	UINT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
	UINT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
	
	UINT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
	UINT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
};



/*
 * texture parameters
 * */
struct gl_texture_parameters{

//    gl_depth_stencil_texture_mode depth_stencil_texture_mode;
//    std::int32_t texture_base_level;
//    std::int32_t texture_max_level;
//    gl_texture_swizzle_component texture_swizzle_r;
//    gl_texture_swizzle_component texture_swizzle_g;
//    gl_texture_swizzle_component texture_swizzle_b;
//    gl_texture_swizzle_component texture_swizzle_a;
//    std::float_t texture_lod_bias;

};

/*
 * a texture combined with storage, texture parameters, sampler parameters
 * and sampler parameters can bind a sampler object to overwrite
 * */
class gl_texture_t : public gl_object
{
public:
	gl_texture_t()
	{}

    gl_texture_t(gl_texture_type type, const gl_texture_parameters& parameters):
		gl_object(gl_object_type::TEXTURE_OBJ),
		_type(type),
		_unit(0),
        _parameters(parameters)
	{
		glCreateTextures(static_cast<GLenum>(_type), 1, &_handle);
	}

	~gl_texture_t() override
	{
		glDeleteTextures(1, &_handle);
	}

	virtual gl_texture_internal_format get_internal_format() const { return gl_texture_internal_format::F_R32; };

public:

	void bind(uint32 unit)
	{
		glBindTextureUnit(unit, _handle);
		_unit = unit;
	}

	void unbind() const
	{
		glBindTextureUnit(_unit, 0);
	}

protected:

	gl_texture_type _type;

	uint32 _unit;

    gl_texture_parameters _parameters;

};

// mipmaps
class gl_texture_1d : public gl_texture_t 
{
public:
	gl_texture_1d(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width)
	{
		_allocate(mipmaps_num, internal_format, width);
	}

	gl_texture_1d(const gl_texture_1d&) = delete;
	gl_texture_1d& operator=(const gl_texture_1d&) = delete;

	~gl_texture_1d()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width)
	{
		glDeleteTextures(1, &_handle);
		_allocate(mipmaps_num, internal_format, width);
	}

	void fill(int32 mipmap_index, int32 x_offset, int32 width, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		glTextureSubImage1D(_handle, mipmap_index, x_offset, width, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
	}

	void fetch(int32 mipmap_index, int32 x_offset, int32 width, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, int32 size, void* pixels)
	{
		glGetTextureSubImage(_handle, mipmap_index, x_offset, 0, 0, width, 1, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), size, pixels);
	}

	void copy()
	{
		//glCopyTextureSubImage1D();
	}

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

public:

	int32 get_mipmaps_num() const { return _mipmaps_num; }
	
	int32 get_width() const { return _width; }

	gl_texture_internal_format get_internal_format() const { return _internal_format; }

private:
	
	int32 _mipmaps_num;

	int32 _width;

	gl_texture_internal_format _internal_format;

	void _allocate(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width)
	{
		glTextureStorage1D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width);
		_mipmaps_num = mipmaps_num;
		_width = width;
		_internal_format = internal_format;
	}

};
// mipmaps
class gl_texture_1d_array : public gl_texture_t
{
public:
    gl_texture_1d_array(int32 elements_num, int32 mipmaps_num, int32 width, gl_texture_internal_format internal_format)
    {
		_allocate(elements_num, mipmaps_num, width, internal_format);
	}

	gl_texture_1d_array(const gl_texture_1d_array&) = delete;
	gl_texture_1d_array& operator=(const gl_texture_1d_array&) = delete;

	~gl_texture_1d_array()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(int32 elements_num, int32 mipmaps_num, int32 width, gl_texture_internal_format internal_format) 
	{
		glDeleteTextures(1, &_handle);
		_allocate(elements_num, mipmaps_num, width, internal_format);
	}

	void fill(int32 element_index, int32 mipmap_index, int32 x_offset, int32 width, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		glTextureSubImage2D(_handle, mipmap_index, x_offset, element_index, width, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
	}

	void fetch(int32 element_index, int32 mipmap_index, int32 x_offset, int32 width, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, int32 size, void* pixels)
	{
		glGetTextureSubImage(_handle, mipmap_index, x_offset, element_index, 0, width, 1, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), size, pixels);
	}

    void build_mipmaps()
    {
		glGenerateTextureMipmap(_handle);
    }

public:

	int32 get_mipmaps_num() const { return _mipmaps_num; }

	int32 get_elements_num() const { return _elements_num; }

private:

	int32 _mipmaps_num;

	int32 _elements_num;

	void _allocate(int32 elements_num, int32 mipmaps_num, int32 width, gl_texture_internal_format internal_format)
	{
		glTextureStorage2D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, elements_num);
	}

};
// no mipmaps
class gl_texture_buffer : public gl_texture_t
{
public:
	gl_texture_buffer(gl_buffer* buffer, gl_texture_internal_format internal_format)
	{
		glCreateTextures(GL_TEXTURE_BUFFER, 1, &_handle);
		_allocate(buffer, internal_format);
	}

	gl_texture_buffer(const gl_texture_buffer&) = delete;
	gl_texture_buffer& operator=(const gl_texture_buffer&) = delete;

	~gl_texture_buffer()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(gl_buffer* buffer, gl_texture_internal_format internal_format)
	{
		_allocate(buffer, internal_format);
	}

public:

	int32 get_width()
	{
		if (_buffer)
		{
			return _buffer->get_bytes_num();
		}
		return 0;
	}

private:

	gl_buffer* _buffer;

	void _allocate(gl_buffer* buffer, gl_texture_internal_format internal_format)
	{
		glTextureBuffer(_handle, static_cast<GLenum>(internal_format), buffer->get_handle());
	}

};
// mipmaps
class gl_texture_2d : public gl_texture_t
{
public:
    gl_texture_2d(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
    {
		_allocate(mipmaps_num, internal_format, width, height);
	}

	gl_texture_2d(const gl_texture_2d&) = delete;
	gl_texture_2d& operator=(const gl_texture_2d&) = delete;

	~gl_texture_2d()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
	{
		glDeleteTextures(1, &_handle);
		_allocate(mipmaps_num, internal_format, width, height);
	}

	void fill(int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		if (!pixels) return;
		glTextureSubImage2D(_handle, mipmap_index, x_offset, y_offset, width, height, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
	}
	
	void fetch(int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, int32 size, void* pixels)
	{
		glGetTextureSubImage(_handle, mipmap_index, x_offset, y_offset, 0, width, height, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), size, pixels);
	}

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

	int32 get_width(int32 mipmap_index)
	{
		int32 _width = 0;
		glGetTextureLevelParameteriv(_handle, mipmap_index, GL_TEXTURE_WIDTH, &_width);
		return _width;
	}

	int32 get_height(int32 mipmap_index)
	{
		int32 _height = 0;
		glGetTextureLevelParameteriv(_handle, mipmap_index, GL_TEXTURE_HEIGHT , &_height);
		return _height;
	}

	int32 get_depth(int32 mipmap_index)
	{
		int32 _depth = 0;
		glGetTextureLevelParameteriv(_handle, mipmap_index, GL_TEXTURE_DEPTH, &_depth);
		return _depth;
	}

private:

	void _allocate(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &_handle);
		glTextureStorage2D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, height);
	}

};
// mipmaps
class gl_texture_2d_array : public gl_texture_t
{
public:
    gl_texture_2d_array(int32 elements_num, int32 mipmaps_num, int32 width, int32 height, gl_texture_internal_format internal_format)
    {
		_allocate(elements_num, mipmaps_num, width, height, internal_format);
	}

	gl_texture_2d_array(const gl_texture_2d_array&) = delete;
	gl_texture_2d_array& operator=(const gl_texture_2d_array&) = delete;

	~gl_texture_2d_array()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(int32 elements_num, int32 mipmaps_num, int32 width, int32 height, gl_texture_internal_format internal_format)
	{
		glDeleteTextures(1, &_handle);
		_allocate(elements_num, mipmaps_num, width, height, internal_format);
	}

	void fill(int32 element_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		glTextureSubImage3D(_handle, mipmap_index, x_offset, y_offset, element_index, width, height, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
	}

	void fetch(int32 element_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, int32 size, void* pixels)
	{
		glGetTextureSubImage(_handle, mipmap_index, x_offset, y_offset, element_index, width, height, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), size, pixels);
	}

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

private:

	void _allocate(int32 elements_num, int32 mipmaps_num, int32 width, int32 height, gl_texture_internal_format internal_format)
	{
		glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &_handle);
		glTextureStorage3D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, height, elements_num);
	}

};
// mipmaps
class gl_texture_cube : public gl_texture_t
{
public:
    gl_texture_cube(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
    {
		_allocate(mipmaps_num, internal_format, width, height);
	}

	gl_texture_cube(const gl_texture_cube&) = delete;
	gl_texture_cube& operator=(const gl_texture_cube&) = delete;

	~gl_texture_cube()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
	{
		glDeleteTextures(1, &_handle);
		_allocate(mipmaps_num, internal_format, width, height);
	}

	void fill(gl_cube_face_index face_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glTexSubImage2D(static_cast<GLenum>(face_index), mipmap_index, x_offset, y_offset, width, height, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void fill(int32 face_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glTexSubImage2D(static_cast<GLenum>(_cast_face_index(face_index)), mipmap_index, x_offset, y_offset, width, height, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void fetch(gl_cube_face_index face_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, int32 size, void* pixels)
	{
		glGetTextureSubImage(_handle, mipmap_index, x_offset, y_offset, _cast_face_index(face_index), width, height, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), size, pixels);
	}

	void fetch(int32 face_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, int32 size, void* pixels)
	{
		glGetTextureSubImage(_handle, mipmap_index, x_offset, y_offset, face_index, width, height, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), size, pixels);
	}

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

private:

	static int32 _cast_face_index(gl_cube_face_index face_index)
	{
		switch (face_index)
		{
		case gl_cube_face_index::POSITIVE_X: return 0;
		case gl_cube_face_index::NEGATIVE_X: return 1;
		case gl_cube_face_index::POSITIVE_Y: return 2;
		case gl_cube_face_index::NEGATIVE_Y: return 3;
		case gl_cube_face_index::POSITIVE_Z: return 4;
		case gl_cube_face_index::NEGATIVE_Z: return 5;
		}
	}

	static gl_cube_face_index _cast_face_index(int32 face_index)
	{
		switch (face_index)
		{
		case 0: return gl_cube_face_index::POSITIVE_X;
		case 1: return gl_cube_face_index::NEGATIVE_X;
		case 2: return gl_cube_face_index::POSITIVE_Y;
		case 3: return gl_cube_face_index::NEGATIVE_Y;
		case 4: return gl_cube_face_index::POSITIVE_Z;
		case 5: return gl_cube_face_index::NEGATIVE_Z;
		}
	}

	void _allocate(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
	{
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &_handle);
		glTextureStorage2D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, height);
	}

};
// mipmaps
class gl_texture_cube_array : public gl_texture_t
{
public:
    gl_texture_cube_array(int32 elements_num, int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
    {
		_allocate(elements_num, mipmaps_num, internal_format, width, height);
	}

	gl_texture_cube_array(const gl_texture_cube_array&) = delete;
	gl_texture_cube_array& operator=(const gl_texture_cube_array&) = delete;

	~gl_texture_cube_array()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(int32 elements_num, int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
	{
		glDeleteTextures(1, &_handle);
		_allocate(elements_num, mipmaps_num, internal_format, width, height);
	}

	void fill(int32 element_index, gl_cube_face_index face_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		glTextureSubImage3D(_handle, mipmap_index, x_offset, y_offset, element_index + _cast_face_index(face_index), width, height, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
	}

	void fill(int32 element_index, int32 face_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		glTextureSubImage3D(_handle, mipmap_index, x_offset, y_offset, element_index + face_index, width, height, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
	}

	void fetch(int32 element_index, gl_cube_face_index face_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, int32 size, void* pixels)
	{
		glGetTextureSubImage(_handle, mipmap_index, x_offset, y_offset, element_index + _cast_face_index(face_index), width, height, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), size, pixels);
	}

	void build_mipmaps() 
	{
		glGenerateTextureMipmap(_handle);
	}

private:

	static int32 _cast_face_index(gl_cube_face_index face_index)
	{
		switch (face_index)
		{
		case gl_cube_face_index::POSITIVE_X: return 0;
		case gl_cube_face_index::NEGATIVE_X: return 1;
		case gl_cube_face_index::POSITIVE_Y: return 2;
		case gl_cube_face_index::NEGATIVE_Y: return 3;
		case gl_cube_face_index::POSITIVE_Z: return 4;
		case gl_cube_face_index::NEGATIVE_Z: return 5;
		}
	}


	void _allocate(int32 elements_num, int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
	{
		glCreateTextures(GL_TEXTURE_CUBE_MAP_ARRAY, 1, &_handle);
		glTextureStorage3D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, height, elements_num * 6);
	}

};
// no mipmaps
class gl_texture_rectangle : public gl_texture_t 
{
public:
	gl_texture_rectangle(int32 width, int32 height, gl_texture_internal_format internal_format)
	{
		_allocate(width, height, internal_format);
	}

	gl_texture_rectangle(const gl_texture_rectangle&) = delete;
	gl_texture_rectangle& operator=(const gl_texture_rectangle&) = delete;

	~gl_texture_rectangle()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(int32 width, int32 height, gl_texture_internal_format internal_format)
	{
		glDeleteTextures(1, &_handle);
		_allocate(width, height, internal_format);
	}

	void fill(int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		glTextureSubImage2D(_handle, 0, x_offset, y_offset, width, height, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
	}

	void fetch(int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, int32 size, void* pixels)
	{
		glGetTextureSubImage(_handle, 0, x_offset, y_offset, 0, width, height, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), size, pixels);
	}

private:

	void _allocate(int32 width, int32 height, gl_texture_internal_format internal_format)
	{
		glCreateTextures(GL_TEXTURE_RECTANGLE, 1, &_handle);
		glTextureStorage2D(_handle, 1, static_cast<GLenum>(internal_format), width, height);
	}

};
// no mipmaps
class gl_texture_2d_multisample : public gl_texture_t
{
public:
	gl_texture_2d_multisample(int32 samples_num, gl_texture_internal_format internal_format, int32 width, int32 height, bool fixed_sample_locations)
	{
		_allocate(samples_num, internal_format, width, height, fixed_sample_locations);
	}

	gl_texture_2d_multisample(const gl_texture_2d_multisample&) = delete;
	gl_texture_2d_multisample& operator=(const gl_texture_2d_multisample&) = delete;

	~gl_texture_2d_multisample()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(int32 samples_num, gl_texture_internal_format internal_format, int32 width, int32 height, bool fixed_sample_locations)
	{
		glDeleteTextures(1, &_handle);
		_allocate(samples_num, internal_format, width, height, fixed_sample_locations);
	}

private:

	void _allocate(int32 samples_num, gl_texture_internal_format internal_format, int32 width, int32 height, bool fixed_sample_locations)
	{
		glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &_handle);
		glTextureStorage2DMultisample(_handle, samples_num, static_cast<GLenum>(internal_format), width, height, fixed_sample_locations);
	}

};
// no mipmaps
class gl_texture_2d_multisample_array : public gl_texture_t
{
public:
	gl_texture_2d_multisample_array(int32 elements_num, int32 samples_num, gl_texture_internal_format internal_format, int32 width, int32 height, bool fixed_sample_locations)
	{
		_allocate(elements_num, samples_num, internal_format, width, height, fixed_sample_locations);
	}

	gl_texture_2d_multisample_array(const gl_texture_2d_multisample_array&) = delete;
	gl_texture_2d_multisample_array& operator=(const gl_texture_2d_multisample_array&) = delete;

	~gl_texture_2d_multisample_array()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(int32 elements_num, int32 samples_num, gl_texture_internal_format internal_format, int32 width, int32 height, bool fixed_sample_locations)
	{
		glDeleteTextures(1, &_handle);
		_allocate(elements_num, samples_num, internal_format, width, height, fixed_sample_locations);
	}

private:

	void _allocate(int32 elements_num, int32 samples_num, gl_texture_internal_format internal_format, int32 width, int32 height, bool fixed_sample_locations)
	{
		glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 1, &_handle);
		glTextureStorage3DMultisample(_handle, samples_num, static_cast<GLenum>(internal_format), width, height, elements_num, fixed_sample_locations);
	}

};
// mipmaps
class gl_texture_3d : public gl_texture_t
{
public:
	gl_texture_3d(int32 mipmaps_num, int32 width, int32 height, int32 depth, gl_texture_internal_format internal_format) :
		_mipmaps_num(mipmaps_num),
		_width(width), _height(height), _depth(depth),
		_internal_format(internal_format)
    {
		_allocate();
	}

	gl_texture_3d(const gl_texture_3d&) = delete;
	gl_texture_3d& operator=(const gl_texture_3d&) = delete;

	~gl_texture_3d()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void reallocate(int32 mipmaps_num, int32 width, int32 height, int32 depth, gl_texture_internal_format internal_format)
	{
		glDeleteTextures(1, &_handle);
		_mipmaps_num = mipmaps_num;
		_width = width;
		_height = height;
		_width = width;
		_internal_format = internal_format;
		_allocate();
	}

	void fill(int32 mipmap_index, int32 x_offset, int32 y_offset, int32 z_offset, int32 width, int32 height, int32 depth, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		glTextureSubImage3D(_handle, mipmap_index, x_offset, y_offset, z_offset, width, height, depth, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
	}

	void fetch(int32 mipmap_index, int32 x_offset, int32 y_offset, int32 z_offset, int32 width, int32 height, int32 depth, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, int32 size, void* pixels)
	{
		glGetTextureSubImage(_handle, mipmap_index, x_offset, y_offset, z_offset, width, height, depth, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), size, pixels);
	}

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

public:

	int32 get_mipmaps_num() const { return _mipmaps_num; }

	int32 get_width() const { return _width; }

	int32 get_height() const { return _height; }

	int32 get_depth() const { return _height; }

	gl_texture_internal_format get_internal_format() const { return _internal_format; }

private:
	
	int32 _mipmaps_num;
	
	int32 _width, _height, _depth;
	
	gl_texture_internal_format _internal_format;

	void _allocate()
	{
		glCreateTextures(GL_TEXTURE_3D, 1, &_handle);
		glTextureStorage3D(_handle, _mipmaps_num, static_cast<GLenum>(_internal_format), _width, _height, _depth);
	}

};

#endif