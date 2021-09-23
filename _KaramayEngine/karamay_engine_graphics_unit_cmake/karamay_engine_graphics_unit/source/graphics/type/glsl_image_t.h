#ifndef GLSL_IMAGE_T_H
#define GLSL_IMAGE_T_H

#include "glsl_class.h"

#define check_and_log(expr, fatal) \
if(expr){\
std::cerr<<fatal<<std::endl;\
return;\
}\

enum class glsl_image_format_layout_qualifier
{
    R16F,RG16F,RGBA16F,
    R32F,RG32F,RGBA32F,
    R11F_G11F_B10F,

    R8,R16,
    RG8,RG16,
    RGB8,RGB16,
    RGB10_A2,

    R8_SNORM,R16_SNORM,
    RG8_SNORM,RG16_SNORM,
    RGBA8_SNORM,RGBA16_SNORM,

    R8I,R16I,R32I,
    RG8I,RG16I,RG32I,
    RGBA8I,RGBA16I,RGBA32I,

    R8UI,R16UI,R32UI,
    RG8UI,RG16UI,RG32UI,
    RGBA8UI,RGBA16UI,RGBA32UI,
    RGB10_A2UI,
};

enum class glsl_image_memory_qualifier
{
    COHERENT,
    VOLATILE,
    RESTRICT,
    READONLY,
    WRITEONLY
};

enum class gl_image_access_mode : GLenum
{
    READ_ONLY = GL_READ_ONLY,
    WRITE_ONLY = GL_WRITE_ONLY,
    READ_WRITE = GL_READ_WRITE
};

/*
 * layout(FormatLayoutQualifier) uniform [MemoryQualifier] image IMAGE_NAME[10];
 *
 * Image variables refer to an image, of a particular type, stored within a texture.
 * These are used for arbitrary loading/storing of values within shaders. [Ëæ»ú·ÃÎÊ]
 * these type have array semantics
 * */
class glsl_image_t : public glsl_opaque_t {
public:
    glsl_image_t() = delete;
    glsl_image_t(glsl_image_format_layout_qualifier format_layout_qualifier, glsl_image_memory_qualifier memory_qualifier, const char* type_name, const char* value_name) :
            _type_name(type_name),
            _value_name(value_name),
            _format_layout_qualifier(format_layout_qualifier),
            _memory_qualifier(memory_qualifier),
            _image_format(transfer_format_layout_qualifier(format_layout_qualifier)),
            _access_mode(transfer_memory_qualifier(memory_qualifier))
    {
        //std::sprintf(_token.c_str(),"layout(binding=s%,s%) uniform s% s% s%;","0", "r32f", "image1D", "restrict", "pos");

    }

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

private:

    static gl_image_access_mode transfer_memory_qualifier(glsl_image_memory_qualifier memory_qualifier)
    {
        switch (memory_qualifier) {
            case glsl_image_memory_qualifier::COHERENT:return gl_image_access_mode::READ_WRITE;
            case glsl_image_memory_qualifier::VOLATILE:return gl_image_access_mode::READ_WRITE;
            case glsl_image_memory_qualifier::RESTRICT:return gl_image_access_mode::READ_WRITE;
            case glsl_image_memory_qualifier::READONLY:return gl_image_access_mode::READ_ONLY;
            case glsl_image_memory_qualifier::WRITEONLY:return gl_image_access_mode::WRITE_ONLY;
        }
    }

