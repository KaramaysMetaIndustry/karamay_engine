#include "glsl_transparent_class.h"


class glsl_transparent_class *glsl_vec3_clazz::construct(const std::vector<std::string> &params) const {
    if(params.size() == 3)
    {
        std::float_t value0, value1, value2;
        std::istringstream(params[0]) >> value0;
        std::istringstream(params[1]) >> value1;
        std::istringstream(params[2]) >> value2;
        return new glsl_vec3(value0, value1, value2);
    }
}

class glsl_transparent_class *glsl_float_clazz::construct(const std::vector<std::string> &params) const {
    if(params.size() == 1)
    {
        std::float_t value = 0;
        std::istringstream(params[0]) >> value;
        return new glsl_float(value);
    }
}

class glsl_transparent_class *glsl_vec2_clazz::construct(const std::vector<std::string> &params) const {
    if(params.size() == 2)
    {
        std::float_t value0, value1;
        std::istringstream(params[0]) >> value0;
        std::istringstream(params[1]) >> value1;
        return new glsl_vec2(value0, value1);
    }
}

class glsl_transparent_class *glsl_vec4_clazz::construct(const std::vector<std::string> &params) const {
    if(params.size() == 1)
    {
        std::float_t value0, value1, value2, value3;
        std::istringstream(params[0]) >> value0;
        std::istringstream(params[1]) >> value1;
        std::istringstream(params[2]) >> value2;
        std::istringstream(params[3]) >> value3;
        return new glsl_vec4(value0, value1, value2, value3);
    }
}
