#ifndef GLSL_IMAGE_H
#define GLSL_IMAGE_H

#include "../base/glsl_class.h"
#include "../../resource/texture/gl_texture.h"

#define ExtractStr(Specifier) #Specifier

enum class gl_image_format
{
    rgba32f = GL_RGBA32F,
    rgba16f = GL_RGBA16F,
    rg32f = GL_RG32F,
    rg16f = GL_RG16F,
    r11f_g11f_b10f = GL_R11F_G11F_B10F,
    r32f = GL_R32F,
    r16f = GL_R16F,
    rgba32ui = GL_RGBA32UI,
    rgba16ui = GL_RGBA16UI,
    rgb10_a2ui = GL_RGB10_A2UI,
    rgba8ui = GL_RGBA8UI,
    rg32ui = GL_RG32UI,
    rg16ui = GL_RG16UI,
    rg8ui = GL_RG8UI,
    r32ui = GL_R32UI,
    r16ui = GL_R16UI,
    r8ui = GL_R8UI,
    rgba32i = GL_RGBA32I,
    rgba16i = GL_RGBA16I,
    rgba8i = GL_RGBA8I,
    rg32i = GL_RG32I,
    rg16i = GL_RG16I,
    rg8i = GL_RG8I,
    r32i = GL_R32I,
    r16i = GL_R16I,
    r8i = GL_R8I,
    rgba16 = GL_RGBA16,
    rgb10_a2 = GL_RGB10_A2,
    rgba8 = GL_RGBA8,
    rg16 = GL_RG16,
    rg8 = GL_RG8,
    r16 = GL_R16,
    r8 = GL_R8,
    rgba16_snorm = GL_RGBA16_SNORM,
    rgba8_snorm = GL_RGBA8_SNORM,
    rg16_snorm = GL_RG16_SNORM,
    rg8_snorm = GL_RG8_SNORM,
    r16_snorm = GL_R16_SNORM,
    r8_snorm = GL_R8_SNORM
};

enum class gl_image_access_mode : GLenum
{
    READ_ONLY = GL_READ_ONLY,
    WRITE_ONLY = GL_WRITE_ONLY,
    READ_WRITE = GL_READ_WRITE
};

enum class glsl_image_memory_qualifier
{
   COHERENT,
   VOLATILE,
   RESTRICT,
   READONLY,
   WRITEONLY
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
    glsl_image_t(
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, 
        const std::string& type_name,
        const std::string& var_name
    ) :
        _format(format),
        _memory_qualifiers(memory_qualifiers),
        _type_name(type_name),
        _var_name(var_name)
    {}

    glsl_image_t(const glsl_image_t&) = delete;
    glsl_image_t& operator=(const glsl_image_t&) = delete;

    ~glsl_image_t() = default;

protected:

    void _set_image(gl_texture_t* texture, int32 mipmap_index, int32 element_index)
    {
        if (_bindless_handle)
        {
            glMakeImageHandleNonResidentARB(_bindless_handle);
        }
        _bindless_handle = glGetImageHandleARB(texture->get_handle(), mipmap_index, false, element_index, static_cast<GLenum>(_format));
        glMakeImageHandleResidentARB(_bindless_handle, static_cast<GLenum>(_access_mode));
    }

    void _set_image(gl_texture_t* texture, int32 mipmap_index)
    {
        if (_bindless_handle)
        {
            glMakeImageHandleNonResidentARB(_bindless_handle);
        }
        _bindless_handle = glGetImageHandleARB(texture->get_handle(), mipmap_index, true, 0, static_cast<GLenum>(_format));
        glMakeImageHandleResidentARB(_bindless_handle, static_cast<GLenum>(_access_mode));
    }
    
    gl_image_format _format;
    gl_image_access_mode _access_mode;
    std::vector<glsl_image_memory_qualifier> _memory_qualifiers;

    uint64 _bindless_handle;
    
