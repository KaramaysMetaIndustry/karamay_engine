#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "../glo/gl_object.h"
#include "../buffers/raw_buffer/gl_buffer.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "../dependencies/stb/stb_image.h"
//
//class gl_image
//{
//public:
//	gl_image()
//	{}
//
//public:
//
//	bool load(const std::string& path)
//	{
//		stbi_set_flip_vertically_on_load(true);
//		_pixels = stbi_load(path.c_str(), &width, &height, &channels_num, 0);
//		if (_pixels == nullptr) {
//			std::cout << "load fail" << std::endl;
//		}
//	}
//
//private:
//	stbi_uc* _pixels;
//	int32 width, height;
//	int32 channels_num;
//};

enum class gl_pixel_store
{
	// If true, byte ordering for multibyte color components, depth components, or stencil indices is reversed.
	// That is, if a four-byte component consists of bytes b 0 , b 1 , b 2 , b 3 , it is stored in memory as b 3 , b 2 , b 1 , b 0 if GL_PACK_SWAP_BYTES is true. 
	// GL_PACK_SWAP_BYTES has no effect on the memory order of components within a pixel, only on the order of bytes within components or indices.
	// For example, the three components of a GL_RGB format pixel are always stored with red first, green second, and blue third, regardless of the value of GL_PACK_SWAP_BYTES.
	PACK_SWAP_BYTES = GL_PACK_SWAP_BYTES,
	PACK_LSB_FIRST = GL_PACK_LSB_FIRST,
	PACK_ROW_LENGTH = GL_PACK_ROW_LENGTH,
	PACK_IMAGE_HEIGHT = GL_PACK_IMAGE_HEIGHT,
	PACK_SKIP_PIXELS = GL_PACK_SKIP_PIXELS,
	PACK_SKIP_ROWS = GL_PACK_SKIP_ROWS,
	PACK_SKIP_IMAGES = GL_PACK_SKIP_IMAGES,
	// Specifies the alignment requirements for the start of each pixel row in memory. 
	// The allowable values are 1 (byte-alignment), 2 (rows aligned to even-numbered bytes), 4 (word-alignment), and 8 (rows start on double-word boundaries).
	PACK_ALIGNMENT = GL_PACK_ALIGNMENT,

	UNPACK_SWAP_BYTES = GL_UNPACK_SWAP_BYTES,
	UNPACK_LSB_FIRST = GL_UNPACK_LSB_FIRST,
	UNPACK_ROW_LENGTH = GL_UNPACK_ROW_LENGTH,
	UNPACK_IMAGE_HEIGHT = GL_UNPACK_IMAGE_HEIGHT,
	UNPACK_SKIP_PIXELS = GL_UNPACK_SKIP_PIXELS,
	UNPACK_SKIP_ROWS = GL_UNPACK_SKIP_ROWS,
	UNPACK_SKIP_IMAGES = GL_UNPACK_SKIP_IMAGES,
	UNPACK_ALIGNMENT = GL_UNPACK_ALIGNMENT
};

enum class gl_texture_type : GLenum
{
	TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
	TEXTURE_1D = GL_TEXTURE_1D,
	TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
	TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
	TEXTURE_2D = GL_TEXTURE_2D,
	TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
	TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
	TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
    TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
    TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
	TEXTURE_3D = GL_TEXTURE_3D
};

enum class gl_texture_internal_format : GLenum
{
	R_I8 = GL_R8I, // R + BYTE
	R_I16 = GL_R16I, // R + SHORT
	R_I32 = GL_R32I, // R + INT
	RG_I8 = GL_RG8I, // RG + BYTE
	RG_I16 = GL_RG16I, // RG + SHORT
	RG_I32 = GL_RG32I, // RG + INT
	RGB_I8 = GL_RGB8I, // RGB + BYTE
	RGB_I16 = GL_RGB16I, // RGB + SHORT
	RGB_I32 = GL_RGB32I, // RGB + INT
	RGBA_I8 = GL_RGBA8I, // RGBA + BYTE
	RGBA_I16 = GL_RGBA16I, // RGBA + SHORT
	RGBA_I32 = GL_RGBA32I, // RGBA + INT

	R_UI8 = GL_R8UI, // R + UBYTE
	R_UI16 = GL_R16UI, // R + USHORT
	R_UI32 = GL_R32UI, // R + UINT
	RG_UI8 = GL_RG8UI, // RG + UBYTE
	RG_UI16 = GL_RG16UI, // RG + USHORT
	RG_UI32 = GL_RG32UI, // RG + UINT
	RGB_UI8 = GL_RGB8UI,  // RGB + UBYTE
	RGB_UI16 = GL_RGB16UI, // RGB + USHORT
	RGB_UI32 = GL_RGB32UI, // RGB + UINT
	RGBA_UI8 = GL_RGBA8UI, // RGBA + UBYTE
	RGBA_UI16 = GL_RGBA16UI, // RGBA + USHORT
	RGBA_UI32 = GL_RGBA32UI, // RGBA + UINT

	R_F32 = GL_R32F, // R + FLOAT
	RG_F32 = GL_RG32F, // RG + FLOAT
	RGB_F32 = GL_RGB32F, // RGB + FLOAT
	RGBA_F32 = GL_RGBA32F, // RGBA + FLOAT

