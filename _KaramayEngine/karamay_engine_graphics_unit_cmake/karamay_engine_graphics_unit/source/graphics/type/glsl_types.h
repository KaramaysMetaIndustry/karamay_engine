#ifndef H_GLSL_TYPES
#define H_GLSL_TYPES

#include "public/glm.h"

class glsl_clazz
{

};

class glsl_class {

protected:

    static std::unordered_map<std::string, const glsl_clazz*> _clazz_map;

};




class glsl_transparent_clazz : public glsl_clazz
{

public:
    virtual class glsl_transparent_class* create_instance(const std::vector<std::string>& params) const = 0;

public:
    const std::string type_name;
    const std::int64_t type_size;
    const std::string type_component_name;
    const std::int64_t type_component_size;
    const std::int32_t type_components_count;

    bool operator==(const glsl_transparent_clazz& other) const
    {
        return type_name == other.type_name;
    }

    bool operator!=(const glsl_transparent_clazz& other) const
    {
        return type_name != other.type_name;
    }
};

class glsl_transparent_class : public glsl_class
{
private:

    static std::unordered_map<std::string, const glsl_transparent_clazz*> _clazz_map;

public:

    static glsl_transparent_class* create(const std::string& class_name, const std::vector<std::string>& params)
    {
        auto _it = _clazz_map.find(class_name);
        if(_it != _clazz_map.cend())
        {
            const glsl_transparent_clazz* _clazz = _it->second;
            if(_clazz->type_components_count == params.size())
            {
                return _clazz->create_instance(params);
            }
        }
    }

    [[nodiscard]] virtual const glsl_transparent_clazz& clazz() const = 0;

    [[nodiscard]] virtual const std::uint8_t* data() const = 0;

};

class glsl_float : public glsl_transparent_class
{
public:
    using client_t = glm::vec1;

    explicit glsl_float(std::float_t scalar) :
        client_value(scalar)
    {}

    client_t client_value;

private:

    static const glsl_transparent_clazz _clazz;

public:

    [[nodiscard]] const glsl_transparent_clazz& clazz() const override {return _clazz; }

    [[nodiscard]] const std::uint8_t* data() const override {return reinterpret_cast<const std::uint8_t*>(&client_value);}

};


class glsl_vec2 : public glsl_transparent_class
{
public:
    using client_t = glm::vec2;

    explicit glsl_vec2(std::float_t x, std::float_t y) :
            client_value(x, y)
    {}

    client_t client_value;

public:

    [[nodiscard]] const glsl_transparent_clazz& clazz() const override {return _clazz; }

    [[nodiscard]] const std::uint8_t* data() const override {return reinterpret_cast<const std::uint8_t*>(&client_value);}

private:

    static const glsl_transparent_clazz _clazz;

};


class glsl_vec3 : public glsl_transparent_class
{
public:
    using client_t = glm::vec3;

    explicit glsl_vec3(std::float_t x, std::float_t y, std::float_t z) :
            client_value(x, y, z)
    {}

    client_t client_value;

public:

    [[nodiscard]] const glsl_transparent_clazz& clazz() const override {return _clazz; }

    [[nodiscard]] const std::uint8_t* data() const override {return reinterpret_cast<const std::uint8_t*>(&client_value);}

private:

    static const glsl_transparent_clazz _clazz;

};

const glsl_transparent_clazz glsl_vec3::_clazz = {};

class glsl_vec4 : public glsl_transparent_class
{
public:
    using client_t = glm::vec4;

    explicit glsl_vec4(std::float_t x, std::float_t y, std::float_t z, std::float_t w) :
            client_value(x, y, z, w)
    {}

    client_t client_value;

public:

    [[nodiscard]] const glsl_transparent_clazz& clazz() const override {return _clazz; }

    [[nodiscard]] const std::uint8_t* data() const override {return reinterpret_cast<const std::uint8_t*>(&client_value);}

private:

    static const glsl_transparent_clazz _clazz;

};

