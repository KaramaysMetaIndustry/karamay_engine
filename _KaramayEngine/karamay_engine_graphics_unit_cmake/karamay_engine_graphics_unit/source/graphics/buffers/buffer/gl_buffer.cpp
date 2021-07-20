#include "gl_buffer.h"

const std::int64_t gl_buffer::THEORETICAL_MAX_CAPACITY = INT64_MAX;
const std::int64_t gl_buffer::GPU_MAX_CAPACITY = 0;
const std::int64_t gl_buffer::HARDWARE_MAX_CAPACITY = 0;
const std::int64_t gl_buffer::BUFFER_AVAILABLE_MAX_CAPACITY = INT32_MAX;

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
    if(offset < 0 || size < 0 || offset + size > _capacity) return;

    const auto* _mapped_memory = reinterpret_cast<const std::uint8_t*>(
            glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_READ_BIT))
    );

    if(_mapped_memory) handler(_mapped_memory, size);

    glUnmapNamedBuffer(_handle);
}

void gl_buffer::execute_mutable_memory_handler(std::int64_t offset, std::int64_t size, const std::function<void(std::uint8_t*, std::int64_t)>& handler)
{
    if(offset + size > _capacity) return;

    auto* _mapped_memory = reinterpret_cast<std::uint8_t*>(
            glMapNamedBufferRange(_handle, offset, size, GL_MAP_WRITE_BIT)
    );

    if(_mapped_memory)
    {
        handler(_mapped_memory, size);
        glFlushMappedNamedBufferRange(_handle, offset, size);
        //glMemoryBarrier();
    } // make sure modification pushed to GPU

    glUnmapNamedBuffer(_handle);
}

void gl_buffer::_reallocate(std::int64_t new_capacity)
{
    if(!_check_capacity(new_capacity)) return;

    std::uint32_t new_handle = 0;
    glCreateBuffers(1, &new_handle);
    if(new_handle != 0)
    {
        glNamedBufferStorage(new_handle, new_capacity, nullptr, _storage_flags);
        //glCopyNamedBufferSubData(_handle,new_handle, 0, 0, _size);
        glDeleteBuffers(1, &_handle);

        _handle = new_handle; _capacity = new_capacity;
    }
}

void gl_buffer::reallocate(std::int64_t capacity, gl_buffer_storage_options storage_options)
{
    // search the suitable buffers
    auto _it = std::find_if(_buffer_pool.begin(), _buffer_pool.end(), [&](const gl_buffer_pool_element& element){
        return _check_buffer_validation(capacity, storage_options);
    });

    // do not find one, create a new one
    if(_it == _buffer_pool.end())
    {
        glCreateBuffers(1, &_handle);
        if(_handle != 0)
        {
            if(storage_options.is_map_read) _storage_flags |= GL_MAP_READ_BIT;
            if(storage_options.is_map_write) _storage_flags |= GL_MAP_WRITE_BIT;
            if(storage_options.is_map_persistent) _storage_flags |= GL_MAP_PERSISTENT_BIT;
            if(storage_options.is_map_coherent) _storage_flags |= GL_MAP_COHERENT_BIT;
            if(storage_options.is_client_storage) _storage_flags |= GL_CLIENT_STORAGE_BIT;
            if(storage_options.is_dynamic_storage) _storage_flags |= GL_DYNAMIC_STORAGE_BIT;

            glNamedBufferStorage(_handle, capacity, nullptr, _storage_flags);
            _required_capacity = capacity;
        }
    }else{ // find a suitable buffers
        // fetch
        _handle = _it->handle;
        _required_capacity = capacity;
        _storage_options = _it->storage_options;
        _storage_flags = _it->storage_flags;
        _capacity = _it->capacity;

        //_buffer_pool.remove(*_it);
    }
}

