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

class glsl_compute_shader final : public glsl_shader
{
public:
	glsl_compute_shader() {}

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
class glsl_vertex_shader final: public glsl_graphics_shader
{
public:
	glsl_vertex_shader() = default;

	glsl_vertex_shader(const glsl_vertex_shader&) = delete;
	glsl_vertex_shader& operator=(const glsl_vertex_shader&) = delete;

	~glsl_vertex_shader() = default;

public:
	bool generate_template(const std::string& path) override
	{}

	bool load(const std::string& path) override
	{
		_shader = new gl_shader(gl_shader_type::VERTEX_SHADER, path);
		return _shader->get_compile_status();
	}
};
class glsl_tessellation_control_shader final : public glsl_graphics_shader 
{
public:
	glsl_tessellation_control_shader() = default;

	glsl_tessellation_control_shader(const glsl_tessellation_control_shader&) = delete;
	glsl_tessellation_control_shader& operator=(const glsl_tessellation_control_shader&) = delete;

	~glsl_tessellation_control_shader() = default;

public:

	bool generate_template(const std::string& path) override
	{

	}

	bool load(const std::string& tesc_path) override
	{
		_shader = new gl_shader(gl_shader_type::TESS_CONTROL_SHADER, tesc_path);
	}

};
class glsl_tessellation_evaluation_shader final : glsl_graphics_shader 
{
public:
	glsl_tessellation_evaluation_shader() = default;

	glsl_tessellation_evaluation_shader(const glsl_tessellation_evaluation_shader&) = delete;
	glsl_tessellation_evaluation_shader& operator=(const glsl_tessellation_evaluation_shader&) = delete;

	~glsl_tessellation_evaluation_shader() = default;

public:

	bool generate_template(const std::string & path) override
	{

	}

	bool load(const std::string & tese_path) override
	{
		_shader = new gl_shader(gl_shader_type::TESS_EVALUATION_SHADER, tese_path);
	}
};
class glsl_geometry_shader final : public glsl_graphics_shader
{
public:
	glsl_geometry_shader() = default;

	glsl_geometry_shader(const glsl_geometry_shader&) = delete;
	glsl_geometry_shader operator=(const glsl_geometry_shader&) = delete;

	~glsl_geometry_shader() = default;

public:
	
	bool generate_template(const std::string& path) override
	{

	}

	bool load(const std::string& path) override
	{
		_shader = new gl_shader(gl_shader_type::GEOMETRY_SHADER, path);
		return _shader->get_compile_status();
	}

};
class glsl_fragment_shader final : public glsl_graphics_shader
{
public:
	glsl_fragment_shader() = default;

	glsl_fragment_shader(const glsl_fragment_shader&) = delete;
	glsl_fragment_shader operator=(const glsl_fragment_shader&) = delete;

	~glsl_fragment_shader() = default;

public:
	bool generate_template(const std::string& path) override
	{

	}

	bool load(const std::string& path) override
	{
		_shader = new gl_shader(gl_shader_type::FRAGMENT_SHADER, path);
		return _shader->get_compile_status();
	}
};

class glsl_task_shader final {}; // .task
class glsl_mesh_shader final{}; // .mesh


// .rgen  Ray Generation shader
// .rchit Closest Hit Shader
// .rmiss Miss Shader
// .rint Intersection Shader
// .rahit  Any Hit shader
// .rcall 



#define refUniformBlock()
#define refShaderStorageBlock()
#define refAtomicCounter()


#define vertexShader()
#define tessellationShader()
#define geometryShader()
#define fragmentShader()


#endif
