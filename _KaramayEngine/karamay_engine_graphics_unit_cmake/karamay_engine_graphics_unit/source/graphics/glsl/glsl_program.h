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

class glsl_graphics_pipeline_program final{
public:
	glsl_graphics_pipeline_program() = default;
	glsl_graphics_pipeline_program(const std::shared_ptr<glsl_vertex_shader>& vs, const std::shared_ptr<glsl_fragment_shader>& fs) :
		_vertex_shader(vs), _tessellation_shader(nullptr), _geometry_shader(nullptr), _fragment_shader(fs)
	{
		_collect_parameters();
	}
	glsl_graphics_pipeline_program(const std::shared_ptr<glsl_vertex_shader>& vs, const std::shared_ptr<glsl_tessellation_shader>& ts, const std::shared_ptr<glsl_fragment_shader>& fs) :
		_vertex_shader(vs), _tessellation_shader(ts), _geometry_shader(nullptr), _fragment_shader(fs)
	{
		_collect_parameters();
	}
	glsl_graphics_pipeline_program(const std::shared_ptr<glsl_vertex_shader>& vs, const std::shared_ptr<glsl_geometry_shader>& gs, const std::shared_ptr<glsl_fragment_shader>& fs) :
		_vertex_shader(vs), _tessellation_shader(nullptr), _geometry_shader(gs), _fragment_shader(fs) 
	{
		_collect_parameters();
	}
	glsl_graphics_pipeline_program(const std::shared_ptr<glsl_vertex_shader>& vs, const std::shared_ptr<glsl_tessellation_shader>& ts, const std::shared_ptr<glsl_geometry_shader>& gs, const std::shared_ptr<glsl_fragment_shader>& fs) :
		_vertex_shader(vs), _tessellation_shader(ts), _geometry_shader(gs), _fragment_shader(fs) 
	{
		_collect_parameters();
	}

	glsl_graphics_pipeline_program(const glsl_graphics_pipeline_program&) = delete;
	glsl_graphics_pipeline_program& operator=(const glsl_graphics_pipeline_program&) = delete;


	~glsl_graphics_pipeline_program() = default;

public:
	
	const glsl_graphics_pipeline_parameters& parameters() const { return _parameters; }

	const std::shared_ptr<glsl_vertex_shader>& vs() const { return _vertex_shader; }
	const std::shared_ptr<glsl_tessellation_shader>& ts() const { return _tessellation_shader; }
	const std::shared_ptr<glsl_geometry_shader>& gs() const { return _geometry_shader; }
	const std::shared_ptr<glsl_fragment_shader>& fs() const { return _fragment_shader; }


private:

	std::vector<glsl_sampler1D*> _sampler1Ds;
	std::vector<glsl_sampler1DArray*> _sampler1DArrays;
	std::vector<glsl_sampler1DShadow*> _sampler1DShadows;
	std::vector<glsl_sampler1DArrayShadow*> _sampler1DArrayShadows;
	std::vector<glsl_sampler2D*> _sampler2Ds;
	std::vector<glsl_sampler2DArray*> _sampler2DArrays;
	std::vector<glsl_sampler2DShadow*> _sampler2DShadows;
	std::vector<glsl_sampler2DArrayShadow*> _sampler2DArrayShadows;
	std::vector<glsl_sampler2DMS*> _sampler2DMSs;
	std::vector<glsl_sampler2DMSArray*> _sampler2DMSArrays;
	std::vector<glsl_samplerCube*> _samplerCubes;
	std::vector<glsl_samplerCubeArray*> _samplerCubeArrays;
	std::vector<glsl_samplerCubeShadow*> _samplerCubeShadows;
	std::vector<glsl_samplerCubeArrayShadow*> _samplerCubeArrayShadows;
	std::vector<glsl_sampler2DRect*> _sampler2DRects;
	std::vector<glsl_sampler2DRectShadow*> _sampler2DRectShadows;
	std::vector<glsl_samplerBuffer*> _samplerBuffers;

public:

	glsl_sampler1D* sampler1D(const std::string& name)
	{
		auto* _sampler1D = new glsl_sampler1D(_sampler1Ds.size() - 1, name);
		_sampler1Ds.push_back(_sampler1D);
		return _sampler1D;
	}
	glsl_sampler1DArray* sampler1DArray() {}
	glsl_sampler1DShadow* sampler1DShadow() {}
	glsl_sampler1DArrayShadow* sampler1DArrayShadow() {}
	glsl_sampler2D* sampler2D() {}
	glsl_sampler2DArray* sampler2DArray() {}
	glsl_sampler2DShadow* sampler2DShadow() {}
	glsl_sampler2DArrayShadow* sampler2DArrayShadow() {}
	glsl_sampler2DMS* sampler2DMS() {}
	glsl_sampler2DMSArray* sampler2DMSArray() {}
	glsl_samplerCube* samplerCube() {}
	glsl_samplerCubeArray* samplerCubeArray() {}
	glsl_samplerCubeShadow* samplerCubeShadow() {}
	glsl_samplerCubeArrayShadow* samplerCubeArrayShadow() {}
	glsl_sampler2DRect* sampler2DRect() {}
	glsl_sampler2DRectShadow* sampler2DRectShadow() {}
	glsl_samplerBuffer* samplerBuffer() {}

	/*glsl_sampler1D* sampler1D() {}
	glsl_sampler1DArray* sampler1DArray() {}
	glsl_sampler1DShadow* sampler1DShadow() {}
	glsl_sampler1DArrayShadow* sampler1DArrayShadow() {}
	glsl_sampler2D* sampler2D() {}
	glsl_sampler2DArray* sampler2DArray() {}
	glsl_sampler2DShadow* sampler2DShadow() {}
	glsl_sampler2DArrayShadow* sampler2DArrayShadow() {}
	glsl_sampler2DMS* sampler2DMS() {}
	glsl_sampler2DMSArray* sampler2DMSArray() {}
	glsl_samplerCube* samplerCube() {}
	glsl_samplerCubeArray* samplerCubeArray() {}
	glsl_samplerCubeShadow* samplerCubeShadow() {}
	glsl_samplerCubeArrayShadow* samplerCubeArrayShadow() {}
	glsl_sampler2DRect* sampler2DRect() {}
	glsl_sampler2DRectShadow* sampler2DRectShadow() {}
	glsl_samplerBuffer* samplerBuffer() {}*/

private:

	std::vector<glsl_image1D*> _image1Ds;
	std::vector<glsl_image1DArray*> _image1DArrays;

public:


private:

	// must have impl
	std::shared_ptr<glsl_vertex_shader> _vertex_shader;
	// optional stage
	std::shared_ptr<glsl_tessellation_shader> _tessellation_shader;
	// optional stage
	std::shared_ptr<glsl_geometry_shader> _geometry_shader;
	// must have impl
	std::shared_ptr<glsl_fragment_shader> _fragment_shader;

	void _collect_parameters()
	{
		auto& _collected_uniform_blocks = _parameters.uniform_blocks;

	}

	glsl_graphics_pipeline_parameters _parameters;

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