	NOR_R_I8 = GL_R8_SNORM, // R + BYTE
	NOR_R_I16 = GL_R16_SNORM, // R + SHORT
	NOR_RG_I8 = GL_RG8_SNORM, // RG + BYTE
	NOR_RG_I16 = GL_RG16_SNORM, // RG + SHORT
	NOR_RGB_I8 = GL_RGB8_SNORM, // RGB + BYTE
	NOR_RGB_I16 = GL_RGB16_SNORM, // RGB + SHORT
	NOR_RGBA_I8 = GL_RGBA8_SNORM, // RGBA + BYTE
	NOR_RGBA_I16 = GL_RGBA16_SNORM, // RGBA + SHORT

	NOR_R_UI8 = GL_R8, // R + UBYTE
	NOR_R_UI16 = GL_R16, // R + USHORT
	NOR_RG_UI8 = GL_RG8, // RG + UBYTE
	NOR_RG_UI16 = GL_RG16, // RG + USHORT
	NOR_RGB_UI8 = GL_RGB8, // RGB + UBYTE
	NOR_RGB_UI16 = GL_RGB16, // RGB + USHORT
	NOR_RGBA_UI8 = GL_RGBA8, // RGBA + UBYTE
	NOR_RGBA_UI16 = GL_RGBA16, // RGBA + USHORT
	
	//NOR_UI_RGB4 = GL_RGB4,
	//NOR_UI_RGB5 = GL_RGB5,
	NOR_RGB_UI16_5_6_5 = GL_RGB565, // RGB + USHORT_5_6_5
	//NOR_UI_RGB10 = GL_RGB10,
	//NOR_UI_RGB12 = GL_RGB12,
	//NOR_UI_RGBA2 = GL_RGBA2,
	NOR_RGBA_UI16_4_4_4_4 = GL_RGBA4, // RGBA + USHORT_4_4_4_4
	NOR_RGBA_UI16_5_5_5_1 = GL_RGB5_A1, // RGBA + USHORT_5_5_5_1
	NOR_RGBA_UI32_10_10_10_2 = GL_RGB10_A2, // RGBA + UINT_10_10_10_2
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
	DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
	DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
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
	INT16 = GL_SHORT,
	INT8 = GL_BYTE,
	INT32 = GL_INT,

	UINT8 = GL_UNSIGNED_BYTE,
	UINT16 = GL_UNSIGNED_SHORT,
	UINT32 = GL_UNSIGNED_INT,

	FLOAT = GL_FLOAT,
	
	UINT8_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
	UINT8_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,

	UINT16_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
	UINT16_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
	UINT16_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
	UINT16_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
	UINT16_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
	UINT16_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,

	UINT32_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
	UINT32_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
	UINT32_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
	UINT32_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
};

enum class gl_cube_face_index : GLenum
{
	POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};


enum class gl_depth_stencil_texture_mode : GLenum
{
	DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
	STENCIL_INDEX = GL_STENCIL_INDEX,
};

enum class gl_texture_compare_mode : GLenum
{
	COMPARE_REF_TO_TEXTURE = GL_COMPARE_REF_TO_TEXTURE,
	NONE = GL_NONE,
};

enum class gl_texture_compare_func : GLenum
{
	LEQUAL = GL_LEQUAL,
	GEQUAL = GL_GEQUAL,
	LESS = GL_LESS,
	GREATER = GL_GREATER,
	EQUAL = GL_EQUAL,
	NOTEQUAL = GL_NOTEQUAL,
	ALWAYS = GL_ALWAYS,
	NEVER = GL_NEVER
};

enum class gl_texture_min_filter
{
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR,
	NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
};

enum class gl_texture_mag_filter
{
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR,
};

enum class gl_texture_swizzle_component : GLenum
{
	RED = GL_RED,
	GREEN = GL_GREEN,
	BLUE = GL_BLUE,
	ALPHA = GL_ALPHA,
	ZERO = GL_ZERO,
	ONE = GL_ONE
};

enum class gl_texture_wrap_mode : GLenum
{
	CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
	CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	REPEAT = GL_REPEAT,
	MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE
};


struct gl_mipmap_range
{
	uint32 bottom, top;
};

struct gl_array_range
{
	uint32 begin, end;
};

class gl_sampler final : public gl_object 
{
public:
	gl_sampler() : 
		gl_object(gl_object_type::SAMPLER_OBJ),
		_texture_compare_mode(gl_texture_compare_mode::NONE)
	{
		glCreateSamplers(1, &_handle);
	}

	gl_sampler(const gl_sampler&) = delete;
	gl_sampler& operator=(const gl_sampler&) = delete;

	~gl_sampler() override
	{
		glDeleteSamplers(1, &_handle);
	}

public:

	void set_min_filter(gl_texture_min_filter min_filter) 
	{
		glSamplerParameteri(_handle, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(min_filter));
	}

	void set_mag_filter(gl_texture_mag_filter mag_filter) 
	{
		glSamplerParameteri(_handle, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(mag_filter));
	}

	void set_min_lod(float min_lod) 
	{
		glSamplerParameterf(_handle, GL_TEXTURE_MIN_LOD, min_lod);
	}

	void set_max_lod(float max_lod) 
	{
		glSamplerParameterf(_handle, GL_TEXTURE_MAX_LOD, max_lod);
	}

	void set_border_color(glm::vec4 color) 
	{
		glSamplerParameterfv(_handle, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(color));
	}

	void set_wrap_s(gl_texture_wrap_mode mode) 
	{
		glSamplerParameteri(_handle, GL_TEXTURE_WRAP_S, static_cast<GLenum> (mode));
	}