const glsl_transparent_clazz glsl_vec4::_clazz = {};





class glsl_int : public glsl_transparent_class
{
public:
    using client_t = glm::ivec1;

    explicit glsl_int(std::int32_t scalar) :
        client_value(scalar)
    {}

    client_t client_value;

public:

    [[nodiscard]] const glsl_transparent_clazz& meta() const override {return _meta;}

    [[nodiscard]] const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(&client_value); }

private:

    static const glsl_transparent_clazz _meta;

};

const glsl_transparent_clazz glsl_int::_meta
= {"int", sizeof(glm::vec1), "int", sizeof(glm::vec1::value_type), 1};


class glsl_ivec2 : public glsl_transparent_class
{
public:
    using client_t = glm::ivec2;

    glsl_ivec2(std::int32_t x, std::int32_t y) :
        client_value(x, y)
    {}

    client_t client_value;

    [[nodiscard]] const glsl_transparent_clazz& meta() const override {return _meta;}

    [[nodiscard]] const std::uint8_t* data() const override {return reinterpret_cast<const std::uint8_t*>(&client_value);}

private:

    static const glsl_transparent_clazz _meta;

};

const glsl_transparent_clazz glsl_ivec2::_meta
= {"ivec2", sizeof(glm::vec2), "int", sizeof(glm::vec2::value_type), 2};


class glsl_opaque_clazz : public glsl_clazz
{

};

class glsl_opaque_type : public glsl_class
{

};






