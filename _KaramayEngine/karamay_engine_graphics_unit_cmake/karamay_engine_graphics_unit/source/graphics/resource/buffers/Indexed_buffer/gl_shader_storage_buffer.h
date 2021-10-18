#ifndef GL_SHADER_STORAGE_BUFFER_H
#define GL_SHADER_STORAGE_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"
#include "graphics/glsl/glsl_shader_storage_block.h"

struct gl_shader_storage_buffer_descriptor{
    std::vector<std::shared_ptr<glsl_shader_storage_block_t>> shader_storage_blocks;
};

class gl_shader_storage_buffer final{
public:
    struct gl_shader_storage_block_layout{
        std::uint32_t binding;
        std::int64_t offset;
        std::shared_ptr<glsl_shader_storage_block_t> block;
    };

public:
    gl_shader_storage_buffer() = default;
    explicit gl_shader_storage_buffer(const gl_shader_storage_buffer_descriptor& descriptor)
    {
        // generate uniform blocks' layout infos
        std::int64_t _initialization_size = 0;
        std::int64_t _block_offset = 0;
        const auto& _shader_storage_blocks = descriptor.shader_storage_blocks;
        for(std::uint32_t _idx = 0; _idx < _shader_storage_blocks.size(); ++_idx)
        {
            const auto& _shader_storage_block = _shader_storage_blocks[_idx];

            // create layout
            _layouts.push_back({_idx, _block_offset, _shader_storage_block});

            // do not affect _initialization_size and _block_offset validation
            if(_idx == _shader_storage_blocks.size()) break;
            // raw offset
            const std::int64_t _raw_block_offset = _block_offset + _shader_storage_block->size();
            // add padding
            _block_offset += _raw_block_offset -
                             _raw_block_offset%GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT + GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT;
            // calc total size
            _initialization_size += _block_offset;
        }

        // create buffer
        gl_buffer_storage_options _options{};
        _buffer = std::make_unique<gl_buffer>(_initialization_size, _options);
        if(!_buffer) return;

        // upload data
        _buffer->execute_mapped_memory_writer(
                0,
                _initialization_size,
                [this](std::uint8_t* data, std::int64_t size){
                    if(!data || size < 0) return;
                    // make sure the padding initialized by zero
                    std::memset(data, 0, size);
                    // fill the block data
                    for(const auto& _layout : _layouts)
                    {
                        std::memcpy(data + _layout.offset, _layout.block->data(), _layout.block->size());
                    }
                });

    }
    gl_shader_storage_buffer(const gl_shader_storage_buffer&) = delete;
    gl_shader_storage_buffer& operator=(const gl_shader_storage_buffer&) = delete;

    ~gl_shader_storage_buffer() = default;

public:

    void bind() noexcept
    {
        if(!_buffer) return;

        for(const auto& _layout : _layouts)
        {
            glBindBufferRange(GL_SHADER_STORAGE_BUFFER,
                              _layout.binding, _buffer->get_handle(),
                              _layout.offset,
                              _layout.block->size()
            );
        }
    }

    void unbind() noexcept
    {
        if(!_buffer) return;

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void upload() noexcept
    {
        if(!_buffer) return;

        for(const auto& _layout : _layouts)
        {
            if(_layout.block && _layout.block->is_dirty)
            {
                if(!_layout.block->data()) return;
                _buffer->write(_layout.offset, _layout.block->data(), _layout.block->size());
                _layout.block->is_dirty = false;
            }
        }
    }

    void download() noexcept
    {
        if(!_buffer) return;

        _buffer->execute_mapped_memory_reader(
                0,
                _buffer->size(),
                [this](const uint8_t* data, std::int64_t size){
                    for(const auto& _layout : _layouts)
                    {
                        std::memcpy(_layout.block->data(), data + _layout.offset, _layout.block->size());
                    }
                });
    }

private:

    std::unique_ptr<gl_buffer> _buffer;

    std::vector<gl_shader_storage_block_layout> _layouts;

};

#endif
