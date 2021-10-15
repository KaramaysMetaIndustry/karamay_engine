#ifndef GL_ATOMIC_COUNTER_BUFFER_H
#define GL_ATOMIC_COUNTER_BUFFER_H

#include "gl_buffer.h"

struct gl_atomic_counter_buffer_descriptor{
    std::vector<std::shared_ptr<glsl_atomic_counter_t>> atomic_counters;
};

class gl_atomic_counter_buffer final{
    struct gl_atomic_counter_layout
    {
        std::uint32_t binding;
        std::int32_t offset;
        std::shared_ptr<glsl_atomic_counter_t> counter;
    };

public:
    gl_atomic_counter_buffer() = delete;
    explicit gl_atomic_counter_buffer(const gl_atomic_counter_buffer_descriptor& descriptor)
    {
        _initialize_acbo(descriptor);
    }

    ~gl_atomic_counter_buffer() = default;

public:

    void bind()
    {
        if(!_buffer) return;

        for(const auto& _layout: _layouts)
        {
            glBindBufferRange(GL_ATOMIC_COUNTER_BUFFER,
                              _layout.binding,
                              _buffer->get_handle(),_layout.offset, 4
            );
        }
    }

    void unbind()
    {
        if(!_buffer) return;

        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);

    }

private:

    std::unique_ptr<gl_buffer> _buffer;

    std::vector<gl_atomic_counter_layout> _layouts;

private:

    void _initialize_acbo(const gl_atomic_counter_buffer_descriptor& descriptor)
    {
        std::int64_t _acbo_initialization_size =
                static_cast<std::int64_t>(descriptor.atomic_counters.size() * sizeof (std::uint32_t));

        gl_buffer_storage_options _options{};
        _buffer = std::make_unique<gl_buffer>(_acbo_initialization_size, _options);
        if(!_buffer) return;

        _buffer->execute_mapped_memory_writer(0, _buffer->size(), [this](std::uint8_t* data, std::int64_t size){
            if(!data || size < 0) return;

            // no padding
            //std::memset(data,0, size);
            for(const auto& _layout : _layouts)
            {
                std::memcpy(data, &_layout.counter->data, 4);
                data += 4;
            }

        });
    }

};

#endif
