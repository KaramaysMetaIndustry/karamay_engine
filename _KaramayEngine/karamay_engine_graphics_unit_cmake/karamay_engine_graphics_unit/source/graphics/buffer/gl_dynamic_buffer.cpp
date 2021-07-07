//
// Created by Regicide Ji on 2021/7/1.
//

#include "gl_dynamic_buffer.h"

void gl_dynamic_buffer::reallocate(std::int32_t new_capacity, gl_dynamic_buffer_usage new_usage)
{
    if(!_check_capacity(new_capacity)) return;

    glNamedBufferData(_handle, new_capacity, nullptr, static_cast<GLenum>(new_usage));

    _capacity = new_capacity; _usage = new_usage;
    rapidly_fill();
}

void gl_dynamic_buffer::reallocate(std::int32_t new_capacity)
{
    if(!_check_capacity(new_capacity)) return;

    glNamedBufferData(_handle, new_capacity, nullptr, static_cast<GLenum>(_usage));

    _capacity = new_capacity;
    rapidly_fill();
}
