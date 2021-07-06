//
// Created by jichengcheng on 2021/7/1.
//

#include "gl_buffer_base.h"

const std::int32_t  gl_buffer_base::MAX_CAPACITY = INT32_MAX;

void gl_buffer_base::clear()
{
    std::uint8_t _value = 0;
    glClearNamedBufferData(_handle, GL_R8UI, GL_RED, GL_UNSIGNED_BYTE, &_value);
}

void gl_buffer_base::fill(std::int32_t offset, const std::uint8_t *data, std::int32_t data_size)
{
    if(!data || offset < 0 || data_size < 0 || (offset + data_size > _capacity)) return;

    glNamedBufferSubData(_handle, offset, data_size, reinterpret_cast<const void*>(data));
    // ** data_size > data real size, it will not case exception
    // because glNamedBufferSubData operation is read-only to data
}
