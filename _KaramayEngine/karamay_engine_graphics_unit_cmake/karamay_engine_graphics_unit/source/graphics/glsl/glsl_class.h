#ifndef H_GLSL_CLASS
#define H_GLSL_CLASS

#include "public/stl.h"
#include "public/glm.h"
#include "public/_glew.h"
#include "graphics/texture/gl_texture.h"

/*
 * glsl type
 *
 * */
class glsl_t {
public:
    [[nodiscard]] virtual const std::string& token() const = 0;
};

struct glsl_transparent_t_meta
{
    std::uint32_t components_count;
    std::uint32_t component_type_size;
    std::string component_type_name;
    std::uint32_t component_type_gl_enum;
    std::uint32_t type_size;
    std::string semantic_name;

    glsl_transparent_t_meta(
            std::uint32_t _components_count,
            std::uint32_t _component_type_size,
            std::uint32_t _component_type_gl_enum,
            std::uint32_t _type_size,
            std::string _semantic_name) :
            components_count(_components_count),
            component_type_size(_component_type_size),
            component_type_gl_enum(_component_type_gl_enum),
            type_size(_type_size),
            semantic_name(_semantic_name)
    {}
};

/*
 * glsl transparent type
 *
 * */
class glsl_transparent_t : public glsl_t{
public:
    virtual std::uint8_t* data() = 0;
	[[nodiscard]] virtual const std::uint8_t* data() const = 0;
	[[nodiscard]] virtual const std::int64_t size() const = 0;
};

/*
 * glsl opaque type
 * sampler/image/atomic_counter
 * */
class glsl_opaque_t : public glsl_t{

};

/*
 * [opaque type]
 * exp : layout(binding=0, offset=4) uniform atomic_uint counter_one;
 * pipeline only manage one atomic_counter_buffer for all registered counters
 * */
class glsl_atomic_counter_t : public glsl_opaque_t{
public:
    glsl_atomic_counter_t() : data(0){}
    explicit glsl_atomic_counter_t(std::uint32_t value) : data(value){}
    glsl_atomic_counter_t(const glsl_atomic_counter_t&) = delete;
    glsl_atomic_counter_t& operator=(const glsl_atomic_counter_t&) = delete;

    ~glsl_atomic_counter_t() = default;

public:
    [[nodiscard]] const std::string& token() const override
    {
        //_token.append("layout(binding={0}, offset={1}) uniform atomic_uint {2};",);
    }



private:

    std::uint32_t data;

    std::string _token;

};

/*
 * sampler/image
 * */
class glsl_texture_handler_t : glsl_opaque_t{
public:
    virtual void bind() = 0;
    virtual void unbind() = 0;
};


enum class glsl_storage_qualifier
{
    _const,
    _in,
    _out,
    _uniform,
    _buffer,
    _shared
};

enum class glsl_auxiliary_storage_qualifier
{
    _centroid,
    _sampler,
    _patch,
};

enum class glsl_layout_qualifier
{

};


#define TOKEN_STR(__TOKEN__) #__TOKEN__

#define DEFINE_GLSL_TRANSPARENT_T(GLSL_T_NAME, GLSL_T_SEMANTIC_NAME)\
class glsl_##GLSL_T_NAME final : public glsl_transparent_t{\
public:\
	glsl_##GLSL_T_NAME() = default;\
	explicit glsl_##GLSL_T_NAME(const glm::GLSL_T_SEMANTIC_NAME& value){}\
	~glsl_##GLSL_T_NAME() = default;\
public:\
	glm::GLSL_T_SEMANTIC_NAME client_value;\
};\



