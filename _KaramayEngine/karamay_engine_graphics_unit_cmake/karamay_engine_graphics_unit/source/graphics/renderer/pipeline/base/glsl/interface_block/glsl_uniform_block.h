#ifndef GLSL_UNIFORM_BLOCK_H
#define GLSL_UNIFORM_BLOCK_H

#include "../base/glsl_class.h"
#include "../../resource/buffers/Indexed_buffer/gl_uniform_buffer.h"

enum class glsl_uniform_block_memory_layout
{
    SHARED,
    STD140,
    PACKED
};

/*
 * [transparent type]
 * exp : layout(row_major,std140/shared/packed,binding=0) uniform { ... };
 * pipeline manage 3 ubos
 * */
class glsl_uniform_block : public glsl_interface_block_t
{
public:
    glsl_uniform_block() = delete;
    glsl_uniform_block(
            glsl_interface_block_matrix_layout _matrix_layout,
            glsl_uniform_block_memory_layout _memory_layout
    ) {}
    glsl_uniform_block(const glsl_uniform_block&) = delete;
    glsl_uniform_block& operator=(const glsl_uniform_block&) = delete;

    ~glsl_uniform_block() = default;

public:

    void set_uniform_buffer(gl_uniform_buffer* uniform_buffer)
    {
        _uniform_buffer = uniform_buffer;
    }

    gl_uniform_buffer* get_uniform_buffer() const { return _uniform_buffer; }

public:

    void bind()
    {
        _uniform_buffer->bind();
    }

    void unbind()
    {
        _uniform_buffer->unbind();
    }

private:

    gl_uniform_buffer* _uniform_buffer;

};

#endif
