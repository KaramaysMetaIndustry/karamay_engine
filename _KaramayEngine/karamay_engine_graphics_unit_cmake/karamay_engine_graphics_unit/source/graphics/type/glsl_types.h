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


};


enum class glsl_basic_component_type
{
    FLOAT,
    DOUBLE,
    UINT,
    INT,
};

enum class glsl_basic_attribute_type
{
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    DOUBLE,
    DVEC2,
    DVEC3,
    DVEC4,

    INT,
    IVEC2,
    IVEC3,
    IVEC4,
    UINT,
    UVEC2,
    UVEC3,
    UVEC4
};

//class glsl_basic_t : public glsl_transparent_t {
//public:
//    virtual glsl_basic_component_type get_component_type() = 0;
//    virtual GLenum get_component_type_GLenum() = 0;
//    virtual std::string get_component_type_name() = 0;
//    virtual std::int64_t get_component_type_size() = 0;
//    virtual std::int32_t get_components_count() = 0;
//    virtual glsl_basic_attribute_type get_attribute_type() = 0;
//    virtual std::string get_attribute_type_name() = 0;
//    virtual std::int64_t get_attribute_type_size() = 0;
//    virtual const std::uint8_t* get_data() = 0;
//};
//
//class glsl_float : public glsl_basic_t
//{
//public:
//    glsl_basic_component_type get_component_type() override {return glsl_basic_component_type::FLOAT;}
//    GLenum get_component_type_GLenum() override {return GL_FLOAT;}
//    std::string get_component_type_name() override {return "FLOAT";}
//    std::int64_t get_component_type_size() override {return sizeof(GLfloat);}
//    std::int32_t get_components_count() override {return 1;}
//    glsl_basic_attribute_type get_attribute_type() override {return glsl_basic_attribute_type::FLOAT;}
//    std::string get_attribute_type_name() override {return "float";}
//    std::int64_t get_attribute_type_size() override {return sizeof(GLfloat);}
//    const std::uint8_t* get_data() override { return reinterpret_cast<const std::uint8_t*>(glm::value_ptr(core)); }
//
//public:
//
//    glm::vec1 core;
//
//public:
//    explicit glsl_float(std::float_t x) :
//        core(x)
//    {
//    }
//
//
//};
//
//class glsl_vec2 : public glsl_basic_t
//{
//public:
//    glsl_basic_component_type get_component_type() override {return glsl_basic_component_type::FLOAT;}
//    GLenum get_component_type_GLenum() override {return GL_FLOAT;}
//    std::string get_component_type_name() override {return "FLOAT";}
//    std::int64_t get_component_type_size() override {return sizeof(GLfloat);}
//    std::int32_t get_components_count() override {return 2;}
//    glsl_basic_attribute_type get_attribute_type() override {return glsl_basic_attribute_type::VEC2;}
//    std::string get_attribute_type_name() override {return "vec2";}
//    std::int64_t get_attribute_type_size() override {return sizeof(GLfloat) * 2;}
//    const std::uint8_t* get_data() override { return reinterpret_cast<const std::uint8_t*>(glm::value_ptr(core)); }
//public:
//    glm::vec2 core;
//
//};
//
//class glsl_vec3 : public glsl_basic_t
//{
//public:
//    glsl_basic_component_type get_component_type() override {return glsl_basic_component_type::FLOAT;}
//    GLenum get_component_type_GLenum() override {return GL_FLOAT;}
//    std::string get_component_type_name() override {return "FLOAT";}
//    std::int64_t get_component_type_size() override {return sizeof(GLfloat);}
//    std::int32_t get_components_count() override {return 3;}
//    glsl_basic_attribute_type get_attribute_type() override {return glsl_basic_attribute_type::VEC3;}
//    std::string get_attribute_type_name() override {return "vec3";}
//    std::int64_t get_attribute_type_size() override {return sizeof(GLfloat) * 3;}
//    const std::uint8_t* get_data() override { return reinterpret_cast<const std::uint8_t*>(glm::value_ptr(core)); }
//public:
//    glm::vec3 core;
//};

//class glsl_vec4 : public glsl_basic_t
//{
//public:
//    glm::vec4 core;
//};
//
//class glsl_matrix_t
//{};
//
//class glsl_mat2 : public glsl_matrix_t
//{
//public:
//    glm::mat2 core;
//};
//
//class glsl_mat2x3 : public glsl_matrix_t
//{
//public:
//    glm::mat2x3 core;
//};
//
//class glsl_mat2x4 : public glsl_matrix_t
//{
//public:
//    glm::mat2x4 core;
//};
//
//class glsl_mat3 : public glsl_matrix_t
//{
//public:
//    glm::mat3 core;
//};
//
//class glsl_mat3x2 : public glsl_matrix_t
//{
//public:
//    glm::mat3x2 core;
//};
//
//class glsl_mat3x4 : public glsl_matrix_t
//{
//public:
//    glm::mat3x4 core;
//};
//
//class glsl_mat4 : public glsl_matrix_t
//{
//public:
//    glm::mat4 core;
//};
//
//class glsl_mat4x3 : public glsl_matrix_t
//{
//public:
//    glm::mat4x3 core;
//};
//
//class glsl_mat4x2 : public glsl_matrix_t
//{
//public:
//    glm::mat4x2 core;
//};


using glsl_float = glm::vec1;
using glsl_vec2 = glm::vec2;
using glsl_vec3 = glm::vec3;
using glsl_vec4 = glm::vec4;

using glsl_mat2 = glm::mat2;
using glsl_mat2x3 = glm::mat2x3;
using glsl_mat2x4 = glm::mat2x4;
using glsl_mat3 = glm::mat3;
using glsl_mat3x2 = glm::mat3x2;
using glsl_mat3x4 = glm::mat3x4;
using glsl_mat4 = glm::mat4;
using glsl_mat4x2 = glm::mat4x2;
using glsl_mat4x3 = glm::mat4x3;

using glsl_double = glm::dvec1;
using glsl_dvec2 = glm::dvec2;
using glsl_dvec3 = glm::dvec3;
using glsl_dvec4 = glm::dvec4;

using glsl_dmat2 = glm::dmat2;
using glsl_dmat2x3 = glm::dmat2x3;
using glsl_dmat2x4 = glm::dmat2x4;
using glsl_dmat3 = glm::dmat3;
using glsl_dmat3x2 = glm::dmat3x2;
using glsl_dmat3x4 = glm::dmat3x4;
using glsl_dmat4 = glm::dmat4;
using glsl_dmat4x2 = glm::dmat4x2;
using glsl_dmat4x3 = glm::dmat4x3;

using glsl_uint = glm::uvec1;
using glsl_uvec2 = glm::uvec2;
using glsl_uvec3 = glm::uvec3;
using glsl_uvec4 = glm::uvec4;

using glsl_int = glm::ivec1;
using glsl_ivec2 = glm::ivec2;
using glsl_ivec3= glm::ivec3;
using glsl_ivec4= glm::ivec4;

using glsl_bool = glm::bvec1;
using glsl_bvec2 = glm::bvec2;
using glsl_bvec3 = glm::bvec3;
using glsl_bvec4 = glm::bvec4;

#endif