// float scalar && vectors && matrices
DEFINE_GLSL_TRANSPARENT_T(float, vec1)
DEFINE_GLSL_TRANSPARENT_T(vec2, vec2)
DEFINE_GLSL_TRANSPARENT_T(vec3, vec3)
DEFINE_GLSL_TRANSPARENT_T(vec4, vec4)
DEFINE_GLSL_TRANSPARENT_T(mat2, mat2)
DEFINE_GLSL_TRANSPARENT_T(mat2x3, mat2x3)
DEFINE_GLSL_TRANSPARENT_T(mat2x4, mat2x4)
DEFINE_GLSL_TRANSPARENT_T(mat3, mat3)
DEFINE_GLSL_TRANSPARENT_T(mat3x2, mat3x2)
DEFINE_GLSL_TRANSPARENT_T(mat3x4, mat3x4)
DEFINE_GLSL_TRANSPARENT_T(mat4, mat4)
DEFINE_GLSL_TRANSPARENT_T(mat4x2, mat4x2)
DEFINE_GLSL_TRANSPARENT_T(mat4x3, mat4x3)
// double scalar && vectors && matrices
DEFINE_GLSL_TRANSPARENT_T(double, dvec1)
DEFINE_GLSL_TRANSPARENT_T(dvec2, dvec2)
DEFINE_GLSL_TRANSPARENT_T(dvec3, dvec3)
DEFINE_GLSL_TRANSPARENT_T(dvec4, dvec4)
DEFINE_GLSL_TRANSPARENT_T(dmat2, dmat2)
DEFINE_GLSL_TRANSPARENT_T(dmat2x3, dmat2x3)
DEFINE_GLSL_TRANSPARENT_T(dmat2x4, dmat2x4)
DEFINE_GLSL_TRANSPARENT_T(dmat3, dmat3)
DEFINE_GLSL_TRANSPARENT_T(dmat3x2, dmat3x2)
DEFINE_GLSL_TRANSPARENT_T(dmat3x4, dmat3x4)
DEFINE_GLSL_TRANSPARENT_T(dmat4, dmat4)
DEFINE_GLSL_TRANSPARENT_T(dmat4x2, dmat4x2)
DEFINE_GLSL_TRANSPARENT_T(dmat4x3, dmat4x3)
// int scalar && vectors
DEFINE_GLSL_TRANSPARENT_T(int, ivec1)
DEFINE_GLSL_TRANSPARENT_T(ivec2, ivec2)
DEFINE_GLSL_TRANSPARENT_T(ivec3, ivec3)
DEFINE_GLSL_TRANSPARENT_T(ivec4, ivec4)
// uint scalar && vectors
DEFINE_GLSL_TRANSPARENT_T(uint, uvec1)
DEFINE_GLSL_TRANSPARENT_T(uvec2, uvec2)
DEFINE_GLSL_TRANSPARENT_T(uvec3, uvec3)
DEFINE_GLSL_TRANSPARENT_T(uvec4, uvec4)



/*
 *
 * */
class glsl_interface_block_t : public glsl_t{
public:
    glsl_interface_block_t() = default;
    glsl_interface_block_t(const glsl_interface_block_t&) = delete;

    ~glsl_interface_block_t() = default;

public:
    virtual std::uint8_t* data() = 0;
    [[nodiscard]] virtual const std::uint8_t* data() const = 0;
    [[nodiscard]] virtual std::int64_t size() const = 0;

};

enum class glsl_interface_block_matrix_layout
{
    ROW_MAJOR,
    COLUMN_MAJOR
};

enum class glsl_uniform_block_memory_layout
{
    SHARED,
    STD140,
    PACKED
};

enum class glsl_shader_storage_block_memory_layout
{
    STD140,
    STD430
};

/*
 * [transparent type]
 * exp : layout(row_major,std140/shared/packed,binding=0) uniform { ... };
 * pipeline manage 3 ubos
 * */
class glsl_uniform_block_t : public glsl_interface_block_t{
public:
    glsl_uniform_block_t() = default;
    glsl_uniform_block_t(
            glsl_interface_block_matrix_layout matrix_layout,
            glsl_uniform_block_memory_layout _memory_layout,
            std::uint32_t binding
            ) : memory_layout(_memory_layout){}
    glsl_uniform_block_t(const glsl_uniform_block_t&) = delete;
    glsl_uniform_block_t& operator=(const glsl_uniform_block_t&) = delete;

    ~glsl_uniform_block_t() = default;

    const glsl_uniform_block_memory_layout memory_layout;

public:

    void mark_dirty(bool is_dirty) {}

    bool is_dirty(){}

};

/*
 * [transparent type]
 * exp : layout(row_major,std140/std430,binding=0) buffer { ... };
 * these blocks can control their value directly
 * */
class glsl_shader_storage_block_t : public glsl_interface_block_t{
public:
    glsl_shader_storage_block_t() = default;
    glsl_shader_storage_block_t(
            glsl_interface_block_matrix_layout matrix_layout,
            glsl_shader_storage_block_memory_layout memory_layout,
            std::uint32_t binding
            ){}
    glsl_shader_storage_block_t(const glsl_shader_storage_block_t&) = delete;
    glsl_shader_storage_block_t& operator=(const glsl_shader_storage_block_t&) = delete;

