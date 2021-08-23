#ifndef H_GLSL_CLASS
#define H_GLSL_CLASS

#include "public/_glew.h"
#include "public/glm.h"
#include "public/stl.h"

#include "graphics/sampler/gl_sampler.h"
#include "graphics/texture/gl_texture.h"

class glsl_t
{
	//virtual std::string get_t_token() = 0;

};

/*
* transparent_t
* include [scalars] [vectors] [matrices]
*/

class glsl_transparent_t : public glsl_t
{
public:
	virtual const glsl_transparent_t_meta& meta() const = 0;
	virtual const std::uint8_t* data() const = 0;
};

struct glsl_transparent_t_meta
{
	std::uint32_t components_count;
	std::uint32_t component_type_size;
	std::string component_type_name;
	std::uint32_t component_type_gl_enum;
	std::uint32_t type_size;
	std::string semantic_name;

	glsl_transparent_t_meta(
		std::uint32_t _components_count, 
		std::uint32_t _component_type_size,
		std::uint32_t _component_type_gl_enum,
		std::uint32_t _type_size,
		std::string _semantic_name) :
		components_count(_components_count),
		component_type_size(_component_type_size),
		component_type_gl_enum(_component_type_gl_enum),
		type_size(_type_size),
		semantic_name(_semantic_name)
	{}
};

#define DEFINE_GLSL_TRANSPARENT_T(GLSL_T_NAME, GLSL_T_SEMANTIC_NAME, GLSL_T_SEMANTIC_NAME_STR)\
class glsl_##GLSL_T_NAME final : public glsl_transparent_t\
{\
public:\
	glsl_##GLSL_T_NAME() = default;\
	explicit glsl_##GLSL_T_NAME(const glm::GLSL_T_SEMANTIC_NAME& value){}\
	~glsl_##GLSL_T_NAME() = default;\
public:\
	glm::GLSL_T_SEMANTIC_NAME client_value;\
private:\
	static const glsl_transparent_t_meta _meta;\
public:\
	const glsl_transparent_t_meta& meta() const override { return _meta; };\
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(&client_value); };\
};\
const glsl_transparent_t_meta glsl_##GLSL_T_NAME::_meta(glm::##GLSL_T_SEMANTIC_NAME::length(), sizeof(glm::##GLSL_T_SEMANTIC_NAME::value_type), to_enum<glm::GLSL_T_SEMANTIC_NAME::value_type>(), sizeof(glm::dvec3), GLSL_T_SEMANTIC_NAME_STR);\


template<typename t>
constexpr std::uint32_t to_enum() { return 0; }
template<>
constexpr std::uint32_t to_enum<glm::vec1::value_type>() { return GL_FLOAT; }
template<>
constexpr std::uint32_t to_enum<glm::dvec1::value_type>() { return GL_DOUBLE; }
template<>
constexpr std::uint32_t to_enum<glm::uvec1::value_type>() { return GL_UNSIGNED_INT; }
template<>
constexpr std::uint32_t to_enum<glm::ivec1::value_type>() { return GL_INT; }

