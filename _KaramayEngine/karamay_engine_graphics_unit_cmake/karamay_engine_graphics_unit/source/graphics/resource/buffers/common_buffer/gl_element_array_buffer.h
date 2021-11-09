#ifndef GL_ELEMENT_BUFFER_H
#define GL_ELEMENT_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"


/*
* dynamic storage
*/
class ElementArrayBuffer final{
public:
    ElementArrayBuffer() : _buffer(nullptr) {}
    ElementArrayBuffer(std::int64_t size, std::uint8_t* data) : _buffer(nullptr)
    {
        _allocate(size, data);
    }

    ~ElementArrayBuffer() = default;

public:

    void Reallocate(UInt32 IndicesNum) 
    {
        const Int64 Size = sizeof(UInt32) * IndicesNum;

        if (!_buffer || (_buffer && _buffer->size != Size))
        {
            _allocate(Size, nullptr);
        }
    }

    void Fill(UInt32 Offset, const std::vector<UInt32>& Indices) 
    {
        if (_buffer)
        {
            _buffer->execute_mapped_memory_writer(Offset, _buffer->size, [&](std::uint8_t* data, std::int64_t size) {
                if (!data || size < 0) return;
                std::memcpy(data, Indices.data(), size);
                });
        }
    }

public:

    void Bind() noexcept
    {
        if(!_buffer) return;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer->get_handle());
    }

    void Unbind() noexcept
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