	void set_wrap_t(gl_texture_wrap_mode mode) 
	{
		glSamplerParameteri(_handle, GL_TEXTURE_WRAP_T, static_cast<GLenum>(mode));
	}

	void set_wrap_r(gl_texture_wrap_mode mode)
	{
		glSamplerParameteri(_handle, GL_TEXTURE_WRAP_R, static_cast<GLenum>(mode));
	}

	void set_compare_mode(gl_texture_compare_mode mode) 
	{
		glSamplerParameteri(_handle, GL_TEXTURE_COMPARE_MODE, static_cast<GLint>(mode));
	}

	void set_compare_func(gl_texture_compare_func func)
	{
		glSamplerParameteri(_handle, GL_TEXTURE_COMPARE_FUNC, static_cast<GLint>(func));
	}

	gl_texture_compare_mode get_compare_mode() const { return _texture_compare_mode; }

private:

	gl_texture_compare_mode _texture_compare_mode;

	//
	//	gl_sampler_enum::texture_mag_filter get_texture_mag_filter()
	//	{
	//		GLint value = 0;
	//		glGetSamplerParameteriv(_handle, GL_TEXTURE_MAG_FILTER, &value);
	//		return static_cast<gl_sampler_enum::texture_mag_filter>(value);
	//	}
	//
	//	gl_sampler_enum::texture_min_filter get_texture_min_filter()
	//	{
	//		GLint value = 0;
	//		glGetSamplerParameteriv(_handle, GL_TEXTURE_MIN_FILTER, &value);
	//		return static_cast<gl_sampler_enum::texture_min_filter>(value);
	//	}
	//
	//	std::float_t get_max_lod()
	//	{
	//		GLfloat value = 0.0f;
	//		glGetSamplerParameterfv(_handle, GL_TEXTURE_MAX_LOD, &value);
	//		return static_cast<std::float_t>(value);
	//	}
	//
	//	std::float_t get_min_lod()
	//	{
	//		GLfloat value = 0.0f;
	//		glGetSamplerParameterfv(_handle, GL_TEXTURE_MIN_LOD, &value);
	//		return static_cast<std::float_t>(value);
	//	}
	//
	//	gl_sampler_enum::texture_wrap_option get_texture_wrap_s()
	//	{
	//		GLint value = 0;
	//		glGetSamplerParameteriv(_handle, GL_TEXTURE_WRAP_S, &value);
	//		return static_cast<gl_sampler_enum::texture_wrap_option>(value);
	//	}
	//
	//	gl_sampler_enum::texture_wrap_option get_texture_wrap_t()
	//	{
	//		GLint value = 0;
	//		glGetSamplerParameteriv(_handle, GL_TEXTURE_WRAP_T, &value);
	//		return static_cast<gl_sampler_enum::texture_wrap_option>(value);
	//	}
	//
	//	gl_sampler_enum::texture_wrap_option get_texture_wrap_r()
	//	{
	//		GLint value = 0;
	//		glGetSamplerParameteriv(_handle, GL_TEXTURE_WRAP_R, &value);
	//		return static_cast<gl_sampler_enum::texture_wrap_option>(value);
	//	}
	//
	//	glm::vec4 get_texture_border_color()
	//	{
	//		GLfloat* values = nullptr;
	//		glGetSamplerParameterfv(_handle, GL_TEXTURE_BORDER_COLOR, values);
	//		return glm::vec4();
	//	}
	//
	//	gl_sampler_enum::texture_compare_mode get_texture_compare_mode()
	//	{
	//		GLint value = 0;
	//		glGetSamplerParameteriv(_handle, GL_TEXTURE_COMPARE_MODE, &value);
	//		return static_cast<gl_sampler_enum::texture_compare_mode>(value);
	//	}
	//
	//	gl_sampler_enum::texture_compare_func get_texture_compare_func()
	//	{
	//		GLint value = 0;
	//		glGetSamplerParameteriv(_handle, GL_TEXTURE_COMPARE_FUNC, &value);
	//		return static_cast<gl_sampler_enum::texture_compare_func>(value);
	//	}
	//
	//private:
	//
	//	bool is_sampler_object() const
	//	{
	//		return glIsSampler(_handle) == GL_TRUE ? true : false;
	//	}
};

class gl_texture_t : public gl_object
{
protected:
	gl_texture_t(gl_texture_type type) :
		gl_object(gl_object_type::TEXTURE_OBJ),
		_type(type),
		_bindless_handle(0)
	{
		glCreateTextures(static_cast<GLenum>(_type), 1, &_handle);
	}

	gl_texture_t(const gl_texture_t&) = delete;
	gl_texture_t& operator=(const gl_texture_t&) = delete;

	~gl_texture_t()
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void set_sparse_enable(bool enable)
	{
		glTextureParameteri(_handle, GL_TEXTURE_SPARSE_ARB, enable ? GL_TRUE : GL_FALSE);
	}

	void set_depth_stencil_mode(gl_depth_stencil_texture_mode mode)
	{
		glTextureParameteri(_handle, GL_DEPTH_STENCIL_TEXTURE_MODE, static_cast<GLenum>(mode));
	}

	void set_base_level(int32 base_level)
	{
		glTextureParameteri(_handle, GL_TEXTURE_BASE_LEVEL, base_level);
	}

	void set_border_color(const glm::vec4& color)
	{
		glTextureParameterfv(_handle, GL_TEXTURE_BORDER_COLOR, (const float*)&color);
	}