    ~glsl_shader_storage_block_t() = default;

public:

    const std::string& token() const override
    {
        return _token;
    }


private:
    std::string _token;

};


/*
 * these blocks cannot control their value directly.
 * exp :
 *
 * vertex_shader:
 * in InVertexData{ ... } inData;
 * out OutVertexData{ ... } outData;
 *
 * tessellation evaluation shader:
 * in InVertexData{ ... } inData[];
 * out InVertexData{ ... } outData[];
 *
 * geometry shader:
 *
 *
 *
 * */
class glsl_in_block_t : public glsl_t{

};

/*
 *
 * */
class glsl_out_block_t : public glsl_t{

};


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
    glsl_image_t() = delete;
    glsl_image_t(glsl_image_format_layout_qualifier format_layout_qualifier, glsl_image_memory_qualifier memory_qualifier, const char* type_name, const char* value_name) :
            _type_name(type_name),
            _value_name(value_name),
            _format_layout_qualifier(format_layout_qualifier),
            _memory_qualifier(memory_qualifier),
            _image_format(transfer_format_layout_qualifier(format_layout_qualifier)),
            _access_mode(transfer_memory_qualifier(memory_qualifier))
    {}

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
    }

    static gl_image_format transfer_format_layout_qualifier(glsl_image_format_layout_qualifier format_layout_qualifier)
    {
    }

};

class glsl_image1D : public glsl_image_t{
public:
    glsl_image1D() = delete;
    glsl_image1D(
            glsl_image_format_layout_qualifier format_layout_qualifier,
            glsl_image_memory_qualifier memory_qualifier,
            const std::string& name
            ) :
            glsl_image_t(format_layout_qualifier, memory_qualifier, "image1D", name.c_str())
    {}

    glsl_image1D(const glsl_image1D&) = delete;
    glsl_image1D& operator=(const glsl_image1D&) = delete;

    ~glsl_image1D() = default;

    std::shared_ptr<gl_texture_1d_t> texture_1d;
    std::int32_t mipmap_index;

    void bind() override
    {

//        check_and_log(texture_1d, "do not have texture resource.")
//        check_and_log(texture_1d->exists(mipmap_index), "the mipmap_index specified  does not exist.")
//        check_and_log(texture_1d->format() != _image_format,"the texture format does not fit to image format specified.")

        glBindImageTexture(0, // unit
                           texture_1d->get_handle(), mipmap_index, // mipmap
                           GL_TRUE, 0, // not an array or whole array
                           static_cast<GLenum>(_access_mode), // access
                           static_cast<GLenum>(texture_1d->format()) // format
        );
    }

    void unbind() override
    {
        if(!texture_1d) return;
    }

};

class glsl_image1DArray : private glsl_image_t{
public:
    struct glsl_image1DArrayResource{
        std::shared_ptr<gl_texture_1d_array_t> texture_1d_array;
        std::int32_t mipmap_index;
        glsl_image1DArrayResource() : texture_1d_array(nullptr), mipmap_index(0){}
    }resource;

    glsl_image1DArray() = delete;
    glsl_image1DArray(
            glsl_image_format_layout_qualifier format_layout_qualifier,
            glsl_image_memory_qualifier memory_qualifier,
            const char* value_name
            ):
            glsl_image_t(
                    format_layout_qualifier,
                    memory_qualifier,
                    "image1DArray",
                    value_name
                    )
    {}

    glsl_image1DArray(const glsl_image1DArray&) = delete;
    glsl_image1DArray& operator=(const glsl_image1DArray&) = delete;

    ~glsl_image1DArray() = default;

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


/*
 * exp : layout(binding=0) uniform sampler2D positionTexture;
 *
 * */
class glsl_sampler_t : public glsl_texture_handler_t{
public:
    glsl_sampler_t() = delete;
    glsl_sampler_t(const std::string& type_name, const std::string& value_name)
    {}
    glsl_sampler_t(const glsl_sampler_t&) = delete;
    glsl_sampler_t& operator=(const glsl_sampler_t&) = delete;

    ~glsl_sampler_t() = default;

public:

