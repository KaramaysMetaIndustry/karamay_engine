//
// Created by jichengcheng on 2021/7/1.
//

#ifndef KARAMAY_ENGINE_GRAPHICS_UNIT_GL_BUFFER_BASE_H
#define KARAMAY_ENGINE_GRAPHICS_UNIT_GL_BUFFER_BASE_H

#include "graphics/glo/gl_object.h"

class gl_buffer_base : public gl_object{

public:

    const static std::int32_t max_capacity;

public:

    std::int32_t get_capacity() const {return _capacity;}

    void clear()
    {
        std::uint32_t _value = 1;
        glClearNamedBufferData(_handle, GL_R32UI, GL_RED, GL_UNSIGNED_INT, &_value);
    }

protected:

    std::int32_t _capacity;

protected:

    [[nodiscard]] bool _check_capacity(std::int32_t capacity) const
    {
        return capacity != _capacity && capacity < max_capacity;
    }

};



#endif
