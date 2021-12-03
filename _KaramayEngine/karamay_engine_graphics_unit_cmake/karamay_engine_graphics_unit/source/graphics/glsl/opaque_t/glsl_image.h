#ifndef GLSL_IMAGE_H
#define GLSL_IMAGE_H

#include "graphics/glsl/glsl_class.h"
#include "graphics/resource/texture/gl_texture.h"

enum class glsl_image_format_qualifier
{
    // image*
    R16F, RG16F, RGBA16F,
    R32F, RG32F, RGBA32F,
    R11F_G11F_B10F,
    
    R8, R16,
    RG8, RG16,
    RGB8, RGB16,
    RGB10_A2,
    
    R8_SNORM, R16_SNORM,
    RG8_SNORM, RG16_SNORM,
    RGBA8_SNORM, RGBA16_SNORM,
    
    // int iimage*
    R8I, R16I, R32I,
    RG8I, RG16I, RG32I,
    RGBA8I, RGBA16I, RGBA32I,
   
    // uint uimage*
    R8UI, R16UI, R32UI,
    RG8UI, RG16UI, RG32UI,
    RGBA8UI, RGBA16UI, RGBA32UI,
    
    RGB10_A2UI
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
 *
 * exp : layout(binding=3,rgba32f) uniform writeonly readonly image1D imageColors;
 *
 * */
class glsl_image_t : public glsl_texture_handler_t 
{
public:
    glsl_image_t(uint32 binding, glsl_image_format_qualifier format_qualifier, const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, const std::string& type_name, const std::string& var_name) :
        _binding(binding),
        _format_qualifier(format_qualifier),
        _memory_qualifiers(memory_qualifiers),
        _type_name(type_name),
        _var_name(var_name)
    {
        // gen token
        std::string _memory_qualifer_seq;
        for (const auto& _q : _memory_qualifiers)
        {
            _memory_qualifer_seq.append(_cast_memory_qualifier(_q) + " ");
        }

        _token = std::string("layout(binding=") + std::to_string(binding) +  "," + _cast_format_qualifier(format_qualifier) +  ") uniform " + _memory_qualifer_seq + _type_name + " " + var_name + ";";
    }

    glsl_image_t(const glsl_image_t&) = delete;
    glsl_image_t& operator=(const glsl_image_t&) = delete;

    ~glsl_image_t() = default;

public:

    void bind()
    {
        glBindImageTexture(
            _binding, _binding_info.tex->get_handle(), _binding_info.mipmap_index, _binding_info.is_layered, _binding_info.layer_index, 
            static_cast<GLenum>(_access_mode), 0
        );
    }

    void unbind()
    {
        glBindImageTexture(_binding, 0, 0, 0, 0, 0, 0);
    }

protected:

    struct image_binding_info
    {
        int32 mipmap_index;
        gl_texture_t* tex;
        bool is_layered;
        int32 layer_index;
    } _binding_info;

    gl_image_access_mode _access_mode;
   
    uint32 _binding;
    glsl_image_format_qualifier _format_qualifier;
    std::vector<glsl_image_memory_qualifier> _memory_qualifiers;
    std::string _type_name;
    std::string _var_name;
    std::string _token;

    static std::string _cast_format_qualifier(glsl_image_format_qualifier format_qualifier)
    {
        switch (format_qualifier)
        {
        case glsl_image_format_qualifier::R11F_G11F_B10F: return "r11f_g11f_b10f";
        default: return "";
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

class glsl_image : public glsl_image_t
{
public:
    glsl_image(uint32 binding, glsl_image_format_qualifier format_qualifier, const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, const std::string& type_name, const std::string& var_name) :
        glsl_image_t(binding, format_qualifier, memory_qualifiers, type_name, var_name)
    {}

protected:

    bool _check_internal_format(gl_texture_internal_format internal_format)
    {
        return false;
    }

};

class glsl_iimage : public glsl_image_t
{

};

class glsl_uimage : public glsl_image_t
{

};

class glsl_image1D : public glsl_image
{
public:
    glsl_image1D(uint32 binding, glsl_image_format_qualifier format_qualifier, const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, const std::string& var_name) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "image1D", var_name)
    {}

    glsl_image1D(const glsl_image1D&) = delete;
    glsl_image1D& operator=(const glsl_image1D&) = delete;

    ~glsl_image1D() = default;

public:

    void set_image_1d(gl_texture_1d* texture_1d, int32 mipmap_index) 
    {
        if (!_check_internal_format(texture_1d->get_internal_format())) return;

        _binding_info.tex = texture_1d;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = mipmap_index;
    }

    void set_image_1d(gl_texture_1d_array* texture_1d_array, int32 element_index, int32 mipmap_index)
    {
        if (!_check_internal_format(texture_1d_array->get_internal_format())) return;

        _binding_info.tex = texture_1d_array;
        _binding_info.is_layered = false;
        _binding_info.layer_index = element_index;
        _binding_info.mipmap_index = mipmap_index;
    }

};

class glsl_image1DArray : private glsl_image
{
public:
    glsl_image1DArray(uint32 binding, glsl_image_format_qualifier format_qualifier, const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, const std::string& var_name) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "image1DArray", var_name)
    {}

    glsl_image1DArray(const glsl_image1DArray&) = delete;
    glsl_image1DArray& operator=(const glsl_image1DArray&) = delete;

    ~glsl_image1DArray() = default;

public:

    void set_image_1d_array(gl_texture_1d_array* texture_1d_array, int32 mipmap_index)
    {
        if (!_check_internal_format(texture_1d_array->get_internal_format())) return;
        
        _binding_info.tex = texture_1d_array;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = mipmap_index;
    }

};

class glsl_image2D : public glsl_image
{
public:
    glsl_image2D(uint32 binding, glsl_image_format_qualifier format_qualifier, const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, const std::string& var_name) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "image2D", var_name)
    {}