    [[nodiscard]] const std::string& token() const override{
        std::string _token("layout(binding={0}) uniform {1} {2};");
    }

};

class glsl_sampler1D : public glsl_sampler_t{
public:
    struct glsl_sampler1DResource
    {
        std::shared_ptr<gl_texture_1d_t> texture_1d;
        std::shared_ptr<gl_sampler> sampler;
    } resource;

    glsl_sampler1D() = delete;
    explicit glsl_sampler1D(const std::string& value_name) :
            glsl_sampler_t("sampler1D", value_name)
    {}
    glsl_sampler1D(const glsl_sampler1D&) = delete;
    glsl_sampler1D& operator=(const glsl_sampler1D&) = delete;

    void bind() override
    {
        if(!resource.texture_1d)
        {
            std::cerr<<"warning, sampler1D do not have resource bound."<<std::endl;
            return;
        }

        glBindTextureUnit(0, resource.texture_1d->get_handle());
        if(resource.sampler)
        {
            resource.sampler->bind(0);
        }
    }

    void unbind() override
    {
        if(!resource.texture_1d) return;
        glBindTextureUnit(0, 0);
        if(resource.sampler)
        {
            //.sampler->unbind();
        }
    }

};

class glsl_sampler1DArray : public glsl_sampler_t{
public:
    struct glsl_sampler1DArrayResource
    {
        std::shared_ptr<gl_texture_1d_array_t> texture_1d_array;
        std::shared_ptr<gl_sampler> sampler;
    } resource;

    glsl_sampler1DArray() = delete;
    explicit glsl_sampler1DArray(const std::string& value_name) :
            glsl_sampler_t("sampler1DArray", value_name)
    {}
    glsl_sampler1DArray(const glsl_sampler1DArray&) = delete;
    glsl_sampler1DArray& operator=(const glsl_sampler1DArray&) = delete;

    ~glsl_sampler1DArray() = default;

    void bind() override
    {

    }

    void unbind() override
    {}

};

class glsl_sampler2D : public glsl_sampler_t{
public:
    struct glsl_sampler2DResource
    {
        std::shared_ptr<gl_texture_2d_t> texture_2d;
        std::int32_t mipmap_index;
    } resource;

public:

    glsl_sampler2D() = default;


    void bind() override
    {
        glBindTextureUnit(GL_TEXTURE0, resource.texture_2d->get_handle());
    }

    void unbind() override
    {
        glBindTextureUnit(GL_TEXTURE0, 0);
    }


};

class glsl_sampler2DArray : public glsl_sampler_t{
public:
    struct glsl_sampler2DArrayResource
    {
        std::shared_ptr<gl_texture_2d_array_t> texture_2d_array;
        std::int32_t mipmap_index;
    } resource;

    glsl_sampler2DArray() = delete;

    ~glsl_sampler2DArray() = default;

    void bind()
    {
        glBindTextureUnit(GL_TEXTURE0, resource.texture_2d_array->get_handle());
    }

    void unbind()
    {
        glBindTextureUnit(GL_TEXTURE0, 0);
    }

};

class glsl_sampler2DMS : public glsl_sampler_t{
public:
    struct glsl_sampler2DMSResource
    {
        std::shared_ptr<gl_texture_2d_multisample_t> texture_2d_multisample;
    } resource;

    void bind()
    {
        glBindTextureUnit(GL_TEXTURE0, resource.texture_2d_multisample->get_handle());
    }

    void unbind()
    {
        glBindTextureUnit(GL_TEXTURE0, 0);
    }


};

class glsl_sampler2DMSArray : public glsl_sampler_t{
public:

    struct glsl_sampler2DMSArrayResource
    {
        std::shared_ptr<gl_texture_2d_multisample_array_t> texture_2d_multisample_array;
    } resource;

public:

    glsl_sampler2DMSArray() = delete;

public:

    void bind()
    {
        glBindTextureUnit(GL_TEXTURE0, resource.texture_2d_multisample_array->get_handle());
    }