	void set_compare_mode(gl_texture_compare_mode mode)
	{
		_texture_compare_mode = mode;
		glTextureParameteri(_handle, GL_TEXTURE_COMPARE_MODE, static_cast<GLenum>(mode));
	}

	void set_compare_func(gl_texture_compare_func func)
	{
		glTextureParameteri(_handle, GL_TEXTURE_COMPARE_FUNC, static_cast<GLenum>(func));
	}

	void set_lod_bias(float bias)
	{
		glTextureParameterf(_handle, GL_TEXTURE_LOD_BIAS, bias);
	}

	void set_min_filter(gl_texture_min_filter min_filter)
	{
		glTextureParameteri(_handle, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(min_filter));
	}

	void set_mag_filter(gl_texture_mag_filter mag_filter)
	{
		glTextureParameteri(_handle, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(mag_filter));
	}

	void set_min_lod(int32 min_lod)
	{
		glTextureParameteri(_handle, GL_TEXTURE_MIN_LOD, min_lod);
	}

	void set_max_lod(int32 max_lod)
	{
		glTextureParameteri(_handle, GL_TEXTURE_MAX_LOD, max_lod);
	}

	void set_max_level(int32 max_level)
	{
		glTextureParameteri(_handle, GL_TEXTURE_MAX_LEVEL, max_level);
	}

	void set_swizzle_r(gl_texture_swizzle_component r) 
	{
		glTextureParameteri(_handle, GL_TEXTURE_SWIZZLE_R, static_cast<GLenum>(r));
	}
	
	void set_swizzle_g(gl_texture_swizzle_component g) 
	{
		glTextureParameteri(_handle, GL_TEXTURE_SWIZZLE_R, static_cast<GLenum>(g));
	}
	
	void set_swizzle_b(gl_texture_swizzle_component b) 
	{
		glTextureParameteri(_handle, GL_TEXTURE_SWIZZLE_R, static_cast<GLenum>(b));
	}
	
	void set_swizzle_a(gl_texture_swizzle_component a) 
	{
		glTextureParameteri(_handle, GL_TEXTURE_SWIZZLE_R, static_cast<GLenum>(a));
	}
	
	void set_swizzle_rgba(gl_texture_swizzle_component r, gl_texture_swizzle_component g, gl_texture_swizzle_component b, gl_texture_swizzle_component a) 
	{

	}

	void set_warp_s(gl_texture_wrap_mode mode) 
	{
		glTextureParameteri(_handle, GL_TEXTURE_WRAP_S, static_cast<GLenum>(mode));
	}

	void set_warp_t(gl_texture_wrap_mode mode)
	{
		glTextureParameteri(_handle, GL_TEXTURE_WRAP_T, static_cast<GLenum>(mode));
	}

	void set_warp_r(gl_texture_wrap_mode mode) 
	{
		glTextureParameteri(_handle, GL_TEXTURE_WRAP_R, static_cast<GLenum>(mode));
	}

	gl_texture_compare_mode get_compare_mode() const { return _texture_compare_mode; }

private:

	gl_texture_compare_mode _texture_compare_mode;


public:

	uint64 get_bindless_handle() const { return _bindless_handle; }

	virtual gl_texture_internal_format get_internal_format() const { return gl_texture_internal_format::R_F32; };

	static int32 cast_face_index(gl_cube_face_index face_index)
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

protected:

	gl_texture_type _type;

	uint64 _bindless_handle;


};

class gl_texture_1d_t : public gl_texture_t 
{
public:
	gl_texture_1d_t() :
		gl_texture_t(gl_texture_type::TEXTURE_1D)
	{}

	gl_texture_1d_t(const gl_texture_1d_t&) = delete;
	gl_texture_1d_t& operator=(const gl_texture_1d_t&) = delete;

	~gl_texture_1d_t() = default;

public:

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

public:

	gl_texture_internal_format get_internal_format() const { return _internal_format; }

	int32 get_mipmaps_num() const { return _mipmaps_num; }
	
	int32 get_width() const { return _width; }

protected:

	gl_texture_internal_format _internal_format;

	int32 _width;
	
	int32 _mipmaps_num;

};
class gl_texture_1d_array_t : public gl_texture_t
{
public:
	gl_texture_1d_array_t() :
		gl_texture_t(gl_texture_type::TEXTURE_1D_ARRAY)
	{}

	gl_texture_1d_array_t(const gl_texture_1d_array_t&) = delete;
	gl_texture_1d_array_t& operator=(const gl_texture_1d_array_t&) = delete;

	~gl_texture_1d_array_t() = default;

public:

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

};
class gl_texture_rectangle_t : public gl_texture_t
{
public:
	gl_texture_rectangle_t() :
		gl_texture_t(gl_texture_type::TEXTURE_RECTANGLE)
	{}

	gl_texture_rectangle_t(const gl_texture_rectangle_t&) = delete;
	gl_texture_rectangle_t& operator=(const gl_texture_rectangle_t&) = delete;

	~gl_texture_rectangle_t() = default;

public:

	void fill(int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		glTextureSubImage2D(_handle, 0, x_offset, y_offset, width, height, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
	}

	void fetch(int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, int32 size, void* pixels)
	{
		glGetTextureSubImage(_handle, 0, x_offset, y_offset, 0, width, height, 1, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), size, pixels);
	}

};
class gl_texture_2d_t : public gl_texture_t
{
public:
	gl_texture_2d_t() :
		gl_texture_t(gl_texture_type::TEXTURE_2D)
    {}

