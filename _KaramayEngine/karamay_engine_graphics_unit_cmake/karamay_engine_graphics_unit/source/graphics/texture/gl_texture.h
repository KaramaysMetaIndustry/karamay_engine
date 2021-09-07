#ifndef GL_TEXTURE_BASE_H
#define GL_TEXTURE_BASE_H

#include "graphics/glo/gl_object.h"
#include "graphics/sampler/gl_sampler.h"

enum class internal_format : GLenum
{
	// base format
	DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
	DEPTH_STENCI = GL_DEPTH_STENCIL,

	RED = GL_RED,
	RG = GL_RG,
	RGB = GL_RGB,
	RGBA = GL_RGBA,

	R8 = GL_R8, //r-8bit-unsigned_normalized_integer [0, 2^8-1] maps [0.0, 1.0]
	R8_SNORM = GL_R8_SNORM, //r-8bit signed normalized integer [-2^8, 2^8] maps [-1.0, 1.0]
	R16 = GL_R16, //r-16bit unsigned normalized integer [0, 2^16-1] maps [0.0, 1.0]
	R16_SNORM = GL_R16_SNORM, //r-16bit signed normalized integer [-2^16, 2^16] maps [-1.0, 1.0]

	// 2-components
	RG8 = GL_RG8, // rg-8bit
	RG8_SNORM = GL_RG8_SNORM, // rg-8bit
	RG16 = GL_RG16,
	RG16_SNORM = GL_RG16_SNORM,

	// 3-components
	R3_G3_B2 = GL_R3_G3_B2,
	RGB4 = GL_RGB4,
	RGB5 = GL_RGB5,
	RGB8 = GL_RGB8,
	RGB8_SNORM = GL_RGB8_SNORM,
	RGB10 = GL_RGB10,
	RGB12 = GL_RGB12,
	RGB16_SNORM = GL_RGB16_SNORM,

	// 4-components
	RGBA2 = GL_RGBA2,
	RGBA4 = GL_RGBA4,
	RGB5_A1 = GL_RGB5_A1,
	RGBA8 = GL_RGBA8,
	RGBA8_SNORM = GL_RGBA8_SNORM,
	RGB10_A2 = GL_RGB10_A2,
	RGB10_A2UI = GL_RGB10_A2UI,
	RGBA12 = GL_RGBA12,
	RGBA16 = GL_RGBA16,

	// sRGB
	SRGB8 = GL_SRGB8,
	SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,

	// per-float16
	R16F = GL_R16F,
	RG16F = GL_RG16F,
	RGB16F = GL_RGB16F,
	RGBA16F = GL_RGBA16F,
	// per-float32
	R32F = GL_R32F,
	RG32F = GL_RG32F,
	RGB32F = GL_RGB32F,
	RGBA32F = GL_RGBA32F,
	// 32bit per-float
	R11F_G11F_B10F = GL_R11F_G11F_B10F,
	// 32bit
	RGB9_E5 = GL_RGB9_E5,

	// 8 int
	R8I = GL_R8I,
	RG8I = GL_RG8I,
	RGB8I = GL_RGB8I,
	RGBA8I = GL_RGBA8I,
	// 8 uint
	R8UI = GL_R8UI,
	RG8UI = GL_RG8UI,
	RGB8UI = GL_RGB8UI,
	RGBA8UI = GL_RGBA8UI,
	// 16 int
	R16I = GL_R16I,
	RG16I = GL_RG16I,
	RGB16I = GL_RGB16I,
	RGBA16I = GL_RGBA16I,
	// 16 uint
	R16UI = GL_R16UI,
	RG16UI = GL_RG16UI,
	RGB16UI = GL_RGB16UI,
	RGBA16UI = GL_RGBA16UI,
	// 32 int
	R32I = GL_R32I,
	RG32I = GL_RG32I,
	RGB32I = GL_RGB32I,
	RGBA32I = GL_RGBA32I,
	// 32 int
	R32UI = GL_R32UI,
	RG32UI = GL_RG32UI,
	RGB32UI = GL_RGB32UI,
	RGBA32UI = GL_RGBA32UI,


	// compressed format
	// generic formats
	COMPRESSED_RED = GL_COMPRESSED_RED,
	COMPRESSED_RG = GL_COMPRESSED_RG,
	COMPRESSED_RGB = GL_COMPRESSED_RGB,
	COMPRESSED_RGBA = GL_COMPRESSED_RGBA,
	COMPRESSED_SRGB = GL_COMPRESSED_SRGB,
	COMPRESSED_SRGB_ALPHA = GL_COMPRESSED_SRGB_ALPHA,

	// specific formats
	// https://zhuanlan.zhihu.com/p/144389736
	COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1, // UNSIGNED NORMALIZED 1-COMPONENT ONLY
	COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1, // SIGNED NORMALIZED 1-COMPONENT ONLY
	COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2, // UNSIGNED NORMALIZED 2-COMPONENTS
	COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2, // signed normalized 2-components

	COMPRESSED_RGBA_BPTC_UNORM = GL_COMPRESSED_RGBA_BPTC_UNORM, // UNSIGNED NORMALIZED 4-COMPONENTS
	COMPRESSED_SRGB_ALPHA_BPTC_UNORM = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM, // UNSIGNED NORMALIZED 4-COMPONENTS IN THE SRGB COLOR SPACE
	COMPRESSED_RGB_BPTC_SIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT, // SIGNED, FLOATING-POINT 3-COMPONENTS
	COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT // unsigned, floating-point 3-components
};

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

enum class depth_stencil_texture_mode : GLenum
{
	STENCIL_INDEX = GL_STENCIL_INDEX,
	DEPTH_COMPONENT = GL_DEPTH_COMPONENT
};


enum class gl_texture_type : GLenum
{
	TEXTURE_BUFFER = GL_TEXTURE_BUFFER,

	TEXTURE_1D = GL_TEXTURE_1D,
	TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
	
	TEXTURE_2D = GL_TEXTURE_2D,
	TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
	TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
	TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
	TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,

	TEXTURE_3D = GL_TEXTURE_3D,

	TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
	TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY
};

enum class gl_image_format : GLenum
{
	// base format
	stencil_index = GL_STENCIL_INDEX,
	depth_component = GL_DEPTH_COMPONENT,
	depth_stencil = GL_DEPTH_STENCIL,
	r = GL_RED,
	rg =  GL_RG,
	rgb = GL_RGB,
	rgba = GL_RGBA,
	//
	compressed_r = GL_COMPRESSED_RED,
	compressed_rg = GL_COMPRESSED_RG,
	compressed_rgb = GL_COMPRESSED_RGB,
	compressed_rgba =  GL_COMPRESSED_RGBA,
	compressed_srgb = GL_COMPRESSED_SRGB,
	compressed_srgb_alpha = GL_COMPRESSED_SRGB_ALPHA,
	
