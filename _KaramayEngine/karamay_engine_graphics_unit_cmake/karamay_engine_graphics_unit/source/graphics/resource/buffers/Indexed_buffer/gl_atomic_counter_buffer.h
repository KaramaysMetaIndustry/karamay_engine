#ifndef GL_ATOMIC_COUNTER_BUFFER_H
#define GL_ATOMIC_COUNTER_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"
#include "graphics/glsl/opaque_t/glsl_atomic_counter.h"

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
        std::uint32_t binding;
        std::int32_t offset;
        std::shared_ptr<glsl_atomic_counter_t> atomic_counter;
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
                _layouts.push_back({_idx, static_cast<std::int32_t>(_idx * 4), _atomic_counter});
                _initialization_size += 4;
            }
        }

        // generate buffer
        BufferStorageOptions _Options{};
        _buffer = std::make_unique<Buffer>(_Options, _initialization_size);
        if(_buffer) return;

        // upload data
        _buffer->ExecuteMappedMemoryWriter(
                0,
                _initialization_size,
                [this](std::uint8_t* data, std::int64_t size)
        {
            if(!data || size < 0) return;
            //std::memset(data, 0, size); //no padding
            for(const auto& _layout : _layouts)
            {
                std::memcpy(data + _layout.offset, _layout.atomic_counter->data(), 4);
            }
        });
    }

    ~gl_atomic_counter_buffer() = default;

public:

    void bind() noexcept
    {
        if(!_buffer) return;

        for(const auto& _layout: _layouts)
        {
            glBindBufferRange(GL_ATOMIC_COUNTER_BUFFER,
                              _layout.binding,
                              _buffer->get_handle(),
                              _layout.offset, 4
            );
        }
    }

    void unbind() noexcept
    {
        if(!_buffer) return;

        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
    }

    void upload()
    {
        if(!_buffer) return;

        for(const auto& _layout : _layouts)
        {
            if(_layout.atomic_counter && _layout.atomic_counter->dirty)
            {
                _buffer->ExecuteMappedMemoryWriter(
                        _layout.offset,
                        4,
                        [_layout](std::uint8_t* data, std::int64_t size){
                            std::memcpy(data, _layout.atomic_counter->data(), 4);
                        });
            }
        }
    }

    void download()
    {
        if(!_buffer) return;

        for(const auto& _layout : _layouts)
        {
            if(_layout.atomic_counter && _layout.atomic_counter->dirty)
            {
                _buffer->ExecuteMappedMemoryReader(
                        _layout.offset,
                        4,
                        [_layout](const std::uint8_t* data, std::int64_t size){
                            std::memcpy(_layout.atomic_counter->data(), data, 4);
                        });
            }
        }
    }

private:

    std::unique_ptr<Buffer> _buffer;

    std::vector<gl_atomic_counter_layout> _layouts;

};


#endif
