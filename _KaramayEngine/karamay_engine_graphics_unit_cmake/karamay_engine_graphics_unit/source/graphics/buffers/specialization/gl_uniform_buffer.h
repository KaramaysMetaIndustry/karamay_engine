#ifndef H_GL_UNIFORM_BUFFER
#define H_GL_UNIFORM_BUFFER

#include "graphics/buffers/buffer/gl_buffer.h"
#include "graphics/glsl/transparent_t/interface_block_t/glsl_interface_block_t.h"

enum class gl_uniform_buffer_layout
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

struct gl_uniform_buffer_block_layout{
    std::uint32_t binding;
    std::int64_t offset;
    std::int64_t size;
    std::shared_ptr<glsl_uniform_block_t> block;
};

class gl_uniform_buffer final{
public:
	gl_uniform_buffer() = default;
	explicit gl_uniform_buffer(const std::vector<std::shared_ptr<glsl_uniform_block_t>>& uniform_blocks)
    {
	    std::int64_t _ubo_initialization_size = 0;
	    std::int64_t _block_offset = 0;
	    for(std::uint32_t _index = 0; _index < uniform_blocks.size(); ++_index)
        {
	        const std::int64_t& _block_size = uniform_blocks[_index]->data_size;
	        // generate layout
	        _layouts.push_back({_index, _block_offset, _block_size, uniform_blocks[_index]});
            // calc offset/ total size
	        _block_offset += _block_size;
            _ubo_initialization_size += _block_size;
        }

	    // create ubo
        gl_buffer_storage_options _options;
	    _options.is_dynamic_storage = true;
	    _options.is_client_storage = true;
	    _buffer = std::make_unique<gl_buffer>(_ubo_initialization_size, _options);
	    if(_buffer)
        {
	        _buffer->execute_mapped_memory_writer(0, _buffer->size(), [](std::uint8_t * data, std::int64_t size){

	        });
        }
	    //_buffer->execute_mapped_memory_writer(0, _buffer->)

    }

    ~gl_uniform_buffer() = default;

public:

    void bind() noexcept
    {
        if(!_buffer) return;

        for(const auto& _block_layout : _layouts)
        {
            glBindBufferRange(GL_UNIFORM_BUFFER,
                              _block_layout.binding,
                              _buffer->get_handle(),
                              _block_layout.offset, _block_layout.size
            );
        }
    }

    void unbind() noexcept
    {
        if(!_buffer) return;

        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void flush_dirty_blocks()
    {
        for(const auto& _layout : _layouts)
        {
            if(_layout.block && _layout.block->is_dirty())
            {
                _buffer->write(_layout.offset, _layout.block->data, _layout.size);
                _layout.block->mark_dirty(false);
            }
        }
    }

private:

    std::unique_ptr<gl_buffer> _buffer;

    std::vector<gl_uniform_buffer_block_layout> _layouts;

};

#endif