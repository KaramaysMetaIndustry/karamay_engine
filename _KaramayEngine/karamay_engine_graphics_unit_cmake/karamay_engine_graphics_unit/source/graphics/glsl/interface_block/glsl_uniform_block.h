#ifndef GLSL_UNIFORM_BLOCK_H
#define GLSL_UNIFORM_BLOCK_H

#include "../base/glsl_class.h"
#include "graphics/opengl/resource/buffers/Indexed_buffer/gl_uniform_buffer.h"

enum class glsl_uniform_block_memory_layout
{
    SHARED,
    STD140,
    PACKED
};

struct glsl_block_item
{
    uint64 padding;
    uint64 offset;
    uint64 size;
};

/*
 * [transparent type]
 * exp : layout(row_major,std140/shared/packed,binding=0) uniform { ... };
 * pipeline manage 3 ubos
 * */
class glsl_uniform_block : public glsl_interface_block_t
{
public:
    glsl_uniform_block(
        glsl_interface_block_matrix_layout _matrix_layout,
        glsl_uniform_block_memory_layout _memory_layout,
        const std::vector<glsl_block_item>& items
    ) {}

    glsl_uniform_block(const glsl_uniform_block&) = delete;
    glsl_uniform_block& operator=(const glsl_uniform_block&) = delete;

    ~glsl_uniform_block() = default;

public:

    void update(const std::string& name)
    {

    }

    void associate(gl_uniform_buffer* uniform_buffer, uint64 offset, uint64 size)
    {
        _associated_uniform_buffer = uniform_buffer;
        //glUniformBlockBinding(0, glGetUniformBlockIndex(0, _block_name.c_str()), _binding);
    }

    void bind()
    {
        if (_associated_uniform_buffer)
        {
            glBindBufferRange(GL_UNIFORM_BUFFER, _binding, _associated_uniform_buffer->get_handle(), _binding_offset, _binding_size);
        }
    }

    void unbind()
    {
        glBindBufferRange(GL_UNIFORM_BUFFER, _binding, 0, 0, 0);
    }

    const std::string& block_name() const { return _block_name; }

private:

    std::string _block_name;
    
    uint32 _binding;

    std::vector<glsl_block_item> _items;
    
    gl_uniform_buffer* _associated_uniform_buffer;
    
    uint64 _binding_offset, _binding_size;

    void _add_item(const glsl_block_item& item)
    {
        _items.push_back(item);
    }

protected:

    template<typename GLSL_SAMPLER_T>
    std::shared_ptr<GLSL_SAMPLER_T> _create_sampler(const std::string& name)
    {
        std::shared_ptr<GLSL_SAMPLER_T> _sampler = std::make_shared<GLSL_SAMPLER_T>(name);
        _sampler->manager = this;
        glsl_block_item _item;
        _add_item(_item);
        return _sampler;
    }

    template<typename GLSL_IMAGE_T>
    std::shared_ptr<GLSL_IMAGE_T> _create_image(const std::string& name, gl_image_format format, const std::vector<glsl_image_memory_qualifier>& memory_qualifiers)
    {
        std::shared_ptr<GLSL_IMAGE_T> _image = std::make_shared<GLSL_IMAGE_T>(name, format, memory_qualifiers);
        glsl_block_item _item;
        _item.padding = 0;
        _item.offset = 0;
        _item.size = sizeof(uint64);

        _add_item(_item);
        return _image;
    }

};




#endif
