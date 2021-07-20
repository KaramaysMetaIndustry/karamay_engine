#include "gl_uniform_buffer.h"
#include "graphics/program/gl_program.h"

std::unordered_map<std::string, std::int64_t> gl_uniform_buffer::_glsl_type_size_map = {
        {"float", sizeof(glsl_float)},
        {"vec2", sizeof(glsl_vec2)},
        {"vec3", sizeof(glsl_vec3)},
        {"vec4", sizeof(glsl_vec4)},
        {"double", sizeof(glsl_double)},
        {"dvec2", sizeof(glsl_dvec2)},
        {"dvec3", sizeof(glsl_dvec3)},
        {"dvec4", sizeof(glsl_dvec4)},

        {"int", sizeof(glsl_int)},
        {"ivec2", sizeof(glsl_ivec2)},
        {"ivec3", sizeof(glsl_ivec3)},
        {"ivec4", sizeof(glsl_ivec4)},
        {"uint", sizeof(glsl_uint)},
        {"uvec2", sizeof(glsl_uvec2)},
        {"uvec3", sizeof(glsl_uvec3)},
        {"uvec4", sizeof(glsl_uvec4)},

        {"mat2", sizeof(glsl_mat2)},
        {"mat2x3", sizeof(glsl_mat2x3)},
        {"mat2x4", sizeof(glsl_mat2x4)},
        {"mat3", sizeof(glsl_mat3)},
        {"mat3x2", sizeof(glsl_mat3x2)},
        {"mat3x4", sizeof(glsl_mat3x4)},
        {"mat4", sizeof(glsl_mat4)},
        {"mat4x2", sizeof(glsl_mat4x2)},
        {"mat4x3", sizeof(glsl_mat4x3)},

        {"dmat2", sizeof(glsl_dmat2)},
        {"dmat2x3", sizeof(glsl_dmat2x3)},
        {"dmat2x4", sizeof(glsl_dmat2x4)},
        {"dmat3", sizeof(glsl_dmat3)},
        {"dmat3x2", sizeof(glsl_dmat3x2)},
        {"dmat3x4", sizeof(glsl_dmat3x4)},
        {"dmat4", sizeof(glsl_dmat4)},
        {"dmat4x2", sizeof(glsl_dmat4x2)},
        {"dmat4x3", sizeof(glsl_dmat4x3)}
};

void gl_uniform_buffer::bind(std::uint32_t binding)
{
    if(_public_buffer)
    {
        glBindBufferRange(GL_UNIFORM_BUFFER, binding, _public_buffer->get_handle(), _uniform_buffer_offset, _uniform_buffer_size);
        gl_buffer::_throw_errors("glBindBufferRange");
        _binding = binding;
    }
#ifdef _DEBUG
    std::cout << "uniform buffers [ "<< _block_name <<"]" << std::endl;
    std::cout << "binding: " << _binding <<std::endl;
    std::cout << "offset: " << _uniform_buffer_offset<<std::endl;
    std::cout << "size: " << _uniform_buffer_size<<std::endl;
#endif
}

void gl_uniform_buffer::unbind()
{
	glBindBufferRange(GL_UNIFORM_BUFFER, _binding, 0, 0, 0);
	_binding = 0;
}

void gl_uniform_buffer::_generate_packed_memory(const std::vector<std::pair<std::string, std::string>> &rows)
{
    if (_owner.lock())
    {
    }
}

void gl_uniform_buffer::_generate_shared_memory(const std::vector<std::pair<std::string, std::string>> &rows)
{
    if(_owner.lock())
    {
        GLuint al = GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT;
        _uniform_buffer_offset = _public_buffer->get_size();
        _uniform_buffer_size = _owner.lock()->get_uniform_buffer_block_size(_block_name);
        for(const auto& row : rows)
        {
            std::int64_t _offset = _uniform_buffer_offset + _owner.lock()->get_uniform_buffer_item_offset(row.second);
            auto _attribute_size = _glsl_type_size_map.find(row.first)->second;
            _attribute_layout.emplace(row.second, std::pair<std::int64_t, std::int64_t>(_offset, _attribute_size));
        }
        // place the public buffers
        _public_buffer->push_back('0', _uniform_buffer_size);
    }
}
