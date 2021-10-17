#ifndef GLSL_UNIFORM_BLOCK_H
#define GLSL_UNIFORM_BLOCK_H


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
class glsl_uniform_block_t : public glsl_interface_block_t{
public:
    glsl_uniform_block_t() = delete;
    glsl_uniform_block_t(
            glsl_interface_block_matrix_layout _matrix_layout,
            glsl_uniform_block_memory_layout _memory_layout
    ) :
            matrix_layout(_matrix_layout),
            memory_layout(_memory_layout),
            is_dirty(false)
    {}
    glsl_uniform_block_t(const glsl_uniform_block_t&) = delete;
    glsl_uniform_block_t& operator=(const glsl_uniform_block_t&) = delete;

    ~glsl_uniform_block_t() = default;

    const glsl_interface_block_matrix_layout matrix_layout;

    const glsl_uniform_block_memory_layout memory_layout;

public:

    bool is_dirty;


};


#endif
