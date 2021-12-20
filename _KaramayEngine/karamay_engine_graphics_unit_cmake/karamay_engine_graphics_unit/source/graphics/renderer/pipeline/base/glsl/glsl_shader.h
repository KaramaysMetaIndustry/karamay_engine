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
	glsl_shader()
	{}

	~glsl_shader() {}

};
struct glsl_compute_shader_descriptor {};
class glsl_compute_shader : public glsl_shader
{
public:
	glsl_compute_shader(const glsl_compute_shader_descriptor& descriptor)
	{}

};

class glsl_graphics_shader : public glsl_shader
{
public:

};

struct glsl_vertex_shader_descriptor
{

};
class glsl_vertex_shader final: public glsl_graphics_shader
{
public:
	glsl_vertex_shader(const glsl_vertex_shader_descriptor& descriptor)
	{
	}

	glsl_vertex_shader(const glsl_vertex_shader&) = delete;
	glsl_vertex_shader& operator=(const glsl_vertex_shader&) = delete;

	~glsl_vertex_shader()
	{

	}

public:

	bool load(const std::string& path)
	{
		_shader = new gl_shader(gl_shader_type::VERTEX_SHADER, path);
		return _shader->get_compile_status();
	}

	gl_shader* get_shader() const { return _shader; }

private:
	gl_shader* _shader;

};
struct glsl_tessellation_shader_descriptor {};
class glsl_tessellation_shader final : public glsl_graphics_shader 
{
public:
	glsl_tessellation_shader(const glsl_tessellation_shader_descriptor& descriptor)
	{}

	glsl_tessellation_shader(const glsl_tessellation_shader&) = delete;
	glsl_tessellation_shader& operator=(const glsl_tessellation_shader&) = delete;

	~glsl_tessellation_shader()
	{}

	bool load(const std::string& tesc_path, const std::string& tese_path)
	{
		_tesc = new gl_shader(gl_shader_type::TESS_CONTROL_SHADER, tesc_path);
		_tese = new gl_shader(gl_shader_type::TESS_EVALUATION_SHADER, tese_path);
		return (_tesc->get_compile_status()) && (_tese->get_compile_status());
	}

	std::pair<gl_shader*, gl_shader*> get_shader() const { return std::make_pair(_tesc, _tese); }

private:

	gl_shader* _tesc;
	gl_shader* _tese;

};
struct glsl_geometry_shader_descriptor {};
class glsl_geometry_shader final : public glsl_graphics_shader
{
public:
	glsl_geometry_shader(const glsl_geometry_shader_descriptor& descriptor) 
	{}

	glsl_geometry_shader(const glsl_geometry_shader&) = delete;
	glsl_geometry_shader operator=(const glsl_geometry_shader&) = delete;

	~glsl_geometry_shader()
	{}

public:

	bool load(const std::string& path)
	{
		_shader = new gl_shader(gl_shader_type::GEOMETRY_SHADER, path);
		return _shader->get_compile_status();
	}

	gl_shader* get_shader() const { return _shader; }

private:

	gl_shader* _shader;

};
struct glsl_fragment_shader_descriptor {};
class glsl_fragment_shader final : public glsl_graphics_shader
{
public:
	glsl_fragment_shader(const glsl_fragment_shader_descriptor& descriptor)
	{}

	glsl_fragment_shader(const glsl_fragment_shader&) = delete;
	glsl_fragment_shader operator=(const glsl_fragment_shader&) = delete;

	~glsl_fragment_shader()
	{}

public:

	bool load(const std::string& path)
	{
		_shader = new gl_shader(gl_shader_type::FRAGMENT_SHADER, path);
		return _shader->get_compile_status();
	}

	gl_shader* get_shader() const { return _shader; }

private:
	gl_shader* _shader;
};


#endif
