#ifndef H_GLSL_CLASS
#define H_GLSL_CLASS

#include "public/stl.h"
#include "public/glm.h"
#include "public/_glew.h"


/*
 * glsl type
 *
 * */
class glsl_t {
public:
    [[nodiscard]] virtual const std::string& token() const {};
};

struct glsl_transparent_t_meta
{
    std::uint32_t components_count;
    std::uint32_t component_type_size;
    std::string component_type_name;
    std::uint32_t component_type_gl_enum;
    std::uint32_t type_size;
    std::string semantic_name;

    glsl_transparent_t_meta(
            std::uint32_t _components_count,
            std::uint32_t _component_type_size,
            std::uint32_t _component_type_gl_enum,
            std::uint32_t _type_size,
            std::string _semantic_name) :
            components_count(_components_count),
            component_type_size(_component_type_size),
            component_type_gl_enum(_component_type_gl_enum),
            type_size(_type_size),
            semantic_name(_semantic_name)
    {}
};

/*
 * glsl transparent type
 *
 * */
class glsl_transparent_t : public glsl_t{
public:
    virtual std::uint8_t* data() = 0;
	[[nodiscard]] virtual const std::uint8_t* data() const = 0;
	[[nodiscard]] virtual const std::int64_t size() const = 0;
};

/*
 * glsl opaque type
 * sampler/image/atomic_counter
 * */
class glsl_opaque_t : public glsl_t{

};


/*
 * sampler/image
 * */
class glsl_texture_handler_t : glsl_opaque_t{
public:
    virtual void bind() = 0;
    virtual void unbind() = 0;
};

enum class glsl_storage_qualifier
{
    _const,
    _in,
    _out,
    _uniform,
    _buffer,
    _shared
};

enum class glsl_auxiliary_storage_qualifier
{
    _centroid,
    _sampler,
    _patch,
};

/*
 *
 * */
class glsl_interface_block_t : public glsl_t{
public:
    glsl_interface_block_t() = default;
    glsl_interface_block_t(const glsl_interface_block_t&) = delete;

    ~glsl_interface_block_t() = default;

public:
    virtual std::uint8_t* data() = 0;
    [[nodiscard]] virtual const std::uint8_t* data() const = 0;
    [[nodiscard]] virtual std::int64_t size() const = 0;

};

enum class glsl_interface_block_matrix_layout
{
    ROW_MAJOR,
    COLUMN_MAJOR
};


#define TOKEN_STR(__TOKEN__) #__TOKEN__

#define DEFINE_GLSL_TRANSPARENT_T(GLSL_T_NAME, GLSL_T_SEMANTIC_NAME)\
class glsl_##GLSL_T_NAME final : public glsl_transparent_t{\
public:\
	glsl_##GLSL_T_NAME() = default;\
	explicit glsl_##GLSL_T_NAME(const glm::GLSL_T_SEMANTIC_NAME& value){}\
	~glsl_##GLSL_T_NAME() = default;\
public:\
	glm::GLSL_T_SEMANTIC_NAME client_value;\
};\



// float scalar && vectors && matrices
DEFINE_GLSL_TRANSPARENT_T(float, vec1)
DEFINE_GLSL_TRANSPARENT_T(vec2, vec2)
DEFINE_GLSL_TRANSPARENT_T(vec3, vec3)
DEFINE_GLSL_TRANSPARENT_T(vec4, vec4)
DEFINE_GLSL_TRANSPARENT_T(mat2, mat2)
DEFINE_GLSL_TRANSPARENT_T(mat2x3, mat2x3)
DEFINE_GLSL_TRANSPARENT_T(mat2x4, mat2x4)
DEFINE_GLSL_TRANSPARENT_T(mat3, mat3)
DEFINE_GLSL_TRANSPARENT_T(mat3x2, mat3x2)
DEFINE_GLSL_TRANSPARENT_T(mat3x4, mat3x4)
DEFINE_GLSL_TRANSPARENT_T(mat4, mat4)
DEFINE_GLSL_TRANSPARENT_T(mat4x2, mat4x2)
DEFINE_GLSL_TRANSPARENT_T(mat4x3, mat4x3)
// double scalar && vectors && matrices
DEFINE_GLSL_TRANSPARENT_T(double, dvec1)
DEFINE_GLSL_TRANSPARENT_T(dvec2, dvec2)
DEFINE_GLSL_TRANSPARENT_T(dvec3, dvec3)
DEFINE_GLSL_TRANSPARENT_T(dvec4, dvec4)
DEFINE_GLSL_TRANSPARENT_T(dmat2, dmat2)
DEFINE_GLSL_TRANSPARENT_T(dmat2x3, dmat2x3)
DEFINE_GLSL_TRANSPARENT_T(dmat2x4, dmat2x4)
DEFINE_GLSL_TRANSPARENT_T(dmat3, dmat3)
DEFINE_GLSL_TRANSPARENT_T(dmat3x2, dmat3x2)
DEFINE_GLSL_TRANSPARENT_T(dmat3x4, dmat3x4)
DEFINE_GLSL_TRANSPARENT_T(dmat4, dmat4)
DEFINE_GLSL_TRANSPARENT_T(dmat4x2, dmat4x2)
DEFINE_GLSL_TRANSPARENT_T(dmat4x3, dmat4x3)
// int scalar && vectors
DEFINE_GLSL_TRANSPARENT_T(int, ivec1)
DEFINE_GLSL_TRANSPARENT_T(ivec2, ivec2)
DEFINE_GLSL_TRANSPARENT_T(ivec3, ivec3)
DEFINE_GLSL_TRANSPARENT_T(ivec4, ivec4)
// uint scalar && vectors
DEFINE_GLSL_TRANSPARENT_T(uint, uvec1)
DEFINE_GLSL_TRANSPARENT_T(uvec2, uvec2)
DEFINE_GLSL_TRANSPARENT_T(uvec3, uvec3)
DEFINE_GLSL_TRANSPARENT_T(uvec4, uvec4)


#endif
