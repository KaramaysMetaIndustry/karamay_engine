#ifndef GL_TEXTURE_BASE_H
#define GL_TEXTURE_BASE_H

#include "graphics/glo/gl_object.h"
#include "graphics/sampler/gl_sampler.h"

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
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE, // uint8
		BYTE = GL_BYTE, // int8
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT, // uint16
		SHORT = GL_SHORT, //int16
		UNSIGNED_INT = GL_UNSIGNED_INT, //uint32
		INT = GL_INT, //int32
		
		HALF_FLOAT = GL_HALF_FLOAT, // float16
		FLOAT = GL_FLOAT, // float32

		UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
		UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,

		UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
		UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
		UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4, // 16
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

enum class gl_cube_face_index : GLenum {
	positive_x = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	negative_x = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	positive_y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	negative_y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	positive_z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	negative_z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};


enum class gl_texture_pixel_format : GLenum
{
	// normalized (i/ui)
	// uint8 [0, 255] => [0, 1.0]
	// NormalizedUI8R
	r8_ui_nor = GL_R8, // £¨uint8, uint8, uint8£©
	r8_i_nor = GL_R8_SNORM, //(int8, int8, int8)
	r16_ui_nor = GL_R16, // (uint16, uint16, uint16)
	r16_i_nor = GL_R16_SNORM, //(int16, int16, int16)
	rg8_ui_nor = GL_RG8, //
	rg8_i_nor = GL_RG8_SNORM,
	rg16_ui_nor = GL_RG16,
	rg16_i_nor = GL_RG16_SNORM,

	r3_g3_b2_ui_nor, //
	
	rgb4_ui_nor,
	rgb5_ui_nor,

	rgb8_ui_nor, //
	rgb8_i_nor,
	
	rgb10_ui_nor,
	rgb12_ui_nor,

	rgb16_i_nor, // (int16, int16, int16)
	
	rgba2_ui_nor,
	rgba4_ui_nor,
	rgb5_a1_ui_nor,
	rgba8_ui_nor,
	rgba8_i_nor,
	rgb10_a2_ui_nor,
	rgb10_a2_ui,
	rgba12_ui_nor,

	rgba16_ui_nor,
	
	srgb8_ui_nor,
	srgb8_a8_ui_nor,

	r16_f,
	rg16_f,
	rgb16_f,
	rgba16_f,
	r32_f,
	rg32_f,
	rgb32_f,
	rgba32_f,
	r11_g11_b10_f,
	
	rgb9_e5,

	r8_i,
	r8_ui,
	r16_i,
	r16_ui,
	r32_i,
	r32_ui,
	rg8_i,
	rg8_ui,
	rg16_i,
	rg16_ui,
	rg32_i,
	rg32_ui,
	rgb8_i,
	rgb8_ui,
	rgb16_i,
	rgb16_ui,
	rgb32_i,
	rgb32_ui,
	rgba8_i,
	rgba8_ui,
	rgba16_i,
	rgba16_ui,
	rgba32_i,
	rgba32_ui,

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

// texImage*
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

	//I_R8 = GL_R8I,
	//I_R16 = GL_R16I,
	I_R32 = GL_R32I, // int
	//I_RG8 = GL_RG8I,
	//I_RG16 = GL_RG16I,
	I_RG32 = GL_RG32I, // ivec2
	//I_RGB8 = GL_RGB8I,
	//I_RGB16 = GL_RGB16I,
	I_RGB32 = GL_RGB32I, // ivec3
	//I_RGBA8 = GL_RGBA8I,
	//I_RGBA16 = GL_RGBA16I,
	I_RGBA32 = GL_RGBA32I, // ivec4
	//UI_R8 = GL_R8UI,
	//UI_R16= GL_R16UI,
	UI_R32 = GL_R32UI, // uint
	//UI_RG8 = GL_RG8UI,
	//UI_RG16 = GL_RG16UI,
	UI_RG32 = GL_RG32UI, // uvec2
	//UI_RGB8 = GL_RGB8UI,
	//UI_RGB16 = GL_RGB16UI,
	UI_RGB32 = GL_RGB32UI, // uvec3
	//UI_RGBA8 = GL_RGBA8UI,
	//UI_RGBA16 = GL_RGBA16UI,
	UI_RGBA32 = GL_RGBA32UI // uvec4
	// compressed format



	
};

class gl_pixels
{
public:
	gl_pixels();

	const std::uint32_t format;
	const std::uint32_t type;
	const std::uint32_t internal_format;
public:
	std::uint8_t* data() {
		gl_image_format::F_R32;
	}



};



std::pair<std::uint32_t, std::uint32_t> pixel_format_to_data_format(gl_texture_pixel_format format)
{
	return std::make_pair(0, 0);
}


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
public:
	
	gl_texture() = default;

	~gl_texture() override
	{
		glDeleteTextures(1, &_handle);
	}

public:

	virtual void bind() = 0;
	
	virtual void unbind() = 0;

