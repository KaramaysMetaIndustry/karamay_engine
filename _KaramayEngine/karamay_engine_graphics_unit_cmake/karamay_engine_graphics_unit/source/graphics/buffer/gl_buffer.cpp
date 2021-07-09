#include "gl_buffer.h"

const std::int64_t gl_buffer::THEORETICAL_MAX_CAPACITY = INT64_MAX;
const std::int64_t gl_buffer::GPU_MAX_CAPACITY = 0;
const std::int64_t gl_buffer::HARDWARE_MAX_CAPACITY = 0;
const std::int64_t gl_buffer::BUFFER_AVAILABLE_MAX_CAPACITY = INT32_MAX;

void gl_buffer::overwrite(std::int64_t offset, const std::uint8_t* data, std::int64_t data_size)
{
    if(!_storage_options.is_dynamic_storage || !data || offset < 0 || data_size < 0 || offset + data_size > _capacity) return; // dangerous: data_size out of data point to

    glNamedBufferSubData(_handle, offset, data_size, reinterpret_cast<const void*>(data));
    // because glNamedBufferSubData operation is read-only to data
}

void gl_buffer::invalidate(std::int64_t offset, std::int64_t size)
{
    glInvalidateBufferSubData(_handle, offset, size);
}

void gl_buffer::output_data_to_buffer(gl_buffer& target_buffer)
{
    if(target_buffer.get_capacity() == _capacity)
    {
        glCopyNamedBufferSubData(_handle, target_buffer.get_handle(), 0, 0, _capacity);
    }
}

void gl_buffer::output_data_to_buffer(std::int64_t self_offset, int64_t output_size, gl_buffer& target, std::int64_t target_offset)
{
    if(self_offset + output_size <= _capacity
        && target_offset + output_size <= target.get_capacity())
    {
        glCopyNamedBufferSubData(_handle, target.get_handle(), self_offset, target_offset, output_size);
    }

}

void gl_buffer::overwrite_by_byte(std::int64_t offset, std::int64_t size)
{
    std::uint8_t unit = 0;
    glClearNamedBufferSubData(_handle, GL_R8UI, offset, size, GL_RED, GL_UNSIGNED_BYTE, &unit);
}

void gl_buffer::execute_immutable_memory_handler(std::int64_t offset, std::int64_t size, const std::function<void(const std::uint8_t*, std::int64_t)>& handler)
{
    if(offset < 0 || size < 0 || offset + size > _size) return;

    const auto* _mapped_memory_block = reinterpret_cast<const std::uint8_t*>(
            glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_READ_BIT))
    );

    if(_mapped_memory_block) handler(_mapped_memory_block, size);

    glUnmapNamedBuffer(_handle);
}

void gl_buffer::execute_mutable_memory_handler(std::int64_t offset, std::int64_t size, const std::function<void(std::uint8_t*, std::int64_t)>& handler)
{
    if(offset + size > _size) return;

    auto* _mapped_memory_block = reinterpret_cast<std::uint8_t*>(
            glMapNamedBufferRange(_handle, offset, size, GL_MAP_WRITE_BIT)
    );

    if(_mapped_memory_block)
    {
        handler(_mapped_memory_block, size);
        glFlushMappedNamedBufferRange(_handle, offset, size);
        //glMemoryBarrier();
    } // make sure modification pushed to GPU

    glUnmapNamedBuffer(_handle);
}

void gl_buffer::_reallocate(std::int64_t new_capacity)
{
    std::cout<<"call the _reallocate"<<std::endl;
    if(!_check_capacity(new_capacity)) return;

    std::uint32_t new_handle = 0;
    glCreateBuffers(1, &new_handle);
    if(new_handle != 0)
    {
        glNamedBufferStorage(new_handle, new_capacity, nullptr, _storage_flags);
        glCopyNamedBufferSubData(_handle,new_handle, 0, 0, _size);
        glDeleteBuffers(1, &_handle);

        _handle = new_handle; _capacity = new_capacity;
    }
}

void gl_buffer::reserve(std::int64_t capacity)
{
    if(capacity >= 0 && capacity > _capacity - _size) _reallocate(_size + capacity);
}

void gl_buffer::shrink_to_fit()
{
    std::cout<<"size: "<< _size << std::endl;
    std::cout<<"capacity: "<<_capacity<<std::endl;
    if(_size < _capacity)
    {
        _reallocate(_size);
    }
}


