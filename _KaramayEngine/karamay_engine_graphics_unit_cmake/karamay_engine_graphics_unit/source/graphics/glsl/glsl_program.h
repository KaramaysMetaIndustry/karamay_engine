#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H

#include "glsl_class.h"
#include "glsl_shader.h"

struct glsl_graphics_pipeline_parameters
{
	std::vector<std::shared_ptr<glsl_uniform_block_t>> uniform_blocks;
	std::vector<std::shared_ptr<glsl_shader_storage_block_t>> shader_storage_blocks;
	std::vector<std::shared_ptr<glsl_atomic_counter_t>> atomic_counters;
	std::vector<std::shared_ptr<glsl_sampler_t>> samplers;
	std::vector<std::shared_ptr<glsl_image_t>> images;
};

class glsl_graphics_pipeline_program final {
public:
	glsl_graphics_pipeline_program() = default;
	glsl_graphics_pipeline_program(glsl_vertex_shader* vs, glsl_fragment_shader* fs) :
		_vertex_shader(vs), _tessellation_shader(nullptr), _geometry_shader(nullptr), _fragment_shader(fs)
	{}
	glsl_graphics_pipeline_program(glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_fragment_shader* fs) :
		_vertex_shader(vs), _tessellation_shader(ts), _geometry_shader(nullptr), _fragment_shader(fs)
	{}
	glsl_graphics_pipeline_program(glsl_vertex_shader* vs, glsl_geometry_shader* gs, glsl_fragment_shader* fs) :
		_vertex_shader(vs), _tessellation_shader(nullptr), _geometry_shader(gs), _fragment_shader(fs)
	{}
	glsl_graphics_pipeline_program(glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_geometry_shader* gs, glsl_fragment_shader* fs) :
		_vertex_shader(vs), _tessellation_shader(ts), _geometry_shader(gs), _fragment_shader(fs)
	{}

	glsl_graphics_pipeline_program(const glsl_graphics_pipeline_program&) = delete;
	glsl_graphics_pipeline_program& operator=(const glsl_graphics_pipeline_program&) = delete;

	~glsl_graphics_pipeline_program() = default;

private:

	glsl_vertex_shader* _vertex_shader;
	glsl_tessellation_shader* _tessellation_shader;
	glsl_geometry_shader* _geometry_shader;
	glsl_fragment_shader* _fragment_shader;

	void _parse()
	{

	}

private:

	std::vector<glsl_sampler1D*> _sampler1Ds;
	std::vector<glsl_sampler1DArray*> _sampler1DArrays;
	std::vector<glsl_sampler2D*> _sampler2Ds;
	std::vector<glsl_sampler2DArray*> _sampler2DArrays;
	std::vector<glsl_samplerCube*> _samplerCubes;
	std::vector<glsl_samplerCubeArray*> _samplerCubeArrays;
	std::vector<glsl_sampler2DMS*> _sampler2DMSs;
	std::vector<glsl_sampler2DMSArray*> _sampler2DMSArrays;
	std::vector<glsl_sampler2DRect*> _sampler2DRects;
	std::vector<glsl_samplerBuffer*> _samplerBuffers;
	std::vector<glsl_sampler1DShadow*> _sampler1DShadows;
	std::vector<glsl_sampler1DArrayShadow*> _sampler1DArrayShadows;
	std::vector<glsl_sampler2DShadow*> _sampler2DShadows;
	std::vector<glsl_sampler2DArrayShadow*> _sampler2DArrayShadows;
	std::vector<glsl_samplerCubeShadow*> _samplerCubeShadows;
	std::vector<glsl_samplerCubeArrayShadow*> _samplerCubeArrayShadows;
	std::vector<glsl_sampler2DRectShadow*> _sampler2DRectShadows;

	std::vector<glsl_isampler1D*> _isampler1Ds;
	std::vector<glsl_isampler1DArray*> _isampler1DArrays;
	std::vector<glsl_isampler2D*> _isampler2Ds;
	std::vector<glsl_isampler2DArray*> _isampler2DArrays;
	std::vector<glsl_isampler2DMS*> _isampler2DMSs;
	std::vector<glsl_isampler2DMSArray*> _isampler2DMSArrays;
	std::vector<glsl_isamplerCube*> _isamplerCubes;
	std::vector<glsl_isamplerCubeArray*> _isamplerCubeArrays;
	std::vector<glsl_isampler2DRect*> _isampler2DRects;
	std::vector<glsl_isamplerBuffer*> _isamplerBuffers;

