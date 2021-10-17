#ifndef GL_ATOMIC_COUNTER_BUFFER_H
#define GL_ATOMIC_COUNTER_BUFFER_H

#include "graphics/resource/buffers/gl_buffer.h"
#include "graphics/glsl/glsl_atomic_counter.h"

/*
 * constructed by pipeline
 *
 * */
struct gl_atomic_counter_buffer_descriptor{
    std::vector<std::shared_ptr<glsl_atomic_counter_t>> atomic_counters;
};

class gl_atomic_counter_buffer final {
public:
    struct gl_atomic_counter_layout{
        std::shared_ptr<glsl_atomic_counter_t> atomic_counter;
        std::uint32_t binding;
        std::int32_t offset;
    };

public:
    gl_atomic_counter_buffer() = delete;
    explicit gl_atomic_counter_buffer(const gl_atomic_counter_buffer_descriptor& descriptor)
    {
        // generate atomic counters' layout infos
        std::int64_t _initialization_size = 0;
        for(std::uint32_t _idx = 0; _idx < descriptor.atomic_counters.size(); ++_idx)
        {
            const auto& _atomic_counter = descriptor.atomic_counters[_idx];
            if(_atomic_counter)
            {
                _layout_infos.push_back({_atomic_counter, _idx, static_cast<std::int32_t>(_idx * 4)});
                _initialization_size += 4;
            }
        }

        // generate buffer
        gl_buffer_storage_options _options{};
        _buffer = std::make_unique<gl_buffer>(_initialization_size, _options);
        if(_buffer) return;

        // upload data
        _buffer->execute_mapped_memory_writer(
                0,
                _initialization_size,
                [this](std::uint8_t* data, std::int64_t size)
        {
            if(!data || size < 0) return;
            //std::memset(data, 0, size); //no padding
            std::vector<std::uint32_t> _counters(_layout_infos.size());
            for(const auto& _binding_info : _layout_infos)
            {
                _counters.push_back(_binding_info.atomic_counter->get());
            }
            // cpy
            std::memcpy(data, _counters.data(), 4 * _counters.size());
        });
    }

    ~gl_atomic_counter_buffer() = default;

public:

    void bind() noexcept
    {
        if(!_buffer) return;

        for(const auto& _layout_info: _layout_infos)
        {
            glBindBufferRange(GL_ATOMIC_COUNTER_BUFFER,
                              _layout_info.binding,
                              _buffer->get_handle(),
                              _layout_info.offset, 4
            );
        }
    }

    void unbind() noexcept
    {
        if(!_buffer) return;

        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
    }

private:

    std::unique_ptr<gl_buffer> _buffer;

    std::vector<gl_atomic_counter_layout> _layout_infos;

};


#endif