    std::string _type_name;
    std::string _var_name;
    std::string _token;

    static std::string _cast_format_qualifier(gl_image_format format)
    {
        switch (format)
        {
        
        }
    }

    static std::string _cast_memory_qualifier(glsl_image_memory_qualifier memory_qualifier)
    {
        switch (memory_qualifier)
        {
        case glsl_image_memory_qualifier::COHERENT : return "coherent";
        case glsl_image_memory_qualifier::READONLY : return "readonly";
        case glsl_image_memory_qualifier::RESTRICT : return "restrict";
        case glsl_image_memory_qualifier::VOLATILE : return "volatile";
        case glsl_image_memory_qualifier::WRITEONLY : return "writeonly";
        default: return "";
        }
    }

};


// float-image
class glsl_image : public glsl_image_t
{
public:
    glsl_image(
        gl_image_format format, 
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, 
        const std::string& type_name, 
        const std::string& var_name
    ) :
        glsl_image_t(format, memory_qualifiers, type_name, var_name)
    {}

protected:

    bool _check_internal_format(gl_texture_internal_format format)
    {
        switch (format)
        {
        case gl_texture_internal_format::R_F32: return true;
        case gl_texture_internal_format::RG_F32: return true;
        case gl_texture_internal_format::RGB_F32: return true;
        case gl_texture_internal_format::RGBA_F32: return true;
        case gl_texture_internal_format::NOR_R_I8: return true;
        case gl_texture_internal_format::NOR_R_I16: return true;
        case gl_texture_internal_format::NOR_RG_I8: return true;
        case gl_texture_internal_format::NOR_RG_I16: return true;
        case gl_texture_internal_format::NOR_RGB_I8: return true;
        case gl_texture_internal_format::NOR_RGB_I16: return true;
        case gl_texture_internal_format::NOR_RGBA_I8: return true;
        case gl_texture_internal_format::NOR_RGBA_I16: return true;
        case gl_texture_internal_format::NOR_R_UI8: return true;
        case gl_texture_internal_format::NOR_R_UI16: return true;
        case gl_texture_internal_format::NOR_RG_UI8: return true;
        case gl_texture_internal_format::NOR_RG_UI16: return true;
        case gl_texture_internal_format::NOR_RGB_UI8: return true;
        case gl_texture_internal_format::NOR_RGB_UI16: return true;
        case gl_texture_internal_format::NOR_RGBA_UI8: return true;
        case gl_texture_internal_format::NOR_RGBA_UI16: return true;
        case gl_texture_internal_format::NOR_RGB_UI16_5_6_5: return true;
        case gl_texture_internal_format::NOR_RGBA_UI16_4_4_4_4: return true;
        case gl_texture_internal_format::NOR_RGBA_UI16_5_5_5_1: return true;
        case gl_texture_internal_format::NOR_RGBA_UI32_10_10_10_2: return true;
        case gl_texture_internal_format::NOR_UI_SRGB8: return true;
        case gl_texture_internal_format::NOR_UI_SRGB8_ALPHA8: return true;
        case gl_texture_internal_format::F_R11_G11_B10: return true;
        case gl_texture_internal_format::RGB9_E5: return true;
        default: return false;
        }
    }
};

class glsl_image1D final : public glsl_image
{
public:
    glsl_image1D(
        const std::string& name,
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers
    ) :
        glsl_image(format, memory_qualifiers, "image1D", name)
    {}

    glsl_image1D(const glsl_image1D&) = delete;
    glsl_image1D& operator=(const glsl_image1D&) = delete;

    ~glsl_image1D() = default;

public:

    void associate(gl_texture_1d* texture, uint32 mipmap_index) noexcept
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;