	// sized format
	NOR_UI_R8 = GL_R8, // uint8[0, 255] => [0.0f, 1.0f]
	NOR_I_R8 = GL_R8_SNORM, // int8[-128, 127] = > [-1.0f, 1.0f]
	NOR_UI_R16 = GL_R16, // uint16[] => []
	NOR_I_R16 = GL_R16_SNORM, // int16[] => []
	NOR_UI_RG8 = GL_RG8, //
	NOR_I_RG8 = GL_RG8_SNORM,
	NOR_UI_RG16 = GL_RG16,
	NOR_I_RG16 = GL_RG16_SNORM, // NOR_I_RG16

	NOR_UI_R3_G3_B2 = GL_R3_G3_B2, // NOR_UI_R3_G3_B2
	NOR_UI_RGB4 = GL_RGB4, // NOR_UI_RGB4
	NOR_UI_RGB5 = GL_RGB5, // NOR_UI_RGB5
	NOR_UI_R5_G6_B5 = GL_RGB565, // NOR_UI_R5_G6_B5
	NOR_UI_RGB8 = GL_RGB8,// NOR_UI_RGB8
	NOR_I_RGB8 = GL_RGB8_SNORM, // NOR_I_RGB8

	NOR_UI_RGB10 = GL_RGB10, // NOR_UI_RGB10
	NOR_UI_RGB12 = GL_RGB12, // NOR_UI_RGB12
	NOR_UI_RGB16 = GL_RGB16, // NOR_UI_RGB16
	NOR_I_RGB16 = GL_RGB16_SNORM, // NOR_I_RGB16

	NOR_UI_RGBA2 = GL_RGBA2, // NOR_UI_RGBA2
	NOR_UI_RGBA4 = GL_RGBA4, // NOR_UI_RGBA4
	NOR_UI_RGB5_A1 = GL_RGB5_A1, // NOR_UI_RGB5_A1
	NOR_UI_RGBA8 = GL_RGBA8, // NOR_UI_RGBA8
	NOR_I_RGBA8 = GL_RGBA8_SNORM, // NOR_I_RGBA8
	NOR_UI_RGB10_A2 = GL_RGB10_A2, // NOR_UI_RGB10_A2
	UI_RGB10_A2 = GL_RGB10_A2UI, // UI_RGB10_A2
	NOR_UI_RGBA12 = GL_RGBA12, // NOR_UI_RGBA12
	NOR_UI_RGBA16 = GL_RGBA16, // NOR_UI_RGBA16
	NOR_I_RGBA16 = GL_RGBA16_SNORM, // NOR_I_RGBA16

	NOR_UI_SRGB8 = GL_SRGB8,
	NOR_UI_SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,

	//F_R16 = GL_R16F,
	//F_RG16 = GL_RG16F,
	//F_RGB16 = GL_RGB16F,
	//F_RGBA16 = GL_RGBA16F,
	F_R32 = GL_R32F, //float
	F_RG32 = GL_RG32F, // vec2
	F_RGB32 = GL_RGB32F, // vec3
	F_RGBA32 = GL_RGBA32F, // vec4

	F_R11_G11_B10 =  GL_R11F_G11F_B10F,

	rgb9_e5,

	/// <summary>
	/// /////////////////////////////////////
	/// </summary>
	
	I_R8 = GL_R8I,
	I_R16 = GL_R16I,
	I_R32 = GL_R32I, // int
	
	I_RG8 = GL_RG8I,
	I_RG16 = GL_RG16I,
	I_RG32 = GL_RG32I, // ivec2
	
	I_RGB8 = GL_RGB8I,
	I_RGB16 = GL_RGB16I,
	I_RGB32 = GL_RGB32I, // ivec3
	
	I_RGBA8 = GL_RGBA8I,
	I_RGBA16 = GL_RGBA16I,
	I_RGBA32 = GL_RGBA32I, // ivec4
	
	R8UI = GL_R8UI,
	R16UI = GL_R16UI,
	R32UI = GL_R32UI,
	RG8UI = GL_RG8UI,
	RG16UI = GL_RG16UI,
	RG32UI = GL_RG32UI,
	RGB8UI = GL_RGB8UI,
	RGB16UI = GL_RGB16UI,
	RGB32UI = GL_RGB32UI,
	RGBA8UI = GL_RGBA8UI,
	RGBA16UI = GL_RGBA16UI,
	RGBA32UI = GL_RGBA32UI
			
	// compressed format

};

enum class gl_pixel_format : GLenum
{
	R = GL_RED,
	RG = GL_RG,
	RGB = GL_RGB,
	RGBA = GL_RGBA,

	BGR = GL_BGR, //
	BGRA = GL_BGRA, //

	R_INTEGER = GL_RED_INTEGER,
	RG_INTEGER = GL_RG_INTEGER,
	RGB_INTEGER = GL_RGB_INTEGER,
	RGBA_INTEGER = GL_RGBA_INTEGER,

	BGR_INTEGER = GL_BGR_INTEGER, //
	BGRA_INTEGER = GL_BGRA_INTEGER, //

	DEPTH_COMPONENT = GL_DEPTH_COMPONENT, // 1 comp
	STENCIL_INDEX = GL_STENCIL_INDEX, // 1 comp
	DEPTH_STENCIL = GL_DEPTH_STENCIL // 2comp
};

enum class gl_pixel_type : GLenum
{
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE, // uint8
	BYTE = GL_BYTE, // int8
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT, // uint16
	SHORT = GL_SHORT, //int16
	UNSIGNED_INT = GL_UNSIGNED_INT, //uint32
	INT = GL_INT, //int32
	HALF_FLOAT = GL_HALF_FLOAT, // float16
	FLOAT = GL_FLOAT, // float32

	UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2, // RGB
	UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV, // RGB
	UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5, // RGB
	UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV, //RGB

	UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4, // RGBA RGBA_INTEGER
	UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV, // RGBA RGBA_INTEGER
	UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1, // RGBA RGBA_INTEGER
	UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV, // RGBA RGBA_INTEGER

	UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8, // RGBA RGBA_INTEGER
	UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV, //RGBA RGBA_INTEGER
	UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2, // RGBA RGBA_INTEGER
	UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV, //RGBA RGBA_INTEGER

	UNSIGNED_INT_24_8 = GL_UNSIGNED_INT_24_8, // DEPTH_STENCIL

	UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV,
	UNSIGNED_INT_5_9_9_9_REV = GL_UNSIGNED_INT_5_9_9_9_REV, // GL_RGB GL_RGB9_E5
	FLOAT_32_UNSIGNED_INT_24_8_REV = GL_FLOAT_32_UNSIGNED_INT_24_8_REV //  GL_DEPTH32F_STENCIL8
};

enum class gl_cube_face_index : GLenum {
	POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};

