#ifndef GLSL_VERTEX_SHADER_H
#define GLSL_VERTEX_SHADER_H
#include "glsl_shader.h"

struct glsl_vertex_shader_input {};

struct glsl_vertex_shader_output {};

class glsl_vertex_shader : public glsl_shader
{
public:
	glsl_vertex_shader() = default;

	glsl_vertex_shader(const glsl_vertex_shader&) = delete;
	glsl_vertex_shader& operator=(const glsl_vertex_shader&) = delete;

	~glsl_vertex_shader() = default;

public:

	bool load(const std::string& pipeline_dir) override;

	bool load();

private:

	glsl_vertex_shader_input _input;

	glsl_vertex_shader_output _output;

public:

	const glsl_vertex_shader_input& input() const noexcept { return _input; }

	const glsl_vertex_shader_output& output() const noexcept { return _output; }

};

#endif