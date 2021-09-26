#ifndef GLSL_ATOMIC_COUNTER_T_H
#define GLSL_ATOMIC_COUNTER_T_H

#include "graphics/glsl/glsl_class.h"

/*
 *
 *
 * */
class glsl_atomic_uint : public glsl_opaque_t{
public:
    glsl_atomic_uint() = default;
    glsl_atomic_uint(std::uint32_t value) {}
    ~glsl_atomic_uint() = default;

private:

    std::uint32_t value;

};


#endif