// float scalar && vectors && matrices
DEFINE_GLSL_TRANSPARENT_T(float, vec1, "float")
DEFINE_GLSL_TRANSPARENT_T(vec2, vec2, "vec2")
DEFINE_GLSL_TRANSPARENT_T(vec3, vec3, "vec3")
DEFINE_GLSL_TRANSPARENT_T(vec4, vec4, "vec4")
DEFINE_GLSL_TRANSPARENT_T(mat2, mat2, "mat2")
DEFINE_GLSL_TRANSPARENT_T(mat2x3, mat2x3, "mat2x3")
DEFINE_GLSL_TRANSPARENT_T(mat2x4, mat2x4, "mat2x4")
DEFINE_GLSL_TRANSPARENT_T(mat3, mat3, "mat3")
DEFINE_GLSL_TRANSPARENT_T(mat3x2, mat3x2, "mat3x2")
DEFINE_GLSL_TRANSPARENT_T(mat3x4, mat3x4, "mat3x4")
DEFINE_GLSL_TRANSPARENT_T(mat4, mat4, "mat4")
DEFINE_GLSL_TRANSPARENT_T(mat4x2, mat4x2, "mat4x2")
DEFINE_GLSL_TRANSPARENT_T(mat4x3, mat4x3, "mat4x3")
// double scalar && vectors && matrices
DEFINE_GLSL_TRANSPARENT_T(double, dvec1, "double")
DEFINE_GLSL_TRANSPARENT_T(dvec2, dvec2, "dvec2")
DEFINE_GLSL_TRANSPARENT_T(dvec3, dvec3, "dvec3")
DEFINE_GLSL_TRANSPARENT_T(dvec4, dvec4, "dvec4")
DEFINE_GLSL_TRANSPARENT_T(dmat2, dmat2, "dmat2")
DEFINE_GLSL_TRANSPARENT_T(dmat2x3, dmat2x3, "dmat2x3")
DEFINE_GLSL_TRANSPARENT_T(dmat2x4, dmat2x4, "dmat2x4")
DEFINE_GLSL_TRANSPARENT_T(dmat3, dmat3, "dmat3")
DEFINE_GLSL_TRANSPARENT_T(dmat3x2, dmat3x2, "dmat3x2")
DEFINE_GLSL_TRANSPARENT_T(dmat3x4, dmat3x4, "dmat3x4")
DEFINE_GLSL_TRANSPARENT_T(dmat4, dmat4, "dmat4")
DEFINE_GLSL_TRANSPARENT_T(dmat4x2, dmat4x2, "dmat4x2")
DEFINE_GLSL_TRANSPARENT_T(dmat4x3, dmat4x3, "dmat4x3")
// int scalar && vectors
DEFINE_GLSL_TRANSPARENT_T(int, ivec1, "int")
DEFINE_GLSL_TRANSPARENT_T(ivec2, ivec2, "ivec2")
DEFINE_GLSL_TRANSPARENT_T(ivec3, ivec3, "ivec3")
DEFINE_GLSL_TRANSPARENT_T(ivec4, ivec4, "ivec4")
// uint scalar && vectors
DEFINE_GLSL_TRANSPARENT_T(uint, uvec1, "uint")
DEFINE_GLSL_TRANSPARENT_T(uvec2, uvec2, "uvec2")
DEFINE_GLSL_TRANSPARENT_T(uvec3, uvec3, "uvec3")
DEFINE_GLSL_TRANSPARENT_T(uvec4, uvec4, "uvec4")



//class glsl_dvec3 final : public glsl_transparent_t
//{
//public:
//	glsl_dvec3() = delete;
//	explicit glsl_dvec3(const glm::dvec3& value) {}
//	~glsl_dvec3() = default;
//public:
//	glm::dvec3 client_value;
//private:
//	static const glsl_transparent_t_meta _meta;
//public:
//	const glsl_transparent_t_meta& meta() const override { return _meta; };
//	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(&client_value); };
//};
//const glsl_transparent_t_meta glsl_dvec3::_meta(glm::dvec3::length(), sizeof(glm::dvec3::value_type), to_enum<glm::dvec3::value_type>(), sizeof(glm::dvec3), "dvec3");


/*
* glsl opaque types
* which can only be used as global uniform
* 
* include [sampler][image][atomic_uint]
*
*/

class glsl_opaque_t : public glsl_t {
};

class glsl_sampler_t : public glsl_opaque_t 
{
};

/*
* definitions of sampler_ts
* 
*/
class glsl_sampler2D : public glsl_sampler_t
{
public:

	explicit glsl_sampler2D()
	{}


public:

	void associate(std::shared_ptr<gl_texture_2d> texture_2d, int sampler_options)
	{
		_texture_2d = texture_2d;
	}

private:

	std::shared_ptr<gl_texture_2d> _texture_2d;

