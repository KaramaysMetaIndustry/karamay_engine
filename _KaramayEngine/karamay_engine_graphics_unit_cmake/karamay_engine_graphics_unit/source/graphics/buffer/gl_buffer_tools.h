#ifndef H_GL_BUFFER_TOOLS
#define H_GL_BUFFER_TOOLS

#include "public/_glew.h"

#define STATIC_ASSERT_GLSL_T()\
static_assert(\
        std::is_same<GLSL_T, glsl_float>::value ||\
        std::is_same<GLSL_T, glsl_vec2>::value ||\
        std::is_same<GLSL_T, glsl_vec3>::value ||\
        std::is_same<GLSL_T, glsl_vec4>::value ||\
        std::is_same<GLSL_T, glsl_double>::value ||\
        std::is_same<GLSL_T, glsl_dvec2>::value ||\
        std::is_same<GLSL_T, glsl_dvec3>::value ||\
        std::is_same<GLSL_T, glsl_dvec4>::value ||\
        std::is_same<GLSL_T, glsl_int>::value ||\
        std::is_same<GLSL_T, glsl_ivec2>::value ||\
        std::is_same<GLSL_T, glsl_ivec3>::value ||\
        std::is_same<GLSL_T, glsl_ivec4>::value ||\
        std::is_same<GLSL_T, glsl_uint>::value ||\
        std::is_same<GLSL_T, glsl_uvec2>::value ||\
        std::is_same<GLSL_T, glsl_uvec3>::value ||\
        std::is_same<GLSL_T, glsl_uvec4>::value ||\
        std::is_same<GLSL_T, glsl_mat2>::value ||\
        std::is_same<GLSL_T, glsl_mat2x3>::value ||\
        std::is_same<GLSL_T, glsl_mat2x4>::value ||\
        std::is_same<GLSL_T, glsl_mat3>::value ||\
        std::is_same<GLSL_T, glsl_mat3x2>::value ||\
        std::is_same<GLSL_T, glsl_mat3x4>::value ||\
        std::is_same<GLSL_T, glsl_mat4>::value ||\
        std::is_same<GLSL_T, glsl_mat4x2>::value ||\
        std::is_same<GLSL_T, glsl_mat4x3>::value ||\
        std::is_same<GLSL_T, glsl_dmat2>::value ||\
        std::is_same<GLSL_T, glsl_dmat2x3>::value ||\
        std::is_same<GLSL_T, glsl_dmat2x4>::value ||\
        std::is_same<GLSL_T, glsl_dmat3>::value ||\
        std::is_same<GLSL_T, glsl_dmat3x2>::value ||\
        std::is_same<GLSL_T, glsl_dmat3x4>::value ||\
        std::is_same<GLSL_T, glsl_dmat4>::value ||\
        std::is_same<GLSL_T, glsl_dmat4x2>::value ||\
        std::is_same<GLSL_T, glsl_dmat4x3>::value\
        , "GLSL_T must be glsl_*")\

enum class internal_format : GLenum
{
    R8 = GL_R8,
    R16 = GL_R16,
    R16F = GL_R16F,
    R32F = GL_R32F,
    R8I = GL_R8I,
    R16I = GL_R16I,
    R32I = GL_R32I,
    R8UI = GL_R8UI,
    R16UI = GL_R16UI,
    R32UI = GL_R32UI,
    RG8 = GL_RG8,
    RG16 = GL_RG16,
    RG16F = GL_RG16F,
    RG32F = GL_RG32F,
    RG8I = GL_RG8I,
    RG16I = GL_RG16I,
    RG32I = GL_RG32I,
    RG8UI = GL_RG8UI,
    RG16UI = GL_RG16UI,
    RG32UI = GL_RG32UI,
    RGB32F = GL_RGB32F,
    RGB32I = GL_RGB32I,
    RGB32UI = GL_RGB32UI,
    RGBA8 = GL_RGBA8,
    RGBA16 = GL_RGBA16,
    RGBA16F = GL_RGBA16F,
    RGBA32F = GL_RGBA32F,
    RGBA8I = GL_RGBA8I,
    RGBA16I = GL_RGBA16I,
    RGBA32I = GL_RGBA32I,
    RGBA8UI = GL_RGBA8UI,
    RGBA16UI = GL_RGBA16UI,
    RGBA32UI = GL_RGBA32UI
};

enum class format : GLenum
{
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    BGR = GL_BGR,
    RGBA = GL_RGBA,
    BGRA = GL_BGRA,
    RED_INTEGER = GL_RED_INTEGER,
    RG_INTEGER = GL_RG_INTEGER,
    RGB_INTEGER = GL_RGB_INTEGER,
    BGR_INTEGER = GL_BGR_INTEGER,
    RGBA_INTEGER = GL_RGBA_INTEGER,
    BGRA_INTEGER = GL_BGRA_INTEGER,
    STENCIL_INDEX = GL_STENCIL_INDEX,
    DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    DEPTH_STENCIL = GL_DEPTH_STENCIL
};