        _set_image(texture, static_cast<int32>(mipmap_index));
    }

    void associate(gl_texture_1d_array* texture, uint32 mipmap_index, uint32 element_index) noexcept
    {
        if (!texture)
        {
            return;
        }

        if (!_check_internal_format(texture->get_internal_format())) 
        {
            return;
        }

        _set_image(texture, static_cast<int32>(mipmap_index), static_cast<int32>(element_index));
    }

};
class glsl_image1DArray final : public glsl_image
{
public:
    glsl_image1DArray(
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, 
        const std::string& var_name
    ) :
        glsl_image(format, memory_qualifiers, "image1DArray", var_name)
    {}

    glsl_image1DArray(const glsl_image1DArray&) = delete;
    glsl_image1DArray& operator=(const glsl_image1DArray&) = delete;

    ~glsl_image1DArray() = default;

public:

    void associate(gl_texture_1d_array* texture, uint32 mipmap_index)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, mipmap_index);
    }

};
class glsl_image2D final : public glsl_image
{
public:
    glsl_image2D(
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, 
        const std::string& var_name
    ) :
        glsl_image(format, memory_qualifiers, "image2D", var_name)
    {}

    glsl_image2D(const glsl_image2D&) = delete;
    glsl_image2D& operator=(const glsl_image2D&) = delete;

    ~glsl_image2D() = default;

public:

    void associate(gl_texture_2d* texture, uint32 mipmap_index)
    {
        if (!texture) return;
        if (mipmap_index < 0) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, mipmap_index);
    }

    void associate(gl_texture_2d_array* texture, uint32 element_index, uint32 mipmap_index)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, mipmap_index, element_index);
    }

    void associate(gl_texture_cube_map* texture, gl_cube_face_index face_index, uint32 mipmap_index)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, mipmap_index, gl_texture_t::cast_face_index(face_index));
    }

    void associate(gl_texture_cube_map_array* texture, uint32 element_index, gl_cube_face_index face_index, uint32 mipmap_index)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, mipmap_index, element_index + gl_texture_t::cast_face_index(face_index));
    }

};
class glsl_image2DArray final : public glsl_image
{
public:
    glsl_image2DArray(
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, 
        const std::string& name
    ) :
        glsl_image(format, memory_qualifiers, "image2DArray", name)
    {}

    glsl_image2DArray(const glsl_image2DArray&) = delete;
    glsl_image2DArray& operator=(const glsl_image2DArray&) = delete;

    ~glsl_image2DArray() = default;

public:

