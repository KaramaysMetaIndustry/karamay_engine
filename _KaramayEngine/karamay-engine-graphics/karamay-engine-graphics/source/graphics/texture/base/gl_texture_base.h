#pragma once
#include "graphics/glo/gl_object.h"

namespace gl_texture_enum
{
	enum class type : GLenum
	{
		TEXTURE_1D = GL_TEXTURE_1D,
		TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,

		TEXTURE_2D = GL_TEXTURE_2D,
		TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,

		TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
		TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,

		TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,

		TEXTURE_3D = GL_TEXTURE_3D,

		TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
		TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,

		TEXTURE_BUFFER = GL_TEXTURE_BUFFER
	};

	enum class pixels_format : GLenum
	{
		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		BGR = GL_BGR,
		RGBA = GL_RGBA,
		BGRA = GL_BGRA,
		RED_INTEGER = GL_RED_INTEGER,
		RG_INTEGER = GL_RG_INTEGER,
		RGB_INTEGER = GL_RGB_INTEGER,
		BGR_INTEGER = GL_BGR_INTEGER,
		RGBA_INTEGER = GL_RGBA_INTEGER,
		BGRA_INTEGER = GL_BGRA_INTEGER,
		STENCIL_INDEX = GL_STENCIL_INDEX,
		DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
		DEPTH_STENCIL = GL_DEPTH_STENCIL
	};

	enum class pixels_type : GLenum
	{
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		BYTE = GL_BYTE,

		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		SHORT = GL_SHORT,

		UNSIGNED_INT = GL_UNSIGNED_INT,
		INT = GL_INT,

		HALF_FLOAT = GL_HALF_FLOAT,
		FLOAT = GL_FLOAT,

		UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
		UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,

		UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
		UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
		UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
		UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
		UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
		UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,

		UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
		UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
		UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
		UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
	};

	enum class internal_format : GLenum
	{
		// base format
		DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
		DEPTH_STENCI = GL_DEPTH_STENCIL,
		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		RGBA = GL_RGBA,

		// sized format
		// default unsigned normalized integer
		// _SNORM
		// F,I,UI
		// ���δָ��������С�ģ�opengl�����Զ������ݽ��нضϣ���֤��ֵ��ΧΪ[0,1]
		// 1-component
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

		//
		R16F = GL_R16F,
		RG16F = GL_RG16F,
		RGB16F = GL_RGB16F,
		RGBA16F = GL_RGBA16F,

		R32F = GL_R32F,
		RG32F = GL_RG32F,
		RGB32F = GL_RGB32F,
		RGBA32F = GL_RGBA32F,

		R11F_G11F_B10F = GL_R11F_G11F_B10F,

		RGB9_E5 = GL_RGB9_E5,

		R8I = GL_R8I,
		R8UI = GL_R8UI,
		R16I = GL_R16I,
		R16UI = GL_R16UI,
		R32I = GL_R32I,
		R32UI = GL_R32UI,

		RG8I = GL_RG8I,
		RG8UI = GL_RG8UI,
		RG16I = GL_RG16I,
		RG16UI = GL_RG16UI,
		RG32I = GL_RG32I,
		RG32UI = GL_RG32UI,

		RGB8I = GL_RGB8I,
		RGB8UI = GL_RGB8UI,
		RGB16I = GL_RGB16I,
		RGB16UI = GL_RGB16UI,
		RGB32I = GL_RGB32I,
		RGB32UI = GL_RGB32UI,

		RGBA8I = GL_RGBA8I,
		RGBA8UI = GL_RGBA8UI,
		RGBA16I = GL_RGBA16I,
		RGBA16UI = GL_RGBA16UI,
		RGBA32I = GL_RGBA32I,
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
		// RGTC һ�ּ򵥵�ѹ����ʽ���洢��ͨ������˫ͨ������
		// https://zhuanlan.zhihu.com/p/144389736
		COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1, // UNSIGNED NORMALIZED 1-COMPONENT ONLY
		COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1, // SIGNED NORMALIZED 1-COMPONENT ONLY
		COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2, // UNSIGNED NORMALIZED 2-COMPONENTS
		COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2, // signed normalized 2-components

		// BPTC 3/4ͨ������
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
		TEXTURE_SWIZZLE_RGBA =  GL_TEXTURE_SWIZZLE_RGBA
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
}

struct gl_texture_pixels_pack
{
	const void* pixels;
	gl_texture_enum::pixels_format format;
	gl_texture_enum::pixels_type type;
	std::uint32_t width;
	std::uint32_t max_mipmaps_num_supported;
};

class gl_sampler;

class gl_texture_base : public gl_object
{
public:

	virtual ~gl_texture_base();

protected:

	gl_texture_base();
	
	std::shared_ptr<class gl_sampler> _sampler;

public:

	void add_sampler(std::shared_ptr<class gl_sampler> sampler)
	{
		_sampler = sampler;
	}


protected:
	void set_depth_stencil_texture_mode(gl_texture_enum::type type, gl_texture_enum::depth_stencil_texture_mode depth_stencil_texture_mode)
	{
		glTexParameteri(static_cast<GLenum>(type),
			static_cast<GLenum>(gl_texture_enum::parameter::DEPTH_STENCIL_TEXTURE_MODE),
			static_cast<GLenum>(depth_stencil_texture_mode));
	}

	void set_texture_base_level(gl_texture_enum::type type, std::uint32_t texture_base_level)
	{}

	void set_texture_max_level(gl_texture_enum::type type, std::uint32_t texture_base_level)
	{}

	void set_texture_swizzle_r(gl_texture_enum::type type, gl_texture_enum::texture_swizzle_component texture_swizzle_r)
	{}

	void set_texture_swizzle_g()
	{}

	void set_texture_swizzle_b()
	{}

	void set_texture_swizzle_a()
	{}

	void set_texture_swizzle_rgba()
	{}
	
};

