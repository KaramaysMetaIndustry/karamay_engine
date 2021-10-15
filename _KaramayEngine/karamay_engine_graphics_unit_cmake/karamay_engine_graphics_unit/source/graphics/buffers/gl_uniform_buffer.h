#ifndef GL_UNIFORM_BUFFER_H
#define GL_UNIFORM_BUFFER_H

#include "gl_buffer.h"

struct gl_uniform_buffer_block_layout{
    std::uint32_t binding;
    std::int64_t offset;
    std::int64_t size;
    std::shared_ptr<glsl_uniform_block_t> block;
};

struct gl_uniform_buffer_block_state
{

};

struct gl_uniform_buffer_descriptor{
    std::vector<std::shared_ptr<glsl_uniform_block_t>> uniform_blocks;
    std::vector<std::shared_ptr<gl_uniform_buffer_block_state>> uniform_block_states;
};

class gl_uniform_buffer final{
public:
    struct gl_uniform_buffer_block_layout{
        std::uint32_t baked_binding;
        std::int64_t baked_offset;
        std::int64_t baked_size;
        std::shared_ptr<glsl_uniform_block_t> block;
    };

public:
    gl_uniform_buffer() = delete;
    explicit gl_uniform_buffer(const gl_uniform_buffer_descriptor& descriptor)
    {
        _initialize_ubo(descriptor);
    }
    gl_uniform_buffer(const gl_uniform_buffer&) = delete;
    gl_uniform_buffer& operator=(const gl_uniform_buffer&) = delete;

    ~gl_uniform_buffer() = default;

public:

    void bind() noexcept
    {
//        if(!_buffer) return;
//
//        for(const auto& _block_layout : _layouts)
//        {
//            glBindBufferRange(GL_UNIFORM_BUFFER, _block_layout.baked_binding, _buffer->get_handle(),_block_layout.baked_offset, _block_layout.baked_size);
//        }
    }

    void unbind() noexcept
    {
//        if(!_buffer) return;
//        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

public:

    void flush_dirty_blocks() noexcept
    {
//        for(const auto& _layout : _layouts)
//        {
//            if(_layout.block && _layout.block->is_dirty())
//            {
//                if(!_layout.block->data()) return;
//                _buffer->write(_layout.baked_offset, _layout.block->data(), _layout.baked_size);
//                _layout.block->mark_dirty(false);
//            }
//        }
    }

    void read_back() noexcept
    {
//        if(!_buffer) return;
//        _buffer->execute_mapped_memory_reader(0, _buffer->size(),
//                                              [this](const uint8_t* data, std::int64_t size){
//                                                  for(const auto& _layout : _layouts)
//                                                  {
//                                                      std::memcpy(_layout.block->data(), data + _layout.baked_offset, _layout.baked_size);
//                                                  }
//                                              });
    }

private:

    std::vector<std::shared_ptr<gl_buffer>> _buffers;

    std::vector<gl_uniform_buffer_block_layout> _layouts;

private:
    // initialize ubo
    void _initialize_ubo(const gl_uniform_buffer_descriptor& descriptor)
    {
        std::unordered_map<glsl_uniform_block_memory_layout, std::vector<std::shared_ptr<glsl_uniform_block_t>>> _uniform_blocks_map;
        for(const auto& _uniform_block : descriptor.uniform_blocks)
        {
            if(_uniform_block)
            {
            }
        }
    }
    // default memory layout
    void _initialize_ubo_std140(const std::vector<std::shared_ptr<glsl_uniform_block_t>>& uniform_blocks)
    {
        std::int64_t _ubo_initialization_size = 0;
        std::int64_t _block_offset = 0;
        for(std::uint32_t _index = 0; _index < uniform_blocks.size(); ++_index)
        {
            const std::int64_t& _block_size = uniform_blocks[_index]->size();
            // generate layout
            _layouts.push_back({_index, _block_offset, _block_size, uniform_blocks[_index]});
            // calc offset/ total size
            const std::int64_t _raw_block_offset = _block_offset + _block_size;
            _block_offset += _raw_block_offset -
                             _raw_block_offset%GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT +
                             GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT;
            _ubo_initialization_size += _block_offset;
        }

        // create ubo
        gl_buffer_storage_options _options{
                true, true, true, true,
                false,false
        };
        _buffer = std::make_unique<gl_buffer>(_ubo_initialization_size, _options);
        if(_buffer)
        {
            // init, upload data to gpu
            _buffer->execute_mapped_memory_writer(0, _buffer->size(),[this](std::uint8_t * data, std::int64_t size){
                // set with zero
                std::memset(data, 0, size);
                // fill with blocks data
                for(const auto& _layout : _layouts)
                {
                    std::uint8_t* _src_data = _layout.block->data();
                    std::int64_t _src_size = _layout.block->size();
                    std::memcpy(data, _src_data, _src_size);
                    data += _layout.baked_offset;
                }
            });
        }
    }
    // TODO
    void _initialize_ubo_shared(const std::vector<std::shared_ptr<glsl_uniform_block_t>>& uniform_blocks){}
    // TODO
    void _initialize_ubo_packed(const std::vector<std::shared_ptr<glsl_uniform_block_t>>& uniform_blocks){}

};
#endif