    glsl_image2D(const glsl_image2D&) = delete;
    glsl_image2D& operator=(const glsl_image2D&) = delete;

    ~glsl_image2D() = default;

public:

    void set_image_2d(gl_texture_2d* texture_2d, int32 mipmap_index)
    {
        if (!texture_2d) return;
        if (mipmap_index < 0) return;
        if (!_check_internal_format(texture_2d->get_internal_format())) return;

        _binding_info.tex = texture_2d;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = mipmap_index;
    }

    void set_image_2d(gl_texture_2d_array* texture_2d_array, int32 element_index, int32 mipmap_index)
    {
        if (!texture_2d_array) return;
        if (!_check_internal_format(texture_2d_array->get_internal_format())) return;

        _binding_info.tex = texture_2d_array;
        _binding_info.is_layered = false;
        _binding_info.layer_index = element_index;
        _binding_info.mipmap_index = mipmap_index;
    }

    void set_image_2d(gl_texture_cube* texture_cube, gl_cube_face_index face_index, int32 mipmap_index) 
    {
        if (!texture_cube) return;
        if (!_check_internal_format(texture_cube->get_internal_format())) return;

        _binding_info.tex = texture_cube;
        _binding_info.is_layered = false;
        _binding_info.layer_index = gl_texture_t::cast_face_index(face_index);
        _binding_info.mipmap_index = mipmap_index;
    }

    void set_image_2d(gl_texture_cube_array* texture_cube_array, int32 element_index, gl_cube_face_index face_index, int32 mipmap_index) 
    {
        if (!texture_cube_array) return;
        if (!_check_internal_format(texture_cube_array->get_internal_format())) return;

        _binding_info.tex = texture_cube_array;
        _binding_info.is_layered = false;
        _binding_info.layer_index = element_index + gl_texture_t::cast_face_index(face_index);
        _binding_info.mipmap_index = mipmap_index;
    }

};

class glsl_image2DArray : public glsl_image
{
public:
    glsl_image2DArray(
        uint32 binding, 
        glsl_image_format_qualifier format_qualifier, 
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers, 
        const std::string& var_name
    ) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "image2DArray", var_name)
    {}

    glsl_image2DArray(const glsl_image2DArray&) = delete;
    glsl_image2DArray& operator=(const glsl_image2DArray&) = delete;

    ~glsl_image2DArray() = default;

public:

    void set_image_2d_array(gl_texture_2d_array* texture_2d_array, int32 mipmap_index)
    {
        if (!texture_2d_array) return;
        if (!_check_internal_format(texture_2d_array->get_internal_format())) return;

        _binding_info.tex = texture_2d_array;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = mipmap_index;
    }

};

class glsl_imageCube : public glsl_image
{
public:

    glsl_imageCube(
        uint32 binding,
        glsl_image_format_qualifier format_qualifier,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "imageCube", var_name)
    {}

    glsl_imageCube(const glsl_imageCube&) = delete;
    glsl_imageCube& operator=(const glsl_image2DArray&) = delete;

    ~glsl_imageCube() = default;

public:

    void set_image_cube(gl_texture_cube* texture_cube, int32 mipmap_index)
    {
        if (!texture_cube) return;
        if (!_check_internal_format(texture_cube->get_internal_format())) return;
        _binding_info.tex = texture_cube;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = mipmap_index;
    }

    void set_image_cube(gl_texture_cube_array* texture_cube_array, int32 mipmap_index)
    {
        if (!texture_cube_array) return;
        if (!_check_internal_format(texture_cube_array->get_internal_format())) return;
        _binding_info.tex = texture_cube_array;
        _binding_info.is_layered = false;
        _binding_info.layer_index = 0;
        _binding_info.mipmap_index = mipmap_index;
    }

};

class glsl_imageCubeArray : public glsl_image
{
public:

    glsl_imageCubeArray(
        uint32 binding,
        glsl_image_format_qualifier format_qualifier,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "imageCubeArray", var_name)
    {}

