#ifndef H_GL_SHADER_STORAGE_BUFFER
#define H_GL_SHADER_STORAGE_BUFFER

#include "public/stl.h"
#include "graphics/buffers/specialization/gl_uniform_buffer.h"

enum class layout
{
    std140,
    std430
};

enum class matrix_layout
{
    row_major,
    column_major
};

class gl_shader_storage_buffer final{
public:
    gl_shader_storage_buffer() = default;
    explicit gl_shader_storage_buffer(const std::vector<std::shared_ptr<glsl_shader_storage_block_t>>& shader_storage_blocks)
    {

    }

public:

    void bind()
    {}

    void unbind();

    void flush_dirty_blocks()
    {

    }

private:

    void _initialize_ssbo(const std::vector<std::shared_ptr<glsl_shader_storage_block_t>>& shader_storage_blocks)
    {

    }


};

#endif

