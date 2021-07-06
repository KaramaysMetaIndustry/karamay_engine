#include "gl_buffer_base.h"

const std::int32_t  gl_buffer_base::MAX_CAPACITY = INT32_MAX;

void gl_buffer_base::fill(std::int32_t offset, const std::uint8_t *data, std::int32_t data_size)
{
    if(!data || offset < 0 || data_size < 0 || (offset + data_size > _capacity)) return;

    glNamedBufferSubData(_handle, offset, data_size, reinterpret_cast<const void*>(data));
    // ** data_size > data real size, it will not case exception
    // because glNamedBufferSubData operation is read-only to data
}

void gl_buffer_base::transfer_data_to(gl_buffer_base *target_buffer)
{
    if(target_buffer && target_buffer->get_capacity() == _capacity)
    {
        glCopyNamedBufferSubData(target_buffer->get_handle(), _handle, 0, 0, _capacity);
    }
}

void gl_buffer_base::transfer_data(std::int32_t self_offset, int32_t self_size, gl_buffer_base *target_buffer, std::int32_t target_buffer_offset)
{
    if(target_buffer
        && self_offset + self_size <= _capacity
        && target_buffer_offset + self_size <= target_buffer->get_capacity())
    {
        glCopyNamedBufferSubData(target_buffer->get_handle(), _handle, self_offset, target_buffer_offset, self_size);
    }

}

void gl_buffer_base::clear()
{
    std::uint8_t _value = 0;
    glClearNamedBufferData(_handle, GL_R8UI, GL_RED, GL_UNSIGNED_BYTE, &_value);
}