    glsl_imageCubeArray(const glsl_imageCubeArray&) = delete;
    glsl_imageCubeArray& operator=(const glsl_imageCubeArray&) = delete;

    ~glsl_imageCubeArray() = default;

public:

    void set_image_cube_array(gl_texture_cube_array* texture_cube_array, int32 mipmap_index)
    {
        if (!texture_cube_array) return;
        if (!_check_internal_format(texture_cube_array->get_internal_format())) return;
        _binding_info.tex = texture_cube_array;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = mipmap_index;
    }

};

class glsl_image2DMS : public glsl_image
{
public:

    glsl_image2DMS(
        uint32 binding,
        glsl_image_format_qualifier format_qualifier,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "image2DMS", var_name)
    {}

    glsl_image2DMS(const glsl_image2DMS&) = delete;
    glsl_image2DMS& operator=(const glsl_image2DMS&) = delete;

    ~glsl_image2DMS() = default;

public:

    void set_image_2d_ms(gl_texture_2d_multisample* texture_2d_multisample, int32 mipmap_index)
    {
        if (!texture_2d_multisample) return;
        if (!_check_internal_format(texture_2d_multisample->get_internal_format())) return;
        _binding_info.tex = texture_2d_multisample;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = mipmap_index;
    }

    void set_image_2d_ms(gl_texture_2d_multisample_array* texture_2d_multisample_array, int32 element_index, int32 mipmap_index)
    {
        if (!texture_2d_multisample_array) return;
        if (!_check_internal_format(texture_2d_multisample_array->get_internal_format())) return;
        _binding_info.tex = texture_2d_multisample_array;
        _binding_info.is_layered = false;
        _binding_info.layer_index = element_index;
        _binding_info.mipmap_index = mipmap_index;
    }

};

class glsl_image2DMSArray : public glsl_image
{
public:
    glsl_image2DMSArray(
        uint32 binding,
        glsl_image_format_qualifier format_qualifier,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "image2DMSArray", var_name)
    {}

    glsl_image2DMSArray(const glsl_image2DMSArray&) = delete;
    glsl_image2DMSArray& operator=(const glsl_image2DMSArray&) = delete;

    ~glsl_image2DMSArray() = default;

public:

    void set_image_2d_ms_array(gl_texture_2d_multisample_array* texture_2d_multisample_array, int32 mipmap_index)
    {
        if (!texture_2d_multisample_array) return;
        if (!_check_internal_format(texture_2d_multisample_array->get_internal_format())) return;
        _binding_info.tex = texture_2d_multisample_array;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = mipmap_index;
    }

};

class glsl_image2DRect : public glsl_image
{
public:
    glsl_image2DRect(
        uint32 binding,
        glsl_image_format_qualifier format_qualifier,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "image2DRect", var_name)
    {}

    glsl_image2DRect(const glsl_image2DRect&) = delete;
    glsl_image2DRect& operator=(const glsl_image2DRect&) = delete;

    ~glsl_image2DRect() = default;

public:

    void set_image_2d_rect(gl_texture_rectangle* texture_rectangle)
    {
        if (!texture_rectangle) return;
        if (!_check_internal_format(texture_rectangle->get_internal_format())) return;
        _binding_info.tex = texture_rectangle;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = 0;
    }
};

class glsl_image3D : public glsl_image
{
public:
    glsl_image3D(
        uint32 binding,
        glsl_image_format_qualifier format_qualifier,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "image3D", var_name)
    {}

    glsl_image3D(const glsl_image3D&) = delete;
    glsl_image3D& operator=(const glsl_image3D&) = delete;

    ~glsl_image3D() = default;

public:

    void set_image_3d(gl_texture_3d* texture_3d, int32 mipmap_index)
    {
        if (!texture_3d) return;
        if (!_check_internal_format(texture_3d->get_internal_format())) return;
        _binding_info.tex = texture_3d;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = mipmap_index;
    }

};

class glsl_imageBuffer : public glsl_image
{
public:
    glsl_imageBuffer(
        uint32 binding,
        glsl_image_format_qualifier format_qualifier,
        const std::vector<glsl_image_memory_qualifier>& memory_qualifiers,
        const std::string& var_name
    ) :
        glsl_image(binding, format_qualifier, memory_qualifiers, "imageBuffer", var_name)
    {}

    glsl_imageBuffer(const glsl_imageBuffer&) = delete;
    glsl_imageBuffer& operator=(const glsl_imageBuffer&) = delete;

    ~glsl_imageBuffer() = default;
    
public:

    void set_image_buffer(gl_texture_buffer* texture_buffer)
    {
        if (!texture_buffer) return;
        if (!_check_internal_format(texture_buffer->get_internal_format())) return;
        _binding_info.tex = texture_buffer;
        _binding_info.is_layered = true;
        _binding_info.mipmap_index = 0;
    }

};


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