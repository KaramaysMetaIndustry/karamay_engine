#ifndef GLSL_SAMPLER_H
#define GLSL_SAMPLER_H

#include "graphics/glsl/glsl_class.h"
#include "graphics/resource/texture/gl_texture.h"
#include "graphics/resource/sampler/gl_sampler.h"

class glsl_sampler_t : public glsl_texture_handler_t
{
protected:
    glsl_sampler_t() = delete;
    glsl_sampler_t(uint32 uint, const std::string& type_token, const std::string var_token) :
        _texture(nullptr),
        _sampler(nullptr),
        _unit(uint)
    {
        _token = "layout(binding = 0) sampler2D diffuse;";
    }

    void associate_texture(gl_texture_t* texture) 
    { 
        _texture = texture; 
    }
    
    gl_texture_t* get_texture() const 
    { 
        return _texture; 
    }

public:

    void assocate_sampler(gl_sampler* sampler)
    {
        _sampler = sampler;
    }

    gl_sampler* get_sampler() const 
    { 
        return _sampler;
    }

    const std::string& get_token() const { return _token; }

    uint32 get_unit() const { return _unit; }

    const std::string& get_var_token() const { return _var_token; }

public:

    void bind()
    {
        if (!_texture)
        {
            std::cerr << "bind canceled, no texture resource" << std::endl;
            return;
        }

        glBindTextureUnit(_unit, _texture->get_handle());
        std::cout << "bind texture at the unit " << _unit << std::endl;

        if (_sampler)
        {
            _sampler->bind(_unit);
            std::cout << "bind sampler at the unit " << _unit << std::endl;
        }

    }

    void unbind()
    {
        glBindTextureUnit(_unit, 0);

        if (_sampler)
        {
            _sampler->unbind(_unit);
        }
    }

private:

    gl_texture_t* _texture;

    gl_sampler* _sampler;

    uint32 _unit;

    std::string _token;

    std::string _var_token;

};


class glsl_sampler1D : public glsl_sampler_t
{
public:
    glsl_sampler1D(uint32 unit, const std::string& var_token) 
        : glsl_sampler_t(unit, "sampler1D", var_token) 
    {}

    glsl_sampler1D(const glsl_sampler1D&) = delete;
    glsl_sampler1D& operator=(const glsl_sampler1D&) = delete;

    ~glsl_sampler1D() = default;

public:

    void associate_texture_1d(gl_texture_1d* texture)
    {
        associate_texture(texture);
    }

    gl_texture_1d* get_texture_1d() const
    {
        return dynamic_cast<gl_texture_1d*>(get_texture());
    }

};

class glsl_sampler1DShadow : public glsl_sampler1D 
{

};

class glsl_sampler1DArray : public glsl_sampler_t
{
public:
    glsl_sampler1DArray(uint32 unit, const std::string& var_token) 
        : glsl_sampler_t(unit, "sampler1DArray", var_token) 
    {}

    glsl_sampler1DArray(const glsl_sampler1DArray&) = delete;
    glsl_sampler1DArray& operator=(const glsl_sampler1DArray&) = delete;

    ~glsl_sampler1DArray() = default;

public:

    void associate_texture_1d_array(gl_texture_1d_array* texture)
    {
        associate_texture(texture);
    }

    gl_texture_1d_array* get_texture_1d_array() const
    {
        return dynamic_cast<gl_texture_1d_array*>(get_texture());
    }

};

class glsl_sampler1DArrayShadow : public glsl_sampler1DArray 
{

};

class glsl_sampler2D : public glsl_sampler_t
{
public:
    glsl_sampler2D(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "sampler2D", var_token)
    {}

    glsl_sampler2D(const glsl_sampler2D&) = delete;
    glsl_sampler2D& operator=(const glsl_sampler2D&) = delete;

    ~glsl_sampler2D() {}

public:

    void associate_texture_2d(gl_texture_2d* texture)
    {
        associate_texture(texture);
    }

    gl_texture_2d* get_texture_2d() const
    {
        return dynamic_cast<gl_texture_2d*>(get_texture());
    }
};

class glsl_sampler2DShadow : public glsl_sampler2D 
{};

class glsl_sampler2DArray : public glsl_sampler_t
{
public:
    glsl_sampler2DArray(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "sampler2DArray", var_token)
    {}

    glsl_sampler2DArray(const glsl_sampler2DArray&) = delete;
    glsl_sampler2DArray& operator=(const glsl_sampler2DArray&) = delete;

    ~glsl_sampler2DArray() = default;

public:

    void associate_texture_2d_array(gl_texture_2d_array* texture)
    {
        associate_texture(texture);
    }

    gl_texture_2d_array* get_texture_2d_array() const
    {
        return dynamic_cast<gl_texture_2d_array*>(get_texture());
    }

};

