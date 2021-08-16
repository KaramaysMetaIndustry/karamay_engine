#ifndef H_GLSL_CLASS
#define H_GLSL_CLASS

#include "public/_glew.h"
#include "public/glm.h"
#include "public/stl.h"

#include "graphics/sampler/gl_sampler.h"
#include "graphics/texture/gl_texture.h"

class glsl_t
{};

class glsl_cacheable
{
	virtual std::int64_t size() const;
	virtual std::int64_t offset() const;
};

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
DEFINE_GLSL_TRANSPARENT_T(int, ivec1, "int")
DEFINE_GLSL_TRANSPARENT_T(ivec2, ivec2, "ivec2")
DEFINE_GLSL_TRANSPARENT_T(ivec3, ivec3, "ivec3")
DEFINE_GLSL_TRANSPARENT_T(ivec4, ivec4, "ivec4")
DEFINE_GLSL_TRANSPARENT_T(uint, uvec1, "uint")
DEFINE_GLSL_TRANSPARENT_T(uvec2, uvec2, "uvec2")
DEFINE_GLSL_TRANSPARENT_T(uvec3, uvec3, "uvec3")
DEFINE_GLSL_TRANSPARENT_T(uvec4, uvec4, "uvec4")


class gl_uniform_block_item
{

};

class gl_uniform_block
{
	static std::vector<gl_uniform_block_item*> items;

public:

	virtual void bind() = 0;

	virtual void unbind() = 0;

};

class gl_shader_storage_block_item
{

};

class gl_shader_storage_block
{
	std::vector<gl_shader_storage_block_item*> items;
};


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

class glsl_opaque_t_meta
{
	std::string semantic_t_name;
};

class glsl_opaque_t : public glsl_t {
	virtual const glsl_opaque_t_meta& meta() const = 0;
	virtual void bind() = 0;
	virtual void unbind() = 0;
	virtual void launch() = 0;
};


/// <summary>
/// samplers
/// </summary>

class glsl_sampler_t : public glsl_opaque_t 
{
	std::string semantic_instance_name;
};

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

public:

	void bind() override
	{}

	void unbind() override
	{
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

	const glsl_opaque_t_meta& meta() const override { return _meta; }
	
	void bind() override
	{

	}
	
	void unbind() override
	{

	}
	
	void launch() override
	{
		
	}

private:

	std::unique_ptr<gl_texture_2d_array> _texture_2d_array;

	std::shared_ptr<gl_sampler> _sampler;

public:

	gl_texture_2d_array& texture() { return *_texture_2d_array; }

	static glsl_opaque_t_meta _meta;

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

/// <summary>
///  images
/// </summary>

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
	read_only,
	write_only,
	read_and_write
};

class glsl_image_t : public glsl_opaque_t
{

};

class glsl_image2D : public glsl_image_t
{};

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

struct gl_program_real_time_struct_maps
{

};
struct ImmdStruct {
	
	std::array<glsl_sampler2D, 5> AlbedoMap;
	std::array<glsl_sampler2DArray, 5> DisplacementMaps;

	glsl_image1D normals;

} Parameters[10];

void test()
{
	sizeof ImmdStruct * 10;
	Parameters->AlbedoMap[0];
	Parameters->AlbedoMap[1];
	Parameters->AlbedoMap[2];
	Parameters->AlbedoMap[5];
}

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

class glsl_atomic_uint : public glsl_opaque_t {};


void tes()
{
}

#endif
