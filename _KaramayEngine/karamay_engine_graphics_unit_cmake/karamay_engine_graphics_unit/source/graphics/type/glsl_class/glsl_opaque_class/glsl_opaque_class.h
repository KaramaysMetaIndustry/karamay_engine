//
// Created by jichengcheng on 2021/7/15.
//

#ifndef KARAMAY_ENGINE_GRAPHICS_UNIT_GLSL_OPAQUE_CLASS_H
#define KARAMAY_ENGINE_GRAPHICS_UNIT_GLSL_OPAQUE_CLASS_H

#include "graphics/type/glsl_class/glsl_class.h"

class glsl_opaque_clazz : public glsl_clazz
{

};

class glsl_opaque_class : public glsl_class
{
protected:
    
    glsl_opaque_class() = default;

};


class glsl_sampler : public glsl_opaque_class
{
public:
    
    glsl_sampler(std::uint32_t unit)
    {}
};

class glsl_sampler2D : public glsl_sampler
{

};

class glsl_sampler2DRect
{};

class glsl_sampler3D
{};

class glsl_samplerCube
{

};







#endif
