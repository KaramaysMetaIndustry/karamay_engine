#ifndef H_GL_UNIFORM_BUFFER
#define H_GL_UNIFORM_BUFFER

#include "graphics/variable/gl_variable.h"
#include "graphics/buffer/gl_buffer.h"
class gl_program;
class gl_buffer;


namespace gl_uniform_buffer_enum
{
	enum class layout
	{
		std140,
		shared,
		packed,
	};

	enum class matrix_layout
	{
		row_major,
		column_major
	};

	enum class reference_style
	{
		global,
		instanced,
		array_instanced,
	};

	enum class reference_shader
	{
		vertex_shader,
		tessc_shader,
		tesse_shader,
		geom_shader,
		fragment_shader
	};

}

enum class gl_uniform_buffer_layout
{
    std140,
    shared,
    packed,
};

#define STATIC_ASSERT_UNIFORM_T()



class gl_uniform_buffer final
{
    static std::unordered_map<std::string, std::int64_t> _glsl_type_size_map;

public:
	
	gl_uniform_buffer(std::shared_ptr<gl_program>& owner,
                      const std::string& block_name, gl_uniform_buffer_layout layout, const std::vector<std::pair<std::string, std::string>>& rows) :
            _owner(owner),
            _block_name(block_name),
	        _uniform_buffer_size(0),
	        _binding(0)
    {
        _generate_memory_layout(layout, rows);
    }

    ~gl_uniform_buffer() = default;

private:

    std::weak_ptr<gl_program> _owner;

    std::shared_ptr<gl_buffer> _buffer;

    std::string _block_name;

    std::unordered_map<std::string, std::pair<std::int64_t, const glsl_transparent_type_meta*>> _attribute_layout;

    std::int64_t _uniform_buffer_offset, _uniform_buffer_size;

    std::uint32_t _binding;

public:

	template<typename GLSL_TRANSPARENT_T>
	void update_uniform(const std::string& name, const GLSL_TRANSPARENT_T& value)
    {
        STATIC_ASSERT_UNIFORM_T();

    }

    /*
     * must check offset, type
     * */
    void update_uniform(const std::string& name, const glsl_transparent_type* value)
    {
        if(_buffer && value)
        {
            auto _it = _attribute_layout.find(name);
            const glsl_transparent_type_meta* _meta = _it->second.second;
            if(_meta && _it != _attribute_layout.cend() && value->meta() == *_meta)
            {
                _buffer->write(_it->second.first, value->data(), _meta->type_size);
            }
        }
    }

public:

    [[nodiscard]] const std::string& block_name() const{return _block_name;}

    [[nodiscard]] std::int64_t uniform_buffer_offset() const {return _uniform_buffer_offset;}

    [[nodiscard]] std::int64_t uniform_buffer_size() const {return _uniform_buffer_size;}

    const auto& get_attribute_layout()
    {
        return _attribute_layout;
    }


    void bind(std::uint32_t binding);

    void unbind();

private:

    void _generate_std140_memory(const std::vector<std::pair<std::string, std::string>>& rows)
    {
        // fetch a uniform buffer offset from the public buffer
        _uniform_buffer_offset = _public_buffer->get_size();
        std::int64_t _offset = _uniform_buffer_offset;
        for(const auto& row : rows)
        {
            auto _attribute_size = _glsl_type_size_map.find(row.first)->second;
            _attribute_layout.emplace(row.second, std::pair<std::int64_t, std::int64_t>(_offset, _attribute_size));
            _uniform_buffer_size += _attribute_size; // calculate the uniform buffer size
            _offset += _attribute_size;
        }
        // place the public buffer
        _public_buffer->push_back('0', _uniform_buffer_size);
    }

    void _generate_shared_memory(const std::vector<std::pair<std::string, std::string>>& rows);

    void _generate_packed_memory(const std::vector<std::pair<std::string, std::string>>& rows);

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
        }
    }

};

#endif