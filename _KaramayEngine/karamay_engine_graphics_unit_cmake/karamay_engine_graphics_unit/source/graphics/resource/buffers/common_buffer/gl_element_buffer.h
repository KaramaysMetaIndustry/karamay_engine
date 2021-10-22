#ifndef GL_ELEMENT_BUFFER_H
#define GL_ELEMENT_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"

struct gl_element_array_buffer_descriptor
{
    std::vector<std::uint32_t> primitives;
    std::uint32_t primitives_num;
};


/*
* dynamic storage
*/
class gl_element_array_buffer final{
public:
    gl_element_array_buffer() = delete;
    explicit gl_element_array_buffer(const gl_element_array_buffer_descriptor& descriptor) :
        _descriptor(descriptor)
    {
        _initialize_ebo(descriptor);
    }

    ~gl_element_array_buffer() = default;

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

    gl_element_array_buffer_descriptor _descriptor;

    std::unique_ptr<gl_buffer> _buffer;

private:

    void _initialize_ebo(const gl_element_array_buffer_descriptor& descriptor)
    {
        auto _initialization_size = static_cast<std::int64_t>(descriptor.primitives.size() * sizeof (std::uint32_t));

        gl_buffer_storage_options _options;
        _options.is_client_storage = false;
        _options.is_dynamic_storage = true;
        _options.is_map_read = true;
        _options.is_map_write = true;
        _options.is_map_coherent = false;
        _options.is_map_persistent = false;

        _buffer = std::make_unique<gl_buffer>(_options, _initialization_size);

        if (!_buffer) return;

        _buffer->execute_mapped_memory_writer(0, _buffer->size, [this](std::uint8_t* data, std::int64_t size){
            if (!data || size < 0) return;

            std::memcpy(data, _descriptor.primitives.data(), _descriptor.primitives.size() * sizeof(std::uint32_t));
           
        });
    }

};


#endif