	std::shared_ptr<gl_sampler> _sampler;

};

class glsl_sampler2DArray : public glsl_sampler_t
{
public: /** constructor / desctructor  */

	explicit glsl_sampler2DArray(
		const gl_texture_2d_array_descriptor& texture_2d_array_descriptor,
		const gl_sampler_descriptor& sampler_descriptor
	) : _texture_2d_array(std::make_unique<gl_texture_2d_array>(texture_2d_array_descriptor)),
		_sampler(std::make_shared<gl_sampler>(sampler_descriptor))
	{}

	explicit glsl_sampler2DArray(
		const gl_texture_2d_array_descriptor& texture_2d_array_descriptor
	) : _texture_2d_array(std::make_unique<gl_texture_2d_array>(texture_2d_array_descriptor)),
		_sampler(nullptr)
	{}

	explicit glsl_sampler2DArray(std::shared_ptr<gl_texture_2d_array> texture, std::shared_ptr<gl_sampler> sampler)
	{}

	glsl_sampler2DArray() = delete;

	virtual ~glsl_sampler2DArray() = default;

public: /** implement functions */

private:

	std::unique_ptr<gl_texture_2d_array> _texture_2d_array;

	std::shared_ptr<gl_sampler> _sampler;

public:

	gl_texture_2d_array& texture() { return *_texture_2d_array; }

};

#define DEFINE_GLSL_SAMPLER_T(GLSL_SAMPLER_T_SEMANTIC_NAME)\
class glsl_##GLSL_SAMPLER_T_SEMANTIC_NAME : public glsl_sampler_t\
{\
\
};\

DEFINE_GLSL_SAMPLER_T(sampler1D)
DEFINE_GLSL_SAMPLER_T(sampler1DArray)
DEFINE_GLSL_SAMPLER_T(sampler2D)
DEFINE_GLSL_SAMPLER_T(sampler2DArray)
DEFINE_GLSL_SAMPLER_T(sampler2DRect)
DEFINE_GLSL_SAMPLER_T(sampler2DMS)
DEFINE_GLSL_SAMPLER_T(sampler2DMSArray)
DEFINE_GLSL_SAMPLER_T(sampler3D)
DEFINE_GLSL_SAMPLER_T(samplerCube)
DEFINE_GLSL_SAMPLER_T(samplerCubeArray)
DEFINE_GLSL_SAMPLER_T(samplerBuffer)
DEFINE_GLSL_SAMPLER_T(sampler1DShadow)
DEFINE_GLSL_SAMPLER_T(sampler2DShadow)
DEFINE_GLSL_SAMPLER_T(sampler2DRectShadow)
DEFINE_GLSL_SAMPLER_T(sampler1DArrayShadow)
DEFINE_GLSL_SAMPLER_T(sampler2DArrayShadow)
DEFINE_GLSL_SAMPLER_T(samplerCubeShadow)
DEFINE_GLSL_SAMPLER_T(samplerCubeArrayShadow)
DEFINE_GLSL_SAMPLER_T(isampler1D)
DEFINE_GLSL_SAMPLER_T(isampler1DArray)
DEFINE_GLSL_SAMPLER_T(isampler2D)
DEFINE_GLSL_SAMPLER_T(isampler2DArray)
DEFINE_GLSL_SAMPLER_T(isampler2DRect)
DEFINE_GLSL_SAMPLER_T(isampler2DMS)
DEFINE_GLSL_SAMPLER_T(isampler2DMSArray)
DEFINE_GLSL_SAMPLER_T(isampler3D)
DEFINE_GLSL_SAMPLER_T(isamplerCube)
DEFINE_GLSL_SAMPLER_T(isamplerCubeArray)
DEFINE_GLSL_SAMPLER_T(isamplerBuffer)
DEFINE_GLSL_SAMPLER_T(isampler1DShadow)
DEFINE_GLSL_SAMPLER_T(isampler2DShadow)
DEFINE_GLSL_SAMPLER_T(isampler2DRectShadow)
DEFINE_GLSL_SAMPLER_T(isampler1DArrayShadow)
DEFINE_GLSL_SAMPLER_T(isampler2DArrayShadow)
DEFINE_GLSL_SAMPLER_T(isamplerCubeShadow)
DEFINE_GLSL_SAMPLER_T(isamplerCubeArrayShadow)
DEFINE_GLSL_SAMPLER_T(usampler1D)
DEFINE_GLSL_SAMPLER_T(usampler1DArray)
DEFINE_GLSL_SAMPLER_T(usampler2D)
DEFINE_GLSL_SAMPLER_T(usampler2DArray)
DEFINE_GLSL_SAMPLER_T(usampler2DRect)
DEFINE_GLSL_SAMPLER_T(usampler2DMS)
DEFINE_GLSL_SAMPLER_T(usampler2DMSArray)
DEFINE_GLSL_SAMPLER_T(usampler3D)
DEFINE_GLSL_SAMPLER_T(usamplerCube)
DEFINE_GLSL_SAMPLER_T(usamplerCubeArray)
DEFINE_GLSL_SAMPLER_T(usamplerBuffer)
DEFINE_GLSL_SAMPLER_T(usampler1DShadow)
DEFINE_GLSL_SAMPLER_T(usampler2DShadow)
DEFINE_GLSL_SAMPLER_T(usampler2DRectShadow)
DEFINE_GLSL_SAMPLER_T(usampler1DArrayShadow)
DEFINE_GLSL_SAMPLER_T(usampler2DArrayShadow)
DEFINE_GLSL_SAMPLER_T(usamplerCubeShadow)
DEFINE_GLSL_SAMPLER_T(usamplerCubeArrayShadow)

