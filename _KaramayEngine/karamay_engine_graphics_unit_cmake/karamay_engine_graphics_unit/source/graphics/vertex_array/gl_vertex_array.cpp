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
	return nullptr;
}

const std::int32_t gl_vertex_array::get_size() const
{
	return _buffer->get_size();
}

gl_vertex_array::~gl_vertex_array()
{
    //~gl_object();
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
    const std::size_t _size = _descriptor.get_vertex_attribute_descriptors().size()  + _descriptor.get_instance_attribute_descriptors().size();
    for(std::uint32_t _index = 0; _index < _size; ++_index)
    {
        glEnableVertexAttribArray(_index);
    }
}

void gl_vertex_array::disable_pointers()
{
    const std::size_t _size = _descriptor.get_vertex_attribute_descriptors().size()  + _descriptor.get_instance_attribute_descriptors().size();
    for(std::uint32_t _index = 0; _index < _size; ++_index)
    {
        glDisableVertexAttribArray(_index);
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

void gl_vertex_array::_reallocate()
{
    const auto& _vertex_attribute_descriptors = _descriptor.get_vertex_attribute_descriptors();
    const auto& _instance_attribute_descriptors = _descriptor.get_instance_attribute_descriptors();
    const auto _vertices_count = _descriptor.get_vertices_count();

    // recalculate memory_size & memory_layout
    // reallocate buffer & reset attrib pointers

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

    if(!_buffer)
    {
        _buffer = std::make_shared<gl_buffer>();
    }

    _buffer->allocate(_memory_demand);

    bind(); _bind_buffer();


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

void gl_vertex_array::_update_attribute(const std::string &attribute_name, std::uint32_t attribute_index, const std::vector<std::uint8_t>& stream)
{
    // if descriptor has been modified, the [_reallocate] will be called right now
    // [_reallocate] will generate new [_memory_demand] & [_memory_layouts_map], also reset the vertex array pointers
    if(_descriptor.is_dirty())
    {
        _reallocate(); _descriptor.dismiss_dirty();
    }

    // fetch precise offset-size pair, then fill the buffer with the specified data
    const auto& _memory_layout = _get_memory_layout(attribute_name, attribute_index);
    if(_buffer && _check_memory_layout(_memory_layout) && stream.size() == _memory_layout.second) // check [_buffer] && check the [_memory_layout] && check stream size
    {
        //            :offset               :size                  :data
        _buffer->fill(_memory_layout.first, _memory_layout.second, reinterpret_cast<const void*>(stream.data()));
    }
}

void gl_vertex_array::update_attribute(const std::string &attribute_name, std::uint32_t attribute_index,
                                       const std::vector<std::uint8_t> &stream) noexcept {
    _update_attribute(attribute_name, attribute_index, stream);
}

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

std::pair<std::uint32_t, std::uint32_t>
gl_vertex_array::_get_memory_layout(const std::string &attribute_name, std::uint32_t attribute_index) {
    auto _it = _memory_layouts_map.find(attribute_name + std::to_string(attribute_index));
    if(_it == _memory_layouts_map.cend()) return std::make_pair(0, 0);

    return _it->second;
}

std::uint8_t gl_vertex_array::_check_memory_layout(const std::pair<std::uint32_t, std::uint32_t> &memory_layout) {
    return !(memory_layout.first == 0 && memory_layout.first == memory_layout.second);
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

    if( (_instances_count % divisor) != 0) return;

    _it->set_divisor(divisor);
    _it->set_count(_instances_count / divisor);
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

void gl_vertex_array_descriptor::dismiss_dirty()
{
    _is_dirty = false;
}

void gl_instance_attribute_descriptor::set_count(std::uint32_t count)
{
    _count = count;
}

void gl_instance_attribute_descriptor::set_divisor(std::uint32_t divisor)
{
    _divisor = divisor;
}