	gl_texture_2d_t(const gl_texture_2d_t&) = delete;
	gl_texture_2d_t& operator=(const gl_texture_2d_t&) = delete;

	~gl_texture_2d_t() = default;

public:

	void fill(int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		if (!pixels) return;
		glTextureSubImage2D(_handle, mipmap_index, x_offset, y_offset, width, height, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
	}

	void clear()
	{
		glm::vec4 _mask(0.f);
		glClearTexSubImage(_handle, 0, 0, 0, 0, 1024, 1024, 1, GL_RGBA, GL_FLOAT, &_mask);
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

};
class gl_texture_2d_array_t : public gl_texture_t
{
public:
	gl_texture_2d_array_t() :
		gl_texture_t(gl_texture_type::TEXTURE_2D_ARRAY)
	{}

	gl_texture_2d_array_t(const gl_texture_2d_array_t&) = delete;
	gl_texture_2d_array_t& operator=(const gl_texture_2d_array_t&) = delete;

	~gl_texture_2d_array_t() = default;

public:

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

};
class gl_texture_cube_map_t : public gl_texture_t
{
public:
	gl_texture_cube_map_t() :
		gl_texture_t(gl_texture_type::TEXTURE_CUBE_MAP)
	{}

	gl_texture_cube_map_t(const gl_texture_cube_map_t&) = delete;
	gl_texture_cube_map_t& operator=(const gl_texture_cube_map_t&) = delete;

	~gl_texture_cube_map_t() = default;

public:

	void fill(gl_cube_face_index face_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		//glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glTexSubImage2D(static_cast<GLenum>(face_index), mipmap_index, x_offset, y_offset, width, height, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void fill(int32 face_index, int32 mipmap_index, int32 x_offset, int32 y_offset, int32 width, int32 height, gl_texture_pixel_format pixel_format, gl_texture_pixel_type pixel_type, const void* pixels)
	{
		//glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glTexSubImage2D(static_cast<GLenum>(_cast_face_index(face_index)), mipmap_index, x_offset, y_offset, width, height, static_cast<GLenum>(pixel_format), static_cast<GLenum>(pixel_type), pixels);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
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

};
class gl_texture_cube_map_array_t : public gl_texture_t
{
public:
	gl_texture_cube_map_array_t() :
		gl_texture_t(gl_texture_type::TEXTURE_CUBE_MAP_ARRAY)
	{}

	gl_texture_cube_map_array_t(const gl_texture_cube_map_array_t&) = delete;
	gl_texture_cube_map_array_t& operator=(const gl_texture_cube_map_array_t&) = delete;

	~gl_texture_cube_map_array_t() = default;

public:

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

};
class gl_texture_2d_multisample_t : public gl_texture_t
{
public:
	gl_texture_2d_multisample_t() :
		gl_texture_t(gl_texture_type::TEXTURE_2D_MULTISAMPLE)
	{}

	gl_texture_2d_multisample_t(const gl_texture_2d_multisample_t&) = delete;
	gl_texture_2d_multisample_t& operator=(const gl_texture_2d_multisample_t&) = delete;

	~gl_texture_2d_multisample_t() = default;

};
class gl_texture_2d_multisample_array_t : public gl_texture_t
{
public:
	gl_texture_2d_multisample_array_t() :
		gl_texture_t(gl_texture_type::TEXTURE_2D_MULTISAMPLE_ARRAY)
	{}

	gl_texture_2d_multisample_array_t(const gl_texture_2d_multisample_array_t&) = delete;
	gl_texture_2d_multisample_array_t& operator=(const gl_texture_2d_multisample_array_t&) = delete;

	~gl_texture_2d_multisample_array_t() = default;

};
class gl_texture_3d_t : public gl_texture_t
{
public:
	gl_texture_3d_t() :
		gl_texture_t(gl_texture_type::TEXTURE_3D)
	{}

	gl_texture_3d_t(const gl_texture_3d_t&) = delete;
	gl_texture_3d_t& operator=(const gl_texture_3d_t&) = delete;

	~gl_texture_3d_t() = default;

public:

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

};

class gl_texture_buffer final : public gl_texture_t
{
public:
	gl_texture_buffer(gl_buffer* buffer, gl_texture_internal_format internal_format) :
		gl_texture_t(gl_texture_type::TEXTURE_BUFFER)
	{
		glTextureBuffer(_handle, static_cast<GLenum>(internal_format), buffer->get_handle());
	}

	gl_texture_buffer(const gl_texture_buffer&) = delete;
	gl_texture_buffer& operator=(const gl_texture_buffer&) = delete;

	~gl_texture_buffer()
	{
		glDeleteTextures(1, &_handle);
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

};

class gl_texture_1d final : public gl_texture_1d_t
{
public:
	gl_texture_1d(gl_texture_internal_format internal_format, int32 width, int32 mipmaps_num) :
		gl_texture_1d_t()
	{
		glTextureStorage1D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width);
	}

	gl_texture_1d(const gl_texture_1d&) = delete;
	gl_texture_1d& operator=(const gl_texture_1d&) = delete;

	~gl_texture_1d() = default;

public:

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

};
class gl_texture_1d_array final : public gl_texture_1d_array_t
{
public:
	gl_texture_1d_array(gl_texture_internal_format internal_format, int32 width, int32 mipmaps_num, int32 elements_num) :
		gl_texture_1d_array_t()
	{
		glTextureStorage2D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, elements_num);
	}

	gl_texture_1d_array(const gl_texture_1d_array&) = delete;
	gl_texture_1d_array& operator=(const gl_texture_1d_array&) = delete;

	~gl_texture_1d_array() = default;

public:

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

};
class gl_texture_rectangle final : public gl_texture_rectangle_t
{
public:
	gl_texture_rectangle(int32 width, int32 height, gl_texture_internal_format internal_format) :
		gl_texture_rectangle_t()
	{
		glTextureStorage2D(_handle, 1, static_cast<GLenum>(internal_format), width, height);
	}

	gl_texture_rectangle(const gl_texture_rectangle&) = delete;
	gl_texture_rectangle& operator=(const gl_texture_rectangle&) = delete;

	~gl_texture_rectangle() = default;

};
class gl_texture_2d final : public gl_texture_2d_t
{
public:
	gl_texture_2d(gl_texture_internal_format internal_format, uint32 width, uint32 height, uint32 mipmaps_num) :
		gl_texture_2d_t()
	{
		glTextureStorage2D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, height);
	}

	gl_texture_2d(const gl_texture_2d&) = delete;
	gl_texture_2d& operator=(const gl_texture_2d&) = delete;

	~gl_texture_2d() = default;

public:

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

};
class gl_texture_2d_array final : public gl_texture_2d_array_t
{
public:
	gl_texture_2d_array(gl_texture_internal_format internal_format, int32 width, int32 height, int32 mipmaps_num, int32 elements_num) :
		gl_texture_2d_array_t()
	{
		glTextureStorage3D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, height, elements_num);
	}

	gl_texture_2d_array(const gl_texture_2d_array&) = delete;
	gl_texture_2d_array& operator=(const gl_texture_2d_array&) = delete;

	~gl_texture_2d_array() = default;

public:

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

};
class gl_texture_cube_map final : public gl_texture_cube_map_t
{
public:
	gl_texture_cube_map(gl_texture_internal_format internal_format, int32 width, int32 height, int32 mipmaps_num) :
		gl_texture_cube_map_t()
	{
		glTextureStorage2D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, height);
	}

