#ifndef GLSL_UNIFORM_BLOCK_H
#define GLSL_UNIFORM_BLOCK_H

#include "graphics/glsl/glsl_class.h"

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

public:
    virtual const std::string token() {}


};

struct MatrixGroup
{
    glsl_mat4x2 m0;
    glsl_mat4x2 m1;
    glsl_mat4x2 m2;
};


#define DEFINE_UNIFORM_BLOCK(BLOCK_NAME, MATRIX_LAYOUT, MEMORY_LAYOUT)\
class glsl_uniform_block_BLOCK_NAME : public glsl_uniform_block_t{\
public:\
    glsl_uniform_block_BLOCK_NAME() : glsl_uniform_block_t(glsl_interface_block_matrix_layout::MATRIX_LAYOUT, glsl_uniform_block_memory_layout::MEMORY_LAYOUT) {}\
    \
    struct glsl_uniform_block_BLOCK_NAME_scope\
    {\
        MatrixGroup group[1][2];\
    } scope;\
\
    std::uint8_t* data() override\
    {\
        return reinterpret_cast<std::uint8_t*>(&scope);\
    }\
\
    const std::uint8_t* data() const override\
    {\
        return reinterpret_cast<const std::uint8_t*>(&scope);\
    }\
\
    std::int64_t size() const override\
    {\
        return sizeof(glsl_uniform_block_BLOCK_NAME_scope);\
    }\
};\
std::shared_ptr<glsl_uniform_block_BLOCK_NAME> (BLOCK_NAME);\


struct glsl_item{
    glsl_item(){}
};

class glsl_uniform_block_t0 : public glsl_uniform_block_t{
public:
    glsl_uniform_block_t0() : glsl_uniform_block_t(glsl_interface_block_matrix_layout::ROW_MAJOR, glsl_uniform_block_memory_layout::STD140){}


    struct glsl_uniform_block_t0_scope
    {
        //MatrixGroup group[1][2];
        //DEFINE_GLSL_TRANSPARENT_T(MatrixGroup, group, [1][2])

        static std::string token;
    } scope;

public:

    [[nodiscard]] const std::uint8_t* data() const override
    {
        return reinterpret_cast<const std::uint8_t*>(&scope);
    }

    std::uint8_t* data() override
    {
        return reinterpret_cast<std::uint8_t*>(&scope);
    }

    [[nodiscard]] std::int64_t size() const override
    {
        return sizeof(glsl_uniform_block_t0_scope);
    }

    [[nodiscard]] const std::string& token() const override
    {
        return glsl_uniform_block_t0_scope::token;
    }

};

template<typename T, typename...GLSL_TRANSPARENT_T>
struct glsl_uniform_block_der
{

};



#endif
