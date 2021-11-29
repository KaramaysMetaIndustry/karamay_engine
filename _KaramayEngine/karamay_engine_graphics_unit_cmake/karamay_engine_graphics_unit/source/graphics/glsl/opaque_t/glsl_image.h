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
class glsl_image_t : public glsl_texture_handler_t {
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


//
//class glsl_image2D : private glsl_image_t {
//public:
//    glsl_image2D(glsl_image_memory_qualifier memory_qualifier, std::string&& value_name) :
//        _value_name(std::move(value_name))
//    {
//    }
//
//public:
//
//    struct glsl_image2DResource
//    {
//        std::shared_ptr<gl_texture_2d_base> texture_2d;
//
//        std::int32_t mipmap_index;
//
//        glsl_image2DResource() : texture_2d(nullptr), mipmap_index(0){}
//
//    } resource;
//
//private:
//
//    void bind() override
//    {
//        std::uint32_t _unit = 0;
//        glBindImageTexture(GL_TEXTURE0 + _unit,
//                           resource.texture_2d->get_handle(),
//                           resource.mipmap_index, false, 0,
//                           static_cast<GLenum>(transfer(_memory_qualifier)),
//                           static_cast<GLenum>(resource.texture_2d->format())
//                           );
//    }
//
//    void unbind() override
//    {
//        glBindImageTexture(GL_TEXTURE0, 0, resource.mipmap_index, false, 0, 1, 1);
//    }
//
//private:
//
//    std::string _value_name;
//
//    glsl_image_memory_qualifier _memory_qualifier;
//
//};
//
//class glsl_image2DArray : public glsl_image_t{
//public:
//    glsl_image2DArray(glsl_image_layout_format_qualifier layout_format, glsl_image_memory_qualifier memory, std::string&& value_name)
//    {}
//
//    struct glsl_image2DArrayResource
//    {
//        std::shared_ptr<gl_texture_2d_array_base> texture_2d_array;
//        std::int32_t mipmap_index;
//
//        glsl_image2DArrayResource() :
//            texture_2d_array(nullptr), mipmap_index(0) {}
//
//        bool check()
//        {
//            if(texture_2d_array && mipmap_index >= 0 && mipmap_index < texture_2d_array->mipmaps_count())
//                return true;
//            return false;
//        }
//    } resource;
//
//private:
//
//    void bind() override
//    {
//        if(!resource.check()) return;
//        for(std::int32_t _idx = 0; _idx < resource.texture_2d_array->elements_count(); ++_idx)
//        {
//            glBindImageTexture(GL_TEXTURE0, resource.texture_2d_array->get_handle(), resource.mipmap_index, true, _idx, 1, 1);
//        }
//    }
//
//    void unbind() override {}
//
//};
//
//class glsl_imageCube : private glsl_image_t{
//public:
//    glsl_imageCube()
//    {}
//
//    struct glsl_imageCubeResource
//    {
//        std::shared_ptr<gl_texture_cube_base> texture_cube;
//        std::int32_t mipmap_index;
//        glsl_imageCubeResource() : texture_cube(nullptr), mipmap_index(0) {}
//    } resource;
//
//};
//
//class glsl_imageCubeArray : private glsl_image_t {
//public:
//    glsl_imageCubeArray()
//    {}
//
//    struct glsl_imageCubeArrayResource
//    {
//        std::shared_ptr<gl_texture_cube_array_base> texture_cube_array;
//        std::int32_t mipmap_index;
//    } resource;
//};
//
//class glsl_image2DMS : private glsl_image_t
//{
//
//    struct glsl_image2DMSResource
//    {
//        std::shared_ptr<gl_texture_2d_multisample_base> texture_2d_multisample;
//    } resource;
//
//};
//
//class glsl_image2DMSArray : private glsl_image_t
//{
//    struct glsl_image2DMSArrayResource
//    {
//        std::shared_ptr<gl_texture_2d_multisample_array_base> texture_2d_multisample_array;
//    } resource;
//};
//
//class glsl_image2DRect : private glsl_image_t
//{
//    struct glsl_image2DRectResource
//    {
//        std::shared_ptr<gl_texture_rectangle_base> texture_rectangle;
//    } resource;
//};
//
//class glsl_image3D : private glsl_image_t
//{
//    struct glsl_image3DResource
//    {
//        std::shared_ptr<gl_texture_3d_base> texture_3d;
//        std::int32_t mipmap_index;
//    } resource;
//};
//
//class glsl_imageBuffer : private glsl_image_t
//{
//
//    struct glsl_imageBufferResource
//    {
//        std::shared_ptr<gl_texture_buffer_base> texture_buffer;
//    } resource;
//};



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