enum class glsl_image_format_layout_qualifier
{
	// r16f, r32f
	// rg16f, rg32f
	// rgb16f, rgb32f
	// rgba16f, rgba32f

	// rgba8, rgba16
	// r11f_g11f_b10f
	// rgb10_a2, rgb10_a2ui
	// rg8, rg16
	// r8, r16

	// rgba{8,16,32}i
	// rg{8,16,32}i
	// r{8,16,32}
	// rgba{32,16,8}ui
	// rg{32,16,8} ui
	// r{32,16,8} ui
	// rgba{16,8}_snorm
	// rg{16,8}_snorm
	// r{16,8}_snorm
};

enum class gl_image_access_mode : GLenum
{
	READ_ONLY = GL_READ_ONLY,
	WRITE_ONLY = GL_WRITE_ONLY,
	READ_WRITE = GL_READ_WRITE
};

enum class gl_image_format : GLenum
{
	R32F = GL_R32F, // [std::float_t] x 1
	RG32F = GL_RG32F, // [std::float_t] x 2
	RGBA32F = GL_RGBA32F,// [std::float_t] x 4
	R32UI = GL_R32UI,
	RG32UI = GL_RG32UI,
	RGBA32UI = GL_RGBA32UI,
	R32I = GL_R32I,
	RG32I = GL_RG32I,
	RGBA32I = GL_RGBA32I,
	
#ifdef GENERAL
	R11F_G11F_B10F = GL_R11F_G11F_B10F,

	RGBA16F = GL_RGBA16F,
	RG16F = GL_RG16F,
	R16F	 = GL_R16F,
	RGBA16UI = GL_RGBA16UI,
	RGB10_A2UI = GL_RGB10_A2UI,
	RGBA8UI = GL_RGBA8UI,
	RG16UI = GL_RG16UI,
	RG8UI = GL_RG8UI,
	R16UI = GL_R16UI,
	R8UI = GL_R8UI,
	RGBA16I = GL_RGBA16I,
	RGBA8I = GL_RGBA8I,
	RG16I = GL_RG16I,
	RG8I = GL_RG8I,
	R16I	= GL_R16I,
	R8I = GL_R8I,
	RGBA16 = GL_RGBA16,
	RGB10_A2 = GL_RGB10_A2,
	RGBA8	= GL_RGBA8,
	RG16 = GL_RG16,
	RG8 = GL_RG8,
	R16 = GL_R16,
	R8 = GL_R8,
	RGBA16_SNORM	= GL_RGBA16_SNORM,
	RGBA8_SNORM = GL_RGBA8_SNORM,
	RG16_SNORM	= GL_RG16_SNORM,
	RG8_SNORM = GL_RG8_SNORM,
	R16_SNORM = GL_R16_SNORM,
	R8_SNORM = GL_R8_SNORM
#endif
};

