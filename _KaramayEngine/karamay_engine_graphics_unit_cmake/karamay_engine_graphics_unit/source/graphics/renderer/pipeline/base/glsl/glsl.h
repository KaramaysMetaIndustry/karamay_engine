#include "base/glsl_class.h"

#include "opaque_t/glsl_image.h"
#include "opaque_t/glsl_sampler.h"
#include "opaque_t/glsl_atomic_counter.h"
#include "interface_block/glsl_uniform_block.h"
#include "interface_block/glsl_shader_storage_block.h"

#include "glsl_program.h"
#include "glsl_shader.h"

//
//
//#define image1D(name, format, ...)\
//glsl_image1D name##(ExtractStr(name), gl_image_format::format, {glsl_image_memory_qualifier::READONLY})\
//
//#define image1DArray(name, format, ...)
//#define image2D(name, format, ...)
//#define image2DArray(name, format, ...)
//#define image2DMS(name, format, ...)
//#define image2DMSArray(name, format, ...)
//#define imageCube(name, format, ...)
//#define imageCubeArray(name, format, ...)
//#define image2DRect(name, format, ...)
//#define image3D(name, format, ...)
//#define imageBuffer(name, format, ...)
//
//#define iimage1D(name, format, ...)
//#define iimage1DArray(name, format, ...)
//#define iimage2D(name, format, ...)
//#define iimage2DArray(name, format, ...)
//#define iimage2DMS(name, format, ...)
//#define iimage2DMSArray(name, format, ...)
//#define iimageCube(name, format, ...)
//#define iimageCubeArray(name, format, ...)
//#define iimage2DRect(name, format, ...)
//#define iimage3D(name, format, ...)
//#define iimageBuffer(name, format, ...)
//
//#define uimage1D(name, format, ...)
//#define uimage1DArray(name, format, ...)
//#define uimage2D(name, format, ...)
//#define uimage2DArray(name, format, ...)
//#define uimage2DMS(name, format, ...)
//#define uimage2DMSArray(name, format, ...)
//#define uimageCube(name, format, ...)
//#define uimageCubeArray(name, format, ...)
//#define uimage2DRect(name, format, ...)
//#define uimage3D(name, format, ...)
//#define uimageBuffer(name, format, ...)
//
//
//#define sampler1D(name)\
//glsl_sampler1D name(ExtractStr(name))\
//
//#define sampler1DArray(name)
//#define sampler2D(name)
//#define sampler2DArray(name)
//#define sampler2DMS(name)
//#define sampler2DMSArray(name)
//#define samplerCube(name)
//#define samplerCubeArray(name)
//#define sampler2DRect(name)
//#define sampler3D(name)
//#define samplerBuffer(name)
//#define sampler2DRect(name)
//
//#define sampler1DShadow(name)
//#define sampler1DArrayShadow(name)
//#define sampler2DShadow(name)
//#define sampler2DArrayShadow(name)
//#define samplerCubeShadow(name)
//#define samplerCubeArrayShadow(name)
//#define sampler2DRectShadow(name)
//
//#define isampler1D(name)
//#define isampler1DArray(name)
//#define isampler2D(name)
//#define isampler2DArray(name)
//#define isampler2DMS(name)
//#define isampler2DMSArray(name)
//#define isamplerCube(name)
//#define isamplerCubeArray(name)
//#define isampler2DRect(name)
//#define isampler3D(name)
//#define isamplerBuffer(name)
//#define isampler2DRect(name)
//
//#define usampler1D(name)
//#define usampler1DArray(name)
//#define usampler2D(name)
//#define usampler2DArray(name)
//#define usampler2DMS(name)
//#define usampler2DMSArray(name)
//#define usamplerCube(name)
//#define usamplerCubeArray(name)
//#define usampler2DRect(name)
//#define usampler3D(name)
//#define usamplerBuffer(name)
//#define usampler2DRect(name)