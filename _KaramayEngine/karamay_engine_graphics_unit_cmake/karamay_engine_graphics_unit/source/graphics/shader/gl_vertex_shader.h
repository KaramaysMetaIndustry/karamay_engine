
#include "gl_shader.h"


struct gl_vertex_shader_attribute
{
	std::string attribute_t;
	std::string attribute_name;
	std::uint32_t binding;
};
using gl_vertex_shader_input_list = std::vector<gl_vertex_shader_attribute>;
using gl_vertex_shader_output_list = std::vector<gl_vertex_shader_attribute>;

class gl_vertex_shader
{
public:

	gl_vertex_shader() = default;

	gl_vertex_shader(
		const gl_vertex_shader_input_list& input_list,
		const gl_vertex_shader_output_list& output_list)
	{
	}


private:

	const gl_vertex_shader_input_list _input_list;
	const gl_vertex_shader_output_list _output_list;


};