std::string transfer_to_image_format_token(gl_image_format format)
{
	switch (format)
	{
	case gl_image_format::stencil_index:
		break;
	case gl_image_format::depth_component:
		break;
	case gl_image_format::depth_stencil:
		break;
	case gl_image_format::r:
		break;
	case gl_image_format::rg:
		break;
	case gl_image_format::rgb:
		break;
	case gl_image_format::rgba:
		break;
	case gl_image_format::compressed_r:
		break;
	case gl_image_format::compressed_rg:
		break;
	case gl_image_format::compressed_rgb:
		break;
	case gl_image_format::compressed_rgba:
		break;
	case gl_image_format::compressed_srgb:
		break;
	case gl_image_format::compressed_srgb_alpha:
		break;
	case gl_image_format::NOR_UI_R8:
		break;
	case gl_image_format::NOR_I_R8:
		break;
	case gl_image_format::NOR_UI_R16:
		break;
	case gl_image_format::NOR_I_R16:
		break;
	case gl_image_format::NOR_UI_RG8:
		break;
	case gl_image_format::NOR_I_RG8:
		break;
	case gl_image_format::NOR_UI_RG16:
		break;
	case gl_image_format::NOR_I_RG16:
		break;
	case gl_image_format::NOR_UI_R3_G3_B2:
		break;
	case gl_image_format::NOR_UI_RGB4:
		break;
	case gl_image_format::NOR_UI_RGB5:
		break;
	case gl_image_format::NOR_UI_R5_G6_B5:
		break;
	case gl_image_format::NOR_UI_RGB8:
		break;
	case gl_image_format::NOR_I_RGB8:
		break;
	case gl_image_format::NOR_UI_RGB10:
		break;
	case gl_image_format::NOR_UI_RGB12:
		break;
	case gl_image_format::NOR_UI_RGB16:
		break;
	case gl_image_format::NOR_I_RGB16:
		break;
	case gl_image_format::NOR_UI_RGBA2:
		break;
	case gl_image_format::NOR_UI_RGBA4:
		break;
	case gl_image_format::NOR_UI_RGB5_A1:
		break;
	case gl_image_format::NOR_UI_RGBA8:
		break;
	case gl_image_format::NOR_I_RGBA8:
		break;
	case gl_image_format::NOR_UI_RGB10_A2:
		break;
	case gl_image_format::UI_RGB10_A2:
		break;
	case gl_image_format::NOR_UI_RGBA12:
		break;
	case gl_image_format::NOR_UI_RGBA16:
		break;
	case gl_image_format::NOR_I_RGBA16:
		break;
	case gl_image_format::NOR_UI_SRGB8:
		break;
	case gl_image_format::NOR_UI_SRGB8_ALPHA8:
		break;
	case gl_image_format::F_R32:
		break;
	case gl_image_format::F_RG32:
		break;
	case gl_image_format::F_RGB32:
		break;
	case gl_image_format::F_RGBA32:
		break;
	case gl_image_format::F_R11_G11_B10:
		break;
	case gl_image_format::rgb9_e5:
		break;
	case gl_image_format::I_R32:
		break;
	case gl_image_format::I_RG32:
		break;
	case gl_image_format::I_RGB32:
		break;
	case gl_image_format::I_RGBA32:
		break;
	case gl_image_format::UI_R32:
		break;
	case gl_image_format::UI_RG32:
		break;
	case gl_image_format::UI_RGB32:
		break;
	case gl_image_format::UI_RGBA32:
		break;
	default:
		break;
	}
}

