#ifndef GL_ELEMENT_BUFFER_H
#define GL_ELEMENT_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"


/*
* dynamic storage
*/
class gl_element_array_buffer final{
public:
    gl_element_array_buffer() : _buffer(nullptr) {}
    gl_element_array_buffer(std::int64_t size, std::uint8_t* data) : _buffer(nullptr)
    {
        _allocate(size, data);
    }

    ~gl_element_array_buffer() = default;


public:

    void reallocate(std::int64_t size, std::uint8_t* new_data = nullptr)
    {
        if (!_buffer || (_buffer && _buffer->size != size))
        {
            _allocate(size, nullptr);
        }
    }

    void fill(std::uint8_t* new_data)
    {
        if (new_data && _buffer)
        {
            _buffer->execute_mapped_memory_writer(0, _buffer->size, [&](std::uint8_t* data, std::int64_t size) {
                if (!data || size < 0) return;
                std::memcpy(data, new_data, size);
                });
        }
    }

    void fill(std::int64_t offset, std::uint8_t* data) {}

public:

    void bind() noexcept
    {
        if(!_buffer) return;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer->get_handle());
    }

    void unbind() noexcept
    {
        if(!_buffer) return;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

private:

    std::unique_ptr<gl_buffer> _buffer;

    void _allocate(std::int64_t size, std::uint8_t* data = nullptr)
    {
        if (!_buffer || (_buffer && _buffer->size != size))
        {
            gl_buffer_storage_options _options;
            _options.is_client_storage = false;
            _options.is_dynamic_storage = true;
            _options.is_map_read = true;
            _options.is_map_write = true;
            _options.is_map_coherent = false;
            _options.is_map_persistent = false;
            _buffer = std::make_unique<gl_buffer>(_options, size);

            fill(data);
        }
    }

};


#endif
