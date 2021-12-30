#ifndef GLSL_BUILDER
#define GLSL_BUILDER

#include "glsl.h"

#define uniformBlock(binding, layout, name)\
class glsl_##name : public glsl_uniform_block\
{\
public:\
    glsl_##name() :\
        glsl_uniform_block(glsl_interface_block_matrix_layout::COLUMN_MAJOR, glsl_uniform_block_memory_layout::layout, {})\
    {\
        \
    }\

#define shaderStorageBlock(binding, layout, name)\
class glsl_##name : public glsl_shader_storage_block\
{\


#define sampler(prefix, suffix, name)\
private:\
std::shared_ptr<glsl_##prefix##sampler##suffix> _##name## = _create_sampler<glsl_##prefix##sampler##suffix>(ExtractStr(name));\
public:\
std::shared_ptr<glsl_##prefix##sampler##suffix> name() const {return _##name;}\

#define sampler1D(name) sampler(,1D, name)
#define sampler1DArray(name) sampler(,1DArray, name)
#define sampler2D(name) sampler(,2D, name)
#define sampler2DArray(name) sampler(,2DArray, name)
#define sampler2DMS(name) sampler(,2DMS, name)
#define sampler2DMSArray(name) sampler(,2DMSArray, name)
#define sampler2DRect(name) sampler(,2DRect, name)
#define samplerCube(name) sampler(,Cube, name)
#define samplerCubeArray(name) sampler(,CubeArray, name)
#define sampler3D(name) sampler(,3D, name)
#define samplerBuffer(name) sampler(,Buffer, name)

#define isampler1D(name) sampler(i, 1D, name)
#define isampler1DArray(name) sampler(i, 1DArray, name)
#define isampler2D(name) sampler(i, 2D, name)
#define isampler2DArray(name) sampler(i, 2DArray, name)
#define isampler2DMS(name) sampler(i, 2DMS, name)
#define isampler2DMSArray(name) sampler(i, 2DMSArray, name)
#define isampler2DRect(name) sampler(i, 2DRect, name)
#define isamplerCube(name) sampler(i, Cube, name)
#define isamplerCubeArray(name) sampler(i, CubeArray, name)
#define isampler3D(name) sampler(i, 3D, name)
#define isamplerBuffer(name) sampler(i, Buffer, name)

#define usampler1D(name) sampler(u, 1D, name)
#define usampler1DArray(name) sampler(u, 1DArray, name)
#define usampler2D(name) sampler(u, 2D, name)
#define usampler2DArray(name) sampler(u, 2DArray, name)
#define usampler2DMS(name) sampler(u, 2DMS, name)
#define usampler2DMSArray(name) sampler(u, 2DMSArray, name)
#define usampler2DRect(name) sampler(u, 2DRect, name)
#define usamplerCube(name) sampler(u, Cube, name)
#define usamplerCubeArray(name) sampler(u, CubeArray, name)
#define usampler3D(name) sampler(u, 3D, name)
#define usamplerBuffer(name) sampler(u, Buffer, name)

#define sampler1DShadow(name) sampler(,1DShadow, name)
#define sampler1DArrayShadow(name) sampler(,1DArrayShadow, name)
#define sampler2DShadow(name) sampler(,2DShadow, name)
#define sampler2DArrayShadow(name) sampler(,2DArrayShadow, name)
#define sampler2DRectShadow(name) sampler(,2DRectShadow, name)
#define samplerCubeShadow(name) sampler(,CubeShadow, name)
#define samplerCubeArrayShadow(name) sampler(,CubeArrayShadow, name)


#define image(prefix, suffix, name, format, ...)\
std::shared_ptr<glsl_##prefix##image##suffix> name = std::make_shared<glsl_##prefix##image##suffix>(ExtractStr(name), gl_image_format::##format, {glsl_image_memory_qualifier::WRITEONLY})

// name, format, (specifiers)
#define image1D(name, format, ...) image(, 1D, name, format, __VA_ARGS__)
#define image1DArray(name, format, ...) image(, 1DArray, name, format, __VA_ARGS__)
#define image2D(name, format, ...) image(, 2D, name, format, __VA_ARGS__)
#define image2DArray(name, format, ...) image(, 2DArray, name, format, __VA_ARGS__)
#define image2DMS(name, format, ...) image(, 2DMS, name, format, __VA_ARGS__)
#define image2DMSArray(name, format, ...) image(, 2DMSArray, name, format, __VA_ARGS__)
#define imageCube(name, format, ...) image(, Cube, name, format, __VA_ARGS__)
#define imageCubeArray(name, format, ...) image(, CubeArray, name, format, __VA_ARGS__)
#define image2DRect(name, format, ...) image(, 2DRect, name, format, __VA_ARGS__)
#define image3D(name, format, ...) image(, 3D, name, format, __VA_ARGS__)
#define imageBuffer(name, format, ...) image(, Buffer, name, format, __VA_ARGS__)

#define iimage1D(name, format, ...) image(i, 1D, name, format, __VA_ARGS__)
#define iimage1DArray(name, format, ...) image(i, 1DArray, name, format, __VA_ARGS__)
#define iimage2D(name, format, ...) image(i, 2D, name, format, __VA_ARGS__)
#define iimage2DArray(name, format, ...) image(i, 2DArray, name, format, __VA_ARGS__)
#define iimage2DMS(name, format, ...) image(i, 2DMS, name, format, __VA_ARGS__)
#define iimage2DMSArray(name, format, ...) image(i, 2DMS, name, format, __VA_ARGS__)
#define iimageCube(name, format, ...) image(i, Cube, name, format, __VA_ARGS__)
#define iimageCubeArray(name, format, ...) image(i, CubeArray, name, format, __VA_ARGS__)
#define iimage2DRect(name, format, ...) image(i, 2DRect, name, format, __VA_ARGS__)
#define iimage3D(name, format, ...) image(i, 3D, name, format, __VA_ARGS__)
#define iimageBuffer(name, format, ...) image(i, Buffer, name, format, __VA_ARGS__)

#define uimage1D(name, format, ...) image(u, 1D, name, format, __VA_ARGS__)
#define uimage1DArray(name, format, ...) image(u, 1DArray, name, format, __VA_ARGS__)
#define uimage2D(name, format, ...) image(u, 2D, name, format, __VA_ARGS__)
#define uimage2DArray(name, format, ...) image(u, 2DArray, name, format, __VA_ARGS__)
#define uimage2DMS(name, format, ...) image(u, 2DMS, name, format, __VA_ARGS__)
#define uimage2DMSArray(name, format, ...) image(u, 2DMS, name, format, __VA_ARGS__)
#define uimageCube(name, format, ...) image(u, Cube, name, format, __VA_ARGS__)
#define uimageCubeArray(name, format, ...) image(u, CubeArray, name, format, __VA_ARGS__)
#define uimage2DRect(name, format, ...) image(u, 2DRect, name, format, __VA_ARGS__)
#define uimage3D(name, format, ...) image(u, 3D, name, format, __VA_ARGS__)
#define uimageBuffer(name, format, ...) image(u, Buffer, name, format, __VA_ARGS__)


#define vec3(name)\
private:\
std::unique_ptr<glsl_vec3> _##name = std::make_unique<glsl_vec3>();\
public:\
glsl_vec3& name() const {return *_##name;};\







#endif