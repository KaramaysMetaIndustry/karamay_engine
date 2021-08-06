#ifndef H_GLSL_TRANSPARENT_CLASS
#define H_GLSL_TRANSPARENT_CLASS

#include "graphics/type/glsl_class/glsl_class.h"

//class glsl_transparent_clazz : public glsl_clazz
//{
//protected:
//
//    glsl_transparent_clazz(
//            const std::string& _class_name, std::uint16_t _class_size,
//            const std::string& _class_component_name, std::uint16_t _class_component_size, std::uint32_t _class_component_gl_enum, std::uint8_t _class_component_count) :
//        class_name(_class_name),
//        class_size(_class_size),
//        class_component_name(_class_component_name),
//        class_component_size(_class_component_size),
//        class_component_gl_enum(_class_component_gl_enum),
//        class_component_count(_class_component_count)
//    {}
//
//public:
//
//    [[nodiscard]] virtual class glsl_transparent_class* construct(const std::vector<std::string>& params) const = 0;
//
//public:
//
//    const std::string class_name;
//    const std::uint16_t class_size;
//    const std::string class_component_name;
//    const std::uint16_t class_component_size;
//    const std::uint32_t class_component_gl_enum;
//    const std::uint8_t class_component_count;
//
//};
//
//#define DEFINE_TRANSPARENT_CLAZZ(CLASS_NAME, CLASS_NAME_STR, COMPONENT_NAME_STR, COMPONENT_GL_ENUM, GLM_TYPE) \
//class glsl_##CLASS_NAME##_clazz : public glsl_transparent_clazz\
//{\
//public:\
//glsl_##CLASS_NAME##_clazz() :\
//        glsl_transparent_clazz(CLASS_NAME_STR, sizeof(glm::GLM_TYPE), COMPONENT_NAME_STR, sizeof(glm::GLM_TYPE::value_type), COMPONENT_GL_ENUM, glm::GLM_TYPE::length())\
//{}\
//public:\
//[[nodiscard]] class glsl_transparent_class* construct(const std::vector<std::string>& params) const override;\
//}
//
//
//
////class glsl_float_clazz : public glsl_transparent_clazz
////{
////public:
////
////    glsl_float_clazz() :
////            glsl_transparent_clazz("float", sizeof(glm::vec1), "float", sizeof(glm::vec1::value_type), GL_FLOAT, glm::vec1::length())
////    {}
////
////public:
////
////    [[nodiscard]] class glsl_transparent_class* construct(const std::vector<std::string>& params) const override;
////
////};
//
//DEFINE_TRANSPARENT_CLAZZ(float, "float", "float", GL_FLOAT, vec1);
//DEFINE_TRANSPARENT_CLAZZ(vec2, "vec2", "float", GL_FLOAT, vec2);
//DEFINE_TRANSPARENT_CLAZZ(vec3, "vec3", "float", GL_FLOAT, vec3);
//DEFINE_TRANSPARENT_CLAZZ(vec4, "vec4", "float", GL_FLOAT, vec4);
//
//DEFINE_TRANSPARENT_CLAZZ(mat2, "mat2", "float", GL_FLOAT, mat2);
//DEFINE_TRANSPARENT_CLAZZ(mat2x3, "mat2x3", "float", GL_FLOAT, mat2x3);
//DEFINE_TRANSPARENT_CLAZZ(mat2x4, "mat2x4", "float", GL_FLOAT, mat2x4);
//DEFINE_TRANSPARENT_CLAZZ(mat3, "mat3", "float", GL_FLOAT, mat3);
//DEFINE_TRANSPARENT_CLAZZ(mat3x2, "mat3x2", "float", GL_FLOAT, mat3x2);
//DEFINE_TRANSPARENT_CLAZZ(mat3x4, "mat3x4", "float", GL_FLOAT, mat3x4);
//DEFINE_TRANSPARENT_CLAZZ(mat4, "mat4", "float", GL_FLOAT, mat4);
//DEFINE_TRANSPARENT_CLAZZ(mat4x2, "mat4x2", "float", GL_FLOAT, mat4x2);
//DEFINE_TRANSPARENT_CLAZZ(mat4x3, "mat4x3", "float", GL_FLOAT, mat4x3);
//
//DEFINE_TRANSPARENT_CLAZZ(double, "double", "double", GL_DOUBLE, dvec1);
//DEFINE_TRANSPARENT_CLAZZ(dvec2, "dvec2", "double", GL_DOUBLE, dvec2);
//DEFINE_TRANSPARENT_CLAZZ(dvec3, "dvec3", "double", GL_DOUBLE, dvec3);
//DEFINE_TRANSPARENT_CLAZZ(dvec4, "dvec4", "double", GL_DOUBLE, dvec4);
//
//DEFINE_TRANSPARENT_CLAZZ(dmat2, "dmat2", "double", GL_DOUBLE, dmat2);
//DEFINE_TRANSPARENT_CLAZZ(dmat2x3, "dmat2x3", "double", GL_DOUBLE, dmat2x3);
//DEFINE_TRANSPARENT_CLAZZ(dmat2x4, "dmat2x4", "double", GL_DOUBLE, dmat2x4);
//DEFINE_TRANSPARENT_CLAZZ(dmat3, "dmat3", "double", GL_DOUBLE, dmat3);
//DEFINE_TRANSPARENT_CLAZZ(dmat3x2, "dmat3x2", "double", GL_DOUBLE, dmat3x2);
//DEFINE_TRANSPARENT_CLAZZ(dmat3x4, "dmat3x4", "double", GL_DOUBLE, dmat3x4);
//DEFINE_TRANSPARENT_CLAZZ(dmat4, "dmat4", "double", GL_DOUBLE, dmat4);
//DEFINE_TRANSPARENT_CLAZZ(dmat4x2, "dmat4x2", "double", GL_DOUBLE, dmat4x2);
//DEFINE_TRANSPARENT_CLAZZ(dmat4x3, "dmat4x3", "double", GL_DOUBLE, dmat4x3);
//
//DEFINE_TRANSPARENT_CLAZZ(int, "int", "int", GL_DOUBLE, ivec1);
//DEFINE_TRANSPARENT_CLAZZ(ivec2, "ivec2", "int", GL_DOUBLE, ivec2);
//DEFINE_TRANSPARENT_CLAZZ(ivec3, "ivec3", "int", GL_DOUBLE, ivec3);
//DEFINE_TRANSPARENT_CLAZZ(ivec4, "ivec4", "int", GL_DOUBLE, ivec4);
//
//DEFINE_TRANSPARENT_CLAZZ(uint, "uint", "uint", GL_DOUBLE, uvec1);
//DEFINE_TRANSPARENT_CLAZZ(uvec2, "uvec2", "uint", GL_DOUBLE, uvec2);
//DEFINE_TRANSPARENT_CLAZZ(uvec3, "uvec3", "uint", GL_DOUBLE, uvec3);
//DEFINE_TRANSPARENT_CLAZZ(uvec4, "uvec4", "uint", GL_DOUBLE, uvec4);
//
//
//
//class glsl_transparent_class : public glsl_class
//{
//protected:
//
//    glsl_transparent_class() = default;
//
//    static std::unordered_map<std::string, const class glsl_transparent_clazz*> _clazz_map;
//
//public:
//
//    [[nodiscard]] virtual const glsl_transparent_clazz* clazz() const = 0;
//
//    [[nodiscard]] virtual const std::uint8_t* stream() const = 0;
//
//};
//
//class glsl_streamable_class : public glsl_transparent_class
//{
//
//};
//
//// class glsl_float : public glsl_transparent_class
//// {
//// public:
//
////    [[nodiscard]] const glsl_transparent_clazz* clazz() const override { return _clazz_map.find("float")->second; }
//
////    [[nodiscard]] const std::uint8_t* stream() const override { return reinterpret_cast<const std::uint8_t*>(&value); }
//
//// public:
//
////    glsl_float() = default;
//
////    glm::vec1 value{};
//
//// };
//
//#define DEFINE_TRANSPARENT_CLASS(CLASS_NAME, CLASS_NAME_STR, GLM_T) \
//class glsl_##CLASS_NAME : public glsl_streamable_class\
//{\
//public:\
//[[nodiscard]] const glsl_transparent_clazz* clazz() const override { return _clazz_map.find(CLASS_NAME_STR)->second; }\
//[[nodiscard]] const std::uint8_t* stream() const override { return reinterpret_cast<const std::uint8_t*>(&val); }\
//public:\
//glsl_##CLASS_NAME() = default;                                      \
//explicit glsl_##CLASS_NAME(const glm::GLM_T& value) : val(value){}                                                                    \
//glm::GLM_T val{};\
//}                                                            \
//
//DEFINE_TRANSPARENT_CLASS(float, "float", vec1);
//DEFINE_TRANSPARENT_CLASS(vec2, "vec2", vec2);
//DEFINE_TRANSPARENT_CLASS(vec3, "vec3", vec3);
//DEFINE_TRANSPARENT_CLASS(vec4, "vec4", vec4);
//
//DEFINE_TRANSPARENT_CLASS(double, "double", dvec1);
//DEFINE_TRANSPARENT_CLASS(dvec2, "dvec2", dvec2);
//DEFINE_TRANSPARENT_CLASS(dvec3, "dvec3", dvec3);
//DEFINE_TRANSPARENT_CLASS(dvec4, "dvec4", dvec4);
//
//DEFINE_TRANSPARENT_CLASS(int, "int", ivec1);
//DEFINE_TRANSPARENT_CLASS(ivec2, "ivec2", ivec2);
//DEFINE_TRANSPARENT_CLASS(ivec3, "ivec3", ivec3);
//DEFINE_TRANSPARENT_CLASS(ivec4, "ivec4", ivec4);
//
//DEFINE_TRANSPARENT_CLASS(uint, "uint", uvec1);
//DEFINE_TRANSPARENT_CLASS(uvec2, "uvec2", uvec2);
//DEFINE_TRANSPARENT_CLASS(uvec3, "uvec3", uvec3);
//DEFINE_TRANSPARENT_CLASS(uvec4, "uvec4", uvec4);
//
//DEFINE_TRANSPARENT_CLASS(mat2, "mat2", mat2);
//DEFINE_TRANSPARENT_CLASS(mat2x3, "mat2x3", mat2x3);
//DEFINE_TRANSPARENT_CLASS(mat2x4, "mat2x4", mat2x4);
//DEFINE_TRANSPARENT_CLASS(mat3, "mat3", mat3);
//DEFINE_TRANSPARENT_CLASS(mat3x2, "mat3x2", mat3x2);
//DEFINE_TRANSPARENT_CLASS(mat3x4, "mat3x4", mat3x4);
//DEFINE_TRANSPARENT_CLASS(mat4, "mat4", mat4);
//DEFINE_TRANSPARENT_CLASS(mat4x2, "mat4x2", mat4x2);
//DEFINE_TRANSPARENT_CLASS(mat4x3, "mat4x3", mat4x3);
//DEFINE_TRANSPARENT_CLASS(dmat2, "dmat2", dmat2);
//DEFINE_TRANSPARENT_CLASS(dmat2x3, "dmat2x3", dmat2x3);
//DEFINE_TRANSPARENT_CLASS(dmat2x4, "dmat2x4", dmat2x4);
//DEFINE_TRANSPARENT_CLASS(dmat3, "dmat3", dmat3);
//DEFINE_TRANSPARENT_CLASS(dmat3x2, "dmat3x2", dmat3x2);
//DEFINE_TRANSPARENT_CLASS(dmat3x4, "dmat3x4", dmat3x4);
//DEFINE_TRANSPARENT_CLASS(dmat4, "dmat4", dmat4);
//DEFINE_TRANSPARENT_CLASS(dmat4x2, "dmat4x2", dmat4x2);
//DEFINE_TRANSPARENT_CLASS(dmat4x3, "dmat4x3", dmat4x3);

#endif