struct glsl_image_layout_qualifier
{


};

enum glsl_image_memory_qualifier
{
	COHERENT,
	VOLATILE,
	RESTRICT,
	READONLY,
	WRITEONLY
};

class glsl_image_t : public glsl_opaque_t
{
public:

	virtual const std::string& get_glsl_image_token() = 0;

protected:

	std::string _generate_glsl_image_token()
	{
		return "##layout## ##memory## uniform image2D input_image;";
	}

};

class glsl_image2D : public glsl_image_t
{

	glsl_image2D()
	{
		_glsl_image_token = _generate_glsl_image_token();
	}

public:

	const std::string& get_glsl_image_token() override
	{
		return _glsl_image_token;
	}

private:

	std::string _glsl_image_token;
};

class glsl_image2DArray : public glsl_image_t
{
public:

	explicit glsl_image2DArray(const std::shared_ptr<gl_texture_2d_array> texture_2d_array, gl_image_access_mode access_mode)
	{
		glBindImageTexture(GL_TEXTURE0,
			texture_2d_array->get_handle(),
			0,
			false, 0,
			static_cast<GLenum>(access_mode),
			static_cast<GLenum>(texture_2d_array->get_descriptor().pixel_format)
		);
	}

	~glsl_image2DArray();

public:


};


#define DEFINE_GLSL_IMAGE_T(GLSL_IMAGE_T_SEMANTIC_NAME)\
class glsl_##GLSL_IMAGE_T_SEMANTIC_NAME : public glsl_image_t\
{\
\
};\

DEFINE_GLSL_IMAGE_T(image1D)
DEFINE_GLSL_IMAGE_T(image1DArray)
DEFINE_GLSL_IMAGE_T(image2D)
DEFINE_GLSL_IMAGE_T(image2DArray)
DEFINE_GLSL_IMAGE_T(image2DRect)
DEFINE_GLSL_IMAGE_T(image2DMS)
DEFINE_GLSL_IMAGE_T(image2DMSArray)
DEFINE_GLSL_IMAGE_T(image3D)
DEFINE_GLSL_IMAGE_T(imageCube)
DEFINE_GLSL_IMAGE_T(imageCubeArray)
DEFINE_GLSL_IMAGE_T(imageBuffer)
DEFINE_GLSL_IMAGE_T(iimage1D)
DEFINE_GLSL_IMAGE_T(iimage1DArray)
DEFINE_GLSL_IMAGE_T(iimage2D)
DEFINE_GLSL_IMAGE_T(iimage2DArray)
DEFINE_GLSL_IMAGE_T(iimage2DRect)
DEFINE_GLSL_IMAGE_T(iimage2DMS)
DEFINE_GLSL_IMAGE_T(iimage2DMSArray)
DEFINE_GLSL_IMAGE_T(iimage3D)
DEFINE_GLSL_IMAGE_T(iimageCube)
DEFINE_GLSL_IMAGE_T(iimageCubeArray)
DEFINE_GLSL_IMAGE_T(iimageBuffer)
DEFINE_GLSL_IMAGE_T(uimage1D)
DEFINE_GLSL_IMAGE_T(uimage1DArray)
DEFINE_GLSL_IMAGE_T(uimage2D)
DEFINE_GLSL_IMAGE_T(uimage2DArray)
DEFINE_GLSL_IMAGE_T(uimage2DRect)
DEFINE_GLSL_IMAGE_T(uimage2DMS)
DEFINE_GLSL_IMAGE_T(uimage2DMSArray)
DEFINE_GLSL_IMAGE_T(uimage3D)
DEFINE_GLSL_IMAGE_T(uimageCube)
DEFINE_GLSL_IMAGE_T(uimageCubeArray)
DEFINE_GLSL_IMAGE_T(uimageBuffer)

