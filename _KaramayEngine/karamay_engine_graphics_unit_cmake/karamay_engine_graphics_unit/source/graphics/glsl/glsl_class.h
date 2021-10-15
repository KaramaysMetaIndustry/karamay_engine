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
    [[nodiscard]] const std::string& token() const {return _token;}

protected:
    std::string _token;
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
	virtual const glsl_transparent_t_meta& meta() const = 0;
	virtual const std::uint8_t* data() const = 0;

};

/*
 * glsl opaque type
 *
 * */
class glsl_opaque_t : public glsl_t{
protected:
	glsl_opaque_t() = default;
	~glsl_opaque_t() = default;

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

enum class glsl_layout_qualifier
{

};



template<typename t>
constexpr std::uint32_t to_enum() { return 0; }
template<>
constexpr std::uint32_t to_enum<glm::vec1::value_type>() { return GL_FLOAT; }
template<>
constexpr std::uint32_t to_enum<glm::dvec1::value_type>() { return GL_DOUBLE; }
template<>
constexpr std::uint32_t to_enum<glm::uvec1::value_type>() { return GL_UNSIGNED_INT; }
template<>
constexpr std::uint32_t to_enum<glm::ivec1::value_type>() { return GL_INT; }

//
//class glsl_dvec3 final : public glsl_transparent_t
//{
//public:
//    glsl_dvec3() = delete;
//    explicit glsl_dvec3(const glm::dvec3& value) {}
//    ~glsl_dvec3() = default;
//public:
//    glm::dvec3 client_value;
//private:
//    static const glsl_transparent_t_meta _meta;
//public:
//    const glsl_transparent_t_meta& meta() const override { return _meta; };
//    const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(&client_value); };
//};
//const glsl_transparent_t_meta glsl_dvec3::_meta(glm::dvec3::length(), sizeof(glm::dvec3::value_type), to_enum<glm::dvec3::value_type>(), sizeof(glm::dvec3), "dvec3");


#define CLASS_NAME(__CLASS__)  #__CLASS__

#define DEFINE_GLSL_TRANSPARENT_T(GLSL_T_NAME, GLSL_T_SEMANTIC_NAME)\
class glsl_##GLSL_T_NAME final : public glsl_transparent_t\
{\
public:\
	glsl_##GLSL_T_NAME() = default;\
	explicit glsl_##GLSL_T_NAME(const glm::GLSL_T_SEMANTIC_NAME& value){}\
	explicit glsl_##GLSL_T_NAME(std::function<void(glsl_transparent_t*)> _register){}\
	~glsl_##GLSL_T_NAME() = default;\
public:\
	glm::GLSL_T_SEMANTIC_NAME client_value;\
private:\
	static const glsl_transparent_t_meta _meta;\
public:\
	const glsl_transparent_t_meta& meta() const override { return _meta; };\
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(&client_value); };\
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



/*
 * attributes transported between shaders
 *
 * */
class glsl_vertex_stream
{

};


/*
 *
 * */
class glsl_interface_block_t{
public:
    glsl_interface_block_t() = default;
    ~glsl_interface_block_t() = default;

public:

    virtual std::uint8_t* data() = 0;

    virtual std::int64_t size() = 0;

};

enum class glsl_uniform_block_memory_qualifier
{

};
enum class glsl_shader_storage_block_memory_qualifier
{

};

/*
 * transparent
 * layout(std140/shared/packed) uniform { ... };
 * per layout blocks will be backed by one buffer, there will be most 3 buffers for blocks
 * */
class glsl_uniform_block_t : public glsl_interface_block_t{
public:
    glsl_uniform_block_t() = default;
    ~glsl_uniform_block_t() = default;

public:

    void mark_dirty(bool is_dirty) {}

    bool is_dirty(){}

};

/*
 * transparent
 * layout(std140/std430) buffer { ... };
 * per layout buffer blocks will be backed by one buffer, there will be most 2 buffers for blocks
 * */
class glsl_shader_storage_block_t : public glsl_interface_block_t{
public:
    glsl_shader_storage_block_t() = default;

};


/*
 * opaque
 * layout(binding=0, offset=4) uniform atomic_uint one;
 * all counters will be backed by only one buffer
 * */
class glsl_atomic_counter_t : public glsl_opaque_t{
public:
    glsl_atomic_counter_t() : data(0){}
    explicit glsl_atomic_counter_t(std::uint32_t value) : data(value){}
    glsl_atomic_counter_t(const glsl_atomic_counter_t&) = delete;
    glsl_atomic_counter_t& operator=(const glsl_atomic_counter_t&) = delete;

    ~glsl_atomic_counter_t() = default;

    std::uint32_t data;

};


#endif