    void associate(gl_texture_2d_array* texture, uint32 mipmap_index)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, mipmap_index);
    }

};
class glsl_imageCube final : public glsl_image
{
public:
    glsl_imageCube(
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(format, memory_qualifiers, "imageCube", var_name)
    {}

    glsl_imageCube(const glsl_imageCube&) = delete;
    glsl_imageCube& operator=(const glsl_image2DArray&) = delete;

    ~glsl_imageCube() = default;

public:

    void associate(gl_texture_cube_map* texture, uint32 mipmap_index)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, mipmap_index);
    }

    void associate(gl_texture_cube_map_array* texture, uint32 element_index, uint32 mipmap_index)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, mipmap_index, element_index);
    }

};
class glsl_imageCubeArray final : public glsl_image
{
public:
    glsl_imageCubeArray(
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(format, memory_qualifiers, "imageCubeArray", var_name) 
    {}

    glsl_imageCubeArray(const glsl_imageCubeArray&) = delete;
    glsl_imageCubeArray& operator=(const glsl_imageCubeArray&) = delete;

    ~glsl_imageCubeArray() = default;

public:

    void associate(gl_texture_cube_map_array* texture, uint32 mipmap_index)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, mipmap_index);
    }

};
class glsl_image2DMS final : public glsl_image
{
public:
    glsl_image2DMS(
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(format, memory_qualifiers, "image2DMS", var_name)
    {}

    glsl_image2DMS(const glsl_image2DMS&) = delete;
    glsl_image2DMS& operator=(const glsl_image2DMS&) = delete;

    ~glsl_image2DMS() = default;

public:

    void associate(gl_texture_2d_multisample* texture)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, 0);
    }

    void associate(gl_texture_2d_multisample_array* texture, uint32 element_index)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, 0, element_index);
    }

};
class glsl_image2DMSArray final : public glsl_image
{
public:
    glsl_image2DMSArray(
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(format, memory_qualifiers, "image2DMSArray", var_name)
    {}

    glsl_image2DMSArray(const glsl_image2DMSArray&) = delete;
    glsl_image2DMSArray& operator=(const glsl_image2DMSArray&) = delete;

    ~glsl_image2DMSArray() = default;

public:

    void associate(gl_texture_2d_multisample_array* texture)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, 0);
    }

};
class glsl_image2DRect final : public glsl_image
{
public:
    glsl_image2DRect(
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(format, memory_qualifiers, "image2DRect", var_name)
    {}

    glsl_image2DRect(const glsl_image2DRect&) = delete;
    glsl_image2DRect& operator=(const glsl_image2DRect&) = delete;

    ~glsl_image2DRect() = default;

public:

    void associate(gl_texture_rectangle* texture)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, 0);
    }

};
class glsl_image3D final : public glsl_image
{
public:
    glsl_image3D(
        gl_image_format format,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(format, memory_qualifiers, "image3D", var_name)
    {}

    glsl_image3D(const glsl_image3D&) = delete;
    glsl_image3D& operator=(const glsl_image3D&) = delete;

    ~glsl_image3D() = default;

public:

    void associate(gl_texture_3d* texture, uint32 mipmap_index)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, mipmap_index);
    }

};
class glsl_imageBuffer final : public glsl_image
{
public:
    glsl_imageBuffer(
        gl_image_format format, 
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, 
        const std::string& var_name) :
        glsl_image(format, memory_qualifiers, "imageBuffer", var_name)
    {}

    glsl_imageBuffer(const glsl_imageBuffer&) = delete;
    glsl_imageBuffer& operator=(const glsl_imageBuffer&) = delete;

    ~glsl_imageBuffer() = default;
    
public:

    void associate(gl_texture_buffer* texture)
    {
        if (!texture) return;
        if (!_check_internal_format(texture->get_internal_format())) return;
        _set_image(texture, 0);
    }

};

// int image
class glsl_iimage : public glsl_image_t
{

};

class glsl_iimage1D final : public glsl_iimage {};
class glsl_iimage1DArray final : public glsl_iimage {};
class glsl_iimage2D final : public glsl_iimage {};
class glsl_iimage2DArray final : public glsl_iimage {};
class glsl_iimageCube final : public glsl_iimage {};
class glsl_iimageCubeArray final : public glsl_iimage {};
class glsl_iimage2DMS final : public glsl_iimage {};
class glsl_iimage2DMSArray final : public glsl_iimage {};
class glsl_iimage2DRect final : public glsl_iimage {};
class glsl_iimage3D final : public glsl_iimage {};
class glsl_iimageBuffer final : public glsl_iimage {};


// uint image
class glsl_uimage : public glsl_image_t
{

};

class glsl_uimage1D final : public glsl_uimage 
{

};
class glsl_uimage1DArray final : public glsl_uimage 
{

};
class glsl_uimage2D final : public glsl_uimage 
{

};
class glsl_uimage2DArray final : public glsl_uimage 
{

};
class glsl_uimageCube final : public glsl_uimage 
{

};
class glsl_uimageCubeArray final : public glsl_uimage 
{

};
class glsl_uimage2DMS final : public glsl_uimage 
{

};
class glsl_uimage2DMSArray final : public glsl_uimage 
{

};
class glsl_uimage2DRect final : public glsl_uimage 
{

};
class glsl_uimage3D final : public glsl_uimage 
{

};
class glsl_uimageBuffer final : public glsl_uimage 
{

};

#endif