#ifndef GL_ELEMENT_BUFFER_H
#define GL_ELEMENT_BUFFER_H

#include "gl_buffer.h"

struct gl_element_array_buffer_descriptor
{
    std::vector<std::uint32_t> primitives;
    std::uint32_t primitives_num;
};

class gl_element_array_buffer{
public:

    gl_element_array_buffer() = delete;
    explicit gl_element_array_buffer(const gl_element_array_buffer_descriptor& descriptor)
    {
        _initialize_ebo(descriptor);
    }

    ~gl_element_array_buffer() = default;

public:

    void bind()
    {
        if(!_buffer) return;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer->get_handle());
    }

    void unbind()
    {
        if(!_buffer) return;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

private:

    std::unique_ptr<gl_buffer> _buffer;

private:

    void _initialize_ebo(const gl_element_array_buffer_descriptor& descriptor)
    {
        std::int64_t _ebo_initialization_size = static_cast<std::int64_t>(descriptor.primitives.size() * sizeof (std::uint32_t));

        gl_buffer_storage_options _options{};
        _buffer = std::make_unique<gl_buffer>(_ebo_initialization_size, _options);

        _buffer->execute_mapped_memory_writer(0, _buffer->size(), [this](std::uint8_t* data, std::int64_t size){

        });
    }

};


#endif
