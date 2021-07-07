#include "gl_buffer_base.h"

const std::int32_t  gl_buffer_base::MAX_CAPACITY = INT32_MAX;

void gl_buffer_base::fill(std::int32_t offset, const std::uint8_t *data, std::int32_t data_size)
{
    if(!data || offset < 0 || data_size < 0 || (offset + data_size > _capacity)) return;

    glNamedBufferSubData(_handle, offset, data_size, reinterpret_cast<const void*>(data));
    // ** data_size > data real size, it will not case exception
    // because glNamedBufferSubData operation is read-only to data
}

void gl_buffer_base::invalidate(std::int32_t offset, std::int32_t size)
{
    glInvalidateBufferSubData(_handle, offset, size);
}

void gl_buffer_base::output_data(gl_buffer_base *target_buffer)
{
    if(target_buffer && target_buffer->get_capacity() == _capacity)
    {
        glCopyNamedBufferSubData(_handle, target_buffer->get_handle(), 0, 0, _capacity);
    }
}

void gl_buffer_base::output_data(std::int32_t self_offset, int32_t output_size, gl_buffer_base *target_buffer, std::int32_t target_buffer_offset)
{
    if(target_buffer
        && self_offset + output_size <= _capacity
        && target_buffer_offset + output_size <= target_buffer->get_capacity())
    {
        glCopyNamedBufferSubData(_handle, target_buffer->get_handle(), self_offset, target_buffer_offset, output_size);
    }

}

void gl_buffer_base::rapidly_fill(std::uint8_t data_mask)
{
    glClearNamedBufferData(_handle, GL_R8UI, GL_RED, GL_UNSIGNED_BYTE, &data_mask);
}

void gl_buffer_base::execute_immutable_memory_handler(std::int32_t offset, std::int32_t size, const std::function<void(const std::uint8_t *, std::int32_t)> &handler)
{
    if(offset < 0 || size < 0 || offset + size > _capacity) return;

    const auto* _mapped_memory_block = reinterpret_cast<const std::uint8_t*>(
            glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_READ_BIT))
    );

    if(_mapped_memory_block) handler(_mapped_memory_block, size);

    glUnmapNamedBuffer(_handle);
}

void gl_buffer_base::execute_mutable_memory_handler(std::int32_t offset, std::int32_t size, const std::function<void(std::uint8_t *, std::int32_t)> &handler)
{
    if(offset + size > _capacity) return;

    auto* _mapped_memory_block = reinterpret_cast<std::uint8_t*>(
            glMapNamedBufferRange(_handle, offset, size, GL_MAP_WRITE_BIT)
    );

    if(_mapped_memory_block)
    {
        handler(_mapped_memory_block, size);
        glFlushMappedNamedBufferRange(_handle, offset, size);
    } // make sure modification pushed to GPU

    glUnmapNamedBuffer(_handle);
}


