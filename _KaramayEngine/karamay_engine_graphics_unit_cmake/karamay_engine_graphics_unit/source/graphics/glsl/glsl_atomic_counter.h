#ifndef GLSL_ATOMIC_COUNTER_H
#define GLSL_ATOMIC_COUNTER_H

#include "glsl_class.h"

/*
 * [opaque type]
 * exp : layout(binding=0, offset=4) uniform atomic_uint counter_one;
 * pipeline only manage one atomic_counter_buffer for all registered counters
 * */
class glsl_atomic_counter_t : public glsl_opaque_t{
public:

    glsl_atomic_counter_t() = delete;
    explicit glsl_atomic_counter_t(std::uint32_t value) : dirty(false), _value(value){}
    glsl_atomic_counter_t(const glsl_atomic_counter_t&) = delete;
    glsl_atomic_counter_t& operator=(const glsl_atomic_counter_t&) = delete;

    ~glsl_atomic_counter_t() = default;

public:

    bool dirty;

    void set(std::uint32_t value)
    {
        _value = value;
        dirty = true;
    }

    [[nodiscard]] std::uint32_t get() const noexcept
    {
        return _value;
    }

public:

    [[nodiscard]] const std::string& token() const override
    {
        //_token.append("layout(binding={0}, offset={1}) uniform atomic_uint {2};",);
    }

private:

    std::uint32_t _value;

};


#endif