class gl_pixels
{
public:
	virtual gl_pixel_format pixel_format() const = 0;
	virtual gl_pixel_type pixel_type() const = 0;
	virtual std::uint32_t pixel_size() const = 0;
	virtual gl_image_format internal_format() const = 0;
	virtual std::uint32_t count() const = 0;
	virtual std::uint8_t* data() const = 0;
};
class gl_pixels_r_u8 : public gl_pixels {
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::R_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_BYTE;
	}
	bool valid_format(gl_image_format image_format) override
	{
		switch (image_format)
		{
		case gl_image_format::NOR_UI_R8: return true;
		case gl_image_format::R8UI: return true;
		}
		return false;
	}
};
class gl_pixels_rg_u8 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RG_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_BYTE;
	}
};
class gl_pixels_rgb_u8 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RGB_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_BYTE;
	}
};
class gl_pixels_rgba_u8 : public gl_pixels {
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RGBA_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_BYTE;
	}
	std::uint8_t* data() const override
	{

	}
	std::uint32_t pixels_count() const override
	{

	}
};
class gl_pixels_bgr_u8 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::BGR_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_BYTE;
	}
};
class gl_pixels_bgra_u8 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::BGRA_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_BYTE;
	}
};
class gl_pixels_r_u16 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::R_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_SHORT;
	}
};
class gl_pixels_rg_u16 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RG_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_SHORT;
	}
};
class gl_pixels_rgb_u16 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RGB_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_SHORT;
	}
};
class gl_pixels_rgba_u16 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RGBA_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_SHORT;
	}
};
class gl_pixels_bgr_u16 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::BGR_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_SHORT;
	}
};
class gl_pixels_bgra_u16 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::BGRA_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_SHORT;
	}
};
class gl_pixels_r_u32 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::R_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_INT;
	}
};
class gl_pixels_rg_u32 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RG_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_INT;
	}
};
class gl_pixels_rgb_u32 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RGB_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_INT;
	}
};
class gl_pixels_rgba_u32 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RGBA_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_INT;
	}
};
class gl_pixels_bgr_u32 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::BGR_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_INT;
	}
};
class gl_pixels_bgra_u32 : public gl_pixels 
{
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::BGRA_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_INT;
	}
};



class gl_pixels_rgb_u8_3_3_2 : public gl_pixels 
{
public:	
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RGB_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_BYTE_3_3_2;
	}
	std::uint8_t* data() const override
	{
		_pixels.data();
	}
	std::uint32_t pixels_count() const override
	{
		_pixels.size();
	}

private:
	std::vector<std::uint8_t> _pixels;

public:
	void add(const glm::u8vec3& pixel)
	{
		std::uint8_t _data = 0;
		pixel.r << 5;
		pixel.g << 2;

		_data |= pixel.r;
		_data |= pixel.g;
		_data |= pixel.b;
		_pixels.push_back(_data);
	}
};
class gl_pixels_rgb_u8_2_3_3_rev : public gl_pixels 
{};
class gl_pixels_rgb_u16_5_6_5 : public gl_pixels 
{
public:
	gl_pixel_format pixel_format() const override
	{
		return gl_pixel_format::RGB_INTEGER;
	}
	gl_pixel_type pixel_type() const override
	{
		return gl_pixel_type::UNSIGNED_SHORT_5_6_5;
	}
	std::uint8_t* data() const override
	{
		_pixels.data();
	}
	std::uint32_t pixels_count() const override
	{
		_pixels.size();
	}

private:
	std::vector<std::uint16_t> _pixels;

public:
	void add(const glm::u16vec3& pixel)
	{
		
	}
};
class gl_pixels_rgb_u16_5_6_5_rev : public gl_pixels 
{};
class gl_pixels_rgba_u16_4_4_4_4 : public gl_pixels 
{};
class gl_pixels_rgba_u16_4_4_4_4_rev : public gl_pixels 
{};
class gl_pixels_rgba_u16_5_5_5_1 : public gl_pixels 
{};
class gl_pixels_rgba_u16_1_5_5_5_rev : public gl_pixels 
{};
class gl_pixels_rgba_u32_8_8_8_8 : public gl_pixels 
{};
class gl_pixels_rgba_u32_8_8_8_8_rev : public gl_pixels 
{};
class gl_pixels_rgba_u32_10_10_10_2 : public gl_pixels 
{};
class gl_pixels_rgba_u32_2_10_10_10_rev : public gl_pixels 
{};


class gl_pixels_r8 : public gl_pixels 
{
	virtual gl_pixel_format pixel_format() const = 0;
	virtual gl_pixel_type pixel_type() const = 0;
	virtual std::uint32_t pixel_size() const = 0;
	virtual gl_pixel_format internal_format() const = 0;
	virtual std::uint32_t count() const = 0;
	virtual std::uint8_t* data() const = 0;

public:

	std::vector<std::uint8_t> _pixels;

	void add(std::uint8_t r) 
	{
		_pixels.push_back(r);
	}

};
class gl_pixels_r16 : public gl_pixels 
{
public:
	std::vector<std::uint16_t> _pixels;

	void add(std::uint16_t r)
	{}
};
class gl_pixels_rg8 : public gl_pixels 
{

public:
	std::vector<glm::u8vec2> _pixels;

	void add(glm::u8vec2 rg) {}
};
class gl_pixels_rg16 : public gl_pixels 
{
	void add(glm::u16vec2 rg)
	{}
};
class gl_pixels_r3g3b2 : public gl_pixels 
{


public:

	std::vector<std::uint8_t> _pixels;

	void add(std::uint8_t r, std::uint8_t g, std::uint8_t b)
	{
		if (r > 7 || g > 7 || b > 3) return;

		std::uint8_t _pixel = 0;
		_pixel |= (r << 5);
		_pixel |= (g << 2);
		_pixel |= b;
		_pixels.push_back(_pixel);
	}
};
//class gl_pixels_rgb4 : public gl_pixels {};
//class gl_pixels_rgb5 : public gl_pixels {};
class gl_pixels_rgb565 : public gl_pixels 
{

	std::vector<std::uint16_t> _pixels;

	void add(std::uint16_t r, std::uint16_t g, std::uint16_t b)
	{
		if (r > 31 || g > 63 || b > 31) return;
		std::uint16_t _pixel = 0;
		_pixel |= (r << 11);
		_pixel |= (g << 5);
		_pixel |= b;
		_pixels.push_back(_pixel);
	}
};
class gl_pixels_rgb8 : public gl_pixels 
{

public:

	void add(std::uint8_t r, std::uint8_t g, std::uint8_t b) {}
};
//class gl_pixels_rgb10 : public gl_pixels {};
//class gl_pixels_rgb12 : public gl_pixels {};
class gl_pixels_rgb16 : public gl_pixels 
{

	void add(std::uint16_t r, std::uint16_t g, std::uint16_t b) {}
};

