#ifndef GLSL_ATOMIC_COUNTER_H
#define GLSL_ATOMIC_COUNTER_H

#include "../base/glsl_class.h"

/*
 * [opaque type]
 * exp : layout(binding=0, offset=4) uniform atomic_uint counter_one;
 * pipeline only manage one atomic_counter_buffer for all registered counters
 * */
class glsl_atomic_counter : public glsl_opaque_t
{
public:

    glsl_atomic_counter() = delete;
    explicit glsl_atomic_counter(std::uint32_t value) : dirty(false), _value(value){}
    glsl_atomic_counter(const glsl_atomic_counter&) = delete;
    glsl_atomic_counter& operator=(const glsl_atomic_counter&) = delete;

    ~glsl_atomic_counter() = default;

public:

    bool dirty;

    std::uint8_t* data()
    {
        return reinterpret_cast<std::uint8_t*>(&_value);
    }

    const std::uint8_t* data() const
    {
        return reinterpret_cast<const std::uint8_t*>(&_value);
    }

public:


private:

    std::uint32_t _value;

};


#endif
