#ifndef H_GLSL_TYPES
#define H_GLSL_TYPES

#include "public/glm.h"

using glsl_bool = glm::bvec1;
using glsl_bvec2 = glm::bvec2;
using glsl_bvec3 = glm::bvec3;
using glsl_bvec4 = glm::bvec4;

using glsl_int = glm::ivec1;
using glsl_ivec2 = glm::ivec2;
using glsl_ivec3= glm::ivec3;
using glsl_ivec4= glm::ivec4;

using glsl_uint = glm::uvec1;
using glsl_uvec2 = glm::uvec2;
using glsl_uvec3 = glm::uvec3;
using glsl_uvec4 = glm::uvec4;

using glsl_float = glm::vec1;
using glsl_vec2 = glm::vec2;
using glsl_vec3 = glm::vec3;
using glsl_vec4 = glm::vec4;

using glsl_double = glm::dvec1;
using glsl_dvec2 = glm::dvec2;
using glsl_dvec3 = glm::dvec3;
using glsl_dvec4 = glm::dvec4;

using glsl_mat2 = glm::mat2;
using glsl_mat2x3 = glm::mat2x3;
using glsl_mat2x4 = glm::mat2x4;
using glsl_mat3 = glm::mat3;
using glsl_mat3x2 = glm::mat3x2;
using glsl_mat3x4 = glm::mat3x4;
using glsl_mat4 = glm::mat4;
using glsl_mat4x2 = glm::mat4x2;
using glsl_mat4x3 = glm::mat4x3;

using glsl_dmat2 = glm::dmat2;
using glsl_dmat2x3 = glm::dmat2x3;
using glsl_dmat2x4 = glm::dmat2x4;
using glsl_dmat3 = glm::dmat3;
using glsl_dmat3x2 = glm::dmat3x2;
using glsl_dmat3x4 = glm::dmat3x4;
using glsl_dmat4 = glm::dmat4;
using glsl_dmat4x2 = glm::dmat4x2;
using glsl_dmat4x3 = glm::dmat4x3;

using glsl_sampler1D = glm::vec1;
using glsl_sampler1DArray = glm::vec1;

using glsl_sampler2D = glm::vec1;
using glsl_sampler2DMS = glm::vec1;
using glsl_sampler2DMSArray = glm::vec1;
using glsl_sampler2DArray = glm::vec1;
using glsl_sampler2DRect = glm::vec1;

using glsl_sampler3D = glm::vec1;

using glsl_samplerCube = glm::vec1;
using glsl_samplerCubeArray = glm::vec1;

using glsl_samplerBuffer = glm::vec1;

using glsl_sampler1DShadow = glm::vec1;
using glsl_sampler2DShadow = glm::vec1;
using glsl_sampler2DRectShadow = glm::vec1;
using glsl_sampler1DArrayShadow = glm::vec1;
using glsl_sampler2DArrayShadow = glm::vec1;



enum class glsl_type
{
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    MAT2,
    MAT2X3,
    MAT2X4,
    MAT3,
    MAT3X2,
    MAT3X4,
    MAT4,
    MAT4X2,
    MAT4X3,
    DOUBLE,
    DVEC2,
    DVEC3,
    DVEC4,
    DMAT2,
    DMAT2X3,
    DMAT2X4,
    DMAT3,
    DMAT3X2,
    DMAT3X4,
    DMAT4,
    DMAT4X2,
    DMAT4X3,
    INT,
    IVEC2,
    IVEC3,
    IVEC4,
    UINT,
    UVEC2,
    UVEC3,
    UVEC4
};

int64_t get_glsl_type_size(glsl_type type)
{
    switch (type) {
        case glsl_type::FLOAT: return sizeof(glm::vec1);
        case glsl_type::VEC2: return sizeof(glm::vec2);
        case glsl_type::VEC3: return sizeof(glm::vec3);
        case glsl_type::VEC4: return sizeof(glm::vec4);
        case glsl_type::MAT2: return sizeof(glm::mat2);
        case glsl_type::MAT2X3: return sizeof(glm::mat2x3);
        case glsl_type::MAT2X4: return sizeof(glm::mat2x4);
        case glsl_type::MAT3: return sizeof(glm::mat3);
        case glsl_type::MAT3X2: return sizeof(glm::mat3x2);
        case glsl_type::MAT3X4: return sizeof(glm::mat3x4);
        case glsl_type::MAT4: return sizeof(glm::mat4);
        case glsl_type::MAT4X2: return sizeof(glm::mat4x2);
        case glsl_type::MAT4X3: return sizeof(glm::mat4x3);
        case glsl_type::DOUBLE: return sizeof(glm::dvec1);
        case glsl_type::DVEC2: return sizeof(glm::dvec2);
        case glsl_type::DVEC3: return sizeof(glm::dvec3);
        case glsl_type::DVEC4: return sizeof(glm::dvec4);
        case glsl_type::DMAT2: return sizeof(glm::dmat2);
        case glsl_type::DMAT2X3: return sizeof(glm::dmat2x3);
        case glsl_type::DMAT2X4: return sizeof(glm::dmat2x4);
        case glsl_type::DMAT3: return sizeof(glm::dmat3);
        case glsl_type::DMAT3X2: return sizeof(glm::dmat3x2);
        case glsl_type::DMAT3X4: return sizeof(glm::dmat3x4);
        case glsl_type::DMAT4: return sizeof(glm::dmat4);
        case glsl_type::DMAT4X2: return sizeof(glm::dmat4x2);
        case glsl_type::DMAT4X3: return sizeof(glm::dmat4x3);
        case glsl_type::INT: return sizeof(glm::ivec1);
        case glsl_type::IVEC2: return sizeof(glm::ivec2);
        case glsl_type::IVEC3: return sizeof(glm::ivec3);
        case glsl_type::IVEC4: return sizeof(glm::ivec4);
        case glsl_type::UINT: return sizeof(glm::uvec1);
        case glsl_type::UVEC2: return sizeof(glm::uvec2);
        case glsl_type::UVEC3: return sizeof(glm::uvec3);
        case glsl_type::UVEC4: return sizeof(glm::uvec4);
    }
}


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



#endif
