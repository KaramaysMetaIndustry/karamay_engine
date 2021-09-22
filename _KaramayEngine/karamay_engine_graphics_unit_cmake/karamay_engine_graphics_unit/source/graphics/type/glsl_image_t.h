//
// Created by jichengcheng on 2021/9/18.
//

#ifndef KARAMAY_ENGINE_GRAPHICS_UNIT_GLSL_IMAGE_T_H
#define KARAMAY_ENGINE_GRAPHICS_UNIT_GLSL_IMAGE_T_H

#include "glsl_class.h"

#define check_and_log(expr, fatal) \
if(expr){\
std::cerr<<fatal<<std::endl;\
return;\
}\

std::string transfer_to_image_format_token(gl_image_format format)
{
    switch (format)
    {
        case gl_image_format::NOR_UI_R8:
            break;
        case gl_image_format::NOR_I_R8:
            break;
        case gl_image_format::NOR_UI_R16:
            break;
        case gl_image_format::NOR_I_R16:
            break;
        case gl_image_format::NOR_UI_RG8:
            break;
        case gl_image_format::NOR_I_RG8:
            break;
        case gl_image_format::NOR_UI_RG16:
            break;
        case gl_image_format::NOR_I_RG16:
            break;
        case gl_image_format::NOR_UI_R3_G3_B2:
            break;
        case gl_image_format::NOR_UI_R5_G6_B5:
            break;
        case gl_image_format::NOR_UI_RGB8:
            break;
        case gl_image_format::NOR_I_RGB8:
            break;
        case gl_image_format::NOR_UI_RGB16:
            break;
        case gl_image_format::NOR_I_RGB16:
            break;
        case gl_image_format::NOR_UI_RGBA2:
            break;
        case gl_image_format::NOR_UI_RGBA4:
            break;
        case gl_image_format::NOR_UI_RGB5_A1:
            break;
        case gl_image_format::NOR_UI_RGBA8:
            break;
        case gl_image_format::NOR_I_RGBA8:
            break;
        case gl_image_format::NOR_UI_RGB10_A2:
            break;
        case gl_image_format::UI_RGB10_A2:
            break;
        case gl_image_format::NOR_UI_RGBA16:
            break;
        case gl_image_format::NOR_I_RGBA16:
            break;
        case gl_image_format::NOR_UI_SRGB8:
            break;
        case gl_image_format::NOR_UI_SRGB8_ALPHA8:
            break;
        case gl_image_format::F_R32:
            break;
        case gl_image_format::F_RG32:
            break;
        case gl_image_format::F_RGB32:
            break;
        case gl_image_format::F_RGBA32:
            break;
        case gl_image_format::F_R11_G11_B10:
            break;
        case gl_image_format::I_R32:
            break;
        case gl_image_format::I_RG32:
            break;
        case gl_image_format::I_RGB32:
            break;
        case gl_image_format::I_RGBA32:
            break;
        case gl_image_format::UI_R32:
            break;
        case gl_image_format::UI_RG32:
            break;
        case gl_image_format::UI_RGB32:
            break;
        case gl_image_format::UI_RGBA32:
            break;
        default:
            break;
    }
}
enum class glsl_image_format_layout_qualifier
{
    // r16f, r32f
    // rg16f, rg32f
    // rgb16f, rgb32f
    // rgba16f, rgba32f

    // rgba8, rgba16
    // r11f_g11f_b10f
    // rgb10_a2, rgb10_a2ui
    // rg8, rg16
    // r8, r16

    // rgba{8,16,32}i
    // rg{8,16,32}i
    // r{8,16,32}
    // rgba{32,16,8}ui
    // rg{32,16,8} ui
    // r{32,16,8} ui
    // rgba{16,8}_snorm
    // rg{16,8}_snorm
    // r{16,8}_snorm
};


struct glsl_image_layout_qualifier
{
};

enum class glsl_image_layout_format_qualifier
{};

enum class glsl_image_memory_qualifier
{
    _coherent,
    _volatile,
    _restrict,
    _readonly,
    _writeonly
};


enum class gl_image_access_mode : GLenum
{
    READ_ONLY = GL_READ_ONLY,
    WRITE_ONLY = GL_WRITE_ONLY,
    READ_WRITE = GL_READ_WRITE
};


gl_image_access_mode transfer(glsl_image_memory_qualifier qualifier)
{
    switch (qualifier) {
        case glsl_image_memory_qualifier::_coherent: return gl_image_access_mode::READ_WRITE;
        case glsl_image_memory_qualifier::_volatile: return gl_image_access_mode::READ_WRITE;
        case glsl_image_memory_qualifier::_restrict: return gl_image_access_mode::READ_WRITE;
        case glsl_image_memory_qualifier::_readonly: return gl_image_access_mode::READ_ONLY;
        case glsl_image_memory_qualifier::_writeonly: return gl_image_access_mode::WRITE_ONLY;
        default: return gl_image_access_mode::READ_WRITE;
    }
}