	gl_texture_cube_map(const gl_texture_cube_map&) = delete;
	gl_texture_cube_map& operator=(const gl_texture_cube_map&) = delete;

	~gl_texture_cube_map() = default;

public:

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

};
class gl_texture_cube_map_array final : public gl_texture_cube_map_array_t
{
public:
	gl_texture_cube_map_array(int32 elements_num, int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height) :
		gl_texture_cube_map_array_t()
	{
		glTextureStorage3D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, height, elements_num * 6);
	}

	gl_texture_cube_map_array(const gl_texture_cube_map_array&) = delete;
	gl_texture_cube_map_array& operator=(const gl_texture_cube_map_array&) = delete;

	~gl_texture_cube_map_array() = default;

public:

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

};
class gl_texture_2d_multisample final : public gl_texture_2d_multisample_t
{
public:
	gl_texture_2d_multisample(gl_texture_internal_format internal_format, int32 samples_num, bool fixed_sample_locations, int32 width, int32 height) :
		gl_texture_2d_multisample_t()
	{
		glTextureStorage2DMultisample(_handle, samples_num, static_cast<GLenum>(internal_format), width, height, fixed_sample_locations);
	}

	gl_texture_2d_multisample(const gl_texture_2d_multisample&) = delete;
	gl_texture_2d_multisample& operator=(const gl_texture_2d_multisample&) = delete;

	~gl_texture_2d_multisample() = default;

};
class gl_texture_2d_multisample_array final : public gl_texture_2d_multisample_array_t
{
public:
	gl_texture_2d_multisample_array(gl_texture_internal_format internal_format, int32 samples_num, bool fixed_sample_locations, int32 width, int32 height, int32 elements_num) :
		gl_texture_2d_multisample_array_t()
	{
		glTextureStorage3DMultisample(_handle, samples_num, static_cast<GLenum>(internal_format), width, height, elements_num, fixed_sample_locations);
	}

	gl_texture_2d_multisample_array(const gl_texture_2d_multisample_array&) = delete;
	gl_texture_2d_multisample_array& operator=(const gl_texture_2d_multisample_array&) = delete;

	~gl_texture_2d_multisample_array() = default;

};
class gl_texture_3d final : public gl_texture_3d_t
{
public:
	gl_texture_3d(gl_texture_internal_format format, int32 width, int32 height, int32 depth, int32 mipmaps_num) :
		gl_texture_3d_t()
	{
		glTextureStorage3D(_handle, mipmaps_num, static_cast<GLenum>(format), width, height, depth);
	}

	gl_texture_3d(const gl_texture_3d&) = delete;
	gl_texture_3d& operator=(const gl_texture_3d&) = delete;

	~gl_texture_3d() = default;

public:

	void build_mipmaps()
	{
		glGenerateTextureMipmap(_handle);
	}

};


class gl_texture_view_1d final : public gl_texture_1d_t
{
public:
	gl_texture_view_1d(
		gl_texture_1d* texture_1d, 
		gl_texture_internal_format format,
		const gl_mipmap_range& mipmap_range
	) :
		gl_texture_1d_t()
	{
		glTextureView(_handle, GL_TEXTURE_1D, 
			texture_1d->get_handle(), static_cast<GLenum>(format), 
			mipmap_range.bottom, mipmap_range.top - mipmap_range.bottom + 1,
			0, 1
		);
	}

