#ifndef H_GL_UNIFORM_BUFFER
#define H_GL_UNIFORM_BUFFER

#include "graphics/type/glsl.h"
#include "graphics/buffers/buffer/gl_buffer.h"


class gl_program;
class gl_buffer;


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

class gl_uniform_buffer final
{
public:
	
	gl_uniform_buffer(std::shared_ptr<gl_program>& owner,
                      gl_uniform_buffer_layout layout, std::string block_name, const std::vector<std::pair<std::string, std::string>>& rows,
                      std::uint32_t instances_count) :
            _owner(owner),
            _block_name(std::move(block_name)),
            _instances_count(instances_count),
	        _uniform_buffer_size(0)
    {
	    if(_check_uniform_validation()) _generate_memory_layout(layout, rows);
    }

    ~gl_uniform_buffer() = default;

private:

    std::weak_ptr<gl_program> _owner;

    std::shared_ptr<gl_buffer> _buffer;

    std::uint32_t _instances_count;

    std::string _block_name;

    std::int64_t _uniform_buffer_size;

    std::vector<std::tuple<std::string, const glsl_transparent_clazz*, std::int64_t>> _attribute_layout;

    std::uint32_t _context_binding{};

public:

	template<typename GLSL_TRANSPARENT_T>
	void update_uniform(const std::string& name, const GLSL_TRANSPARENT_T& value)
    {
        if(_buffer)
        {
            for(const auto& _attribute_anchor : _attribute_layout)
            {
                const auto* _clazz = _attribute_anchor
                if(_clazz && _clazz->class_name == name && value.clazz() == _clazz)
                {
                    _buffer->write(_attribute_anchor.second, value.stream(), _clazz->class_size);
                    break;
                }
            }
        }
    }

    void update_uniform(const std::string& name, const glsl_transparent_class* value)
    {
        if(value && _buffer)
        {
            for(const auto& _attribute_anchor : _attribute_layout)
            {
                const auto* _clazz = _attribute_anchor.first;
                if(_clazz && _clazz->class_name == name && value->clazz() == _clazz)
                {
                    _buffer->write(_attribute_anchor.second, value->stream(), _clazz->class_size);
                    break;
                }
            }
        }
    }

public:

    [[nodiscard]] const std::string& block_name() const{return _block_name;}

    [[nodiscard]] std::int64_t uniform_buffer_size() const {return _uniform_buffer_size;}

    [[nodiscard]] const auto& get_attribute_layout() const { return _attribute_layout; }

    void bind(std::uint32_t binding);

    void unbind();

private:

    bool _check_uniform_validation()
    {
        return false;
    }

    void _generate_memory_layout(gl_uniform_buffer_layout layout, const std::vector<std::pair<std::string, std::string>>& rows)
    {
        switch (layout) {
            case gl_uniform_buffer_layout::std140:
                _generate_std140_memory(rows);
                break;
            case gl_uniform_buffer_layout::shared:
                _generate_shared_memory(rows);
                break;
            case gl_uniform_buffer_layout::packed:
                _generate_packed_memory(rows);
                break;
            default: break;
        }
    }

    void _generate_std140_memory(const std::vector<std::pair<std::string, std::string>>& rows)
    {
        std::int64_t _offset = 0;
        for(const auto& row : rows)
        {
            auto _attribute_size = _glsl_type_size_map.find(row.first)->second;
            _attribute_layout.emplace(row.second, std::pair<std::int64_t, std::int64_t>(_offset, _attribute_size));
            _uniform_buffer_size += _attribute_size; // calculate the uniform buffers size
            _offset += _attribute_size;
        }


    }

    void _generate_shared_memory(const std::vector<std::pair<std::string, std::string>>& rows);

    void _generate_packed_memory(const std::vector<std::pair<std::string, std::string>>& rows);

};

#endif