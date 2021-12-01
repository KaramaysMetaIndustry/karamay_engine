#ifndef GLSL_IMAGE_H
#define GLSL_IMAGE_H

#include "graphics/glsl/glsl_class.h"
#include "graphics/resource/texture/gl_texture.h"

enum class glsl_image_format_layout_qualifier
{
    // float
    _r16f,_rg16f,_rgba16f,
    _r32f,_rg32f,_rgba32f,
    _r11f_g11f_b10f,
    // norm float
    _r8,_r16,
    _rg8,_rg16,
    _rgb8,_rgb16,
    _rgb10_a2,
    // snorm float
    _r8_snorm,_r16_snorm,
    _rg8_snorm,_rg16_snorm,
    _rgba8_snorm,_rgba16_snorm,
    // int
    _r8i,_r16i,_r32i,
    _rg8i,_rg16i,_rg32i,
    _rgba8i,_rgba16i,_rgba32i,
    // uint
    _r8ui,_r16ui,_r32ui,
    _rg8ui,_rg16ui,_rg32ui,
    _rgba8ui,_rgba16ui,_rgba32ui,
    _rgb10_a2ui,
};

enum class glsl_image_memory_qualifier
{
//    _coherent,
//    _volatile,
//    _restrict,
//    _readonly,
//    _writeonly
};

enum class gl_image_access_mode : GLenum
{
    READ_ONLY = GL_READ_ONLY,
    WRITE_ONLY = GL_WRITE_ONLY,
    READ_WRITE = GL_READ_WRITE
};

enum class gl_image_unit_format : GLenum
{

};


/*
 * layout(FormatLayoutQualifier) uniform [MemoryQualifier] image IMAGE_NAME[10];
 *
 * Image variables refer to an image, of a particular type, stored within a texture.
 * These are used for arbitrary loading/storing of values within shaders. [Ëæ»ú·ÃÎÊ]
 * these type have array semantics
 *
 * exp : layout(binding=3,rgba32f) uniform writeonly readonly image1D imageColors;
 *
 * */
class glsl_image_t : public glsl_texture_handler_t 
{
public:
    glsl_image_t();

    glsl_image_t(const glsl_image_t&) = delete;
    glsl_image_t& operator=(const glsl_image_t&) = delete;

    ~glsl_image_t() = default;

protected:
    const std::string _type_name;
    const std::string _value_name;
    const glsl_image_format_layout_qualifier _format_layout_qualifier;
    const glsl_image_memory_qualifier _memory_qualifier;
    const gl_image_format _image_format;
    const gl_image_access_mode _access_mode;

};

class glsl_image1D : public glsl_image_t
{
public:
    glsl_image1D(int32 mipmap_index, std::shared_ptr<gl_texture_1d> texture_1d, gl_image_access_mode access_mode, gl_image_unit_format unit_format)
    {
        _mipmap_index = mipmap_index;
        _texture_1d = texture_1d;
        _access_mode = access_mode;
        _unit_format = unit_format;
    }

    glsl_image1D(const glsl_image1D&) = delete;
    glsl_image1D& operator=(const glsl_image1D&) = delete;

    ~glsl_image1D() {}

public:

    void bind(uint32 unit)
    {
        glBindImageTexture(unit, _texture_1d->get_handle(), _mipmap_index, GL_FALSE, 0, static_cast<GLenum>(_access_mode), static_cast<GLenum>(_unit_format));
    }

    void unbind()
    {

    }

private:

    int32 _mipmap_index;
    
    std::shared_ptr<gl_texture_1d> _texture_1d;

    gl_image_access_mode _access_mode;

    gl_image_unit_format _unit_format;

};

class glsl_image1DArray : private glsl_image_t{
public:
    glsl_image1DArray();

    glsl_image1DArray(const glsl_image1DArray&) = delete;
    glsl_image1DArray& operator=(const glsl_image1DArray&) = delete;

    ~glsl_image1DArray() = default;

};

class glsl_image2D {};
class glsl_image2DArray {};
class glsl_imageCube {};
class glsl_imageCubeArray {};
class glsl_image2DMS {};
class glsl_image2DMSArray {};
class glsl_image2DRect {};
class glsl_image3D {};
class glsl_imageBuffer {};


class glsl_iimage1D {};
class glsl_iimage1DArray {};
class glsl_iimage2D {};
class glsl_iimage2DArray {};
class glsl_iimageCube {};
class glsl_iimageCubeArray {};
class glsl_iimage2DMS {};
class glsl_iimage2DMSArray {};
class glsl_iimage2DRect {};
class glsl_iimage3D {};
class glsl_iimageBuffer {};

class glsl_uimage1D {};
class glsl_uimage1DArray {};
class glsl_uimage2D {};
class glsl_uimage2DArray {};
class glsl_uimageCube {};
class glsl_uimageCubeArray {};
class glsl_uimage2DMS {};
class glsl_uimage2DMSArray {};
class glsl_uimage2DRect {};
class glsl_uimage3D {};
class glsl_uimageBuffer {};

#endif