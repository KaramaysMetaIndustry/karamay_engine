#ifndef GLSL_BUILDER_H
#define GLSL_BUILDER_H
#include "glsl.h"

#define def_uniformBlock(binding, layout, name)\
class glsl_##name : public glsl_uniform_block\
{\
public:\
    glsl_##name() :\
        glsl_uniform_block(glsl_interface_block_matrix_layout::COLUMN_MAJOR, glsl_uniform_block_memory_layout::layout, {})\
    {\
        \
    }\

#define decl_uniformBlock(name)\
glsl_##name * name = _create_uniform_block<glsl_##name>()\

#define def_shaderStorageBlock(binding, layout, name)\
class glsl_##name : public glsl_shader_storage_block\
{\
public:\
    glsl_##name() : \
        glsl_shader_storage_block(glsl_interface_block_matrix_layout::COLUMN_MAJOR, glsl_shader_storage_block_memory_layout::layout)\
    {}\


#define decl_shaderStorageBlock(name)\
glsl_##name* name = _create_shader_storage_block<glsl_##name>()\


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


#define imagex(prefix, suffix, name, format, ...)\
std::shared_ptr<glsl_##prefix##image##suffix> name = std::make_shared<glsl_##prefix##image##suffix>(ExtractStr(name), gl_image_format::##format, {glsl_image_memory_qualifier::WRITEONLY})

// name, format, (specifiers)
#define image1D(name, format, ...) imagex(, 1D, name, format, __VA_ARGS__)
#define image1DArray(name, format, ...) imagex(, 1DArray, name, format, __VA_ARGS__)
#define image2D(name, format, ...) imagex(, 2D, name, format, __VA_ARGS__)
#define image2DArray(name, format, ...) imagex(, 2DArray, name, format, __VA_ARGS__)
#define image2DMS(name, format, ...) imagex(, 2DMS, name, format, __VA_ARGS__)
#define image2DMSArray(name, format, ...) imagex(, 2DMSArray, name, format, __VA_ARGS__)
#define imageCube(name, format, ...) imagex(, Cube, name, format, __VA_ARGS__)
#define imageCubeArray(name, format, ...) imagex(, CubeArray, name, format, __VA_ARGS__)
#define image2DRect(name, format, ...) imagex(, 2DRect, name, format, __VA_ARGS__)
#define image3D(name, format, ...) imagex(, 3D, name, format, __VA_ARGS__)
#define imageBuffer(name, format, ...) imagex(, Buffer, name, format, __VA_ARGS__)

#define iimage1D(name, format, ...) imagex(i, 1D, name, format, __VA_ARGS__)
#define iimage1DArray(name, format, ...) imagex(i, 1DArray, name, format, __VA_ARGS__)
#define iimage2D(name, format, ...) imagex(i, 2D, name, format, __VA_ARGS__)
#define iimage2DArray(name, format, ...) imagex(i, 2DArray, name, format, __VA_ARGS__)
#define iimage2DMS(name, format, ...) imagex(i, 2DMS, name, format, __VA_ARGS__)
#define iimage2DMSArray(name, format, ...) imagex(i, 2DMS, name, format, __VA_ARGS__)
#define iimageCube(name, format, ...) imagex(i, Cube, name, format, __VA_ARGS__)
#define iimageCubeArray(name, format, ...) imagex(i, CubeArray, name, format, __VA_ARGS__)
#define iimage2DRect(name, format, ...) imagex(i, 2DRect, name, format, __VA_ARGS__)
#define iimage3D(name, format, ...) imagex(i, 3D, name, format, __VA_ARGS__)
#define iimageBuffer(name, format, ...) imagex(i, Buffer, name, format, __VA_ARGS__)

#define uimage1D(name, format, ...) imagex(u, 1D, name, format, __VA_ARGS__)
#define uimage1DArray(name, format, ...) imagex(u, 1DArray, name, format, __VA_ARGS__)
#define uimage2D(name, format, ...) imagex(u, 2D, name, format, __VA_ARGS__)
#define uimage2DArray(name, format, ...) imagex(u, 2DArray, name, format, __VA_ARGS__)
#define uimage2DMS(name, format, ...) imagex(u, 2DMS, name, format, __VA_ARGS__)
#define uimage2DMSArray(name, format, ...) imagex(u, 2DMS, name, format, __VA_ARGS__)
#define uimageCube(name, format, ...) imagex(u, Cube, name, format, __VA_ARGS__)
#define uimageCubeArray(name, format, ...) imagex(u, CubeArray, name, format, __VA_ARGS__)
#define uimage2DRect(name, format, ...) imagex(u, 2DRect, name, format, __VA_ARGS__)
#define uimage3D(name, format, ...) imagex(u, 3D, name, format, __VA_ARGS__)
#define uimageBuffer(name, format, ...) imagex(u, Buffer, name, format, __VA_ARGS__)


#define vec3(name)\
private:\
std::unique_ptr<glsl_vec3> _##name = std::make_unique<glsl_vec3>();\
public:\
glsl_vec3& name() const {return *_##name;};\



#define refUniformBlock()

#define reshaderStorageBlock()

#define refAtomicCounter()


#define def_vertexShader()\
class glsl_vs : public glsl_vertex_shader\
{\

#define decl_vertexShader()\
glsl_vs* vs = _create_shader<glsl_vs>()\

#define def_tessellationControlShader()\
class glsl_tesc : public glsl_tessellation_control_shader\
{\

#define decl_tessellationControlShader()\
glsl_tesc* tesc = _create_shader<glsl_tesc>()\

#define def_tessellationEvaluationShader()\
class glsl_tese : public glsl_tessellation_evaluation_shader\
{\

#define decl_tessellationEvaludationShader()\
glsl_tese* tese = _create_shader<glsl_tese>()\

#define def_geometryShader()\
class glsl_gs : public glsl_geometry_shader\
{\

#define decl_geometryShader()\
glsl_gs* gs = _create_shader<glsl_gs>()\

#define def_fragmentShader()\
class glsl_fs : public glsl_fragment_shader\
{\

#define decl_fragmentShader()\
glsl_fs* fs = _create_shader<glsl_fs>()\

#define def_computeShader()\
class glsl_cs : public glsl_compute_shader\
{\

#define decl_computeShader()\
glsl_cs* cs = _create_shader<glsl_cs>()\

#define ref_uniformBlock(name)\
void* name = _ref_uniform_block(ExtractStr(name))\

#define ref_shaderStorageBlock(name)\
void* name = _ref_shader_storage_block(ExtractStr(name))\


#define def_taskShader()\
class glsl_ts : public glsl_task_shader\
{\

#define decl_taskShader()\
glsl_ts* ts = _create_shader<glsl_ts>()\

#define def_meshShader()\
class glsl_ms : public glsl_mesh_shader\
{\

#define decl_meshShader()\
glsl_ms* ms = _create_shader<glsl_ms>()\



#endif