    static gl_image_format transfer_format_layout_qualifier(glsl_image_format_layout_qualifier format_layout_qualifier)
    {
        switch (format_layout_qualifier) {

            case glsl_image_format_layout_qualifier::R16F:
                break;
            case glsl_image_format_layout_qualifier::RG16F:
                break;
            case glsl_image_format_layout_qualifier::RGBA16F:
                break;
            case glsl_image_format_layout_qualifier::R32F:
                break;
            case glsl_image_format_layout_qualifier::RG32F:
                break;
            case glsl_image_format_layout_qualifier::RGBA32F:
                break;
            case glsl_image_format_layout_qualifier::R11F_G11F_B10F:
                break;
            case glsl_image_format_layout_qualifier::R8:
                break;
            case glsl_image_format_layout_qualifier::R16:
                break;
            case glsl_image_format_layout_qualifier::RG8:
                break;
            case glsl_image_format_layout_qualifier::RG16:
                break;
            case glsl_image_format_layout_qualifier::RGB8:
                break;
            case glsl_image_format_layout_qualifier::RGB16:
                break;
            case glsl_image_format_layout_qualifier::RGB10_A2:
                break;
            case glsl_image_format_layout_qualifier::R8_SNORM:
                break;
            case glsl_image_format_layout_qualifier::R16_SNORM:
                break;
            case glsl_image_format_layout_qualifier::RG8_SNORM:
                break;
            case glsl_image_format_layout_qualifier::RG16_SNORM:
                break;
            case glsl_image_format_layout_qualifier::RGBA8_SNORM:
                break;
            case glsl_image_format_layout_qualifier::RGBA16_SNORM:
                break;
            case glsl_image_format_layout_qualifier::R8I:
                break;
            case glsl_image_format_layout_qualifier::R16I:
                break;
            case glsl_image_format_layout_qualifier::R32I:
                break;
            case glsl_image_format_layout_qualifier::RG8I:
                break;
            case glsl_image_format_layout_qualifier::RG16I:
                break;
            case glsl_image_format_layout_qualifier::RG32I:
                break;
            case glsl_image_format_layout_qualifier::RGBA8I:
                break;
            case glsl_image_format_layout_qualifier::RGBA16I:
                break;
            case glsl_image_format_layout_qualifier::RGBA32I:
                break;
            case glsl_image_format_layout_qualifier::R8UI:
                break;
            case glsl_image_format_layout_qualifier::R16UI:
                break;
            case glsl_image_format_layout_qualifier::R32UI:
                break;
            case glsl_image_format_layout_qualifier::RG8UI:
                break;
            case glsl_image_format_layout_qualifier::RG16UI:
                break;
            case glsl_image_format_layout_qualifier::RG32UI:
                break;
            case glsl_image_format_layout_qualifier::RGBA8UI:
                break;
            case glsl_image_format_layout_qualifier::RGBA16UI:
                break;
            case glsl_image_format_layout_qualifier::RGBA32UI:
                break;
            case glsl_image_format_layout_qualifier::RGB10_A2UI:
                break;
        }
    }

};

class glsl_image1D : public glsl_image_t{
public:
    struct glsl_image1DResource{
        std::shared_ptr<gl_texture_1d_base> texture_1d;
        std::int32_t mipmap_index;
        glsl_image1DResource() : texture_1d(nullptr), mipmap_index(0){}
    }resource;

    glsl_image1D() = delete;
    glsl_image1D(glsl_image_format_layout_qualifier format_layout_qualifier, glsl_image_memory_qualifier memory_qualifier, const char* value_name) :
            glsl_image_t(format_layout_qualifier, memory_qualifier, "image1D", value_name)
    {}

    glsl_image1D(const glsl_image1D&) = delete;
    glsl_image1D& operator=(const glsl_image1D&) = delete;

    ~glsl_image1D() = default;

public:
    void bind() override
    {
        auto& texture_1d = resource.texture_1d;
        check_and_log(texture_1d, "do not have texture resource.")
        check_and_log(texture_1d->exists(resource.mipmap_index), "the mipmap_index specified  does not exist.")
        check_and_log(texture_1d->format() != _image_format,"the texture format does not fit to image format specified.")

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

class glsl_image1DArray : private glsl_image_t{
public:
    struct glsl_image1DArrayResource{
        std::shared_ptr<gl_texture_1d_array_base> texture_1d_array;
        std::int32_t mipmap_index;
        glsl_image1DArrayResource() : texture_1d_array(nullptr), mipmap_index(0){}
    }resource;

public:
    glsl_image1DArray() = delete;
    glsl_image1DArray(glsl_image_format_layout_qualifier format_layout_qualifier, glsl_image_memory_qualifier memory_qualifier, const char* value_name) :
            glsl_image_t(format_layout_qualifier, memory_qualifier, "image1DArray", value_name)
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


void test()
{
    glsl_image1D pos{glsl_image_format_layout_qualifier::R11F_G11F_B10F, glsl_image_memory_qualifier::RESTRICT, "pos"};
    glsl_image1DArray posArray{glsl_image_format_layout_qualifier::R16, glsl_image_memory_qualifier::RESTRICT, "posArray"};

    pos.resource.texture_1d;
    pos.resource.mipmap_index = 0;

    posArray.resource.texture_1d_array;
    posArray.resource.mipmap_index = 0;

}

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