class glsl_image_t : public glsl_opaque_t {
public:
    glsl_image_t() = delete;
    glsl_image_t(gl_image_format format, gl_image_access_mode access_mode, const std::string& type_name, const std::string& value_name) :
        _format(format),
        _access_mode(access_mode)
    {
        _token = "layout(binding={0},{1}) uniform {2} {3} {4};";
    }
    ~glsl_image_t() = default;

protected:

    gl_image_access_mode _access_mode;
    gl_image_format _format;

};

class glsl_image1D : public glsl_image_t{
public:
    struct glsl_image1DResource{
        std::shared_ptr<gl_texture_1d_base> texture_1d;
        std::int32_t mipmap_index;
        glsl_image1DResource() : texture_1d(nullptr), mipmap_index(0){}
    }resource;

    glsl_image1D() = delete;
    glsl_image1D(gl_image_format format, gl_image_access_mode access_mode, const std::string& value_name) :
            glsl_image_t(format, access_mode, "image1D", value_name)
    {}

    glsl_image1D(const glsl_image1D&) = delete;
    glsl_image1D& operator=(const glsl_image1D&) = delete;

    ~glsl_image1D() = default;

public:
    void bind() override
    {
        auto& texture_1d = resource.texture_1d;
        check_and_log(texture_1d, "do not have texture resource.")
        check_and_log(texture_1d->exists(resource.mipmap_index), "the specified mipmap_index does not exist.")
        check_and_log(texture_1d->format() != _format,"the texture format does not fit to image.")

        glBindImageTexture(0, // unit
                           resource.texture_1d->get_handle(), resource.mipmap_index, // mipmap
                           GL_TRUE, 0, // not an array or whole array
                           static_cast<GLenum>(_access_mode), // access
                           static_cast<GLenum>(resource.texture_1d->format()) // format
                           );
    }

    void unbind() override
    {
        if(!resource.texture_1d) return;
        //glBindImageTexture(0, )
    }

};

class glsl_image1DArray : private glsl_image_t
{
public:
    struct glsl_image1DArrayResource{
        std::shared_ptr<gl_texture_1d_array_base> texture_1d_array;
        std::int32_t mipmap_index;
        glsl_image1DArrayResource() : texture_1d_array(nullptr), mipmap_index(0){}
    }resource;

    glsl_image1DArray() = delete;
    glsl_image1DArray(gl_image_format format, gl_image_access_mode access_mode, const std::string& value_name) :
            glsl_image_t(format, access_mode, "image1DArray", value_name)
    {}

    glsl_image1DArray(const glsl_image1DArray&) = delete;
    glsl_image1DArray& operator=(const glsl_image1DArray&) = delete;

    ~glsl_image1DArray() = default;

public:
    void bind() override
    {
        if(!resource.texture_1d_array) return;
        glBindImageTexture(0,
                           resource.texture_1d_array->get_handle(), resource.mipmap_index,
                           GL_TRUE, 0,
                           static_cast<GLenum>(_access_mode),
                           static_cast<GLenum>(resource.texture_1d_array->format())
                           );
    }

    void unbind() override
    {
        if(!resource.texture_1d_array) return;
    }

};

class glsl_image2D : private glsl_image_t {
public:
    glsl_image2D(glsl_image_memory_qualifier memory_qualifier, std::string&& value_name) :
        _value_name(std::move(value_name))
    {
    }

public:

    struct glsl_image2DResource
    {
        std::shared_ptr<gl_texture_2d_base> texture_2d;

        std::int32_t mipmap_index;

        glsl_image2DResource() : texture_2d(nullptr), mipmap_index(0){}

    } resource;

private:

    void bind() override
    {
        std::uint32_t _unit = 0;
        glBindImageTexture(GL_TEXTURE0 + _unit,
                           resource.texture_2d->get_handle(),
                           resource.mipmap_index, false, 0,
                           static_cast<GLenum>(transfer(_memory_qualifier)),
                           static_cast<GLenum>(resource.texture_2d->format())
                           );
    }

    void unbind() override
    {
        glBindImageTexture(GL_TEXTURE0, 0, resource.mipmap_index, false, 0, 1, 1);
    }

private:

    std::string _value_name;

    glsl_image_memory_qualifier _memory_qualifier;

};

class glsl_image2DArray : public glsl_image_t{
public:
    glsl_image2DArray(glsl_image_layout_format_qualifier layout_format, glsl_image_memory_qualifier memory, std::string&& value_name)
    {}

    struct glsl_image2DArrayResource
    {
        std::shared_ptr<gl_texture_2d_array_base> texture_2d_array;
        std::int32_t mipmap_index;

