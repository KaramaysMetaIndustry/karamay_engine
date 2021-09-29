#include "graphics/pipeline/base/gl_pipeline.h"
#include "graphics/glsl/glsl_class.h"
#include "graphics/glsl/opaque_t/glsl_sampler_t.h"
#include "graphics/glsl/opaque_t/glsl_image_t.h"
#include "graphics/glsl/opaque_t/glsl_atomic_counter_t.h"
#include "graphics/glsl/transparent_t/interface_block_t/glsl_interface_block_t.h"
#include "graphics/program/gl_program.h"

class gl_compute_pipeline_parameters{
public:
    std::vector<std::shared_ptr<glsl_sampler_t>> samplers;
    std::vector<std::shared_ptr<glsl_image_t>> images;
    std::vector<std::shared_ptr<glsl_atomic_uint>> atomic_counters;
    std::vector<std::shared_ptr<glsl_uniform_block_t>> uniform_blocks;
    std::vector<std::shared_ptr<glsl_buffer_block_t>> buffer_blocks;

};

struct gl_compute_pipeline_descriptor
{
};

class gl_compute_pipeline final : public gl_pipeline{
public:
    gl_compute_pipeline() = delete;
	explicit gl_compute_pipeline(const gl_compute_pipeline_descriptor& descriptor)
	{
	    // ... generate shader code file

	    // ... initialize program
	    _program = std::make_unique<gl_program>();
	    _program->construct({});
	    // ... initialize parameters

	}
	gl_compute_pipeline(const gl_compute_pipeline&) = delete;
	gl_compute_pipeline& operator=(const gl_compute_pipeline&) = delete;

	~gl_compute_pipeline() = default;
public:

    void bind()
    {
        if(parameters)
        {
            for(const auto& sampler : parameters->samplers) if(sampler) sampler->bind();
            for(const auto& image : parameters->images) if(image) image->bind();

            const auto& atomic_counters = parameters->atomic_counters;
            const auto& uniform_blocks = parameters->uniform_blocks;
            const auto& buffer_blocks = parameters->buffer_blocks;
        }
    }

    void unbind()
    {
        if(parameters)
        {
            for(const auto& sampler : parameters->samplers) if(sampler) sampler->unbind();
            for(const auto& image : parameters->images) if(image) image->unbind();

        }
    }

	/*
	* Dispatch compute
	*/
	void dispatch(std::uint32_t group_size_x, std::uint32_t group_size_y, std::uint32_t group_size_z)
	{
		glDispatchCompute(group_size_x, group_size_y, group_size_z);
	}

private:

    std::unique_ptr<gl_program> _program;

	std::unordered_map<std::string, std::int32_t> _binding_cache;

	void _generate_binding_cache()
    {}

public:

    const std::shared_ptr<gl_compute_pipeline_parameters> parameters;


};