	gl_texture_view_1d(
		gl_texture_1d_array* texture_1d_array, 
		gl_texture_internal_format format,
		const gl_mipmap_range& mipmap_range,
		const gl_array_range& array_range
	) :
		gl_texture_1d_t()
	{
		glTextureView(_handle, GL_TEXTURE_1D,
			texture_1d_array->get_handle(), static_cast<GLenum>(format),
			mipmap_range.bottom, mipmap_range.top - mipmap_range.bottom + 1,
			array_range.begin, array_range.end - array_range.begin + 1
		);
	}

};
class gl_texture_view_1d_array final : public gl_texture_1d_array_t
{
public:
	gl_texture_view_1d_array(
		gl_texture_1d* texture_1d, 
		gl_texture_internal_format format,
		const gl_mipmap_range& mipmap_range
	) : 
		gl_texture_1d_array_t()
	{
		glTextureView(_handle, GL_TEXTURE_1D_ARRAY,
			texture_1d->get_handle(), static_cast<GLenum>(format),
			mipmap_range.bottom, mipmap_range.top - mipmap_range.bottom + 1,
			0, 1
		);
	}

	gl_texture_view_1d_array(
		gl_texture_1d_array* texture_1d_array, 
		gl_texture_internal_format format,
		const gl_mipmap_range& mipmap_range,
		const gl_array_range& array_range
	) : 
		gl_texture_1d_array_t()
	{
		glTextureView(_handle, GL_TEXTURE_1D_ARRAY,
			texture_1d_array->get_handle(), static_cast<GLenum>(format),
			mipmap_range.bottom, mipmap_range.top - mipmap_range.bottom + 1,
			array_range.begin, array_range.end - array_range.begin + 1
		);
	}

};
class gl_texture_view_rectangle final : public gl_texture_rectangle_t
{
	gl_texture_view_rectangle(
		gl_texture_rectangle* texture_cube_rectangle, 
		gl_texture_internal_format format
	) : 
		gl_texture_rectangle_t()
	{
		glTextureView(_handle, GL_TEXTURE_RECTANGLE,
			texture_cube_rectangle->get_handle(), static_cast<GLenum>(format),
			0, 1,
			0, 1
		);
	}
};
class gl_texture_view_2d final : public gl_texture_2d_t
{
public:
	gl_texture_view_2d(
		gl_texture_2d* texture_2d, 
		gl_texture_internal_format format,
		const gl_mipmap_range& mipmap_range
	) : 
		gl_texture_2d_t()
	{
		glTextureView(_handle, GL_TEXTURE_2D,
			texture_2d->get_handle(), static_cast<GLenum>(format),
			mipmap_range.bottom, mipmap_range.top - mipmap_range.bottom + 1,
			0, 1
		);
	}

	gl_texture_view_2d(
		gl_texture_2d_array* texture_2d_array, 
		gl_texture_internal_format format,
		const gl_mipmap_range& mipmap_range,
		const gl_array_range& array_range
	) : 
		gl_texture_2d_t()
	{
		glTextureView(_handle, GL_TEXTURE_2D,
			texture_2d_array->get_handle(), static_cast<GLenum>(format),
			mipmap_range.bottom, mipmap_range.top - mipmap_range.bottom + 1,
			array_range.begin, array_range.end - array_range.begin + 1
		);
	}

	gl_texture_view_2d(
		gl_texture_cube_map* texture_cube_map, 
		gl_texture_internal_format format,
		const gl_mipmap_range& mipmap_range,
		const gl_array_range& array_range
	) :
		gl_texture_2d_t()
	{
		glTextureView(_handle, GL_TEXTURE_2D,
			texture_cube_map->get_handle(), static_cast<GLenum>(format),
			mipmap_range.bottom, mipmap_range.top - mipmap_range.bottom + 1,
			0, 1
		);
	}

	gl_texture_view_2d(
		gl_texture_cube_map_array* texture_cube_map_array, gl_texture_internal_format format,
		const gl_mipmap_range& mipmap_range,
		const gl_array_range& array_range
	) :
		gl_texture_2d_t()
	{
		glTextureView(_handle, GL_TEXTURE_2D,
			texture_cube_map_array->get_handle(), static_cast<GLenum>(format),
			mipmap_range.first, mipmap_range.second + 1,
			layer_range.first, layer_range.second + 1
		);
	}

};
class gl_texture_view_2d_array final : public gl_texture_2d_array_t
{
public:
	gl_texture_view_2d_array(
		gl_texture_2d* texture_2d, 
		gl_texture_internal_format format,
		const std::pair<uint32, uint32>& mipmap_range,
		const std::pair<uint32, uint32>& layer_range
	) : 
		gl_texture_2d_array_t()
	{
		glTextureView(_handle, GL_TEXTURE_2D_ARRAY,
			texture_2d->get_handle(), static_cast<GLenum>(format),
			mipmap_range.first, mipmap_range.second - mipmap_range.first + 1,
			layer_range.first, layer_range.second - layer_range.first + 1
		);
	}

