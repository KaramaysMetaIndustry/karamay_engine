#ifndef GLSL_SHADER_STORAGE_BLOCK_H
#define GLSL_SHADER_STORAGE_BLOCK_H

#include "graphics/glsl/glsl_class.h"

enum class glsl_shader_storage_block_memory_layout
{
    STD140,
    STD430
};

/*
 * [transparent type]
 * exp : layout(row_major,std140/std430,binding=0) buffer { ... };
 * these blocks can control their value directly
 * */
class glsl_shader_storage_block_t : public glsl_interface_block_t{
public:
    glsl_shader_storage_block_t() = default;
    glsl_shader_storage_block_t(
            glsl_interface_block_matrix_layout matrix_layout,
            glsl_shader_storage_block_memory_layout memory_layout
    ){}
    glsl_shader_storage_block_t(const glsl_shader_storage_block_t&) = delete;
    glsl_shader_storage_block_t& operator=(const glsl_shader_storage_block_t&) = delete;

    ~glsl_shader_storage_block_t() = default;

public:

    bool is_dirty;

    const std::string& token() const override
    {
        return _token;
    }


private:
    std::string _token;

};

#endif