	std::vector<glsl_usampler1D*> _usampler1Ds;
	std::vector<glsl_usampler1DArray*> _usampler1DArrays;
	std::vector<glsl_usampler2D*> _usampler2Ds;
	std::vector<glsl_usampler2DArray*> _usampler2DArrays;
	std::vector<glsl_usampler2DMS*> _usampler2DMSs;
	std::vector<glsl_usampler2DMSArray*> _usampler2DMSArrays;
	std::vector<glsl_usamplerCube*> _usamplerCubes;
	std::vector<glsl_usamplerCubeArray*> _usamplerCubeArrays;
	std::vector<glsl_usampler2DRect*> _usampler2DRects;
	std::vector<glsl_usamplerBuffer*> _usamplerBuffers;

public:

	glsl_sampler1D* sampler1D(const std::string& name)
	{
		return nullptr;
	}
	glsl_sampler1DArray* sampler1DArray(const std::string& name) {}
	glsl_sampler2D* sampler2D(const std::string& name) { return nullptr; }
	glsl_sampler2DArray* sampler2DArray(const std::string& name) {}
	glsl_sampler2DMS* sampler2DMS(const std::string& name) {}
	glsl_sampler2DMSArray* sampler2DMSArray(const std::string& name) {}
	glsl_samplerCube* samplerCube(const std::string& name) {}
	glsl_samplerCubeArray* samplerCubeArray(const std::string& name) {}
	glsl_sampler2DRect* sampler2DRect(const std::string& name) {}
	glsl_samplerBuffer* samplerBuffer(const std::string& name) {}

	glsl_isampler1D* isampler1D(const std::string& name)
	{
		return nullptr;
	}
	glsl_isampler1DArray* isampler1DArray(const std::string& name) {}
	glsl_isampler2D* isampler2D(const std::string& name) {}
	glsl_isampler2DArray* isampler2DArray(const std::string& name) {}
	glsl_isampler2DMS* isampler2DMS(const std::string& name) {}
	glsl_isampler2DMSArray* isampler2DMSArray(const std::string& name) {}
	glsl_isamplerCube* isamplerCube(const std::string& name) {}
	glsl_isamplerCubeArray* isamplerCubeArray(const std::string& name) {}
	glsl_isampler2DRect* isampler2DRect(const std::string& name) {}
	glsl_isamplerBuffer* isamplerBuffer(const std::string& name) {}

	glsl_usampler1D* usampler1D(const std::string& name)
	{
		return nullptr;
	}
	glsl_usampler1DArray* usampler1DArray(const std::string& name) {}
	glsl_usampler2D* usampler2D(const std::string& name) {}
	glsl_usampler2DArray* usampler2DArray(const std::string& name) {}
	glsl_usampler2DMS* usampler2DMS(const std::string& name) {}
	glsl_usampler2DMSArray* usampler2DMSArray(const std::string& name) {}
	glsl_usamplerCube* usamplerCube(const std::string& name) {}
	glsl_usamplerCubeArray* usamplerCubeArray(const std::string& name) {}
	glsl_usampler2DRect* usampler2DRect(const std::string& name) {}
	glsl_usamplerBuffer* usamplerBuffer(const std::string& name) {}

private:

	std::vector<glsl_image1D*> _image1Ds;
	std::vector<glsl_image1DArray*> _image1DArrays;
	std::vector<glsl_image2D*> _image2Ds;
	std::vector<glsl_image2DArray*> _image2DArrays;
	std::vector<glsl_imageCube*> _imageCubes;
	std::vector<glsl_imageCubeArray*> _imageCubeArrays;
	std::vector<glsl_image2DMS*> _image2DMSs;
	std::vector<glsl_image2DMSArray*> _image2DMSArrays;
	std::vector<glsl_image2DRect*> _image2DRects;
	std::vector<glsl_image3D*> _image3Ds;
	std::vector<glsl_imageBuffer*> _imageBuffers;