/*
* layout(binding = 0, offset = 0) uniform atomic_uint;
* only declare in global scope as a uniform
* 
*/
class glsl_atomic_uint : public glsl_opaque_t {};



/*
* All of interface blocks can not include any opaque types(only transparent types)
* glsl_scalar
* glsl_vector
* glsl_matrix
*/
#define DEFINE_UNIFORM_INTERFACE_BLOCK
#define DEFINE_IN_INTERFACE_BLOCK
#define DEFINE_OUT_INTERFACE_BLOCK
#define DEFINE_BUFFER_INTERFACE_BLOCK 

class glsl_interface_block
{
public:

	glsl_interface_block()
	{}

private:
	// declaration spec + var name
	std::vector<std::pair<const glsl_transparent_t*, std::string>> _cached_items;

};

class glsl_in_block
{};
class glsl_out_block
{};
class glsl_uniform_block
{
public:
	
	glsl_uniform_interface_block() {}

private:

	

};
class glsl_shader_storage_block
{};

class gl_pipeline_global_parameters
{
private:
	
	std::vector<glsl_uniform_block*> _uniform_blocks;
	
	std::vector<glsl_shader_storage_block*> _shader_storage_blocks;

};

class gl_pipeline_parameters
{
	glsl_in_block* _in_block;

	glsl_out_block* _out_block;
};

#define DEFINE_UNIFORM_INTERFACE_BEGIN(UNIFORM_INTERFACE_BLOCK_NAME)\
struct UNIFORM_INTERFACE_BLOCK_NAME {\

#define DEFINE_UNIFORM_INTERFACE_END(UNIFORM_INTERFACE_BLOCK_INSTANCE_NAME)\
} UNIFORM_INTERFACE_BLOCK_INSTANCE_NAME;\
const std::uint8_t* block_ptr()\
{\
	return reinterpret_cast<const std::uint8_t*>(&UNIFORM_INTERFACE_BLOCK_INSTANCE_NAME);\
}\
const std::uint64_t block_size()\
{\
	return sizeof UNIFORM_INTERFACE_BLOCK_INSTANCE_NAME;\
}\

#define DEFINE_UNIFORM_INTERFACE_ARRAY_END(UNIFORM_INTERFACE_BLOCK_INSTANCE_NAME, ARRAY_SIZE)\
} UNIFORM_INTERFACE_BLOCK_INSTANCE_NAME[ARRAY_SIZE];\
const std::uint8_t* block_ptr()\
{\
	return reinterpret_cast<const std::uint8_t*>(&UNIFORM_INTERFACE_BLOCK_INSTANCE_NAME);\
}\
const std::uint64_t block_size()\
{\
	return sizeof UNIFORM_INTERFACE_BLOCK_INSTANCE_NAME * ARRAY_SIZE;\
}\

#define DEFINE_UNIFORM_INTERFACE_ITEM(GLSL_TRANSPARENT_T, ITEM_NAME)\
glsl_##GLSL_TRANSPARENT_T ITEM_NAME\

#define DEFINE_UNIFORM_INTERFACE_ITEM_ARRAY(GLSL_TRANSPARENT_T, ITEM_NAME, ARRAY_SIZE)\
glsl_##GLSL_TRANSPARENT_T ITEM_NAME[ARRAY_SIZE] \


class PPUniformBlock : public glsl_uniform_block
{

public:
	void test()
	{
		matrices[0].postion;
		
	}

public:

	DEFINE_UNIFORM_INTERFACE_BEGIN(Matrix)
	DEFINE_UNIFORM_INTERFACE_ITEM_ARRAY(vec4, color, 10);
	DEFINE_UNIFORM_INTERFACE_ITEM(vec4, postion);
	DEFINE_UNIFORM_INTERFACE_ITEM(mat4x3, matrix, 2);
	DEFINE_UNIFORM_INTERFACE_ARRAY_END(matrices, 10)

};







#endif
