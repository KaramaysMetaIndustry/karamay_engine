#ifndef GLSL_SHADER_H
#define GLSL_SHADER_H

#include "interface_block/glsl_uniform_block.h"
#include "interface_block/glsl_shader_storage_block.h"
#include "opaque_t/glsl_atomic_counter.h"
#include "opaque_t/glsl_image.h"
#include "opaque_t/glsl_sampler.h"
#include "graphics/renderer/pipeline/base/resource/shader/gl_shader.h"

class glsl_shader
{
public:

	glsl_shader() = default;

	~glsl_shader() = default;

public:

	virtual bool generate_template(const std::string& path) = 0;

	virtual bool load(const std::string& path) = 0;

	gl_shader* get_shader() const { return _shader; }

protected:

	gl_shader* _shader;

	std::vector<glsl_uniform_block*> _uniform_block_refs;
	std::vector<glsl_shader_storage_block*> _shader_storage_block_refs;
	std::vector<glsl_atomic_counter*> _atomic_counter_refs;

};

class glsl_graphics_shader : public glsl_shader
{
public:

};


// .cs
class glsl_compute_shader : public glsl_shader
{
public:
	glsl_compute_shader() = default;

	glsl_compute_shader(const glsl_compute_shader&) = delete;
	glsl_compute_shader& operator=(const glsl_compute_shader&) = delete;

	~glsl_compute_shader() = default;

public:

	bool generate_template(const std::string& path) override
	{
		for (auto _ub_ref : _uniform_block_refs)
		{

		}

		for (auto _ssb_ref : _shader_storage_block_refs)
		{

		}

		for (auto _ac_ref : _atomic_counter_refs)
		{

		}

	}

	bool load(const std::string& path) override
	{
		_shader = new gl_shader(gl_shader_type::COMPUTE_SHADER, path);
	}

};

// .vert
class glsl_vertex_shader: public glsl_graphics_shader
{
public:
	glsl_vertex_shader() = default;

	glsl_vertex_shader(const glsl_vertex_shader&) = delete;
	glsl_vertex_shader& operator=(const glsl_vertex_shader&) = delete;

	~glsl_vertex_shader() = default;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{

	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::VERTEX_SHADER, pipeline_dir);
		return _shader->get_compile_status();
	}

};

// .tesc
class glsl_tessellation_control_shader : public glsl_graphics_shader 
{
public:
	glsl_tessellation_control_shader() = default;

	glsl_tessellation_control_shader(const glsl_tessellation_control_shader&) = delete;
	glsl_tessellation_control_shader& operator=(const glsl_tessellation_control_shader&) = delete;

	~glsl_tessellation_control_shader() = default;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{

	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::TESS_CONTROL_SHADER, pipeline_dir);
	}

};

// .tese
class glsl_tessellation_evaluation_shader : glsl_graphics_shader 
{
public:
	glsl_tessellation_evaluation_shader() = default;

	glsl_tessellation_evaluation_shader(const glsl_tessellation_evaluation_shader&) = delete;
	glsl_tessellation_evaluation_shader& operator=(const glsl_tessellation_evaluation_shader&) = delete;

	~glsl_tessellation_evaluation_shader() = default;

public:

	bool generate_template(const std::string & pipeline_dir) override
	{

	}

	bool load(const std::string & pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::TESS_EVALUATION_SHADER, pipeline_dir);
	}

};

// .geom
class glsl_geometry_shader : public glsl_graphics_shader
{
public:
	glsl_geometry_shader() = default;

	glsl_geometry_shader(const glsl_geometry_shader&) = delete;
	glsl_geometry_shader operator=(const glsl_geometry_shader&) = delete;

	~glsl_geometry_shader() = default;

public:
	
	bool generate_template(const std::string& pipeline_dir) override
	{

	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::GEOMETRY_SHADER, pipeline_dir);
		return _shader->get_compile_status();
	}

};

struct glsl_fragment_shader_input_item {};
struct glsl_fragment_shader_output_item {};

// .frag
class glsl_fragment_shader : public glsl_graphics_shader
{
public:
	glsl_fragment_shader() = default;

	glsl_fragment_shader(const glsl_fragment_shader&) = delete;
	glsl_fragment_shader operator=(const glsl_fragment_shader&) = delete;

	~glsl_fragment_shader() = default;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{
		std::ifstream _file;

		std::string _content = "#version 460\n";

	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::FRAGMENT_SHADER, pipeline_dir);
		return _shader->get_compile_status();
	}

protected:

	std::vector<glsl_fragment_shader_input_item> _input_items;
	std::vector<glsl_fragment_shader_output_item> _output_items;

};




// .task
class glsl_task_shader final {}; 

// .mesh
class glsl_mesh_shader final{}; 

// .rgen  Ray Generation shader
class glsl_ray_generation_shader final{};

// .rchit Closest Hit Shader
class glsl_closest_hit_shader final {};

// .rmiss Miss Shader
class glsl_miss_shader final {};

// .rint Intersection Shader
class glsl_intersection_shader final {};

// .rahit  Any Hit shader
class glsl_any_hit_shader final {};

// .rcall 



#define refUniformBlock()

#define refShaderStorageBlock()

#define refAtomicCounter()


#define vertexShader()\
class glsl_vs : public glsl_vertex_shader\
{\

#define tessellationControlShader()\
class glsl_tesc : public glsl_tessellation_control_shader\
{\

#define tessellationEvaluationShader()\
class glsl_tese : public glsl_tessellation_evaluation_shader\
{\

#define geometryShader()\
class glsl_gs : public glsl_geometry_shader\
{\

#define fragmentShader()\
class glsl_fs : public glsl_fragment_shader\
{\


#endif