	std::vector<glsl_iimage1D*> _iimage1Ds;
	std::vector<glsl_iimage1DArray*> _iimage1DArrays;
	std::vector<glsl_iimage2D*> _iimage2Ds;
	std::vector<glsl_iimage2DArray*> _iimage2DArrays;
	std::vector<glsl_iimageCube*> _iimageCubes;
	std::vector<glsl_iimageCubeArray*> _iimageCubeArrays;
	std::vector<glsl_iimage2DMS*> _iimage2DMSs;
	std::vector<glsl_iimage2DMSArray*> _iimage2DMSArrays;
	std::vector<glsl_iimage2DRect*> _iimage2DRects;
	std::vector<glsl_iimage3D*> _iimage3Ds;
	std::vector<glsl_iimageBuffer*> _iimageBuffers;

	std::vector<glsl_uimage1D*> _uimage1Ds;
	std::vector<glsl_uimage1DArray*> _uimage1DArrays;
	std::vector<glsl_uimage2D*> _uimage2Ds;
	std::vector<glsl_uimage2DArray*> _uimage2DArrays;
	std::vector<glsl_uimageCube*> _uimageCubes;
	std::vector<glsl_uimageCubeArray*> _uimageCubeArrays;
	std::vector<glsl_uimage2DMS*> _uimage2DMSs;
	std::vector<glsl_uimage2DMSArray*> _uimage2DMSArrays;
	std::vector<glsl_uimage2DRect*> _uimage2DRects;
	std::vector<glsl_uimage3D*> _uimage3Ds;
	std::vector<glsl_uimageBuffer*> _uimageBuffers;

public:

	glsl_image1D* image1D(const std::string& name) {}
	glsl_image1DArray* image1DArray(const std::string& name) {}
	glsl_image2D* image2D(const std::string& name) { return nullptr; }
	glsl_image2DArray* image2DArray(const std::string& name) {}
	glsl_imageCube* imageCube(const std::string& name) {}
	glsl_imageCubeArray* imageCubeArray(const std::string& name) {}
	glsl_image2DMS* image2DMS(const std::string& name) {}
	glsl_image2DMSArray* image2DMSArray(const std::string& name) {}
	glsl_image2DRect* image2DRect(const std::string& name) {}
	glsl_image3D* image3D(const std::string& name) {}
	glsl_imageBuffer* imageBuffer(const std::string& name) {}

	glsl_iimage1D* iimage1D(const std::string& name) {}
	glsl_iimage1DArray* iimage1DArray(const std::string& name) {}
	glsl_iimage2D* iimage2D(const std::string& name) {}
	glsl_iimage2DArray* iimage2DArray(const std::string& name) {}
	glsl_iimageCube* iimageCube(const std::string& name) {}
	glsl_iimageCubeArray* iimageCubeArray(const std::string& name) {}
	glsl_iimage2DMS* iimage2DMS(const std::string& name) {}
	glsl_iimage2DMSArray* iimage2DMSArray(const std::string& name) {}
	glsl_iimage2DRect* iimage2DRect(const std::string& name) {}
	glsl_iimage3D* iimage3D(const std::string& name) {}
	glsl_iimageBuffer* iimageBuffer(const std::string& name) {}

	glsl_uimage1D* uimage1D(const std::string& name) {}
	glsl_uimage1DArray* uimage1DArray(const std::string& name) {}
	glsl_uimage2D* uimage2D(const std::string& name) {}
	glsl_uimage2DArray* uimage2DArray(const std::string& name) {}
	glsl_uimageCube* uimageCube(const std::string& name) {}
	glsl_uimageCubeArray* uimageCubeArray(const std::string& name) {}
	glsl_uimage2DMS* uimage2DMS(const std::string& name) {}
	glsl_uimage2DMSArray* uimage2DMSArray(const std::string& name) {}
	glsl_uimage2DRect* uimage2DRect(const std::string& name) {}
	glsl_uimage3D* uimage3D(const std::string& name) {}
	glsl_uimageBuffer* uimageBuffer(const std::string& name) {}

private:

	std::vector<glsl_uniform_block_t*> _uniform_blocks;
	std::vector<glsl_shader_storage_block_t*> _shader_storage_blocks;
	std::vector<glsl_atomic_counter_t*> _atomic_counters;

