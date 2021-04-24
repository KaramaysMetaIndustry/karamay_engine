#pragma once
#include "graphics/glo/gl_object.h"

enum class gl_texture_type : GLenum
{
	texture_1d = GL_TEXTURE_1D,
	texture_1d_array = GL_TEXTURE_1D_ARRAY,
	texture_2d = GL_TEXTURE_2D,
	texture_2d_array = GL_TEXTURE_2D_ARRAY,
	texture_2d_multisample = GL_TEXTURE_2D_MULTISAMPLE,
	texture_2d_multisample_array = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
	texture_rectangle = GL_TEXTURE_RECTANGLE,
	texture_3d = GL_TEXTURE_3D,
	texture_cube_map = GL_TEXTURE_CUBE_MAP,
	texture_cube_map_array = GL_TEXTURE_CUBE_MAP_ARRAY,
	texture_buffer = GL_TEXTURE_BUFFER
};


enum class gl_texture_data_type : GLenum
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

enum class gl_base_internal_format : GLenum
{
	DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
	DEPTH_STENCI = GL_DEPTH_STENCIL,
	RED = GL_RED,
	RG = GL_RG,
	RGB = GL_RGB,
	RGBA = GL_RGBA
};

enum class gl_sized_internal_format : GLenum
{
	R8 = GL_R8,
	R8_SNORM = GL_R8_SNORM,
	R16 = GL_R16,
	R16_SNORM = GL_R16_SNORM,
	RG8 = GL_RG8,
	RG8_SNORM = GL_RG8_SNORM,
	RG16 = GL_RG16,
	RG16_SNORM = GL_RG16_SNORM,
	R3_G3_B2 = GL_R3_G3_B2,
	RGB4 = GL_RGB4,
	RGB5 = GL_RGB5,
	RGB8 = GL_RGB8,
	RGB8_SNORM = GL_RGB8_SNORM,
	RGB10 = GL_RGB10,
	RGB12 = GL_RGB12,
	RGB16_SNORM = GL_RGB16_SNORM,
	RGBA2 = GL_RGBA2,
	RGBA4 = GL_RGBA4,
	RGB5_A1 = GL_RGB5_A1,
	RGBA8 = GL_RGBA8,
	RGBA8_SNORM = GL_RGBA8_SNORM,
	RGB10_A2 = GL_RGB10_A2,
	RGB10_A2UI = GL_RGB10_A2UI,
	RGBA12 = GL_RGBA12,
	RGBA16 = GL_RGBA16,
	SRGB8 = GL_SRGB8,
	SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
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
	RGBA32UI = GL_RGBA32UI
};

enum class gl_compressed_internal_format : GLenum
{
	// generic formats
	compressed_red = GL_COMPRESSED_RED,
	compressed_rg = GL_COMPRESSED_RG,
	compressed_rgb = GL_COMPRESSED_RGB,
	compressed_rgba = GL_COMPRESSED_RGBA,
	compressed_srgb = GL_COMPRESSED_SRGB,
	compressed_srgb_alpha = GL_COMPRESSED_SRGB_ALPHA,

	// specific formats
	// RGTC 一种简单的压缩格式，存储单通道或者双通道纹理
	// https://zhuanlan.zhihu.com/p/144389736
	compressed_red_rgtc1 = GL_COMPRESSED_RED_RGTC1, // unsigned normalized 1-component only
	compressed_signed_red_rgtc1 = GL_COMPRESSED_SIGNED_RED_RGTC1, // signed normalized 1-component only
	compressed_rg_rgtc2 = GL_COMPRESSED_RG_RGTC2, // unsigned normalized 2-components
	compressed_signed_rg_rgtc2 = GL_COMPRESSED_SIGNED_RG_RGTC2, // signed normalized 2-components

	compressed_rgba_bptc_unorm = GL_COMPRESSED_RGBA_BPTC_UNORM, // unsigned normalized 4-components
	compressed_srgb_alpha_bptc_unorm = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM, // unsigned normalized 4-components in the sRGB color space
	compressed_rgb_bptc_signed_float = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT, // signed, floating-point 3-components
	compressed_rgb_bptc_unsigned_float = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT // unsigned, floating-point 3-components
};

class gl_texture_base : public gl_object
{
protected:
	gl_texture_base();

public:
	virtual ~gl_texture_base();
};

