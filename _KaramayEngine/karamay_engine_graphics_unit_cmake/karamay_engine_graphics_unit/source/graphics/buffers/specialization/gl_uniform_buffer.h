#ifndef H_GL_UNIFORM_BUFFER
#define H_GL_UNIFORM_BUFFER

#include "graphics/buffers/buffer/gl_buffer.h"
#include "graphics/glsl/transparent_t/interface_block_t/glsl_interface_block_t.h"

enum class gl_uniform_buffer_memory_layout
{
    std140,
    shared,
    packed
};

enum class gl_uniform_buffer_matrix_layout
{
    row_major,
    column_major
};

struct gl_uniform_buffer_block_query_info{

};

struct gl_uniform_buffer_descriptor{
    gl_uniform_buffer_memory_layout memory_layout;
    gl_uniform_buffer_matrix_layout matrix_layout;
    std::vector<std::shared_ptr<glsl_uniform_block_t>> uniform_blocks;
    std::vector<std::shared_ptr<gl_uniform_buffer_block_query_info>> uniform_block_query_infos;

    gl_uniform_buffer_descriptor() :
        memory_layout(gl_uniform_buffer_memory_layout::std140),
        matrix_layout(gl_uniform_buffer_matrix_layout::row_major),
        uniform_blocks(),
        uniform_block_query_infos()
    {}
};


/*
 * flush 粒度单位为 block
 * read back 粒度为 buffer
 *
 * */
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
        if(!_buffer) return;

        for(const auto& _block_layout : _layouts)
        {
            glBindBufferRange(GL_UNIFORM_BUFFER, _block_layout.baked_binding, _buffer->get_handle(),_block_layout.baked_offset, _block_layout.baked_size);
        }
    }

    void unbind() noexcept
    {
        if(!_buffer) return;
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

public:

    void flush_dirty_blocks() noexcept
    {
        for(const auto& _layout : _layouts)
        {
            if(_layout.block && _layout.block->is_dirty())
            {
                if(!_layout.block->data) return;
                _buffer->write(_layout.baked_offset, _layout.block->data, _layout.baked_size);
                _layout.block->mark_dirty(false);
            }
        }
    }

    void read_back() noexcept
    {
        if(!_buffer) return;
        _buffer->execute_mapped_memory_reader(0, _buffer->size(),
                                              [this](const uint8_t* data, std::int64_t size){
            for(const auto& _layout : _layouts)
            {
                std::memcpy(_layout.block->data, data + _layout.baked_offset, _layout.baked_size);
            }
        });
    }

private:

    std::unique_ptr<gl_buffer> _buffer;

    std::vector<gl_uniform_buffer_block_layout> _layouts;

private:
    // initialize ubo
    void _initialize_ubo(const gl_uniform_buffer_descriptor& descriptor)
    {
        switch (descriptor.memory_layout) {
            case gl_uniform_buffer_memory_layout::std140:
                _initialize_ubo_std140(descriptor.uniform_blocks);
                break;
            case gl_uniform_buffer_memory_layout::shared:
                _initialize_ubo_shared(descriptor.uniform_blocks);
                break;
            case gl_uniform_buffer_memory_layout::packed:
                _initialize_ubo_packed(descriptor.uniform_blocks);
                break;
        }
    }
    // default memory layout
    void _initialize_ubo_std140(const std::vector<std::shared_ptr<glsl_uniform_block_t>>& uniform_blocks)
    {
        std::int64_t _ubo_initialization_size = 0;
        std::int64_t _block_offset = 0;
        for(std::uint32_t _index = 0; _index < uniform_blocks.size(); ++_index)
        {
            const std::int64_t& _block_size = uniform_blocks[_index]->data_size;
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
                    std::uint8_t* _src_data = _layout.block->data;
                    std::int64_t _src_size = _layout.block->data_size;
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