enum class data_type : GLenum
{
    HALF_FLOAT = GL_HALF_FLOAT,
    FLOAT = GL_FLOAT,

    BYTE = GL_BYTE,
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    SHORT = GL_SHORT,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    INT = GL_INT,
    UNSIGNED_INT = GL_UNSIGNED_INT,

    UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
    UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
    UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
    UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
    UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
    UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
    UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
    UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
    UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
};

enum class access : GLenum
{
    READ_WRITE = GL_READ_WRITE,
    READ_ONLY = GL_READ_ONLY,
    WRITE_ONLY = GL_WRITE_ONLY
};

enum class gl_buffer_storage_flag : GLenum
{
    MAP_READ_BIT = GL_MAP_READ_BIT,
    MAP_WRITE_BIT = GL_MAP_WRITE_BIT,
    DYNAMIC_STORAGE_BIT = GL_DYNAMIC_STORAGE_BIT,
    CLIENT_STORAGE_BIT = GL_CLIENT_STORAGE_BIT,
    MAP_PERSISTENT_BIT = GL_MAP_PERSISTENT_BIT,
    MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT
};

struct gl_buffer_storage_options
{
    std::uint8_t is_map_read;
    std::uint8_t is_map_write;
    std::uint8_t is_dynamic_storage;
    std::uint8_t is_client_storage;
    std::uint8_t is_map_persistent;
    std::uint8_t is_map_coherent;

    bool operator==(const gl_buffer_storage_options& other) const
    {
        return other.is_map_read == is_map_read &&
        other.is_map_write == is_map_write &&
        other.is_map_coherent == is_map_coherent &&
        other.is_map_persistent == is_map_persistent &&
        other.is_dynamic_storage == is_dynamic_storage &&
        other.is_client_storage == is_client_storage;
    }
};

enum class gl_buffer_map_access_flag : GLenum
{
    MAP_READ_BIT = GL_MAP_READ_BIT,
    MAP_WRITE_BIT = GL_MAP_WRITE_BIT,
    MAP_PERSISTENT = GL_MAP_PERSISTENT_BIT,
    MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT,

    MAP_INVALIDATE_RANGE_BIT = GL_MAP_INVALIDATE_RANGE_BIT,
    MAP_INVALIDATE_BUFFER_BIT = GL_MAP_INVALIDATE_BUFFER_BIT,
    MAP_FLUSH_EXPLICIT_BIT = GL_MAP_FLUSH_EXPLICIT_BIT,
    MAP_UNSYNCHRONIZED_BIT = GL_MAP_UNSYNCHRONIZED_BIT
};

enum class gl_buffer_type
{

};

enum class gl_buffer_memory_barrier_flag
{
    VERTEX_ATTRIB_ARRAY_BARRIER_BIT = GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT,
    ELEMENT_ARRAY_BARRIER_BIT = GL_ELEMENT_ARRAY_BARRIER_BIT,
    TRANSFORM_FEEDBACK_BARRIER_BIT = GL_TRANSFORM_FEEDBACK_BARRIER_BIT,

    UNIFORM_BARRIER_BIT = GL_UNIFORM_BARRIER_BIT,
    SHADER_STORAGE_BARRIER_BIT = GL_SHADER_STORAGE_BARRIER_BIT,
    ATOMIC_COUNTER_BARRIER_BIT = GL_ATOMIC_COUNTER_BARRIER_BIT,

    FRAMEBUFFER_BARRIER_BIT = GL_FRAMEBUFFER_BARRIER_BIT,

    TEXTURE_FETCH_BARRIER_BIT = GL_TEXTURE_FETCH_BARRIER_BIT,

    SHADER_IMAGE_ACCESS_BARRIER_BIT = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,

    COMMAND_BARRIER_BIT = GL_COMMAND_BARRIER_BIT,

    PIXEL_BUFFER_BARRIER_BIT = GL_PIXEL_BUFFER_BARRIER_BIT,

    TEXTURE_UPDATE_BARRIER_BIT = GL_TEXTURE_UPDATE_BARRIER_BIT,
    BUFFER_UPDATE_BARRIER_BIT = GL_BUFFER_UPDATE_BARRIER_BIT
};

enum class gl_buffer_memory_barrier_region_flag
{
    UNIFORM_BARRIER_BIT = GL_UNIFORM_BARRIER_BIT,
    SHADER_STORAGE_BARRIER_BIT = GL_SHADER_STORAGE_BARRIER_BIT,
    ATOMIC_COUNTER_BARRIER_BIT = GL_ATOMIC_COUNTER_BARRIER_BIT,

    FRAMEBUFFER_BARRIER_BIT = GL_FRAMEBUFFER_BARRIER_BIT,

    SHADER_IMAGE_ACCESS_BARRIER_BIT = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,

    TEXTURE_FETCH_BARRIER_BIT = GL_TEXTURE_FETCH_BARRIER_BIT
};


#endif