class gl_pixels_r8snor : public gl_pixels 
{
	void add(std::int8_t r)
	{}
};
class gl_pixels_r16snor : public gl_pixels 
{
	void add(std::int16_t r) {}
};
class gl_pixels_rg8snor : public gl_pixels 
{
	void add(std::int8_t r, std::int8_t g) {}
};
class gl_pixels_rg16snor : public gl_pixels 
{
	void add(std::int16_t r, std::int16_t g) {}
};
class gl_pixels_rgb8snor : public gl_pixels 
{
	void add(std::int8_t r, std::int8_t g, std::int8_t b) {}
};
class gl_pixels_rgb16snor : public gl_pixels 
{
	void add(std::int16_t r, std::int16_t g, std::int16_t b) {}
};
class gl_pixels_rgba8snor : public gl_pixels 
{
	void add(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {}
};
class gl_pixels_rgba16snor : public gl_pixels 
{
	void add(std::uint16_t r, std::uint16_t g, std::uint16_t b, std::uint16_t a) {}
};

//class gl_pixels_r16f : public gl_pixels {};
class gl_pixels_r32f : public gl_pixels 
{
	void add(std::float_t r);
};
//class gl_pixels_rg16f : public gl_pixels {};
class gl_pixels_rg32f : public gl_pixels 
{
	void add(std::float_t r, std::float_t g) {}
};
//class gl_pixels_rgb16f : public gl_pixels {};
class gl_pixels_rgb32f : public gl_pixels 
{
	void add(std::float_t r, std::float_t g, std::float_t b) {}
};
//class gl_pixels_rgba16f : public gl_pixels {};
class gl_pixels_rgba32f : public gl_pixels 
{
	void add(std::float_t r, std::float_t g, std::float_t b, std::float_t a) {}
};

class gl_pixels_r11fg11fb10f : public gl_pixels {};

class gl_pixels_r8ui : public gl_pixels 
{
	void add(std::uint8_t r) {}
};
class gl_pixels_r16ui : public gl_pixels 
{
	void add(std::uint16_t r) {}
};
class gl_pixels_r32ui : public gl_pixels 
{
	void add(std::uint32_t r) {}
};
class gl_pixels_rg8ui : public gl_pixels 
{
	void add(std::uint8_t r, std::uint8_t g) {}
};
class gl_pixels_rg16ui : public gl_pixels 
{
	void add(std::uint16_t r, std::uint16_t g) {}
};
class gl_pixels_rg32ui : public gl_pixels 
{
	void add(std::uint32_t r, std::uint32_t g) {}
};
class gl_pixels_rgb8ui : public gl_pixels 
{
	void add(std::uint8_t r, std::uint8_t g, std::uint8_t b) {}
};
class gl_pixels_rgb16ui : public gl_pixels 
{
	void add(std::uint16_t r, std::uint16_t g, std::uint16_t b) {}
};
class gl_pixels_rgb32ui : public gl_pixels 
{
	void add(std::uint32_t r, std::uint32_t g, std::uint32_t b) {}
};
class gl_pixels_rgba8ui : public gl_pixels 
{
	void add(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {}
};
class gl_pixels_rgba16ui : public gl_pixels 
{
	void add(std::uint16_t r, std::uint16_t g, std::uint16_t b, std::uint16_t a) {}
};
class gl_pixels_rgba32ui : public gl_pixels 
{
	void add(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a) {}
};

class gl_pixels_rgb10a2ui : public gl_pixels 
{

	std::vector<std::uint32_t> _pixels;
	void add(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a) 
	{
		if (r > 1023 || g > 1023 || b > 1023 || a > 3) return;
		std::uint32_t _pixel = 0;
		_pixel |= (r << 22);
		_pixel |= (g << 12);
		_pixel |= (b << 2);
		_pixel |= a;
		_pixels.push_back(_pixel);
	}
};

class gl_pixels_r8i : public gl_pixels 
{
public:
	void add(std::int8_t r) {}
};
class gl_pixels_r16i : public gl_pixels 
{
	void add(std::int16_t r) {}
};
class gl_pixels_r32i : public gl_pixels 
{

	void add(std::int32_t r) {}
};
class gl_pixels_rg8i : public gl_pixels 
{
public:
	void add(std::int8_t r, std::int8_t g) {}
};
class gl_pixels_rg16i : public gl_pixels 
{
public:
	void add(std::int16_t r, std::int16_t g) {}
};
class gl_pixels_rg32i : public gl_pixels 
{
public:
	void add(std::int32_t r, std::int32_t g) {}
};
class gl_pixels_rgb8i : public gl_pixels 
{
public:
	void add(std::int8_t r, std::int8_t g, std::int8_t b) {}
};
class gl_pixels_rgb16i : public gl_pixels 
{
public:
	void add(std::int16_t r, std::int16_t g, std::int16_t b) {}
};
class gl_pixels_rgb32i : public gl_pixels 
{
public:
	void add(std::int32_t r, std::int32_t g, std::int32_t b) {}
};
class gl_pixels_rgba8i : public gl_pixels 
{
public:
	void add(std::int8_t r, std::int8_t g, std::int8_t b, std::int8_t a) {}
};
class gl_pixels_rgba16i : public gl_pixels 
{
public:
	void add(std::int16_t r, std::int16_t g, std::int16_t b, std::int16_t a) {}
};
class gl_pixels_rgba32i : public gl_pixels 
{
public:
	void add(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a) {}
};

class gl_pixels_depth16 : public gl_pixels {};
class gl_pixels_depth24 : public gl_pixels {};
class gl_pixels_depth32 : public gl_pixels {};
class gl_pixels_depth32f : public gl_pixels {};

class gl_pixels_stencil1 : public gl_pixels {};
class gl_pixels_stencil4 : public gl_pixels {};
class gl_pixels_stencil8 : public gl_pixels {};
class gl_pixels_stencil16 : public gl_pixels {};

class gl_pixels_srgb8 : public gl_pixels {};
class gl_pixels_srgb8alpha8 : public gl_pixels {};

class gl_pixels_rgb9_e5 : public gl_pixels {};

struct gl_texture_descriptor
{
	struct gl_texture_base_parameters
	{
		gl_depth_stencil_texture_mode  depth_stencil_texture_mode;
		std::int32_t texture_base_level;
		std::int32_t texture_max_level;
		gl_texture_swizzle_component texture_swizzle_r;
		gl_texture_swizzle_component texture_swizzle_g;
		gl_texture_swizzle_component texture_swizzle_b;
		gl_texture_swizzle_component texture_swizzle_a;
		std::float_t texture_lod_bias;

