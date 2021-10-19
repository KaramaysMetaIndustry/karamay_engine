#ifndef GLSL_SAMPLER_H
#define GLSL_SAMPLER_H

#include "graphics/glsl/glsl_class.h"
#include "graphics/resource/texture/gl_texture.h"
#include "graphics/resource/sampler/gl_sampler.h"

/*
 * EXP : layout(binding=0) uniform sampler2D positionTexture;
 * declare a sampler uniform.
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
