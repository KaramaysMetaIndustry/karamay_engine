#ifndef H_GLSL_TYPES
#define H_GLSL_TYPES

#include "public/glm.h"

//
//enum class glsl_transparent_clazz_component_type : std::uint8_t
//{
//    FLOAT,
//    DOUBLE,
//    UINT,
//    INT,
//};
//
//constexpr std::uint32_t to_gl_enum(glsl_transparent_clazz_component_type component_type)
//{
//    switch (component_type) {
//        case glsl_transparent_clazz_component_type::FLOAT: return GL_FLOAT;
//        case glsl_transparent_clazz_component_type::DOUBLE: return GL_DOUBLE;
//        case glsl_transparent_clazz_component_type::UINT: return GL_UNSIGNED_INT;
//        case glsl_transparent_clazz_component_type::INT: return GL_INT;
//        default: return 0;
//    }
//}
//
//constexpr const char* to_string(glsl_transparent_clazz_component_type component_type)
//{
//    switch (component_type) {
//        case glsl_transparent_clazz_component_type::FLOAT: return "FLOAT";
//        case glsl_transparent_clazz_component_type::DOUBLE: return "DOUBLE";
//        case glsl_transparent_clazz_component_type::UINT: return "UINT";
//        case glsl_transparent_clazz_component_type::INT: return "INT";
//        default: return "";
//    }
//}
//

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