		gl_texture_base_parameters() :
			depth_stencil_texture_mode(),
			texture_base_level(0),
			texture_max_level(1000),
			texture_swizzle_r(gl_texture_swizzle_component::RED),
			texture_swizzle_g(gl_texture_swizzle_component::GREEN),
			texture_swizzle_b(gl_texture_swizzle_component::BLUE),
			texture_swizzle_a(gl_texture_swizzle_component::ALPHA),
			texture_lod_bias(0.0f)
		{}
	} base_parameters;
	

	//explicit gl_texture_descriptor(
	//	gl_depth_stencil_texture_mode _depth_stencil_texture_mode, 
	//	std::int32_t _texture_base_level, 
	//	std::int32_t _texture_max_level, 
	//	gl_texture_swizzle_component _texture_swizzle_r,
	//	gl_texture_swizzle_component _texture_swizzle_g,
	//	gl_texture_swizzle_component _texture_swizzle_b,
	//	gl_texture_swizzle_component _texture_swizzle_a,
	//	std::float_t _texture_lod_bias
	//) :
	//	depth_stencil_texture_mode(_depth_stencil_texture_mode),
	//	texture_base_level(_texture_base_level),
	//	texture_max_level(_texture_max_level),
	//	texture_swizzle_r(_texture_swizzle_r),
	//	texture_swizzle_g(_texture_swizzle_g),
	//	texture_swizzle_b(_texture_swizzle_b),
	//	texture_swizzle_a(_texture_swizzle_a),
	//	texture_lod_bias(_texture_lod_bias)
	//{}

};

class gl_texture : public gl_object
{
protected:

	gl_texture() = delete;
	gl_texture(gl_texture_type type):
		_type(type)
	{
		glCreateTextures(static_cast<GLenum>(_type), 1, &_handle);

	}
	
	~gl_texture() override
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void bind()
	{
		std::uint32_t unit = 0;
		glBindTextureUnit(GL_TEXTURE0 + unit, _handle);
		_unit = unit;
	}

	void unbind() 
	{
		glBindTextureUnit(GL_TEXTURE0 + _unit, 0);
	}

protected:

	gl_texture_type _type;

	std::uint32_t _unit;

protected:

	static std::unordered_map<gl_texture_type, std::queue<std::uint32_t>> _texture_units;

};

/*
* normalized coordinates, mipmapping
* Images in this texture all are 1-dimensional. They have width, but no height or depth.
*/
struct gl_texture_1d_descriptor
{
	gl_image_format format;
	std::int32_t length;
	std::int32_t mipmaps_count;

	gl_texture_1d_descriptor(gl_image_format _format, std::int32_t _length, std::int32_t _mipmaps_count) :
		format(_format),
		length(_length),
		mipmaps_count(_mipmaps_count)
	{}
	gl_texture_1d_descriptor(gl_image_format _format, std::int32_t _length) :
		format(_format),
		length(_length),
		mipmaps_count(1)
	{}

	gl_texture_1d_descriptor() = delete;
	gl_texture_1d_descriptor(const gl_texture_1d_descriptor&) = default;
	gl_texture_1d_descriptor& operator=(const gl_texture_1d_descriptor&) = default;

	~gl_texture_1d_descriptor() = default;
};

class gl_texture_1d final : 
	public gl_texture
{
public:

	gl_texture_1d() = delete;
	gl_texture_1d(const gl_texture_1d_descriptor& descriptor) :
		gl_texture(gl_texture_type::TEXTURE_1D),
		descriptor(descriptor)
	{
		glTextureStorage1D(
			_handle,
			descriptor.mipmaps_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.length
		);

		_generate_mipmaps_length();
	}

	gl_texture_1d(const gl_texture_1d&) = delete;
	gl_texture_1d& operator=(const gl_texture_1d&) = delete;

	~gl_texture_1d() override = default;

	const gl_texture_1d_descriptor descriptor;

private:

	std::vector<std::int32_t> _mipmaps_length;

	void _generate_mipmaps_length()
	{
		_mipmaps_length.resize(descriptor.mipmaps_count);
		for (std::int32_t _index = 0; _index < descriptor.mipmaps_count; ++_index)
		{
			_mipmaps_length[_index] = descriptor.length / 2;
		}
	}

public:

	std::int32_t get_mipmap_length(std::int32_t mipmap_index)
	{
		if(mipmap_index < 0 || mipmap_index >= _mipmaps_length.size()) return -1;
		return _mipmaps_length[mipmap_index];
	}

public:

	void fill(std::shared_ptr<gl_pixels> pixels)
	{
		glTextureSubImage1D(_handle, 0, 0, descriptor.length, 
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill(std::int32_t offset, const std::shared_ptr<gl_pixels> pixels)
	{
		if (!pixels || offset < 0) return;

		glTextureSubImage1D(_handle,
			0,
			offset, pixels->count(),
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()), 
			pixels->data()
		);
	}

	void fill(std::int32_t mipmap_index, std::int32_t offset, const std::shared_ptr<gl_pixels> pixels)
	{
		std::int32_t _mipmap_length = get_mipmap_length(0);
		if (!pixels || _mipmap_length < 0 || offset < 0 || offset > _mipmap_length) return;
		glTextureSubImage1D(_handle,
			0,
			offset, _mipmap_length,
			GL_RGBA, GL_UNSIGNED_BYTE, pixels->data()
		);
	}

	void fill_mask(std::int32_t x_offset, std::int32_t length, GLenum format, GLenum type, const void* data)
	{
		glClearTexSubImage(_handle, 
			0,
			x_offset, 0, 0, 
			length, 0, 0,
			format, type, data
		);
	}

	void fill_mask(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t length, GLenum format, GLenum type, const void* data)
	{
		glClearTexSubImage(_handle,
			mipmap_index,
			x_offset, 0, 0,
			length, 0, 0,
			format, type, data
		);
	}

public:

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_1D, _handle);
		glGenerateMipmap(GL_TEXTURE_1D);
		glBindTexture(GL_TEXTURE_1D, 0);
	}

public:

	std::uint8_t* fetch_pixels(GLuint mipmap_index, GLenum format, GLenum type)
	{
		std::uint8_t* _pixels = nullptr;
		glGetTextureImage(_handle, 
			mipmap_index, 
			format, type, 
			0, _pixels
		);
		return _pixels;
	}

private:

	void invalidate_mipmap(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t width)
	{
		glInvalidateTexSubImage(_handle, mipmap_index, x_offset, 0, 0, width, 0, 0);
	}

	void test()
	{
		
		this->bind();
	}
};

struct gl_texture_1d_array_descriptor
{
	gl_image_format format;
	std::int32_t length;
	std::int32_t mipmaps_count;
	std::int32_t elements_count;

	gl_texture_1d_array_descriptor(std::int32_t _elements_count, std::int32_t _length, gl_image_format _format, std::int32_t _mipmaps_count) :
		elements_count(_elements_count),
		length(_length),
		format(_format),
		mipmaps_count(_mipmaps_count)
	{}

