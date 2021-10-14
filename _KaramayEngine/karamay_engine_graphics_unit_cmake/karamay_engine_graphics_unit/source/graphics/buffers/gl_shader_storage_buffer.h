#ifndef H_GL_SHADER_STORAGE_BUFFER
#define H_GL_SHADER_STORAGE_BUFFER

#include "public/stl.h"
#include "gl_uniform_buffer.h"

enum class gl_shader_storage_buffer_memory_layout
{
    std140,
    std430
};

enum class gl_shader_storage_buffer_matrix_layout
{
    row_major,
    column_major
};

struct glsl_shader_storage_block_state
{

};

struct gl_shader_storage_buffer_descriptor{
    gl_shader_storage_buffer_memory_layout memory_layout;
    gl_shader_storage_buffer_matrix_layout matrix_layout;
    std::vector<std::shared_ptr<glsl_shader_storage_block_t>> shader_storage_blocks;
    std::vector<std::shared_ptr<glsl_shader_storage_block_state>> shader_storage_block_states;
};

class gl_shader_storage_buffer final{
public:
    gl_shader_storage_buffer() = default;
    explicit gl_shader_storage_buffer(const gl_shader_storage_buffer_descriptor& descriptor)
    {
        _initialize_ssbo(descriptor);
    }

public:

    void bind()
    {}

    void unbind();

    void flush_dirty_blocks()
    {

    }

private:

    void _generate_memory_layout()
    {

    }

    void _initialize_ssbo(const gl_shader_storage_buffer_descriptor& descriptor)
    {
        switch (descriptor.memory_layout) {
            case gl_shader_storage_buffer_memory_layout::std140:
                _initialize_ssbo_std140(descriptor);
                break;
            case gl_shader_storage_buffer_memory_layout::std430:
                _initialize_ssbo_std430(descriptor);
                break;
        }
    }

    void _initialize_ssbo_std140(const gl_shader_storage_buffer_descriptor& descriptor)
    {

    }

    void _initialize_ssbo_std430(const gl_shader_storage_buffer_descriptor& descriptor)
    {}


};

#endif

