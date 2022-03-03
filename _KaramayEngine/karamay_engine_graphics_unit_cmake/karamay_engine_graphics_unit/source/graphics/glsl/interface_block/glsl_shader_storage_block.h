#ifndef GLSL_SHADER_STORAGE_BLOCK_H
#define GLSL_SHADER_STORAGE_BLOCK_H

#include "../base/glsl_class.h"
#include "graphics/opengl/resource/buffers/Indexed_buffer/gl_shader_storage_buffer.h"

enum class glsl_shader_storage_block_memory_layout
{
    STD140,
    STD430
};

/*
 * [transparent type]
 * exp : layout(row_major,std140/std430,binding=0) buffer { ... };
 * these blocks can control their value directly
 * */
class glsl_shader_storage_block : public glsl_interface_block_t
{
public:
    glsl_shader_storage_block() = default;
    glsl_shader_storage_block(
            glsl_interface_block_matrix_layout matrix_layout,
            glsl_shader_storage_block_memory_layout memory_layout
    ){}
    glsl_shader_storage_block(const glsl_shader_storage_block&) = delete;
    glsl_shader_storage_block& operator=(const glsl_shader_storage_block&) = delete;

    ~glsl_shader_storage_block() = default;

public:

    const std::string& block_name() const { return _block_name; }

private:

    std::string _block_name;

protected:

    template<typename T>
    std::shared_ptr<T> _create_sampler(const std::string& name)
    {
        static_assert(std::is_base_of_v<glsl_sampler_t, T>, "you must specify a glsl sampler type");

        std::shared_ptr<T> _sampler = std::make_shared<T>(name);
        // _sampler->manager = this;
        glsl_block_item _item;
        //_add_item(_item);
        return _sampler;
    }

    template<typename T>
    std::shared_ptr<T> _create_image(const std::string& name, gl_image_format format, const std::vector<glsl_image_memory_qualifier>& memory_qualifiers)
    {
        static_assert(std::is_base_of_v<glsl_image_t>, "you must specify a glsl image type");

        std::shared_ptr<T> _image = std::make_shared<T>(name, format, memory_qualifiers);
        glsl_block_item _item;
        _item.padding = 0;
        _item.offset = 0;
        _item.size = sizeof(uint64);
        _add_item(_item);
        return _image;
    }

private:

    void _add_item(glsl_block_item item) {}

};

#endif