	// layout(binding=0) gsamplerBuffer samplerBuffer;
	// layout(binding=0, format=rgb32f) gimageBuffer imageName;
	// layout(binding=0) uniform Matrices
	// {}
	void test()
	{

	}

};

struct glsl_vertex_processing_pipeline_program
{
	// must have impl
	std::shared_ptr<glsl_vertex_shader> vertex_shader;
	// optional stage
	std::shared_ptr<glsl_tessellation_shader> tessellation_shader;
	// optional stage
	std::shared_ptr<glsl_geometry_shader> geometry_shader;
};

struct glsl_compute_pipeline_program
{
	std::shared_ptr<glsl_compute_shader> compute_shader;
};

//struct glsl_graphics_pipeline_program {
//	// must have impl
//	std::shared_ptr<glsl_vertex_shader> vertex_shader;
//	// optional stage
//	std::shared_ptr<glsl_tessellation_shader> tessellation_shader;
//	// optional stage
//	std::shared_ptr<glsl_geometry_shader> geometry_shader;
//	// must have impl
//	std::shared_ptr<glsl_fragment_shader> fragment_shader;
//
//	glsl_graphics_pipeline_program() :
//		vertex_shader(nullptr), tessellation_shader(nullptr), geometry_shader(nullptr),
//		fragment_shader(nullptr)
//	{}
//} program;

#define TOKEN(__NAME__) #__NAME__



#define DEFINE_GLSL_STRUCT(STRUCT_NAME, ...)\
struct STRUCT_NAME{\
STRUCT_NAME(){ glsl_program_t::register_glsl_struct(TOKEN(__VA_ARGS__));}\
\
static const char* token(){return TOKEN(__VA_ARGS__);}\
__VA_ARGS__\
}\



#define DECLARE_STD140_UNIFORM_BLOCK(NAME, ...)\
struct NAME {\
\
NAME() = default;\
static const char* token(){return TOKEN(__VA_ARGS__);}\
virtual const std::uint8_t* data() const {return reinterpret_cast<const std::uint8_t*>(this);}\
virtual std::uint8_t* data() {return reinterpret_cast<std::uint8_t*>(this);}\
virtual std::int64_t size() const {return sizeof(NAME);}\
\
\
__VA_ARGS__\
} global_std140_uniform_block\

#define DECLARE_SHARED_UNIFORM_BLOCK()\

#define DECLARE_PACKED_UNIFORM_BLOCK()\

#define DECLARE_STD140_SHADER_STORAGE_BLOCK(NAME, ...)\

#define DECLARE_STD430_SHADER_STORAGE_BLOCK(BLOCK_NAME)\

#define DECLARE_SAMPLER()\

#define DECLARE_IMAGE()\

#define DECLARE_ATOMIC_COUNTER()\

class glsl_program_t
{

public:
	static void register_glsl_struct(const char* struct_name) {}
	//static void register_glsl_uniform_block(const glsl_uniform_block_t* block) {}
	static void register_uniform_block() {}
	//
	static void register_shader_storage_block() {}
	//
	static void register_image() {}
	//
	static void register_sampler() {}
	//
	static void register_atomic_counter() {}

public:

	DEFINE_GLSL_STRUCT(MatrixStruct,
		glm::mat4 model_mat[10];
		glm::mat4 view_mat[10];
		glm::mat4 projection_mat[10];
	);

public:

	DECLARE_STD140_UNIFORM_BLOCK(UniformBlock,
		glm::vec2 a[5];
		glm::uvec2 x[2];
		glm::vec3 offset_position;
		MatrixStruct matrices;
	);

	DECLARE_STD140_SHADER_STORAGE_BLOCK(UniformBlock,
		glm::vec2 a[5];
		glm::uvec2 x[2];
		glm::vec3 offset_position;
		MatrixStruct matrices;
	);

	//DECLARE_IMAGE(glsl_sampler2D a);



public:

	void test()
	{
		// collect all struct definitions

		// collect all blocks

		// collect all uniforms


		global_std140_uniform_block.a;
		global_std140_uniform_block.matrices.model_mat;
	}

};

#endif