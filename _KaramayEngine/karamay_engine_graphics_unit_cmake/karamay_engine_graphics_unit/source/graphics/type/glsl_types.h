#ifndef H_GLSL_TYPES
#define H_GLSL_TYPES

#include "public/glm.h"


enum class glsl_transparent_clazz_component_type : std::uint8_t
{
    FLOAT,
    DOUBLE,
    UINT,
    INT,
};

constexpr std::uint32_t to_gl_enum(glsl_transparent_clazz_component_type component_type)
{
    switch (component_type) {
        case glsl_transparent_clazz_component_type::FLOAT: return GL_FLOAT;
        case glsl_transparent_clazz_component_type::DOUBLE: return GL_DOUBLE;
        case glsl_transparent_clazz_component_type::UINT: return GL_UNSIGNED_INT;
        case glsl_transparent_clazz_component_type::INT: return GL_INT;
        default: return 0;
    }
}

constexpr const char* to_string(glsl_transparent_clazz_component_type component_type)
{
    switch (component_type) {
        case glsl_transparent_clazz_component_type::FLOAT: return "FLOAT";
        case glsl_transparent_clazz_component_type::DOUBLE: return "DOUBLE";
        case glsl_transparent_clazz_component_type::UINT: return "UINT";
        case glsl_transparent_clazz_component_type::INT: return "INT";
        default: return "";
    }
}

struct glsl_transparent_clazz
{
    glsl_transparent_clazz_component_type component_type;
    std::uint32_t component_type_gl_enum;
    std::string component_type_name;
    std::uint32_t component_size;
    std::uint32_t components_count;

    std::uint32_t type_size;
    std::string type_name;


    glsl_transparent_clazz(glsl_transparent_clazz_component_type _component_type) :
        component_type(_component_type),
        component_type_gl_enum(to_gl_enum(_component_type)),
        component_type_name(to_string(_component_type)),
        type_size(0),
        type_name("float")
    {

    }

};

struct glsl_basic_clazz : public glsl_transparent_clazz
{

};

struct glsl_matrix_clazz : public glsl_transparent_clazz
{

};


class glsl_transparent_t
{
private:
    static const glsl_transparent_clazz _transparent_type_meta;

public:

    [[nodiscard]] virtual const glsl_transparent_clazz& meta() const { return _transparent_type_meta;}

    [[nodiscard]] virtual const std::uint8_t* data() const = 0;

    [[nodiscard]] virtual std::uint32_t size() const = 0;

};

class glsl_basic_t : public glsl_transparent_t {};

class glsl_matrix_t : public glsl_transparent_t {};


class glsl_float : public glsl_basic_t
{
private:

    static const glsl_transparent_clazz _float_meta_data;

public:

    glm::vec1 value;

public:

    [[nodiscard]] const glsl_transparent_clazz& meta() const override { return _float_meta_data;}

    explicit glsl_float(std::float_t value) :
        value(value)
    {

    }
};

class glsl_vec2 : public glsl_basic_t
{
public:
    glm::vec2 core;
};

class glsl_vec3 : public glsl_basic_t
{
public:
    glm::vec3 core;
};

class glsl_vec4 : public glsl_basic_t
{
public:
    glm::vec4 core;
};

class glsl_mat2 : public glsl_matrix_t
{
public:
    glm::mat2 core;
};

class glsl_mat2x3 : public glsl_matrix_t
{
public:
    glm::mat2x3 core;
};

class glsl_mat2x4 : public glsl_matrix_t
{
public:
    glm::mat2x4 core;
};

class glsl_mat3 : public glsl_matrix_t
{
public:
    glm::mat3 core;
};

class glsl_mat3x2 : public glsl_matrix_t
{
public:
    glm::mat3x2 core;
};

class glsl_mat3x4 : public glsl_matrix_t
{
public:
    glm::mat3x4 core;
};

class glsl_mat4 : public glsl_matrix_t
{
public:
    glm::mat4 core;
};

class glsl_mat4x3 : public glsl_matrix_t
{
public:
    glm::mat4x3 core;
};

class glsl_mat4x2 : public glsl_matrix_t
{
public:
    glm::mat4x2 core;
};





#endif
