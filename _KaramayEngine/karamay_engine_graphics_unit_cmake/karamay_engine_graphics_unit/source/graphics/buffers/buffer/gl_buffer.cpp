#include "gl_buffer.h"

const std::int64_t gl_buffer::THEORETICAL_MAX_CAPACITY = INT64_MAX;
const std::int64_t gl_buffer::GPU_MAX_CAPACITY = 0;
const std::int64_t gl_buffer::HARDWARE_MAX_CAPACITY = 0;
const std::int64_t gl_buffer::BUFFER_AVAILABLE_MAX_CAPACITY = INT32_MAX;

void gl_buffer::overwrite_by_byte(std::int64_t offset, std::int64_t size)
{
    std::uint8_t unit = 0;
    glClearNamedBufferSubData(_handle, GL_R8UI, offset, size, GL_RED, GL_UNSIGNED_BYTE, &unit);
}

void gl_buffer::_reallocate(std::int64_t new_capacity)
{
    //if(!_check_capacity(new_capacity)) return;

    //std::uint32_t new_handle = 0;
    //glCreateBuffers(1, &new_handle);
    //if(new_handle != 0)
    //{
    //    glNamedBufferStorage(new_handle, new_capacity, nullptr, _storage_flags);
    //    //glCopyNamedBufferSubData(_handle,new_handle, 0, 0, _size);
    //    glDeleteBuffers(1, &_handle);

    //    _handle = new_handle; _capacity = new_capacity;
    //}
}