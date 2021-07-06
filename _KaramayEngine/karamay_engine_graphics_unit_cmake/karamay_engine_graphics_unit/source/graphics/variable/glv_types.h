#pragma once
#include "public/_glew.h"

namespace glv
{
    using float32 = glm::f32vec1;
    using f32vec2 = glm::f32vec2;
    using f32vec3 = glm::f32vec3;
    using f32vec4 = glm::f32vec4;

    using float64 = glm::f64vec1;
    using f64vec2 = glm::f64vec2;
    using f64vec3 = glm::f64vec3;
    using f64vec4 = glm::f64vec4;

    using int32 = glm::i32vec1;
    using i32vec2 = glm::i32vec2;
    using i32vec3 = glm::i32vec3;
    using i32vec4 = glm::i32vec4;

    using uint32 = glm::u32vec1;
    using ui32vec2 = glm::u32vec2;
    using ui32vec3 = glm::u32vec3;
    using ui32vec4 = glm::u32vec4;

    using f32mat2 = glm::mat2;
    using f32mat2x3 = glm::mat2x3;
    using f32mat2x4 = glm::mat2x4;
    using f32mat3 = glm::mat3;
    using f32mat3x2 = glm::mat3x2;
    using f32mat3x4 = glm::mat3x4;
    using f32mat4 = glm::mat4;
    using f32mat4x2 = glm::mat4x2;
    using f32mat4x3 = glm::mat4x3;

    using f64mat2 = glm::dmat2;
    using f64mat2x3 = glm::dmat2x3;
    using f64mat2x4 = glm::dmat2x4;
    using f64mat3 = glm::dmat3;
    using f64mat3x2 = glm::dmat3x2;
    using f64mat3x4 = glm::dmat3x4;
    using f64mat4 = glm::dmat4;
    using f64mat4x2 = glm::dmat4x2;
    using f64mat4x3 = glm::dmat4x3;
}

//
//struct glsl_transparent_class
//{
//    std::uint32_t component_type;
//    std::string component_type_name;
//    std::uint32_t component_size;
//    std::uint32_t components_count;
//    std::uint32_t type_size;
//    std::uint32_t type_name;
//
//};
//
//class glsl_transparent_type
//{
//private:
//    static const glsl_transparent_class _transparent_type_meta;
//
//public:
//
//    virtual glsl_transparent_class meta(){ return _transparent_type_meta;}
//
//};
//
//class glsl_float : public glsl_transparent_type
//{
//private:
//
//    static const glsl_transparent_class _float_meta_data;
//
//public:
//
//    glsl_transparent_class meta() override { return _float_meta_data;}
//
//
//public:
//
//    glm::vec1 value;
//
//};
//
//#define DEFINE_GLSL_TRANSPARENT(CORE_NAME) \
//class glsl_##CORE_NAME : public glsl_transparent_type\
//{\
//private:\
//\
//static const glsl_transparent_class _##CORE_NAME##_meta_data;\
//\
//public:\
//\
//glsl_transparent_class meta() override { return _##CORE_NAME##_meta_data;}\
//\
//};\
//
//
//DEFINE_GLSL_TRANSPARENT(vec2)
//DEFINE_GLSL_TRANSPARENT(vec3)
//DEFINE_GLSL_TRANSPARENT(vec4)
//DEFINE_GLSL_TRANSPARENT(double)
//DEFINE_GLSL_TRANSPARENT(dvec2)
//DEFINE_GLSL_TRANSPARENT(dvec3)
//DEFINE_GLSL_TRANSPARENT(dvec4)
//
//DEFINE_GLSL_TRANSPARENT(int)
//DEFINE_GLSL_TRANSPARENT(ivec2)
//DEFINE_GLSL_TRANSPARENT(ivec3)
//DEFINE_GLSL_TRANSPARENT(ivec4)
//DEFINE_GLSL_TRANSPARENT(uint)
//DEFINE_GLSL_TRANSPARENT(uvec2)
//DEFINE_GLSL_TRANSPARENT(uvec3)
//DEFINE_GLSL_TRANSPARENT(uvec4)
//
//
//void test()
//{
//    glsl_vec2* uv = new glsl_vec2();
//
//
//}