//
//
//using glsl_bool = glm::bvec1;
//using glsl_bvec2 = glm::bvec2;
//using glsl_bvec3 = glm::bvec3;
//using glsl_bvec4 = glm::bvec4;
//
//using glsl_int = glm::ivec1;
//using glsl_ivec2 = glm::ivec2;
//using glsl_ivec3= glm::ivec3;
//using glsl_ivec4= glm::ivec4;
//
//using glsl_uint = glm::uvec1;
//using glsl_uvec2 = glm::uvec2;
//using glsl_uvec3 = glm::uvec3;
//using glsl_uvec4 = glm::uvec4;
//
//using glsl_float = glm::vec1;
//using glsl_vec2 = glm::vec2;
//using glsl_vec3 = glm::vec3;
//using glsl_vec4 = glm::vec4;
//
//using glsl_double = glm::dvec1;
//using glsl_dvec2 = glm::dvec2;
//using glsl_dvec3 = glm::dvec3;
//using glsl_dvec4 = glm::dvec4;
//
//using glsl_mat2 = glm::mat2;
//using glsl_mat2x3 = glm::mat2x3;
//using glsl_mat2x4 = glm::mat2x4;
//using glsl_mat3 = glm::mat3;
//using glsl_mat3x2 = glm::mat3x2;
//using glsl_mat3x4 = glm::mat3x4;
//using glsl_mat4 = glm::mat4;
//using glsl_mat4x2 = glm::mat4x2;
//using glsl_mat4x3 = glm::mat4x3;
//
//using glsl_dmat2 = glm::dmat2;
//using glsl_dmat2x3 = glm::dmat2x3;
//using glsl_dmat2x4 = glm::dmat2x4;
//using glsl_dmat3 = glm::dmat3;
//using glsl_dmat3x2 = glm::dmat3x2;
//using glsl_dmat3x4 = glm::dmat3x4;
//using glsl_dmat4 = glm::dmat4;
//using glsl_dmat4x2 = glm::dmat4x2;
//using glsl_dmat4x3 = glm::dmat4x3;
//
//
//
//
//
//
//// TEXTURE_1D
//using glsl_sampler1D = glm::uvec1;
//using glsl_sampler1DArray = glm::uvec1;
//using glsl_sampler1DShadow = glm::uvec1;
//using glsl_sampler1DArrayShadow = glm::uvec1;
//using glsl_isampler1D = glm::uvec1;
//using glsl_isampler1DArray = glm::uvec1;
//using glsl_usampler1D = glm::uvec1;
//using glsl_usampler1DArray = glm::uvec1;
//
//// TEXTURE_2D
//using glsl_sampler2D = glm::uvec1;
//using glsl_sampler2DArray = glm::uvec1;
//using glsl_sampler2DMS = glm::uvec1;
//using glsl_sampler2DMSArray = glm::uvec1;
//using glsl_sampler2DShadow = glm::uvec1;
//using glsl_sampler2DArrayShadow = glm::uvec1;
//using glsl_isampler2D = glm::uvec1;
//using glsl_isampler2DArray = glm::uvec1;
//using glsl_isampler2DMS = glm::uvec1;
//using glsl_isampler2DMSArray = glm::uvec1;
//using glsl_usampler2D = glm::uvec1;
//using glsl_usampler2DArray = glm::uvec1;
//using glsl_usampler2DMS = glm::uvec1;
//using glsl_usampler2DMSArray = glm::uvec1;
//
//// TEXTURE_RECT
//using glsl_sampler2DRect = glm::uvec1;
//using glsl_sampler2DRectShadow = glm::uvec1;
//using glsl_isampler2DRect = glm::uvec1;
//using glsl_usampler2DRect = glm::uvec1;
//
//// TEXTURE_3D
//using glsl_sampler3D = glm::uvec1;
//using glsl_isampler3D = glm::uvec1;
//using glsl_usampler3D = glm::uvec1;
//
//// TEXTURE_CUBE
//using glsl_samplerCube = glm::uvec1;
//using glsl_samplerCubeArray = glm::uvec1;
//using glsl_samplerCubeShadow = glm::uvec1;
//using glsl_samplerCubeArrayShadow = glm::uvec1;
//using glsl_isamplerCube = glm::uvec1;
//using glsl_isamplerCubeArray = glm::uvec1;
//using glsl_usamplerCube = glm::uvec1;
//using glsl_usamplerCubeArray = glm::uvec1;
//
//// TEXTURE_BUFFER
//using glsl_samplerBuffer = glm::uvec1;
//using glsl_isamplerBuffer = glm::uvec1;
//using glsl_usamplerBuffer = glm::uvec1;
//
//// IMAGE_1D
//using glsl_image1D = glm::uvec1;
//using glsl_image1DArray = glm::uvec1;
//using glsl_iimage1D = glm::uvec1;
//using glsl_iimage1DArray = glm::uvec1;
//using glsl_uimage1D = glm::uvec1;
//using glsl_uimage1DArray = glm::uvec1;
//
//// IMAGE_2D
//using glsl_image2D = glm::uvec1;
//using glsl_image2DDArray = glm::uvec1;
//using glsl_image2DMS = glm::uvec1;
//using glsl_image2DMSArray = glm::uvec1;
//using glsl_iimage2D = glm::uvec1;
//using glsl_iimage2DDArray = glm::uvec1;
//using glsl_uimage2DMS = glm::uvec1;
//using glsl_uimage2DMSArray = glm::uvec1;
//
//// IMAGE_RECT
//using glsl_image2DRect = glm::uvec1;
//using glsl_iimage2DRect = glm::uvec1;
//using glsl_uimage2DRect = glm::uvec1;
//
//// IMAGE_3D
//using glsl_image3D = glm::uvec1;
//using glsl_iimage3D = glm::uvec1;
//using glsl_uimage3D = glm::uvec1;
//
//// IMAGE_CUBE
//using glsl_imageCube = glm::uvec1;
//using glsl_imageCubeArray = glm::uvec1;
//using glsl_iimageCube = glm::uvec1;
//using glsl_iimageCubeArray = glm::uvec1;
//using glsl_uimageCube = glm::uvec1;
//using glsl_uimageCubeArray = glm::uvec1;
//
//// IMAGE_BUFFER
//using glsl_imageBuffer = glm::uvec1;
//using glsl_iimageBuffer = glm::uvec1;
//using glsl_uimageBuffer = glm::uvec1;