class glsl_sampler2DArrayShadow : public glsl_sampler2DArray 
{};

class glsl_sampler2DMS : public glsl_sampler_t
{
public:
    glsl_sampler2DMS(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "sampler2DMS", var_token)
    {}

    glsl_sampler2DMS(const glsl_sampler2DMS&) = delete;
    glsl_sampler2DMS& operator=(const glsl_sampler2DMS&) = delete;

    ~glsl_sampler2DMS()
    {}

public:

    void associate_texture_2d_multisample(gl_texture_2d_multisample* texture)
    {
        associate_texture(texture);
    }

    gl_texture_2d_multisample* get_texture_2d_multisample() const
    {
        return dynamic_cast<gl_texture_2d_multisample*>(get_texture());
    }

};

class glsl_sampler2DMSArray : public glsl_sampler_t
{
public:
    glsl_sampler2DMSArray(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "sampler2DMSArray", var_token)
    {}

    glsl_sampler2DMSArray(const glsl_sampler2DMSArray&) = delete;
    glsl_sampler2DMSArray& operator=(const glsl_sampler2DMSArray&) = delete;

    ~glsl_sampler2DMSArray();

public:

    void associate_texture_2d_multisample_array(gl_texture_2d_multisample_array* texture)
    {
        associate_texture(texture);
    }

    gl_texture_2d_multisample_array* get_texture_2d_multisample_array() const
    {
        return dynamic_cast<gl_texture_2d_multisample_array*>(get_texture());
    }

};

class glsl_samplerCube : public glsl_sampler_t {
public:
    glsl_samplerCube(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "samplerCube", var_token)
    {}

    glsl_samplerCube(const glsl_samplerCube&) = delete;
    glsl_samplerCube& operator=(const glsl_samplerCube&) = delete;

    ~glsl_samplerCube() {}

public:

    void associate_texture_cube(gl_texture_cube* texture)
    {
        associate_texture(texture);
    }

    gl_texture_cube* get_texture_cube() const
    {
        return dynamic_cast<gl_texture_cube*>(get_texture());
    }

};

class glsl_samplerCubeShadow : public glsl_samplerCube 
{};

class glsl_samplerCubeArray : public glsl_sampler_t {
public:
    glsl_samplerCubeArray(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "samplerCubeArray", var_token)
    {}

    glsl_samplerCubeArray(const glsl_samplerCubeArray&) = delete;
    glsl_samplerCubeArray& operator=(const glsl_samplerCubeArray&) = delete;

    ~glsl_samplerCubeArray();

public:

    void associate_texture_cube_array(gl_texture_cube_array* texture)
    {
        associate_texture(texture);
    }

    gl_texture_cube_array* get_texture_cube_array() const
    {
        return dynamic_cast<gl_texture_cube_array*>(get_texture());
    }
};

class glsl_samplerCubeArrayShadow : public glsl_samplerCubeArray 
{};

class glsl_sampler2DRect : public glsl_sampler_t{
public:
    glsl_sampler2DRect(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "sampler2DRect", var_token)
    {}

    glsl_sampler2DRect(const glsl_sampler2DRect&) = delete;
    glsl_sampler2DRect& operator=(const glsl_sampler2DRect&) = delete;

    ~glsl_sampler2DRect();

public:

    void associate_texture_rectangle(gl_texture_rectangle* texture)
    {
        associate_texture(texture);
    }

    gl_texture_rectangle* get_texture_rectangle() const
    {
        return dynamic_cast<gl_texture_rectangle*>(get_texture());
    }

};

class glsl_sampler2DRectShadow : public glsl_sampler2DRect 
{};

class glsl_sampler3D : public glsl_sampler_t 
{
public:
    glsl_sampler3D(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "sampler3D", var_token)
    {}

    glsl_sampler3D(const glsl_sampler3D&) = delete;
    glsl_sampler3D& operator=(const glsl_sampler3D&) = delete;

    ~glsl_sampler3D();

public:

    void associate_texture_3d(gl_texture_3d* texture)
    {
        associate_texture(texture);
    }

    gl_texture_3d* get_texture_3d() const
    {
        return dynamic_cast<gl_texture_3d*>(get_texture());
    }

};

class glsl_samplerBuffer : public glsl_sampler_t
{
public:
    glsl_samplerBuffer(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "samplerBuffer", var_token)
    {}

    glsl_samplerBuffer(const glsl_samplerBuffer&) = delete;
    glsl_samplerBuffer& operator=(const glsl_samplerBuffer&) = delete;

    ~glsl_samplerBuffer() {}

public:

    void associate_texture_buffer(gl_texture_buffer* texture)
    {
        associate_texture(texture);
    }

    gl_texture_buffer* get_texture_buffer() const
    {
        return dynamic_cast<gl_texture_buffer*>(get_texture());
    }

};



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
