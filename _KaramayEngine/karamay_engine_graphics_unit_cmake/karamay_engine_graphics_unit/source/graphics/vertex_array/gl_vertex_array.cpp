#include "gl_vertex_array.h"
#include "graphics/buffer/gl_buffer.h"

bool gl_vertex_array::is_pointer_enabled(std::uint32_t index)
{
	bind();
	GLint _is_enabled = GL_FALSE;
	glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &_is_enabled);
	unbind();
	return _is_enabled;
}

std::uint32_t gl_vertex_array::get_attribute_components_num(std::uint32_t index)
{
	bind();
	GLint _num = 0;
	glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &_num);
	unbind();
	return _num;
}

std::string gl_vertex_array::get_attribute_component_type(std::uint32_t index)
{
	bind();
	GLint _num = 0;
	glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &_num);
	unbind();

	switch (_num)
	{
	case GL_BYTE: return "BYTE";
	case GL_UNSIGNED_BYTE: return "UNSIGNED BYTE";
	case GL_SHORT: return "SHORT";
	case GL_UNSIGNED_SHORT: return "UNSIGNED SHORT";
	case GL_INT: return "INT";
	case GL_UNSIGNED_INT: return "UNSIGNED INT";
	case GL_FLOAT: return "FLOAT";
	case GL_DOUBLE: return "DOUBLE";
	default: return "";
		break;
	}
}

void* gl_vertex_array::get_mapped_data()
{
	if (_buffer)
		return _buffer->map(gl_buffer_enum::access::READ_WRITE);
	return nullptr;
}

const std::int32_t gl_vertex_array::get_size() const
{
	return _buffer->get_size();
}

gl_vertex_array::~gl_vertex_array()
{
	glDeleteVertexArrays(1, &_handle);
}

void gl_vertex_array::bind()
{
	glBindVertexArray(_handle);
}

void gl_vertex_array::unbind()
{
	glBindVertexArray(0);
}

void gl_vertex_array::enable_pointers()
{
	if (_descriptor)
	{
		const std::size_t _size = _descriptor->get_layouts().size();

		for (std::uint32_t i = 0; i < _size; ++i)
		{
			glEnableVertexAttribArray(i);
		}
	}
}

void gl_vertex_array::disable_pointers()
{
	if (_descriptor)
	{
		const std::size_t _size = _descriptor->get_layouts().size();

		for (std::uint32_t i = 0; i < _size; ++i)
		{
			glDisableVertexAttribArray(i);
		}
	}
}

void gl_vertex_array::_bind_buffer()
{
	if (_buffer)
		glBindBuffer(GL_ARRAY_BUFFER, _buffer->get_handle());
}

void gl_vertex_array::_unbind_buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gl_vertex_array::_fill()
{
    bind(); _bind_buffer();
    const auto& _vertex_attribute_descriptors = _descriptor.get_vertex_attribute_descriptors();
    const auto& _instance_attribute_descriptors = _descriptor.get_instance_attribute_descriptors();
    const auto _vertices_count = _descriptor.get_vertices_count();

    std::uint32_t _index = 0;
    std::uint32_t _offset = 0;

    for(const auto& _vad : _vertex_attribute_descriptors)
    {
        const auto _component_type = _vad.get_component_type();
        const auto _component_type_enum = gl_attribute_component::to_GLenum(_component_type);
        const auto _components_count = static_cast<GLint>(_vad.get_component_count());
        const auto _attribute_size = _components_count * static_cast<GLint>(gl_attribute_component::get_size(_component_type));


        if (_component_type == gl_attribute_component::type::INT || _component_type == gl_attribute_component::type::UINT)
        {
            glVertexAttribIPointer(_index, _components_count, _component_type_enum, _attribute_size, reinterpret_cast<const void*>(_offset));
        }
        if (_component_type == gl_attribute_component::type::FLOAT) // original floats
        {
            glVertexAttribPointer(_index, _components_count, _component_type_enum, GL_FALSE, _attribute_size, reinterpret_cast<const void*>(_offset));
        }
        if (_component_type == gl_attribute_component::type::DOUBLE)
        {
            glVertexAttribLPointer(_index, _components_count, _component_type_enum, _attribute_size, reinterpret_cast<const void*>(_offset));
        }


        _offset += _vertices_count * _attribute_size;
        ++_index;
    }

    for(const auto& _iad : _instance_attribute_descriptors) {
        const auto _component_type = _iad.get_component_type();
        const auto _component_type_enum = gl_attribute_component::to_GLenum(_component_type);
        const auto _components_count = static_cast<GLint>(_iad.get_component_count());
        const auto _attribute_size = _components_count * static_cast<GLint>(gl_attribute_component::get_size(_component_type));
        const auto _divisor = _iad.get_divisor();
        const auto _count = _iad.get_count();

        if (_component_type == gl_attribute_component::type::INT || _component_type == gl_attribute_component::type::UINT) {
            glVertexAttribIPointer(_index, _components_count, _component_type_enum, _attribute_size, reinterpret_cast<const void *>(_offset));
        }
        if (_component_type == gl_attribute_component::type::FLOAT) // original floats
        {
            glVertexAttribPointer(_index, _components_count, _component_type_enum, GL_FALSE, _attribute_size, reinterpret_cast<const void *>(_offset));
        }
        if (_component_type == gl_attribute_component::type::DOUBLE) {
            glVertexAttribLPointer(_index, _components_count, _component_type_enum, _attribute_size, reinterpret_cast<const void *>(_offset));
        }

        glVertexAttribDivisor(_index, _divisor);

        _offset += _attribute_size * _count;
        ++_index;
    }

    _unbind_buffer(); unbind();

#ifdef _DEBUG
	const std::size_t _size = _descriptor->get_layouts().size();
	for (std::size_t i = 0; i < _size; ++i)
	{
		std::cout << "pointer [" << i << "] " << is_pointer_enabled(static_cast<std::uint32_t>(i)) << std::endl;
		std::cout << "attribute components num: " << get_attribute_components_num(static_cast<std::uint32_t>(i)) << std::endl;
		std::cout << "attribute components type: " << get_attribute_component_type(static_cast<std::uint32_t>(i)) << std::endl;
	}
#endif
}