	gl_texture_1d_array_descriptor(std::int32_t _elements_count, std::int32_t _length, gl_image_format _format) :
		elements_count(_elements_count),
		length(_length),
		format(_format),
		mipmaps_count(1)
	{}

	gl_texture_1d_array_descriptor() = delete;
	gl_texture_1d_array_descriptor(const gl_texture_1d_array_descriptor&) = default;
	gl_texture_1d_array_descriptor& operator=(const gl_texture_1d_array_descriptor&) = default;

	~gl_texture_1d_array_descriptor() = default;
};

/*
* normalized coordinates, mipmapping, array
*
*/
class gl_texture_1d_array final : 
	public gl_texture
{
public:
	gl_texture_1d_array() = delete;
	gl_texture_1d_array(const gl_texture_1d_array_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_1D_ARRAY),
		descriptor(_descriptor)
	{
		glTextureStorage2D(
			_handle,
			_descriptor.mipmaps_count, static_cast<GLenum>(_descriptor.format),
			_descriptor.length,
			_descriptor.elements_count
		);
	}

	~gl_texture_1d_array() = default;

	const gl_texture_1d_array_descriptor descriptor;

public:

	void fill(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t offset, const std::shared_ptr<gl_pixels> pixels)
	{
		if (!pixels ||
			element_index < 0 || element_index >= descriptor.elements_count ||
			mipmap_index < 0 || mipmap_index >= descriptor.mipmaps_count ||
			offset < 0 || offset >= descriptor.length
			) return;

		glTextureSubImage2D(_handle,
			mipmap_index, offset, 0, pixels->count(), element_index,
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t offset, const void* data)
	{
		if (nullptr ||
			element_index < 0 || element_index >= descriptor.elements_count ||
			mipmap_index < 0 || mipmap_index >= descriptor.mipmaps_count ||
			offset < 0 || offset >= descriptor.length
			) return;

		glTextureSubImage2D(
			_handle,
			mipmap_index, offset, 0, descriptor.length,
			element_index,
			GL_RGBA, GL_UNSIGNED_BYTE,
			data
		);
	}

	void fill_mask(std::int32_t element_index);

	void generate_mipmaps(std::uint32_t target)
	{
		glBindTexture(GL_TEXTURE_1D_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_1D_ARRAY);
		glBindTexture(GL_TEXTURE_1D_ARRAY, 0);
	}

};

////////////////////////////////////////////////////////

struct gl_texture_2d_descriptor : public gl_texture_descriptor
{
	gl_image_format format;
	std::int32_t width, height;
	std::int32_t mipmaps_count;

	explicit gl_texture_2d_descriptor(
		std::int32_t _width, std::int32_t _height,
		gl_image_format _format,
		std::int32_t _mipmaps_count
	) :
		width(_width), height(_height),
		format(_format),
		mipmaps_count(_mipmaps_count),
		gl_texture_descriptor()
	{}

	explicit gl_texture_2d_descriptor(
		std::int32_t _width, std::int32_t _height,
		gl_image_format _format
	) :
		width(_width), height(_height),
		format(_format),
		mipmaps_count(1),
		gl_texture_descriptor()
	{}

	gl_texture_2d_descriptor() = delete;
	gl_texture_2d_descriptor(const gl_texture_2d_descriptor&) = default;
	gl_texture_2d_descriptor& operator=(const gl_texture_2d_descriptor&) = default;

	~gl_texture_2d_descriptor() = default;
};

/*
*  Images in this texture all are 2-dimensional. They have width and height, but no depth.
*/
class gl_texture_2d final : 
	public gl_texture
{
public:
	gl_texture_2d() = delete;
	explicit gl_texture_2d(const gl_texture_2d_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_2D),
		descriptor(_descriptor)
	{
		glTextureStorage2D(_handle,
			descriptor.mipmaps_count,
			static_cast<std::uint32_t>(descriptor.format),
			descriptor.width, descriptor.height
		);
	}

	~gl_texture_2d() = default;

	const gl_texture_2d_descriptor descriptor;

public:

	void fill(std::shared_ptr<gl_pixels> pixels)
	{
		if (!pixels) return;
		glTextureSubImage2D(_handle, 0,
			0, 0, descriptor.width, descriptor.height, 
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()), 
			pixels->data()
		);
	}

	void fill(std::int32_t x_offset, std::int32_t y_offset, std::shared_ptr<gl_pixels> pixels)
	{
		if (!pixels || x_offset < 0 || x_offset >= descriptor.width) return;
	}

	void fill(std::int32_t mipmap_index, std::shared_ptr<gl_pixels> pixels)
	{}

	void fill(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::shared_ptr<gl_pixels> pixels)
	{
		if (!pixels ||
			mipmap_index < 0 || mipmap_index >= descriptor.mipmaps_count ||
			x_offset < 0 || x_offset >= descriptor.width ||
			y_offset < 0 || y_offset >= descriptor.height
			)return;

		glTextureSubImage2D(_handle,
			mipmap_index, x_offset, y_offset,
			0, 0, static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill_mask(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset)
	{}

	void fetch_pixels(std::int32_t mipmap_index)
	{
		//glGetTextureImage(_handle, 0,);
	}

};

struct gl_texture_2d_array_descriptor
{
	gl_image_format format;
	std::int32_t width, height;
	std::int32_t mipmaps_count;
	std::int32_t elements_count;

	gl_texture_2d_array_descriptor(std::int32_t _elements_count, std::int32_t _width, std::int32_t _height, gl_image_format _format, std::int32_t _mipmaps_count) :
		elements_count(_elements_count),
		width(_width), height(_height),
		format(_format),
		mipmaps_count(_mipmaps_count)
	{}
	gl_texture_2d_array_descriptor(std::int32_t _elements_count, std::int32_t _width, std::int32_t _height, gl_image_format _format) :
		elements_count(_elements_count),
		width(_width), height(_height),
		format(_format),
		mipmaps_count(1)
	{}

	gl_texture_2d_array_descriptor() = delete;
	gl_texture_2d_array_descriptor(const gl_texture_2d_array_descriptor&) = default;
	gl_texture_2d_array_descriptor& operator=(const gl_texture_2d_array_descriptor&) = default;

	~gl_texture_2d_array_descriptor() = default;

};

class gl_texture_2d_array final : 
	public gl_texture
{
public:

	explicit gl_texture_2d_array(const gl_texture_2d_array_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_2D_ARRAY),
		descriptor(_descriptor)
	{
		glTextureStorage3D(_handle,
			descriptor.mipmaps_count, static_cast<GLenum>(descriptor.format),
			descriptor.width, _descriptor.height,
			descriptor.elements_count
		);
	}

	gl_texture_2d_array() = delete;
	gl_texture_2d_array(const gl_texture_2d_array&) = delete;
	gl_texture_2d_array& operator=(const gl_texture_2d_array&) = delete;

	~gl_texture_2d_array() override = default;

	const gl_texture_2d_array_descriptor descriptor;

public:

	void fill(std::int32_t element_index, std::shared_ptr<gl_pixels> pixels)
	{
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY,
			0, 0, 0,
			element_index, descriptor.width, descriptor.height, 1,
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill(std::int32_t element_index, std::int32_t x_offset, std::int32_t y_offset, std::shared_ptr<gl_pixels> pixels)
	{
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY,
			0, x_offset, y_offset,
			element_index, 2, 2, 1,
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::shared_ptr<gl_pixels> pixels)
	{
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY,
			mipmap_index, x_offset, y_offset,
			element_index, 2, 2, 1,
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill_mask(std::int32_t element_index)
	{}

public:

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

};

struct gl_texture_rectangle_descriptor
{
	gl_image_format format;
	std::int32_t width, height;

	gl_texture_rectangle_descriptor(gl_image_format _format, std::int32_t _width, std::int32_t _height) :
		format(_format),
		width(_width), height(_height)
	{}

	gl_texture_rectangle_descriptor() = delete;
	gl_texture_rectangle_descriptor(const gl_texture_rectangle_descriptor&) = default;
	gl_texture_rectangle_descriptor& operator=(const gl_texture_rectangle_descriptor&) = default;

	~gl_texture_rectangle_descriptor() = default;
};

class gl_texture_rectangle final : 
	public gl_texture
{
public:
	
	gl_texture_rectangle() = delete;
	gl_texture_rectangle(const gl_texture_rectangle_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_RECTANGLE),
		descriptor(_descriptor)
	{
		glTextureStorage2D(_handle,
			1,
			static_cast<GLenum>(descriptor.format),
			descriptor.width,
			descriptor.height
		);
	}

	~gl_texture_rectangle() override = default;

	const gl_texture_rectangle_descriptor descriptor;

public:

	void fill(std::int32_t width, std::int32_t height, std::int32_t x_offset, std::int32_t y_offset, GLenum format, GLenum type, const void* pixels)
	{
		// GL_TEXTURE_RECTANGLE
		glTextureSubImage2D(_handle, 0, x_offset, y_offset, width, height, format, type, pixels);
	}

};

struct gl_texture_cube_descriptor
{
	gl_image_format format;
	std::int32_t width;
	std::int32_t mipmaps_count;

	gl_texture_cube_descriptor(std::int32_t _width, gl_image_format _format, std::int32_t _mipmaps_count) :
		width(_width),
		format(_format),
		mipmaps_count(_mipmaps_count)
	{}

	gl_texture_cube_descriptor(std::int32_t _width, gl_image_format _format) :
		width(_width),
		format(_format),
		mipmaps_count(1)
	{}

	gl_texture_cube_descriptor() = delete;
	gl_texture_cube_descriptor(const gl_texture_cube_descriptor&) = default;
	gl_texture_cube_descriptor& operator=(const gl_texture_cube_descriptor&) = default;

	~gl_texture_cube_descriptor() = default;
};

class gl_texture_cube final : 
	public gl_texture
{
public:

	gl_texture_cube() = delete;
	explicit gl_texture_cube(const gl_texture_cube_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_CUBE_MAP),
		descriptor(_descriptor)
	{
		glTextureStorage3D(_handle,
			descriptor.mipmaps_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.width, descriptor.width,
			6
		);
	}

	gl_texture_cube(const gl_texture_cube&) = delete;
	gl_texture_cube& operator=(const gl_texture_cube&) = delete;

	~gl_texture_cube() override = default;

	const gl_texture_cube_descriptor descriptor;

public:

	void fill(
		gl_cube_face_index face_index,
		std::int32_t mipmap_index,
		std::int32_t x_offset, std::int32_t y_offset,
		const void* data, std::int32_t width, std::int32_t height
	)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glTexSubImage2D(static_cast<GLenum>(face_index), mipmap_index, x_offset, y_offset, width, height, format, type, data);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void set() {

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
};

struct gl_texture_cube_array_descriptor
{
	gl_image_format format;
	std::int32_t width;
	std::int32_t mipmaps_count;
	std::int32_t elements_count;

	gl_texture_cube_array_descriptor(std::int32_t _elements_count, std::int32_t _width, gl_image_format _format, std::int32_t _mipmaps_count) :
		elements_count(_elements_count),
		width(_width),
		format(_format),
		mipmaps_count(_mipmaps_count)
	{}

	gl_texture_cube_array_descriptor(std::int32_t _elements_count, std::int32_t _width, gl_image_format _format) :
		elements_count(_elements_count),
		width(_width),
		format(_format),
		mipmaps_count(1)
	{}

	gl_texture_cube_array_descriptor() = delete;
	gl_texture_cube_array_descriptor(const gl_texture_cube_array_descriptor&) = default;
	gl_texture_cube_array_descriptor& operator=(const gl_texture_cube_array_descriptor&) = default;

	~gl_texture_cube_array_descriptor() = default;
};

class gl_texture_cube_array final : 
	public gl_texture
{
public:

	explicit gl_texture_cube_array(const gl_texture_cube_array_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_CUBE_MAP_ARRAY),
		descriptor(_descriptor)
	{
		glTextureStorage3D(
			_handle,
			descriptor.mipmaps_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.width, descriptor.width,
			descriptor.elements_count * 6
		);
	}

	gl_texture_cube_array() = delete;
	gl_texture_cube_array(const gl_texture_cube_array&) = delete;
	gl_texture_cube_array& operator=(const gl_texture_cube_array&) = delete;

	~gl_texture_cube_array() override = default;

	const gl_texture_cube_array_descriptor descriptor;

public:

	void fill(
		std::int32_t element_index,
		gl_cube_face_index face_index,
		std::int32_t mipmap_index,
		std::int32_t x_offset, std::int32_t y_offset,
		const void* data, std::int32_t width, std::int32_t height
	)
	{
		glTexSubImage3D(
			static_cast<GLenum>(face_index),
			mipmap_index, x_offset, y_offset, 0,
			width, height, (element_index + 1) * 6 - 1, 
			static_cast<GLenum>(descriptor.format), type, data
		);
	}

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP_ARRAY);
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);
	}

};
 
struct gl_texture_3d_descriptor
{
	gl_image_format format;
	std::int32_t width, height, depth;
	std::int32_t mipmaps_count;

	gl_texture_3d_descriptor(std::int32_t _width, std::int32_t _height, std::int32_t _depth, gl_image_format  _format, std::int32_t _mipmaps_count) :
		width(_width), height(_height), depth(_depth),
		mipmaps_count(_mipmaps_count),
		format(_format)
	{}

	gl_texture_3d_descriptor(std::int32_t _width, std::int32_t _height, std::int32_t _depth, gl_image_format _format) :
		width(_width), height(_height), depth(_depth),
		mipmaps_count(1),
		format(_format)
	{}

	gl_texture_3d_descriptor() = delete;
	gl_texture_3d_descriptor(const gl_texture_3d_descriptor&) = default;
	gl_texture_3d_descriptor& operator=(const gl_texture_3d_descriptor&) = default;

	~gl_texture_3d_descriptor() = default;
};

class gl_texture_3d final : 
	public gl_texture
{
public:

	explicit gl_texture_3d(const gl_texture_3d_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_3D),
		descriptor(_descriptor)
	{
		glTextureStorage3D(
			_handle,
			descriptor.mipmaps_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.width, descriptor.height, descriptor.depth
		);
	}

	~gl_texture_3d() override = default;

	const gl_texture_3d_descriptor descriptor;

public:

	void fill(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t z_offset, const void* data)
	{
		glTextureSubImage3D(
			_handle,
			mipmap_index, x_offset, y_offset, z_offset,
			descriptor.width, descriptor.height, descriptor.depth,
			static_cast<std::uint32_t>(descriptor.format), descriptor.type,
			data
		);
	}

};

struct gl_texture_2d_multisample_descriptor
{
	gl_image_format format;
	std::int32_t width, height;
	std::int32_t samples_count;
	bool fixed_sample_location;

	gl_texture_2d_multisample_descriptor(std::int32_t _samples_count, std::int32_t _width, std::int32_t _height, gl_image_format _format, bool _fixed_sample_location) :
		samples_count(_samples_count),
		width(_width), height(_height),
		format(_format),
		fixed_sample_location(_fixed_sample_location)
	{}

	gl_texture_2d_multisample_descriptor(std::int32_t _samples_count, std::int32_t _width, std::int32_t _height, gl_image_format _format) :
		samples_count(_samples_count),
		width(_width), height(_height),
		format(_format),
		fixed_sample_location(false)
	{}

	gl_texture_2d_multisample_descriptor() = delete;
	gl_texture_2d_multisample_descriptor(const gl_texture_2d_multisample_descriptor&) = default;
	gl_texture_2d_multisample_descriptor& operator=(const gl_texture_2d_multisample_descriptor&) = default;

	~gl_texture_2d_multisample_descriptor() = default;
};

/*
* The image in this texture (only one image. No mipmapping) is 2-dimensional. 
* Each pixel in these images contains multiple samples instead of just one value.
* You can not transfer pixel from client to server, you can noly download pixels from server to client
*/
class gl_texture_2d_multisample : 
	public gl_texture
{
public:
	explicit gl_texture_2d_multisample(const gl_texture_2d_multisample_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_2D_MULTISAMPLE),
		descriptor(_descriptor)
	{
		glTextureStorage2DMultisample(_handle,
			descriptor.samples_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.width, descriptor.height,
			descriptor.fixed_sample_location
		);
	}

	gl_texture_2d_multisample() = delete;
	gl_texture_2d_multisample(const gl_texture_2d_multisample&) = delete;
	gl_texture_2d_multisample& operator=(const gl_texture_2d_multisample&) = delete;

	~gl_texture_2d_multisample() override = default;

	const gl_texture_2d_multisample_descriptor descriptor;

};

struct gl_texture_2d_array_multisample_descriptor
{
	gl_image_format format;
	std::int32_t width, height;
	std::int32_t samples_count;
	bool fixed_sample_location;
	std::int32_t elements_count;

	gl_texture_2d_array_multisample_descriptor(
		std::int32_t _elements_count,
		std::int32_t _samples_count,
		std::int32_t _width, std::int32_t _height,
		gl_image_format _format,
		bool _fixed_sample_location
	) :
		elements_count(_elements_count),
		samples_count(_samples_count),
		width(_width), height(_height),
		format(_format),
		fixed_sample_location(_fixed_sample_location)
	{}

	gl_texture_2d_array_multisample_descriptor(
		std::int32_t _elements_count,
		std::int32_t _samples_count,
		std::int32_t _width, std::int32_t _height,
		gl_image_format _format
	) :
		elements_count(_elements_count),
		samples_count(_samples_count),
		width(_width), height(_height),
		format(_format),
		fixed_sample_location(false)
	{}

	gl_texture_2d_array_multisample_descriptor() = delete;
	gl_texture_2d_array_multisample_descriptor(const gl_texture_2d_array_multisample_descriptor&) = default;
	gl_texture_2d_array_multisample_descriptor& operator=(const gl_texture_2d_array_multisample_descriptor&) = default;

	~gl_texture_2d_array_multisample_descriptor() = default;
};

/*
* Combines 2D array and 2D multisample types. No mipmapping.
* 
*/
class gl_texture_2d_multisample_array final : 
	public gl_texture
{
public:

	explicit gl_texture_2d_multisample_array(const gl_texture_2d_array_multisample_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_2D_MULTISAMPLE_ARRAY),
		descriptor(_descriptor)
	{
		glTextureStorage3DMultisample(_handle,
			descriptor.samples_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.width, descriptor.height,
			descriptor.elements_count,
			descriptor.fixed_sample_location
		);
	}

	gl_texture_2d_multisample_array() = delete;
	gl_texture_2d_multisample_array(const gl_texture_2d_multisample_array&) = delete;
	gl_texture_2d_multisample_array& operator=(const gl_texture_2d_multisample_array&) = delete;

	~gl_texture_2d_multisample_array() override = default;

	const gl_texture_2d_array_multisample_descriptor descriptor;

};

struct gl_texture_buffer_descriptor
{
	gl_image_format format;
	std::int32_t offset, length;
	std::shared_ptr<gl_buffer> buffer;

	gl_texture_buffer_descriptor(gl_image_format _format, std::int32_t _offset, std::int32_t _length, std::shared_ptr<gl_buffer> _buffer) :
		format(_format),
		offset(_offset), length(_length),
		buffer(_buffer)
	{}

	gl_texture_buffer_descriptor() = delete;
	gl_texture_buffer_descriptor(const gl_texture_buffer_descriptor&) = default;
	gl_texture_buffer_descriptor& operator=(const gl_texture_buffer_descriptor&) = default;

	~gl_texture_buffer_descriptor() = default;
};

/*
*
* No mipmapping
*/
class gl_texture_buffer : 
	public gl_texture
{
public:

	gl_texture_buffer() = delete;
	gl_texture_buffer(const gl_texture_buffer_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_BUFFER),
		descriptor(_descriptor)
	{
		glTextureBufferRange(_handle,
			static_cast<GLenum>(descriptor.format),
			descriptor.buffer->get_handle(),
			descriptor.offset, descriptor.length
		);
	}

	gl_texture_buffer(const gl_texture_buffer&) = default;
	gl_texture_buffer& operator=(const gl_texture_buffer&) = default;

	~gl_texture_buffer() override = default;

	const gl_texture_buffer_descriptor descriptor;

};

#endif