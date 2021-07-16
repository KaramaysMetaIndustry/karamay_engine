#ifndef H_GLSL_TRANSPARENT_CLASS
#define H_GLSL_TRANSPARENT_CLASS

#include "graphics/type/glsl_class/glsl_class.h"


class glsl_transparent_clazz : public glsl_clazz
{

public:

    [[nodiscard]] virtual class glsl_transparent_class* construct(const std::vector<std::string>& params) const = 0;

public:

    const std::string class_name;

    const std::uint16_t class_size;

    const std::string class_component_name;

    const std::uint16_t class_component_size;

    const std::uint8_t class_component_count;

};

class glsl_float_clazz : public glsl_transparent_clazz
{
public:
    [[nodiscard]] class glsl_transparent_class* construct(const std::vector<std::string>& params) const override;
};
class glsl_vec2_clazz : public glsl_transparent_clazz
{
public:
    [[nodiscard]] class glsl_transparent_class* construct(const std::vector<std::string>& params) const override;
};
class glsl_vec3_clazz : public glsl_transparent_clazz
{
public:
    [[nodiscard]] class glsl_transparent_class* construct(const std::vector<std::string>& params) const override;
};

class glsl_vec4_clazz : public glsl_transparent_clazz
{
public:
    [[nodiscard]] class glsl_transparent_class* construct(const std::vector<std::string>& params) const override;
};

class glsl_double_clazz : public glsl_transparent_clazz
{};
class glsl_dvec2_clazz : public glsl_transparent_clazz
{};
class glsl_dvec3_clazz : public glsl_transparent_clazz
{};
class glsl_dvec4_clazz : public glsl_transparent_clazz
{};

class glsl_int_clazz : public glsl_transparent_clazz
{};
class glsl_ivec2_clazz : public glsl_transparent_clazz
{};
class glsl_ivec3_clazz : public glsl_transparent_clazz
{};
class glsl_ivec4_clazz : public glsl_transparent_clazz
{};

class glsl_uint_clazz : public glsl_transparent_clazz
{};
class glsl_uvec2_clazz : public glsl_transparent_clazz
{};
class glsl_uvec3_clazz : public glsl_transparent_clazz
{};
class glsl_uvec4_clazz : public glsl_transparent_clazz
{};


class glsl_transparent_class : public glsl_class
{
private:

    static std::unordered_map<std::string, const class glsl_transparent_clazz*> _clazz_map;

public:

    [[nodiscard]] virtual const glsl_transparent_clazz* clazz() const = 0;

    [[nodiscard]] virtual const std::uint8_t* stream() const = 0;

};

class glsl_float : public glsl_transparent_class
{
private:

    static const class glsl_float_clazz* _clazz;

public:

    [[nodiscard]] const glsl_transparent_clazz* clazz() const override { return _clazz; }

    [[nodiscard]] const std::uint8_t* stream() const override { return reinterpret_cast<const std::uint8_t*>(&client_value); }

public:

    explicit glsl_float(std::float_t scalar) :
            client_value(scalar)
    {}

    glm::vec1 client_value;

};
class glsl_vec2 : public glsl_transparent_class
{
private:

    static const class glsl_vec2_clazz* _clazz;

public:

    [[nodiscard]] const glsl_transparent_clazz* clazz() const override { return _clazz; }

    [[nodiscard]] const std::uint8_t* stream() const override { return reinterpret_cast<const std::uint8_t*>(&client_value); }

public:

    explicit glsl_vec2(std::float_t x, std::float_t y) :
            client_value(x, y)
    {}

    glm::vec2 client_value;

};
class glsl_vec3 : public glsl_transparent_class
{

private:

    static const class glsl_vec3_clazz* _clazz;

public:

    [[nodiscard]] const glsl_transparent_clazz* clazz() const override { return _clazz; }

    [[nodiscard]] const std::uint8_t* stream() const override { return reinterpret_cast<const std::uint8_t*>(&client_value); }

public:

    explicit glsl_vec3(std::float_t x, std::float_t y, std::float_t z) :
            client_value(x, y, z)
    {}

    glm::vec3 client_value;

};
class glsl_vec4 : public glsl_transparent_class
{
private:

    static const class glsl_vec4_clazz* _clazz;

public:

    [[nodiscard]] const glsl_transparent_clazz* clazz() const override { return _clazz; }

    [[nodiscard]] const std::uint8_t* stream() const override { return reinterpret_cast<const std::uint8_t*>(&client_value); }

public:
    explicit glsl_vec4(std::float_t x, std::float_t y, std::float_t z, std::float_t w) :
            client_value(x, y, z, w)
    {}

    glm::vec4 client_value;

};







#endif
