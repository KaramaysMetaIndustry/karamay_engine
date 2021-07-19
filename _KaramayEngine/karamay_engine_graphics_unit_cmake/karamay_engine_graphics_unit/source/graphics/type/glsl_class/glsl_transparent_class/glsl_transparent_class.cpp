#include "glsl_transparent_class.h"


class glsl_transparent_class *glsl_float_clazz::construct(const std::vector<std::string> &params) const {
    if(params.size() == 1)
    {
        std::float_t value = 0;
        std::istringstream(params[0]) >> value;
        return new glsl_float(glm::vec1(value));
    }
    return nullptr;
}
class glsl_transparent_class *glsl_vec2_clazz::construct(const std::vector<std::string> &params) const {
    if(params.size() == 2)
    {
        std::float_t value0, value1;
        std::istringstream(params[0]) >> value0;
        std::istringstream(params[1]) >> value1;
        return new glsl_vec2(glm::vec2(value0, value1));
    }
    return nullptr;
}
class glsl_transparent_class *glsl_vec3_clazz::construct(const std::vector<std::string> &params) const {
    if(params.size() == 3)
    {
        std::float_t value0, value1, value2;
        std::istringstream(params[0]) >> value0;
        std::istringstream(params[1]) >> value1;
        std::istringstream(params[2]) >> value2;
        return new glsl_vec3(glm::vec3(value0, value1, value2));
    }
    return nullptr;
}
class glsl_transparent_class *glsl_vec4_clazz::construct(const std::vector<std::string> &params) const {
    if(params.size() == 4)
    {
        std::float_t value0, value1, value2, value3;
        std::istringstream(params[0]) >> value0;
        std::istringstream(params[1]) >> value1;
        std::istringstream(params[2]) >> value2;
        std::istringstream(params[3]) >> value3;
        return new glsl_vec4(glm::vec4(value0, value1, value2, value3));
    }
    return nullptr;
}

class glsl_transparent_class *glsl_mat2_clazz::construct(const std::vector<std::string> &params) const{ return nullptr; }
class glsl_transparent_class *glsl_mat2x3_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_mat2x4_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_mat3_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_mat3x2_clazz::construct(const std::vector<std::string> &params) const{ return nullptr; }
class glsl_transparent_class *glsl_mat3x4_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_mat4_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_mat4x2_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_mat4x3_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}

class glsl_transparent_class *glsl_double_clazz::construct(const std::vector<std::string> &params) const{ return nullptr; }
class glsl_transparent_class *glsl_dvec2_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_dvec3_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_dvec4_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}

class glsl_transparent_class *glsl_dmat2_clazz::construct(const std::vector<std::string> &params) const{ return nullptr; }
class glsl_transparent_class *glsl_dmat2x3_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_dmat2x4_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_dmat3_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_dmat3x2_clazz::construct(const std::vector<std::string> &params) const{ return nullptr; }
class glsl_transparent_class *glsl_dmat3x4_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_dmat4_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_dmat4x2_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_dmat4x3_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}

class glsl_transparent_class *glsl_int_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_ivec2_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_ivec3_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_ivec4_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}

class glsl_transparent_class *glsl_uint_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_uvec2_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_uvec3_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}
class glsl_transparent_class *glsl_uvec4_clazz::construct(const std::vector<std::string> &params) const {return nullptr;}