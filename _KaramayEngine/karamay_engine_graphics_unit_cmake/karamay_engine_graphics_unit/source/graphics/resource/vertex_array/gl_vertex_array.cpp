#include "gl_vertex_array.h"




void gl_vertex_array::_set_vertex_pointers(gl_attribute_component::type attribute_component_type, std::uint32_t index,
                                           std::uint32_t components_count, std::uint32_t attribute_size,
                                           std::uint32_t offset) {
    const auto _attribute_component_type_enum = gl_attribute_component::to_GLenum(attribute_component_type);

    switch (attribute_component_type) {
        case gl_attribute_component::type::INT:
        {
            glVertexAttribIPointer(index, components_count, _attribute_component_type_enum, attribute_size, reinterpret_cast<const void*>(offset));
        }
            break;
        case gl_attribute_component::type::UINT:
        {
            glVertexAttribIPointer(index, components_count, _attribute_component_type_enum, attribute_size, reinterpret_cast<const void*>(offset));
        }
            break;
        case gl_attribute_component::type::FLOAT:
        {
            glVertexAttribPointer(index, components_count, _attribute_component_type_enum, GL_FALSE, attribute_size, reinterpret_cast<const void*>(offset));
        }
            break;
        case gl_attribute_component::type::DOUBLE:
        {
            glVertexAttribLPointer(index, components_count, _attribute_component_type_enum, attribute_size, reinterpret_cast<const void*>(offset));
        }
            break;
        default: break;
    }
}

void gl_vertex_array::_generate_attribute_layout() 
{
    
    const auto& _vertex_attribute_descriptors = _descriptor.get_vertex_attribute_descriptors();
    const auto& _instance_attribute_descriptors = _descriptor.get_instance_attribute_descriptors();
    const auto _vertices_count = _descriptor.get_vertices_count();

    for(const auto& _vertex_attribute_descriptor : _vertex_attribute_descriptors)
    {
        const auto _vertex_attribute_size = _vertex_attribute_descriptor.get_component_count() * gl_attribute_component::get_size(_vertex_attribute_descriptor.get_component_type());
        _memory_demand += _vertex_attribute_size *  _vertices_count;
    }

    for(const auto& _instance_attribute_descriptor : _instance_attribute_descriptors)
    {
        const auto _instance_attribute_size = _instance_attribute_descriptor.get_component_count() * gl_attribute_component::get_size(_instance_attribute_descriptor.get_component_type());
        _memory_demand += _instance_attribute_size *  _instance_attribute_descriptor.get_count();
    }


    std::uint32_t _index = 0;
    std::uint32_t _offset = 0;

    for(const auto& _vad : _vertex_attribute_descriptors)
    {
        const gl_attribute_component::type _component_type = _vad.get_component_type();
        const auto _components_count = static_cast<GLint>(_vad.get_component_count());
        const auto _attribute_size = _components_count * static_cast<GLint>(gl_attribute_component::get_size(_component_type));

        _set_vertex_pointers(_component_type, _index, _components_count, _attribute_size, _offset);

        for(std::uint32_t _sub_index = 0; _sub_index < _vertices_count; ++_sub_index)
        {
            _memory_layouts_map.emplace(_vad.get_name() + std::to_string(_sub_index), std::make_pair(_offset, _attribute_size));
            _offset += _attribute_size;
        }

        ++_index;
    }

    for(const auto& _iad : _instance_attribute_descriptors) {
        const auto _component_type = _iad.get_component_type();
        const auto _components_count = static_cast<GLint>(_iad.get_component_count());
        const auto _attribute_size = _components_count * static_cast<GLint>(gl_attribute_component::get_size(_component_type));
        const auto _divisor = _iad.get_divisor();
        const auto _count = _iad.get_count();

        _set_vertex_pointers(_component_type, _index, _components_count, _attribute_size, _offset);
        glVertexAttribDivisor(_index, _divisor);

        for(std::uint32_t _sub_index = 0; _sub_index < _count; ++_sub_index)
        {
            _memory_layouts_map.emplace(_iad.get_name() + std::to_string(_sub_index), std::make_pair(_offset, _attribute_size));
            _offset += _attribute_size;
        }

        ++_index;
    }

    _unbind_buffer(); unbind();
}