enum class glsl_type_enum
{
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    MAT2,
    MAT2X3,
    MAT2X4,
    MAT3,
    MAT3X2,
    MAT3X4,
    MAT4,
    MAT4X2,
    MAT4X3,
    DOUBLE,
    DVEC2,
    DVEC3,
    DVEC4,
    DMAT2,
    DMAT2X3,
    DMAT2X4,
    DMAT3,
    DMAT3X2,
    DMAT3X4,
    DMAT4,
    DMAT4X2,
    DMAT4X3,
    INT,
    IVEC2,
    IVEC3,
    IVEC4,
    UINT,
    UVEC2,
    UVEC3,
    UVEC4
};

int64_t get_glsl_type_size(glsl_type_enum type)
{
    switch (type) {
        case glsl_type_enum::FLOAT: return sizeof(glm::vec1);
        case glsl_type_enum::VEC2: return sizeof(glm::vec2);
        case glsl_type_enum::VEC3: return sizeof(glm::vec3);
        case glsl_type_enum::VEC4: return sizeof(glm::vec4);
        case glsl_type_enum::MAT2: return sizeof(glm::mat2);
        case glsl_type_enum::MAT2X3: return sizeof(glm::mat2x3);
        case glsl_type_enum::MAT2X4: return sizeof(glm::mat2x4);
        case glsl_type_enum::MAT3: return sizeof(glm::mat3);
        case glsl_type_enum::MAT3X2: return sizeof(glm::mat3x2);
        case glsl_type_enum::MAT3X4: return sizeof(glm::mat3x4);
        case glsl_type_enum::MAT4: return sizeof(glm::mat4);
        case glsl_type_enum::MAT4X2: return sizeof(glm::mat4x2);
        case glsl_type_enum::MAT4X3: return sizeof(glm::mat4x3);
        case glsl_type_enum::DOUBLE: return sizeof(glm::dvec1);
        case glsl_type_enum::DVEC2: return sizeof(glm::dvec2);
        case glsl_type_enum::DVEC3: return sizeof(glm::dvec3);
        case glsl_type_enum::DVEC4: return sizeof(glm::dvec4);
        case glsl_type_enum::DMAT2: return sizeof(glm::dmat2);
        case glsl_type_enum::DMAT2X3: return sizeof(glm::dmat2x3);
        case glsl_type_enum::DMAT2X4: return sizeof(glm::dmat2x4);
        case glsl_type_enum::DMAT3: return sizeof(glm::dmat3);
        case glsl_type_enum::DMAT3X2: return sizeof(glm::dmat3x2);
        case glsl_type_enum::DMAT3X4: return sizeof(glm::dmat3x4);
        case glsl_type_enum::DMAT4: return sizeof(glm::dmat4);
        case glsl_type_enum::DMAT4X2: return sizeof(glm::dmat4x2);
        case glsl_type_enum::DMAT4X3: return sizeof(glm::dmat4x3);
        case glsl_type_enum::INT: return sizeof(glm::ivec1);
        case glsl_type_enum::IVEC2: return sizeof(glm::ivec2);
        case glsl_type_enum::IVEC3: return sizeof(glm::ivec3);
        case glsl_type_enum::IVEC4: return sizeof(glm::ivec4);
        case glsl_type_enum::UINT: return sizeof(glm::uvec1);
        case glsl_type_enum::UVEC2: return sizeof(glm::uvec2);
        case glsl_type_enum::UVEC3: return sizeof(glm::uvec3);
        case glsl_type_enum::UVEC4: return sizeof(glm::uvec4);
    }
}

enum class glsl_basic_component_type
{
    FLOAT,
    DOUBLE,
    UINT,
    INT,
};

enum class glsl_basic_attribute_type
{
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    DOUBLE,
    DVEC2,
    DVEC3,
    DVEC4,

    INT,
    IVEC2,
    IVEC3,
    IVEC4,
    UINT,
    UVEC2,
    UVEC3,
    UVEC4
};

#endif