    void unbind()
    {
        glBindTextureUnit(GL_TEXTURE0, 0);
    }

};

class glsl_samplerCube : public glsl_sampler_t {
public:
    struct glsl_samplerCubeResource
    {
        std::shared_ptr<gl_texture_cube_t> texture_cube;
        std::int32_t mipmap_index;
    } resource;
};

class glsl_samplerCubeArray : public glsl_sampler_t {
public:
    struct glsl_samplerCubeArrayResource
    {
        std::shared_ptr<gl_texture_cube_array_t> texture_cube_array;
        std::int32_t mipmap_index;
    } resource;
};

class glsl_sampler2DRect : public glsl_sampler_t{
public:
    struct glsl_sampler2DRectResource
    {
        std::shared_ptr<gl_texture_rectangle_t> texture_rectangle;
    } resource;
};

class glsl_sampler3D : public glsl_sampler_t {
public:
    struct glsl_sampler3DResource
    {
        std::shared_ptr<gl_texture_3d_t> texture_3d;
        std::int32_t mipmap_index;
    } resource;
};

class glsl_samplerBuffer : public glsl_sampler_t{
public:
    struct glsl_samplerBufferResource
    {
        std::shared_ptr<gl_texture_buffer_t> texture_buffer;
    } resource;
};

class glsl_sampler1DShadow : public glsl_sampler_t{};

class glsl_sampler1DArrayShadow : public glsl_sampler_t{};

class glsl_sampler2DShadow : public glsl_sampler_t{};

class glsl_sampler2DArrayShadow : public glsl_sampler_t{};

class glsl_samplerCubeShadow : public glsl_sampler_t{};

class glsl_samplerCubeArrayShadow : public glsl_sampler_t{};

class glsl_sampler2DRectShadow : public glsl_sampler_t{};



//DEFINE_GLSL_SAMPLER_T(isampler1D)
//DEFINE_GLSL_SAMPLER_T(isampler1DArray)
//DEFINE_GLSL_SAMPLER_T(isampler2D)
//DEFINE_GLSL_SAMPLER_T(isampler2DArray)
//DEFINE_GLSL_SAMPLER_T(isampler2DRect)
//DEFINE_GLSL_SAMPLER_T(isampler2DMS)
//DEFINE_GLSL_SAMPLER_T(isampler2DMSArray)
//DEFINE_GLSL_SAMPLER_T(isampler3D)
//DEFINE_GLSL_SAMPLER_T(isamplerCube)
//DEFINE_GLSL_SAMPLER_T(isamplerCubeArray)
//DEFINE_GLSL_SAMPLER_T(isamplerBuffer)
//DEFINE_GLSL_SAMPLER_T(isampler1DShadow)
//DEFINE_GLSL_SAMPLER_T(isampler2DShadow)
//DEFINE_GLSL_SAMPLER_T(isampler2DRectShadow)
//DEFINE_GLSL_SAMPLER_T(isampler1DArrayShadow)
//DEFINE_GLSL_SAMPLER_T(isampler2DArrayShadow)
//DEFINE_GLSL_SAMPLER_T(isamplerCubeShadow)
//DEFINE_GLSL_SAMPLER_T(isamplerCubeArrayShadow)

//DEFINE_GLSL_SAMPLER_T(usampler1D)
//DEFINE_GLSL_SAMPLER_T(usampler1DArray)
//DEFINE_GLSL_SAMPLER_T(usampler2D)
//DEFINE_GLSL_SAMPLER_T(usampler2DArray)
//DEFINE_GLSL_SAMPLER_T(usampler2DRect)
//DEFINE_GLSL_SAMPLER_T(usampler2DMS)
//DEFINE_GLSL_SAMPLER_T(usampler2DMSArray)
//DEFINE_GLSL_SAMPLER_T(usampler3D)
//DEFINE_GLSL_SAMPLER_T(usamplerCube)
//DEFINE_GLSL_SAMPLER_T(usamplerCubeArray)
//DEFINE_GLSL_SAMPLER_T(usamplerBuffer)
//DEFINE_GLSL_SAMPLER_T(usampler1DShadow)
//DEFINE_GLSL_SAMPLER_T(usampler2DShadow)
//DEFINE_GLSL_SAMPLER_T(usampler2DRectShadow)
//DEFINE_GLSL_SAMPLER_T(usampler1DArrayShadow)
//DEFINE_GLSL_SAMPLER_T(usampler2DArrayShadow)
//DEFINE_GLSL_SAMPLER_T(usamplerCubeShadow)
//DEFINE_GLSL_SAMPLER_T(usamplerCubeArrayShadow)


#endif