	gl_texture_view_2d_array(
		gl_texture_2d_array* texture_2d_array, 
		gl_texture_internal_format format,
		const std::pair<uint32, uint32>& mipmap_range,
		const std::pair<uint32, uint32>& layer_range
	) :
		gl_texture_2d_array_t()
	{
		glTextureView(_handle, GL_TEXTURE_2D_ARRAY,
			texture_2d_array->get_handle(), static_cast<GLenum>(format),
			mipmap_range.first, mipmap_range.second - mipmap_range.first + 1,
			layer_range.first, layer_range.second - layer_range.first + 1
		);
	}

};
class gl_texture_view_cube_map final : public gl_texture_cube_map_t
{
public:
	gl_texture_view_cube_map(
		gl_texture_cube_map* texture_cube_map, 
		gl_texture_internal_format format,
		const std::pair<uint32, uint32>& mipmap_range,
		const std::pair<uint32, uint32>& layer_range
	) :
		gl_texture_cube_map_t()
	{
		glTextureView(_handle, GL_TEXTURE_CUBE_MAP,
			texture_cube_map->get_handle(), static_cast<GLenum>(format),
			mipmap_range.first, mipmap_range.second - mipmap_range.first + 1,
			layer_range.first, layer_range.second - layer_range.first + 1
		);
	}

	gl_texture_view_cube_map(
		gl_texture_cube_map_array* texture_cube_map_array, 
		gl_texture_internal_format format,
		const std::pair<uint32, uint32>& mipmap_range,
		const std::pair<uint32, uint32>& layer_range
	) : 
		gl_texture_cube_map_t()
	{
		glTextureView(_handle, GL_TEXTURE_CUBE_MAP,
			texture_cube_map_array->get_handle(), static_cast<GLenum>(format),
			mipmap_range.first, mipmap_range.second - mipmap_range.first + 1,
			layer_range.first, layer_range.second - layer_range.first + 1
		);
	}

};
class gl_texture_view_cube_map_array final : public gl_texture_cube_map_array_t
{
public:
	gl_texture_view_cube_map_array(
		gl_texture_cube_map* texture_cube_map, 
		gl_texture_internal_format format,
		const std::pair<uint32, uint32>& mipmap_range,
		const std::pair<uint32, uint32>& layer_range
	) : 
		gl_texture_cube_map_array_t()
	{
		glTextureView(_handle, GL_TEXTURE_CUBE_MAP_ARRAY,
			texture_cube_map->get_handle(), static_cast<GLenum>(format),
			mipmap_range.first, mipmap_range.second - mipmap_range.first + 1,
			layer_range.first, layer_range.second - layer_range.first + 1
		);
	}

	gl_texture_view_cube_map_array(
		gl_texture_cube_map_array* texture_cube_map_array, 
		gl_texture_internal_format format,
		const std::pair<uint32, uint32>& mipmap_range,
		const std::pair<uint32, uint32>& layer_range
	) :
		gl_texture_cube_map_array_t()
	{
		glTextureView(_handle, GL_TEXTURE_CUBE_MAP_ARRAY,
			texture_cube_map_array->get_handle(), static_cast<GLenum>(format),
			mipmap_range.first, mipmap_range.second - mipmap_range.first + 1,
			layer_range.first, layer_range.second - layer_range.first + 1
		);
	}

};
class gl_texture_view_2d_multisample final : public gl_texture_2d_multisample_t
{
public:
	gl_texture_view_2d_multisample(
		gl_texture_2d_multisample* texture_2d_multisample, 
		gl_texture_internal_format format
	) : 
		gl_texture_2d_multisample_t()
	{
		glTextureView(_handle, GL_TEXTURE_2D_MULTISAMPLE,
			texture_2d_multisample->get_handle(), static_cast<GLenum>(format),
			0, 1,
			0, 1
		);
	}

	gl_texture_view_2d_multisample(
		gl_texture_2d_multisample_array* texture_2d_multisample_array, 
		gl_texture_internal_format format,
		const std::pair<uint32, uint32>& layer_range
	) : 
		gl_texture_2d_multisample_t()
	{
		glTextureView(_handle, GL_TEXTURE_2D_MULTISAMPLE,
			texture_2d_multisample_array->get_handle(), static_cast<GLenum>(format),
			0, 1,
			layer_range.first, layer_range.second - layer_range.first + 1
		);
	}

};
class gl_texture_view_2d_multisample_array final : public gl_texture_2d_multisample_array_t
{
public:
	gl_texture_view_2d_multisample_array(
		gl_texture_2d_multisample* texture_2d_multisample, 
		gl_texture_internal_format format,
		const std::pair<uint32, uint32>& layer_range
	)
		: gl_texture_2d_multisample_array_t()
	{
		glTextureView(_handle, GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
			texture_2d_multisample->get_handle(), static_cast<GLenum>(format),
			0, 1,
			layer_range.first, layer_range.second - layer_range.first + 1
		);
	}

	gl_texture_view_2d_multisample_array(
		gl_texture_2d_multisample_array* texture_2d_multisample_array, 
		gl_texture_internal_format format,
		const std::pair<uint32, uint32>& layer_range
	)
		: gl_texture_2d_multisample_array_t()
	{
		glTextureView(_handle, GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
			texture_2d_multisample_array->get_handle(), static_cast<GLenum>(format),
			0, 1,
			layer_range.first, layer_range.second
		);
	}

};
class gl_texture_view_3d final : public gl_texture_3d_t
{
public:
	gl_texture_view_3d(
		gl_texture_3d* texture_3d, 
		gl_texture_internal_format format,
		const std::pair<uint32, uint32>& mipmap_range
	) : 
		gl_texture_3d_t()
	{
		glTextureView(_handle, GL_TEXTURE_3D,
			texture_3d->get_handle(), static_cast<GLenum>(format),
			mipmap_range.first, mipmap_range.second - mipmap_range.first + 1,
			0, 1
		);
	}

};

#endif