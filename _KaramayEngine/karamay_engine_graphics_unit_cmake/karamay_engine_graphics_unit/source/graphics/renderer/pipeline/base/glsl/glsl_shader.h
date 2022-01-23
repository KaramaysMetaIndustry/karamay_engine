#ifndef GLSL_SHADER_H
#define GLSL_SHADER_H

#include "graphics/renderer/pipeline/base/resource/shader/gl_shader.h"
#include "interface_block/glsl_uniform_block.h"
#include "interface_block/glsl_shader_storage_block.h"
#include "opaque_t/glsl_atomic_counter.h"
#include "opaque_t/glsl_image.h"
#include "opaque_t/glsl_sampler.h"

class glsl_shader
{
public:

	glsl_shader() = default;

	~glsl_shader() = default;

public:

	virtual bool generate_template(const std::string& pipeline_dir) = 0;

	virtual bool load(const std::string& path) = 0;

	gl_shader* get_shader() const { return _shader; }

	glsl_uniform_block* uniform_block(const std::string& block_name)
	{
		return nullptr;
	}

	glsl_shader_storage_block* shader_storage_block(const std::string& block_name)
	{
		return nullptr;
	}

	glsl_atomic_counter* atomic_uint(const std::string& block_name)
	{
		return nullptr;
	}

protected:

	gl_shader* _shader;

	std::vector<glsl_uniform_block*> _uniform_block_refs;
	std::vector<glsl_shader_storage_block*> _shader_storage_block_refs;
	std::vector<glsl_atomic_counter*> _atomic_counter_refs;

	void* _ref_uniform_block(const std::string& name)
	{
		return nullptr;
	}

	void* _ref_shader_storage_block(const std::string& name)
	{
		return nullptr;
	}

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

		return true;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::COMPUTE_SHADER, pipeline_dir + "/"+ pipeline_dir.substr(pipeline_dir.find_last_of("/") + 1) + ".comp");
		return false;
	}

};

struct glsl_vertex_attribute {};
struct glsl_instance_attribute {};

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
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::VERTEX_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("/") + 1) + ".vert");
		return _shader->get_compile_status();
	}

	const std::vector<glsl_vertex_attribute>& vertex_attributes() const { return _vertex_attributes; }

	const std::vector<glsl_instance_attribute>& instance_attributes() const { return _instance_attributes; }

private:
	
	std::vector<glsl_vertex_attribute> _vertex_attributes;
	
	std::vector<glsl_instance_attribute> _instance_attributes;

protected:

	void _create_vertex_attribute() {}

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
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::TESS_CONTROL_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("/") + 1) + ".tesc");
		return true;
	}

};

// .tese
class glsl_tessellation_evaluation_shader : public glsl_graphics_shader 
{
public:
	glsl_tessellation_evaluation_shader() = default;

	glsl_tessellation_evaluation_shader(const glsl_tessellation_evaluation_shader&) = delete;
	glsl_tessellation_evaluation_shader& operator=(const glsl_tessellation_evaluation_shader&) = delete;

	~glsl_tessellation_evaluation_shader() = default;

public:

	bool generate_template(const std::string & pipeline_dir) override
	{
		return false;
	}

	bool load(const std::string & pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::TESS_EVALUATION_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("/") + 1) + ".tese");
		return false;
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
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::GEOMETRY_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("/") + 1) + ".geom");
		return _shader->get_compile_status();
	}

};

struct glsl_fragment_shader_input_item 
{
	std::string type_name;
	std::string var_name;
};
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
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::FRAGMENT_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("/") + 1) + ".frag");
		return _shader->get_compile_status();
	}

private:
	std::vector<glsl_fragment_shader_input_item> _input_items;
	std::vector<glsl_fragment_shader_output_item> _output_items;

protected:
	
	void _add_input_item(glsl_fragment_shader_input_item input_item)
	{}

	void _add_output_item(glsl_fragment_shader_output_item output_item)
	{}


};


// .task
class glsl_task_shader : public glsl_shader
{
public:

	glsl_task_shader() = default;

	glsl_task_shader(const glsl_task_shader&) = delete;
	glsl_task_shader& operator=(const glsl_task_shader&) = delete;

	~glsl_task_shader() = default;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{
		std::ifstream _file;
		std::string _content = "#version 460\n";
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::TASK_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("/") + 1) + ".task");
		return _shader->get_compile_status();
	}
}; 

// .mesh
class glsl_mesh_shader : public glsl_shader
{
public:
	glsl_mesh_shader() = default;

	glsl_mesh_shader(const glsl_mesh_shader&) = delete;
	glsl_mesh_shader& operator=(const glsl_mesh_shader&) = delete;

	~glsl_mesh_shader() = default;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{
		std::ifstream _file;
		std::string _content = "#version 460\n";
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::MESH_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("/") + 1) + ".mesh");
		return _shader->get_compile_status();
	}
}; 

//
//// .rgen  Ray Generation shader
//class glsl_ray_generation_shader final{};
//
//// .rchit Closest Hit Shader
//class glsl_closest_hit_shader final {};
//
//// .rmiss Miss Shader
//class glsl_miss_shader final {};
//
//// .rint Intersection Shader
//class glsl_intersection_shader final {};
//
//// .rahit  Any Hit shader
//class glsl_any_hit_shader final {};
//
//// .rcall 

#endif
