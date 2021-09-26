#ifndef H_GLSL_CLASS
#define H_GLSL_CLASS

#include "public/_glew.h"
#include "public/glm.h"
#include "public/stl.h"
#include "graphics/sampler/gl_sampler.h"
#include "graphics/texture/gl_texture.h"

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

class glsl_transparent_t : public glsl_t{
public:
	virtual const glsl_transparent_t_meta& meta() const = 0;
	virtual const std::uint8_t* data() const = 0;

};

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


#endif
