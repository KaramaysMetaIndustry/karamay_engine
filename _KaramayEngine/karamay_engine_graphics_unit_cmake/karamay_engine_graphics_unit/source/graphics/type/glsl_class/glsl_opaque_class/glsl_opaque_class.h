#ifndef KARAMAY_ENGINE_GRAPHICS_UNIT_GLSL_OPAQUE_CLASS_H
#define KARAMAY_ENGINE_GRAPHICS_UNIT_GLSL_OPAQUE_CLASS_H

#include "graphics/type/glsl_class/glsl_class.h"
#include "graphics/texture/gl_texture.h"

class glsl_opaque_clazz : public glsl_clazz
{

};

class glsl_opaque_class : public glsl_class
{
protected:
    
    glsl_opaque_class() = default;

};


class glsl_sampler_clazz : public glsl_opaque_clazz
{};

class glsl_sampler : public glsl_opaque_class
{
    std::uint32_t value;
    std::string sematic_name;
    std::shared_ptr<gl_texture_base> texture;

    void bind(std::uint32_t unit_index)
    {
        texture->bind(unit_index);
    }

    void unbind()
    {
        texture->unbind();
    }
};

class glsl_sampler1D : public glsl_sampler 
{
};

class glsl_sampler2D : public glsl_sampler
{

};

class glsl_sampler2DRect : public glsl_sampler
{};

class glsl_sampler3D : public glsl_sampler
{};

class glsl_samplerCube : public glsl_sampler
{

};



#endif