protected:

	std::pair<GLenum, GLenum> _get_data_format_type(gl_texture_pixel_format pixel_format)
	{
		switch (pixel_format)
		{
		case gl_texture_pixel_format::r8_ui_nor:
			break;
		case gl_texture_pixel_format::r8_i_nor:
			break;
		case gl_texture_pixel_format::r16_ui_nor:
			break;
		case gl_texture_pixel_format::r16_i_nor:
			break;
		case gl_texture_pixel_format::rg8_ui_nor:
			break;
		case gl_texture_pixel_format::rg8_i_nor:
			break;
		case gl_texture_pixel_format::rg16_ui_nor:
			break;
		case gl_texture_pixel_format::rg16_i_nor:
			break;
		case gl_texture_pixel_format::r3_g3_b2_ui_nor:
			break;
		case gl_texture_pixel_format::rgb4_ui_nor:
			break;
		case gl_texture_pixel_format::rgb5_ui_nor:
			break;
		case gl_texture_pixel_format::rgb8_ui_nor:
			break;
		case gl_texture_pixel_format::rgb8_i_nor:
			break;
		case gl_texture_pixel_format::rgb10_ui_nor:
			break;
		case gl_texture_pixel_format::rgb12_ui_nor:
			break;
		case gl_texture_pixel_format::rgb16_i_nor:
			break;
		case gl_texture_pixel_format::rgba2_ui_nor:
			break;
		case gl_texture_pixel_format::rgba4_ui_nor:
			break;
		case gl_texture_pixel_format::rgb5_a1_ui_nor:
			break;
		case gl_texture_pixel_format::rgba8_ui_nor:
			break;
		case gl_texture_pixel_format::rgba8_i_nor:
			break;
		case gl_texture_pixel_format::rgb10_a2_ui_nor:
			break;
		case gl_texture_pixel_format::rgb10_a2_ui:
			break;
		case gl_texture_pixel_format::rgba12_ui_nor:
			break;
		case gl_texture_pixel_format::rgba16_ui_nor:
			break;
		case gl_texture_pixel_format::srgb8_ui_nor:
			break;
		case gl_texture_pixel_format::srgb8_a8_ui_nor:
			break;
		case gl_texture_pixel_format::r16_f:
			break;
		case gl_texture_pixel_format::rg16_f:
			break;
		case gl_texture_pixel_format::rgb16_f:
			break;
		case gl_texture_pixel_format::rgba16_f:
			break;
		case gl_texture_pixel_format::r32_f:
			break;
		case gl_texture_pixel_format::rg32_f:
			break;
		case gl_texture_pixel_format::rgb32_f:
			break;
		case gl_texture_pixel_format::rgba32_f:
			break;
		case gl_texture_pixel_format::r11_g11_b10_f:
			break;
		case gl_texture_pixel_format::rgb9_e5:
			break;
		case gl_texture_pixel_format::r8_i:
			break;
		case gl_texture_pixel_format::r8_ui:
			break;
		case gl_texture_pixel_format::r16_i:
			break;
		case gl_texture_pixel_format::r16_ui:
			break;
		case gl_texture_pixel_format::r32_i:
			break;
		case gl_texture_pixel_format::r32_ui:
			break;
		case gl_texture_pixel_format::rg8_i:
			break;
		case gl_texture_pixel_format::rg8_ui:
			break;
		case gl_texture_pixel_format::rg16_i:
			break;
		case gl_texture_pixel_format::rg16_ui:
			break;
		case gl_texture_pixel_format::rg32_i:
			break;
		case gl_texture_pixel_format::rg32_ui:
			break;
		case gl_texture_pixel_format::rgb8_i:
			break;
		case gl_texture_pixel_format::rgb8_ui:
			break;
		case gl_texture_pixel_format::rgb16_i:
			break;
		case gl_texture_pixel_format::rgb16_ui:
			break;
		case gl_texture_pixel_format::rgb32_i:
			break;
		case gl_texture_pixel_format::rgb32_ui:
			break;
		case gl_texture_pixel_format::rgba8_i:
			break;
		case gl_texture_pixel_format::rgba8_ui:
			break;
		case gl_texture_pixel_format::rgba16_i:
			break;
		case gl_texture_pixel_format::rgba16_ui:
			break;
		case gl_texture_pixel_format::rgba32_i:
			break;
		case gl_texture_pixel_format::rgba32_ui:
			break;
		case gl_texture_pixel_format::COMPRESSED_RED:
			break;
		case gl_texture_pixel_format::COMPRESSED_RG:
			break;
		case gl_texture_pixel_format::COMPRESSED_RGB:
			break;
		case gl_texture_pixel_format::COMPRESSED_RGBA:
			break;
		case gl_texture_pixel_format::COMPRESSED_SRGB:
			break;
		case gl_texture_pixel_format::COMPRESSED_SRGB_ALPHA:
			break;
		case gl_texture_pixel_format::COMPRESSED_RED_RGTC1:
			break;
		case gl_texture_pixel_format::COMPRESSED_SIGNED_RED_RGTC1:
			break;
		case gl_texture_pixel_format::COMPRESSED_RG_RGTC2:
			break;
		case gl_texture_pixel_format::COMPRESSED_SIGNED_RG_RGTC2:
			break;
		case gl_texture_pixel_format::COMPRESSED_RGBA_BPTC_UNORM:
			break;
		case gl_texture_pixel_format::COMPRESSED_SRGB_ALPHA_BPTC_UNORM:
			break;
		case gl_texture_pixel_format::COMPRESSED_RGB_BPTC_SIGNED_FLOAT:
			break;
		case gl_texture_pixel_format::COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT:
			break;
		default:
			break;
		}
	}
};



#endif