void gl_vertex_array::_reallocate()
{
    if(_buffer)
    {
        _buffer->allocate(_descriptor.get_memory_demand());
    }

    const auto& _vertex_attribute_descriptors = _descriptor.get_vertex_attribute_descriptors();
    const std::uint32_t _vertices_count = _descriptor.get_vertices_count();
    const auto& _instance_attribute_descriptors = _descriptor.get_instance_attribute_descriptors();

    // handle vertex attributes [attribute, vertex_index] - [offset, size]
    std::uint32_t _offset = 0;
    std::uint32_t _vertex_index = 0;
    for(const auto& _vertex_attribute_descriptor : _vertex_attribute_descriptors)
    {
        if(_vertex_index == _vertices_count)
            _vertex_index = 0;

        const auto _attribute_size = gl_attribute_component::get_size(_vertex_attribute_descriptor.get_component_type()) * _vertex_attribute_descriptor.get_component_count();
        const std::string _key = _vertex_attribute_descriptor.get_name() + std::to_string(_vertex_index);
        const std::pair<std::uint32_t, std::uint32_t> _value(_offset, _attribute_size);

        //_anchor_list.emplace(_key, _value);

        _offset += _attribute_size;
        ++_vertex_index;
    }

    // handle instance attributes
    std::uint32_t _instance_attribute_index = 0;
    for(const auto& _instance_attribute_descriptor : _instance_attribute_descriptors)
    {
        if(_instance_attribute_index == _instance_attribute_descriptor.get_count())
            _instance_attribute_index = 0;
        //const auto

        //_anchor_list.emplace()

        ++_instance_attribute_index;
    }

    _buffer->allocate(100);
    _buffer->fill(0, 100, nullptr);
}

void gl_vertex_array::_update_attribute(const std::string &attribute_name, std::uint32_t attribute_index, const std::uint8_t *stream_ptr, size_t size)
{
    const auto& _memory_layout = _descriptor.get_memory_layout();
    const std::string _location = attribute_name + std::to_string(attribute_index);
    auto _it = _memory_layout.find(_location);
    if(_it == _memory_layout.cend()) throw std::exception("can not find [memory layout] : attribute_name or attribute_index invalid ");

    const auto& _offset_size = _it->second;
    if(size != _offset_size.second) throw std::exception("in-size is not correct");

    if(_buffer)
        _buffer->fill(_offset_size.first, _offset_size.second, reinterpret_cast<const void*>(stream_ptr));

}

void gl_vertex_array_descriptor::set_instance_attribute_count(const std::string &attribute_name, std::uint32_t count)
{
    auto _it = std::find_if(_instance_attribute_descriptors.begin(), _instance_attribute_descriptors.end(),[&attribute_name](const gl_instance_attribute_descriptor& descriptor){
        return descriptor.get_name() == attribute_name;
    });
    if(_it == _instance_attribute_descriptors.cend()) return;

    _it->set_count(count);
    _is_dirty = true;
}

void gl_vertex_array_descriptor::set_instance_attribute_divisor(const std::string &attribute_name, std::uint32_t divisor)
{
    auto _it = std::find_if(_instance_attribute_descriptors.begin(), _instance_attribute_descriptors.end(),[&attribute_name](const gl_instance_attribute_descriptor& descriptor){
        return descriptor.get_name() == attribute_name;
    });
    if(_it == _instance_attribute_descriptors.cend()) return;
    _it->set_divisor(divisor);
    _is_dirty = true;
}

void gl_vertex_array_descriptor::set_instances_count(std::uint32_t instances_count)
{
    _instances_count = instances_count;
    _is_dirty = true;
}

void gl_vertex_array_descriptor::set_vertices_count(std::uint32_t vertices_count)
{
    _vertices_count = vertices_count;
    _is_dirty = true;
}

void gl_instance_attribute_descriptor::set_count(std::uint32_t count) {

}

void gl_instance_attribute_descriptor::set_divisor(std::uint32_t divisor) {

}
