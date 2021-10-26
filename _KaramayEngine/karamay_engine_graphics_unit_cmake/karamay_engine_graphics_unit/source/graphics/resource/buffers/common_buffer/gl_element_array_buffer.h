#ifndef GL_ELEMENT_BUFFER_H
#define GL_ELEMENT_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"

struct gl_element_array_buffer_descriptor
{
    std::uint32_t primitives_num, primitive_size;
};


enum class gl_primitive_mode
{
    POINTS = GL_POINTS,

    LINES = GL_LINES,
    LINES_ADJACENCY = GL_LINES_ADJACENCY,
    LINE_LOOP = GL_LINE_LOOP,
    LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
    LINE_STRIP = GL_LINE_STRIP,

    TRIANGLES = GL_TRIANGLES,
    TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
    TRIANGLE_FAN = GL_TRIANGLE_FAN,

    PATCHES = GL_PATCHES
};


/*
* dynamic storage
*/
class gl_element_array_buffer final{
public:
    gl_element_array_buffer() = default;
    explicit gl_element_array_buffer(const gl_element_array_buffer_descriptor& descriptor) :
        _descriptor(descriptor)
    {
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

    void reallocate(std::int64_t size, std::uint8_t* new_data = nullptr)
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
            
            fill(new_data);
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

private:

    gl_element_array_buffer_descriptor _descriptor;

    std::unique_ptr<gl_buffer> _buffer;

};


#endif
