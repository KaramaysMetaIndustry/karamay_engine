#ifndef GLSL_SHADER_H
#define GLSL_SHADER_H
#include "graphics/glsl/opaque_t/glsl_atomic_counter.h"
#include "graphics/glsl/opaque_t/glsl_image.h"
#include "graphics/glsl/opaque_t/glsl_sampler.h"
#include "graphics/glsl/interface_block/glsl_uniform_block.h"
#include "graphics/glsl/interface_block/glsl_shader_storage_block.h"
#include "graphics/resource/shader/gl_shader.h"

class glsl_shader
{
public:

	glsl_shader() = default;
	glsl_shader(const glsl_shader&) = delete;
	glsl_shader& operator=(const glsl_shader&) = delete;

	virtual ~glsl_shader() = default;

public:

	virtual bool generate_template(const std::string& pipeline_dir) { return false; };

	virtual bool load(const std::string& path) { return false; };

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

// only for Vulkan
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

#endif
