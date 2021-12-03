#ifndef GL_UNIFORM_BUFFER_H
#define GL_UNIFORM_BUFFER_H

#include "../../buffers/raw_buffer/gl_buffer.h"

struct gl_uniform_buffer_descriptor{
};


class gl_uniform_buffer final{
public:

    gl_uniform_buffer() = delete;
    explicit gl_uniform_buffer(const gl_uniform_buffer_descriptor& descriptor)
    {
       // // generate uniform blocks' layout infos
       //int64 _initialization_size = 0;
       //int64 _block_offset = 0;
       // const auto& _uniform_blocks = descriptor.uniform_blocks;
       // for(std::uint32_t _idx = 0; _idx < _uniform_blocks.size(); ++_idx)
       // {
       //     const auto& _uniform_block = _uniform_blocks[_idx];

       //     // create layout
       //     _layouts.push_back({_idx, _block_offset, _uniform_block});

       //     // do not affect _initialization_size and _block_offset validation
       //     if(_idx == _uniform_blocks.size()) break;
       //     // raw offset
       //     const std::int64_t _raw_block_offset = _block_offset + _uniform_block->size();
       //     // add padding
       //     _block_offset += _raw_block_offset - _raw_block_offset%GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT + GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT;
       //     // calc total size
       //     _initialization_size += _block_offset;
       // }

       // // create buffer
       // gl_buffer_storage_options _options;
       // _options.client_storage = true; // allow backup to client
       // _options.dynamic_storage = true; // allow dynamic change
       // _options.map_read = true; // allow map read
       // _options.map_write = true; // allow map write
       // _options.map_persistent = true; // allow shader access when mapped
       // _options.map_coherent = true; // allow shader access keep coherent with client operation when mapped

       // _buffer = std::make_unique<gl_buffer>(_options, _initialization_size);
       // if(!_buffer) return;

       // // upload data
       // _buffer->execute_mapped_memory_writer(
       //         0,
       //         _initialization_size,
       //         [this](void* data, std::int64_t size){
       //             if(!data || size < 0) return;
       //             // make sure the padding initialized by zero
       //             std::memset(data, 0, size);
       //             // fill the block data
       //             for(const auto& _layout : _layouts)
       //             {
       //                 //std::memcpy(data + _layout.offset, _layout.block->data(), _layout.block->size());
       //             }
       //         });
    }
    gl_uniform_buffer(const gl_uniform_buffer&) = delete;
    gl_uniform_buffer& operator=(const gl_uniform_buffer&) = delete;

    ~gl_uniform_buffer() = default;

public:

    void bind() noexcept
    {
    }

    void unbind() noexcept
    {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

public:

    void upload() noexcept
    {
        /*if(!_buffer) return;

        glMemoryBarrierByRegion(GL_UNIFORM_BARRIER_BIT);

        for(const auto& _layout : _layouts)
        {
            if(_layout.block && _layout.block->is_dirty)
            {
                if(!_layout.block->data()) return;
                _buffer->write(_layout.offset, _layout.block->data(), _layout.block->size());
                _layout.block->is_dirty = false;
            }
        }*/
    }

    void download() noexcept
    {
       
    }

};




#endif