        glsl_image2DArrayResource() :
            texture_2d_array(nullptr), mipmap_index(0) {}

        bool check()
        {
            if(texture_2d_array && mipmap_index >= 0 && mipmap_index < texture_2d_array->mipmaps_count())
                return true;
            return false;
        }
    } resource;

private:

    void bind() override
    {
        if(!resource.check()) return;
        for(std::int32_t _idx = 0; _idx < resource.texture_2d_array->elements_count(); ++_idx)
        {
            glBindImageTexture(GL_TEXTURE0, resource.texture_2d_array->get_handle(), resource.mipmap_index, true, _idx, 1, 1);
        }
    }

    void unbind() override {}

};

class glsl_imageCube : private glsl_image_t{
public:
    glsl_imageCube()
    {}

    struct glsl_imageCubeResource
    {
        std::shared_ptr<gl_texture_cube_base> texture_cube;
        std::int32_t mipmap_index;
        glsl_imageCubeResource() : texture_cube(nullptr), mipmap_index(0) {}
    } resource;

};

class glsl_imageCubeArray : private glsl_image_t {
public:
    glsl_imageCubeArray()
    {}

    struct glsl_imageCubeArrayResource
    {
        std::shared_ptr<gl_texture_cube_array_base> texture_cube_array;
        std::int32_t mipmap_index;
    } resource;
};

class glsl_image2DMS : private glsl_image_t
{

    struct glsl_image2DMSResource
    {
        std::shared_ptr<gl_texture_2d_multisample_base> texture_2d_multisample;
    } resource;

};

class glsl_image2DMSArray : private glsl_image_t
{
    struct glsl_image2DMSArrayResource
    {
        std::shared_ptr<gl_texture_2d_multisample_array_base> texture_2d_multisample_array;
    } resource;
};

class glsl_image2DRect : private glsl_image_t
{
    struct glsl_image2DRectResource
    {
        std::shared_ptr<gl_texture_rectangle_base> texture_rectangle;
    } resource;
};

class glsl_image3D : private glsl_image_t
{
    struct glsl_image3DResource
    {
        std::shared_ptr<gl_texture_3d_base> texture_3d;
        std::int32_t mipmap_index;
    } resource;
};

class glsl_imageBuffer : private glsl_image_t
{

    struct glsl_imageBufferResource
    {
        std::shared_ptr<gl_texture_buffer_base> texture_buffer;
    } resource;
};


void test()
{

}



//
//
//DEFINE_GLSL_IMAGE_T(image1D)
//DEFINE_GLSL_IMAGE_T(image1DArray)
//DEFINE_GLSL_IMAGE_T(image2D)
//DEFINE_GLSL_IMAGE_T(image2DArray)
//DEFINE_GLSL_IMAGE_T(imageCube)
//DEFINE_GLSL_IMAGE_T(imageCubeArray)
//DEFINE_GLSL_IMAGE_T(image2DMS)
//DEFINE_GLSL_IMAGE_T(image2DMSArray)
//DEFINE_GLSL_IMAGE_T(image2DRect)
//DEFINE_GLSL_IMAGE_T(image3D)
//DEFINE_GLSL_IMAGE_T(imageBuffer)

//DEFINE_GLSL_IMAGE_T(iimage1D)
//DEFINE_GLSL_IMAGE_T(iimage1DArray)
//DEFINE_GLSL_IMAGE_T(iimage2D)
//DEFINE_GLSL_IMAGE_T(iimage2DArray)
//DEFINE_GLSL_IMAGE_T(iimageCube)
//DEFINE_GLSL_IMAGE_T(iimageCubeArray)
//DEFINE_GLSL_IMAGE_T(iimage2DMS)
//DEFINE_GLSL_IMAGE_T(iimage2DMSArray)
//DEFINE_GLSL_IMAGE_T(iimage2DRect)
//DEFINE_GLSL_IMAGE_T(iimage3D)
//DEFINE_GLSL_IMAGE_T(iimageBuffer)

//DEFINE_GLSL_IMAGE_T(uimage1D)
//DEFINE_GLSL_IMAGE_T(uimage1DArray)
//DEFINE_GLSL_IMAGE_T(uimage2D)
//DEFINE_GLSL_IMAGE_T(uimage2DArray)
//DEFINE_GLSL_IMAGE_T(uimageCube)
//DEFINE_GLSL_IMAGE_T(uimageCubeArray)
//DEFINE_GLSL_IMAGE_T(uimage2DMS)
//DEFINE_GLSL_IMAGE_T(uimage2DMSArray)
//DEFINE_GLSL_IMAGE_T(uimage2DRect)
//DEFINE_GLSL_IMAGE_T(uimage3D)
//DEFINE_GLSL_IMAGE_T(uimageBuffer)


#endif