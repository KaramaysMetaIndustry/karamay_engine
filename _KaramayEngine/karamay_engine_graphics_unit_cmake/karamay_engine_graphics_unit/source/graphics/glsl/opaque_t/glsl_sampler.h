#ifndef GLSL_SAMPLER_H
#define GLSL_SAMPLER_H

#include "graphics/glsl/glsl_class.h"
#include "graphics/resource/texture/gl_texture.h"
#include "graphics/resource/sampler/gl_sampler.h"

class glsl_sampler_t 
{
protected:
    glsl_sampler_t() = delete;
    glsl_sampler_t(uint32 binding, const std::string& type_token, const std::string var_token) :
        _texture(nullptr),
        _sampler(nullptr),
        _binding(binding)
    {
        _token = "layout(binding = 0) sampler2D diffuse;";
    }

protected:

    virtual void set_texture(gl_texture_t* texture)
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

    uint32 get_unit() const { return _binding; }

    const std::string& get_var_token() const { return _var_token; }

public:

    void bind()
    {
        if (!_texture)
        {
            std::cerr << "bind canceled, no texture resource" << std::endl;
            return;
        }

        glBindTextureUnit(_binding, _texture->get_handle());
        std::cout << "bind texture at the unit " << _binding << std::endl;

        if (_sampler)
        {
            _sampler->bind(_binding);
            std::cout << "bind sampler at the unit " << _binding << std::endl;
        }

    }

    void unbind()
    {
        glBindTextureUnit(_binding, 0);

        if (_sampler)
        {
            _sampler->unbind(_binding);
        }
    }

private:

    gl_texture_t* _texture;
    gl_sampler* _sampler;
    uint32 _binding;
    std::string _token;
    std::string _var_token;
};

class glsl_sampler : public glsl_sampler_t
{
public:
    glsl_sampler(uint32 binding, const std::string& type_name, const std::string& var_name) : glsl_sampler_t(binding, type_name, var_name) {}

protected:

    void set_texture(gl_texture_t* texture) override
    {
        if (!_check_format(texture))
        {
            std::cerr << "internal format must be float about." << std::endl;
            return;
        }
        glsl_sampler_t::set_texture(texture);
    }

    bool _check_format(gl_texture_t* texture)
    {
        switch (texture->get_internal_format())
        {
        case gl_texture_internal_format::F_R11_G11_B10: return true;
        case gl_texture_internal_format::F_R32: return true;
        case gl_texture_internal_format::F_RG32: return true;
        case gl_texture_internal_format::F_RGB32: return true;
        case gl_texture_internal_format::F_RGBA32: return true;
        case gl_texture_internal_format::NOR_I_R16: return true;
        case gl_texture_internal_format::NOR_I_R8: return true;
        case gl_texture_internal_format::NOR_I_RG16: return true;
        case gl_texture_internal_format::NOR_I_RG8: return true;
        case gl_texture_internal_format::NOR_I_RGB16: return true;
        case gl_texture_internal_format::NOR_I_RGB8: return true;
        case gl_texture_internal_format::NOR_I_RGBA16: return true;
        case gl_texture_internal_format::NOR_I_RGBA8: return true;
        case gl_texture_internal_format::NOR_UI_R16: return true;
        case gl_texture_internal_format::NOR_UI_R3_G3_B2: return true;
        case gl_texture_internal_format::NOR_UI_R5_G6_B5: return true;
        case gl_texture_internal_format::NOR_UI_R8: return true;
        case gl_texture_internal_format::NOR_UI_RG16: return true;
        case gl_texture_internal_format::NOR_UI_RG8: return true;
        case gl_texture_internal_format::NOR_UI_RGB10_A2: return true;
        case gl_texture_internal_format::NOR_UI_RGB16: return true;
        case gl_texture_internal_format::NOR_UI_RGB5_A1: return true;
        case gl_texture_internal_format::NOR_UI_RGB8: return true;
        case gl_texture_internal_format::NOR_UI_RGBA16: return true;
        case gl_texture_internal_format::NOR_UI_RGBA2: return true;
        case gl_texture_internal_format::NOR_UI_RGBA4: return true;
        case gl_texture_internal_format::NOR_UI_RGBA8: return true;
        case gl_texture_internal_format::NOR_UI_SRGB8: return true;
        case gl_texture_internal_format::NOR_UI_SRGB8_ALPHA8: return true;
        default: return false;
        }
    }

};

class glsl_samplerShadow : public glsl_sampler {};

class glsl_isampler : public glsl_sampler_t{};

class glsl_usampler :public glsl_sampler_t{};


class glsl_sampler1D : public glsl_sampler
{
public:
    glsl_sampler1D(uint32 unit, const std::string& var_token) 
        : glsl_sampler(unit, "sampler1D", var_token) 
    {}

    glsl_sampler1D(const glsl_sampler1D&) = delete;
    glsl_sampler1D& operator=(const glsl_sampler1D&) = delete;

    ~glsl_sampler1D() = default;

public:

    void set_texture_1d(gl_texture_1d* texture) { set_texture(texture); }

    gl_texture_1d* get_texture_1d() const { return dynamic_cast<gl_texture_1d*>(get_texture()); }

};

class glsl_sampler1DArray : public glsl_sampler
{
public:
    glsl_sampler1DArray(uint32 unit, const std::string& var_token) 
        : glsl_sampler(unit, "sampler1DArray", var_token) 
    {}

