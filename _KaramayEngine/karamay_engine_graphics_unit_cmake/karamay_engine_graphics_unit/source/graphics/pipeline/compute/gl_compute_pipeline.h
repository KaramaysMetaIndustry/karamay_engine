#ifndef _GL_COMPUTE_PIPELINE_H_
#define _GL_COMPUTE_PIPELINE_H_

#include "graphics/glsl/glsl_class.h"
#include "graphics/pipeline/base/gl_pipeline.h"
#include "graphics/program/gl_program.h"
#include "graphics/shader/gl_shader.h"


#define DEFINE_STD140_UNIFORM_BLOCK() \

#define DEFINE_SHARED_UNIFORM_BLOCK() \

#define DEFINE_PACKED_UNIFORM_BLOCK() \

#define DEFINE_STD140_BUFFER_BLOCK() \

#define DEFINE_STD430_BUFFER_BLOCK() \


#define DEFINE_STRUCT(C_STRUCT_NAME, VALUE_NAME)\

#define DEFINE_UNIFORM_BLOCK_ITEM(C_STRUCT_NAME, VALUE_NAME)\
C_STRUCT_NAME VALUE_NAME\

#define DEFINE_UNIFORM_BLOCK_ITEM_ARRAY(C_STRUCT_NAME, VALUE_NAME)\
C_STRUCT_NAME VALUE_NAME\

class gl_compute_pipeline_parameters_meta
{
    struct AsLightModel
    {
    };

    class cpp_uniform_block : public glsl_uniform_block_t
    {
        //AsLightModel A[19];

        DEFINE_UNIFORM_BLOCK_ITEM_ARRAY(AsLightModel, A[19]);
    };


};

class gl_compute_pipeline_parameters{
public:
    std::vector<std::shared_ptr<glsl_sampler_t>> samplers;
    std::vector<std::shared_ptr<glsl_image_t>> images;
    std::vector<std::shared_ptr<glsl_atomic_counter_t>> atomic_counters;
    std::vector<std::shared_ptr<glsl_uniform_block_t>> uniform_blocks;
    std::vector<std::shared_ptr<glsl_shader_storage_block_t>> buffer_blocks;
};

struct gl_compute_pipeline_descriptor{
    std::string name;
    std::string owner_renderer_path;
    std::shared_ptr<gl_compute_shader> compute_shader;
    std::shared_ptr<gl_compute_pipeline_parameters> parameters;
};

class gl_compute_pipeline final{
public:
    gl_compute_pipeline() = delete;
	explicit gl_compute_pipeline(const gl_compute_pipeline_descriptor& descriptor) :
	    parameters(descriptor.parameters)
	{
	    // ... generate shader code file
	    if(std::filesystem::exists(descriptor.owner_renderer_path) && descriptor.compute_shader)
        {
	        std::string _pipeline_path = descriptor.owner_renderer_path + "/"+ descriptor.name + "/";
	        std::filesystem::create_directories(_pipeline_path);
            {
                std::fstream _cs(_pipeline_path + descriptor.name + ".cs");
                if(_cs.is_open())
                {
                    _cs.write(
                            descriptor.compute_shader->code_template().c_str(),
                            descriptor.compute_shader->code_template().size()
                    );
                }
            }
        }
	    // ... initialize program (load and compile shaders)
	    _program = std::make_unique<gl_program>();
	    _program->construct({});
	    // ... initialize parameters
	        // ... generate parameters GPU resource
	        //descriptor.parameters->samplers;
	        //descriptor.parameters->images;
	        descriptor.parameters->atomic_counters;
	        descriptor.parameters->buffer_blocks;
	        descriptor.parameters->uniform_blocks;
	        // ... generate parameters binding cache

	}
	gl_compute_pipeline(const gl_compute_pipeline&) = delete;
	gl_compute_pipeline& operator=(const gl_compute_pipeline&) = delete;

	~gl_compute_pipeline() = default;

public:

    void enable()
    {
        if(_program && _check_memory_pool())
        {
            // enable the program, otherwise all resource binding will not work
            _program->enable();
            // bind resource
            for(const auto& shader_storage_buffer : _memory_pool->shader_storage_buffers)
            {
            }
        }
    }

    void disable()
    {
        if(_program && _check_memory_pool())
        {


            // disable the program, good habit, good boy!
            _program->disable();
        }
    }

public: // commands

	void dispatch(std::uint32_t group_size_x, std::uint32_t group_size_y, std::uint32_t group_size_z)
	{
	    if(_program && _check_memory_pool())
        {
            glDispatchCompute(group_size_x, group_size_y, group_size_z);
        }
	}

private:

    std::unique_ptr<gl_program> _program;

    struct gl_compute_pipeline_parameters_memory_pool
    {
        // atomic_counter_buffer
        std::unique_ptr<gl_atomic_counter_buffer> atomic_counter_buffer;
        // layout - uniform buffer - uniform blocks
        std::unordered_map<std::string, std::unique_ptr<gl_uniform_buffer>> uniform_buffers;
        // layout - shader storage buffer - buffer blocks
        std::unordered_map<std::string, std::unique_ptr<gl_shader_storage_buffer>> shader_storage_buffers;
        // binding cache
        std::unordered_map<std::string, std::int32_t> binding_cache;
    };

    std::unique_ptr<gl_compute_pipeline_parameters_memory_pool> _memory_pool;

    bool _check_memory_pool()
    {
        if(!_memory_pool) return false;
        if(!_memory_pool->atomic_counter_buffer) return false;
        for(const auto& shader_storage_buffer : _memory_pool->shader_storage_buffers)
            if(!shader_storage_buffer.second) return false;
        for(const auto& uniform_buffer : _memory_pool->uniform_buffers)
            if(!uniform_buffer.second) return false;
        //_memory_pool->uniform_buffers.emplace("std140", std::make_unique<gl_uniform_buffer>());
        return true;
    }

    bool _check_program_state() {}

    bool _check_resource_state() {}

    void _generate_parameters_memory_pool()
    {
    }

public:

    const std::shared_ptr<gl_compute_pipeline_parameters> parameters;

};

#endif