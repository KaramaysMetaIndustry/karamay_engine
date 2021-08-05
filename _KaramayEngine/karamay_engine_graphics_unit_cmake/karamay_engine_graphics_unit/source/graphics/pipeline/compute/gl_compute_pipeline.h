#pragma once
#include "graphics/pipeline/base/gl_pipeline.h"
#include "graphics/type/glsl_class/glsl_transparent_class/glsl_transparent_class.h"
#include "graphics/type/glsl_class/glsl_opaque_class/glsl_opaque_class.h"

#define begin_uniform_struct(struct_name, instance_name) \
struct struct_name {\

#define end_uniform_struct }



#define uniform_struct_array(struct_name, instance_name, array_size) \

#define shader_storage_struct()
#define shader_storage_struct_array()

#define uniform_struct_transparent_t(type_name, attrib_name) \
type_name attrib_name\

#define program_parameters_begin()\
struct gl_program_parameters {\

#define program_parameters_end() \
}\


#define immediate_texture_2d(texture_name)
#define immediate_texture_2d(texture_name)
#define immediate_texture_2d(texture_name)
#define immediate_texture_2d(texture_name)

program_parameters_begin()

program_parameters_end();


struct MyUniformStruct
{
	glsl_dmat2 mat_x;
	glsl_dmat2 mat_x;
	glsl_dmat2 mat_x;
	glsl_vec2 uv;
	struct other_struct
	{
		glsl_vec3 xe;
		glsl_mat2 wa;
	} add[2];

	std::string glsl_template()
	{
		return std::string("layout(std140) uniform ") + "my_uniform_buffer {} " + "materials" + "[10]";
	}
} instance_name[10];

#define glsl_uniform_layout_std140 alignas(16)
#define glsl_shader_storage_layout_std140 alignas(16)




template<typename uniform_struct_t, const char* instance_name, int array_size>
class gl_uniform_buffer
{
	uniform_struct_t instance[array_size];

	const std::uint8_t* get_stream() const
	{
		return reinterpret_cast<const std::uint8_t*>(&instance);
	}

	std::int64_t get_stream_size() const
	{
		return sizeof(uniform_struct_t) * array_size;
	}

};


class gl_compute_pipeline_parameters
{
};

#define define_compute_pipeline_parameters()

struct gl_compute_pipeline_descriptor
{
};

/*
*
* 
*/
class gl_compute_pipeline final : public gl_pipeline
{
public:

	explicit gl_compute_pipeline(const gl_compute_pipeline_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		_initialize_compute_pipeline();
	}

	~gl_compute_pipeline() = default;

private:

	gl_compute_pipeline() = default;

	const gl_compute_pipeline_descriptor _descriptor;

	void _initialize_compute_pipeline();

public:
	/*
	* Dispatch compute shader
	*/
	inline void install() 
	{

	}

	inline void dispatch(std::uint32_t group_size_x, std::uint32_t group_size_y, std::uint32_t group_size_z)
	{
		glDispatchCompute(group_size_x, group_size_y, group_size_z);
	}

	inline void dispatch()
	{

	}

	inline void uninstall() {}

};

