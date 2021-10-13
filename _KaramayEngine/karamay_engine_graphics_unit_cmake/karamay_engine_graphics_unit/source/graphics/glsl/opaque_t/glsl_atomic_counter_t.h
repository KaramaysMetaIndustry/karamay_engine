#ifndef GLSL_ATOMIC_COUNTER_T_H
#define GLSL_ATOMIC_COUNTER_T_H

#include "graphics/glsl/glsl_class.h"

/*
 *
 *
 * */
class glsl_atomic_counter : public glsl_opaque_t{
public:
    glsl_atomic_counter() = default;
    glsl_atomic_counter(std::uint32_t value) {}
    ~glsl_atomic_counter() = default;

private:

    std::uint32_t value;

};


#endif
