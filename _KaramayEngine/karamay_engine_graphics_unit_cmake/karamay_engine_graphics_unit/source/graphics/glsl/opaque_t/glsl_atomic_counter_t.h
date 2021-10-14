#ifndef GLSL_ATOMIC_COUNTER_T_H
#define GLSL_ATOMIC_COUNTER_T_H

#include "graphics/glsl/glsl_class.h"

/*
 *
 *
 * */
class glsl_atomic_counter_t : public glsl_opaque_t{
public:
    glsl_atomic_counter_t() = default;
    ~glsl_atomic_counter_t() = default;

public:

    std::uint32_t data;

};


#endif
