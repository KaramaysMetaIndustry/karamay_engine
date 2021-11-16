#ifndef GL_ELEMENT_BUFFER_H
#define GL_ELEMENT_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"


enum class gl_element_type
{
    NONE,
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    UNSIGNED_INT = GL_UNSIGNED_INT
};

class gl_element_array_buffer final{
public:
    using element_buffer_writer = std::function<void(void*, uint32)>;
    using element_buffer_reader = std::function<void(const void*, uint32)>;
    using element_buffer_handler = std::function<void(void*, uint32)>;

    gl_element_array_buffer() = delete;
    gl_element_array_buffer(gl_element_type element_type, uint32 elements_num, const void* initial_elements = nullptr) :                                                                            
        _raw_buffer(nullptr), 
        _element_type(element_type),
        _element_size(0),
        _elements_num(elements_num)
    {
        switch (_element_type)
        {
            case gl_element_type::UNSIGNED_BYTE: _element_size = sizeof(uint8); break;
            case gl_element_type::UNSIGNED_SHORT: _element_size = sizeof(uint16); break;
            case gl_element_type::UNSIGNED_INT: _element_size = sizeof(uint32); break;
            default: break;
        }
        _allocate(_elements_num, initial_elements);
    }

    gl_element_array_buffer(const gl_element_array_buffer&) = delete;
    gl_element_array_buffer& operator=(const gl_element_array_buffer&) = delete;

    ~gl_element_array_buffer() = default;

public:

    const gl_buffer* get_raw() const { return _raw_buffer.get(); }

    uint32 get_elements_num() const { return _elements_num; }

    uint32 get_element_size() const { return _element_size; }

    gl_element_type get_element_type() const { return _element_type; }

public:

    void reallocate(uint32 elements_num, const void* initial_elements)
    {
        if (!initial_elements) return;

        _elements_num = elements_num;
        _allocate(elements_num, initial_elements);
    }

    void write(uint32 element_offset, uint32 elements_num, const void* elements) 
    {
        if (!_raw_buffer || !elements) return;

        _raw_buffer->write(element_offset * _element_size, elements, elements_num * _element_size);
    }

    const void* read(uint32 element_offset, uint32 elements_num) const
    {
        return _raw_buffer? _raw_buffer->read(element_offset * _element_size, elements_num * _element_size) : nullptr;
    }

    void execute_mapped_element_buffer_reader(uint32 element_offset, uint32 elements_num, const element_buffer_reader& reader)
    {
        if (!_raw_buffer) return;

        _raw_buffer->execute_mapped_memory_reader(element_offset * _element_size, elements_num * _element_size,
            [&reader, this](const void* mapped_memory, int64 bytes_num)
            {
                if (!mapped_memory) return;
                reader(mapped_memory, bytes_num / _element_size);
            }
        );
    }

    void execute_mapped_element_buffer_writer(uint32 element_offset, uint32 elements_num, const element_buffer_writer& writer)
    {
        if (!_raw_buffer) return;

        _raw_buffer->execute_mapped_memory_writer(element_offset * _element_size, elements_num * _element_size,
            [&writer, this](void* mapped_memory, int64 bytes_num)
            {
                if (!mapped_memory) return;
                writer(mapped_memory, bytes_num / _element_size);
            }
        );
    }

    void execute_mapped_element_buffer_handler(uint32 element_offset, uint32 elements_num, const element_buffer_handler& handler)
    {
        if (!_raw_buffer) return;

        _raw_buffer->execute_mapped_memory_handler(element_offset * _element_size, elements_num * _element_size,
            [&handler, this](void* mapped_memory, int64 bytes_num)
            {
                if (!mapped_memory) return;
                handler(mapped_memory, bytes_num / _element_size);
            }
        );
    }

    void set_primitive_restart_flag_element(uint32 element_offset)
    {
        if (!_raw_buffer) return;

        _raw_buffer->write(element_offset * _element_size, nullptr, _element_size);
        _primitive_restart_flag_element_indices.push_back(element_offset);
    }

    const std::vector<uint32>& get_primitive_restart_flag_element_offsets() const
    { 
        return _primitive_restart_flag_element_indices;
    }

    void restart_primitive() const
    {
        if (_primitive_restart_flag_element_indices.size() == 0) return;
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0xFFF);
        glDisable(GL_PRIMITIVE_RESTART);
    }

public:

    void bind() const noexcept
    {
        if(!_raw_buffer) return;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _raw_buffer->get_handle());
    }

    void unbind() const noexcept
    {
        if(!_raw_buffer) return;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

private:

    gl_element_type _element_type;

    uint32 _element_size;

    uint32 _elements_num;

    std::vector<uint32> _primitive_restart_flag_element_indices;

    std::unique_ptr<gl_buffer> _raw_buffer;

    void _allocate(uint32 elements_num, const void* initial_elements)
    {
        if (_raw_buffer)
        {
            gl_buffer* _new_buffer = new gl_buffer(_raw_buffer->get_buffer_storage_options(), elements_num * _element_size);
            int64 _bytes_num = _raw_buffer->get_bytes_num() > _new_buffer->get_bytes_num() ? _new_buffer->get_bytes_num() : _raw_buffer->get_bytes_num();
            gl_buffer::memcpy(_new_buffer, 0, _raw_buffer.get(), 0, _bytes_num);
            _raw_buffer.reset(_new_buffer);
        } else {
            gl_buffer_storage_options _options;
            _options.client_storage = false;
            _options.dynamic_storage = true;
            _options.map_read = true;
            _options.map_write = true;
            _options.map_coherent = false;
            _options.map_persistent = false;
            _raw_buffer = std::make_unique<gl_buffer>(_options, elements_num * _element_size);
        }
    }

};


#endif