    glsl_sampler1DArray(const glsl_sampler1DArray&) = delete;
    glsl_sampler1DArray& operator=(const glsl_sampler1DArray&) = delete;

    ~glsl_sampler1DArray() = default;

public:

    void set_texture_1d_array(gl_texture_1d_array* texture) { set_texture(texture); }

    gl_texture_1d_array* get_texture_1d_array() const { return dynamic_cast<gl_texture_1d_array*>(get_texture()); }

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

    void set_texture_2d(gl_texture_2d* texture) { set_texture(texture); }

    gl_texture_2d* get_texture_2d() const { return dynamic_cast<gl_texture_2d*>(get_texture()); }

};

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

    void set_texture_2d_array(gl_texture_2d_array* texture) { set_texture(texture); }

    gl_texture_2d_array* get_texture_2d_array() const { return dynamic_cast<gl_texture_2d_array*>(get_texture()); }

};

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

    void set_texture_2d_multisample(gl_texture_2d_multisample* texture) { set_texture(texture); }

    gl_texture_2d_multisample* get_texture_2d_multisample() const { return dynamic_cast<gl_texture_2d_multisample*>(get_texture()); }

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

    void set_texture_2d_multisample_array(gl_texture_2d_multisample_array* texture) { set_texture(texture); }

    gl_texture_2d_multisample_array* get_texture_2d_multisample_array() const { return dynamic_cast<gl_texture_2d_multisample_array*>(get_texture()); }

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

    void set_texture_cube(gl_texture_cube* texture) { set_texture(texture); }

    gl_texture_cube* get_texture_cube() const { return dynamic_cast<gl_texture_cube*>(get_texture()); }

};

class glsl_samplerCubeArray : public glsl_sampler_t {
public:
    glsl_samplerCubeArray(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "samplerCubeArray", var_token)
    {}

    glsl_samplerCubeArray(const glsl_samplerCubeArray&) = delete;
    glsl_samplerCubeArray& operator=(const glsl_samplerCubeArray&) = delete;

    ~glsl_samplerCubeArray();

public:

    void set_texture_cube_array(gl_texture_cube_array* texture) { set_texture(texture); }

    gl_texture_cube_array* get_texture_cube_array() const { return dynamic_cast<gl_texture_cube_array*>(get_texture()); }

};

class glsl_sampler2DRect : public glsl_sampler_t{
public:
    glsl_sampler2DRect(uint32 unit, const std::string& var_token)
        : glsl_sampler_t(unit, "sampler2DRect", var_token)
    {}

    glsl_sampler2DRect(const glsl_sampler2DRect&) = delete;
    glsl_sampler2DRect& operator=(const glsl_sampler2DRect&) = delete;

    ~glsl_sampler2DRect();

public:

    void set_texture_rectangle(gl_texture_rectangle* texture) { set_texture(texture); }

    gl_texture_rectangle* get_texture_rectangle() const { return dynamic_cast<gl_texture_rectangle*>(get_texture()); }

};

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

    void set_texture_3d(gl_texture_3d* texture) { set_texture(texture); }

    gl_texture_3d* get_texture_3d() const { return dynamic_cast<gl_texture_3d*>(get_texture()); }

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

    void set_texture_buffer(gl_texture_buffer* texture) { set_texture(texture); }

    gl_texture_buffer* get_texture_buffer() const { return dynamic_cast<gl_texture_buffer*>(get_texture()); }

};


class glsl_sampler1DShadow : public glsl_samplerShadow
{

};
class glsl_sampler1DArrayShadow : public glsl_samplerShadow
{

};
class glsl_sampler2DShadow : public glsl_samplerShadow
{};
class glsl_sampler2DArrayShadow : public glsl_samplerShadow
{};
class glsl_samplerCubeShadow : public glsl_samplerShadow
{};
class glsl_samplerCubeArrayShadow : public glsl_samplerShadow
{};
class glsl_sampler2DRectShadow : public glsl_samplerShadow
{};



class glsl_isampler1D : public glsl_isampler {};
class glsl_isampler1DArray : public glsl_isampler {};
class glsl_isampler2D : public glsl_isampler {};
class glsl_isampler2DArray : public glsl_isampler {};
class glsl_isampler2DRect : public glsl_isampler {};
class glsl_isampler2DMS : public glsl_isampler {};
class glsl_isampler2DMSArray : public glsl_isampler {};
class glsl_isamplerCube : public glsl_isampler {};
class glsl_isamplerCubeArray : public glsl_isampler {};
class glsl_isampler3D : public glsl_isampler {};
class glsl_isamplerBuffer : public glsl_isampler {};

class glsl_usampler1D : public glsl_usampler {};
class glsl_usampler1DArray : public glsl_usampler {};
class glsl_usampler2D : public glsl_usampler {};
class glsl_usampler2DArray : public glsl_usampler {};
class glsl_usampler2DRect : public glsl_usampler {};
class glsl_usampler2DMS : public glsl_usampler {};
class glsl_usampler2DMSArray : public glsl_usampler {};
class glsl_usamplerCube : public glsl_usampler {};
class glsl_usamplerCubeArray : public glsl_usampler {};
class glsl_usampler3D : public glsl_usampler {};
class glsl_usamplerBuffer : public glsl_usampler {};

#endif
