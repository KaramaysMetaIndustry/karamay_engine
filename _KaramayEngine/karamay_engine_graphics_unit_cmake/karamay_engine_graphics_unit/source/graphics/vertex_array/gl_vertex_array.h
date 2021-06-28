#ifndef H_GL_VERTEX_ARRAY
#define H_GL_VERTEX_ARRAY

#include "graphics/glo/gl_object.h"
#include "graphics/variable/glv_types.h"


class gl_buffer;

namespace gl_vertex_attribute_component
{
    enum class type
    {
        UNKNOWN = 0,

        INT = GL_INT,
        UNSIGNED_INT = GL_UNSIGNED_INT,
        FLOAT = GL_FLOAT,
        DOUBLE = GL_DOUBLE
    };

    std::string to_string(gl_vertex_attribute_component::type component_type)
    {
        switch(component_type)
        {
            case gl_vertex_attribute_component::type::INT: return "INT";
            case gl_vertex_attribute_component::type::UNSIGNED_INT: return "UNSIGNED_INT";
            case gl_vertex_attribute_component::type::FLOAT: return "FLOAT";
            case gl_vertex_attribute_component::type::DOUBLE: return "DOUBLE";
            default: return "UNKNOWN";
        }
    }

    gl_vertex_attribute_component::type to_enum(const std::string& component_type)
    {
        if(component_type == "INT") return gl_vertex_attribute_component::type::INT;
        if(component_type == "UNSIGNED_INT") return gl_vertex_attribute_component::type::UNSIGNED_INT;
        if(component_type == "FLOAT") return gl_vertex_attribute_component::type::FLOAT;
        if(component_type == "DOUBLE") return gl_vertex_attribute_component::type::DOUBLE;
        return gl_vertex_attribute_component::type::UNKNOWN;
    }

    GLenum to_GLenum(gl_vertex_attribute_component::type component_type)
    {
        return static_cast<GLenum>(component_type);
    }
}


struct gl_vertex_attribute_descriptor
{
    std::string name;

    gl_vertex_attribute_component::type component_type;

    std::uint8_t normalized;

    std::uint32_t components_count;

    std::uint32_t divisor;

    gl_vertex_attribute_descriptor() :
        name(),
        component_type(gl_vertex_attribute_component::type::UNKNOWN),
        normalized(false),
        components_count(0),
        divisor(0)
    {}
};



class gl_vertex_array_descriptor final
{
public:
    gl_vertex_array_descriptor(std::uint32_t vertices_count, std::uint32_t instances_count) :
        _vertices_count(vertices_count)
    {
//        gl_vertex_array_descriptor _vertex_array_descriptor(100, 10);
//        _vertex_array_descriptor.add_attribute_descriptor<glv::i32vec3>("position");
//        _vertex_array_descriptor.add_attribute_descriptor<glv::i32vec4>("color");
//        _vertex_array_descriptor.add_attribute_descriptor<glv::i32vec2>("uv");
//        _vertex_array_descriptor.add_attribute_descriptor<glv::i32vec3>("instance_position_offset", 3);
//
//        _vertex_array_descriptor.add_normalized_attribute_descriptor<glv::f32vec4>("");
    }


private:

    std::uint32_t _vertices_count;

    std::vector<gl_vertex_attribute_descriptor> _vertex_attribute_descriptors;

public:

	template<typename T>
	void add_attribute_descriptor(const std::string& attribute_name, std::uint32_t divisor = 0)
	{
		{
			static_assert(
				std::is_same<glv::int32, T>::value ||std::is_same<glv::i32vec2, T>::value ||
				std::is_same<glv::i32vec3, T>::value ||std::is_same<glv::i32vec4, T>::value ||

				std::is_same<glv::uint32, T>::value ||std::is_same<glv::ui32vec2, T>::value ||
				std::is_same<glv::ui32vec3, T>::value ||std::is_same<glv::ui32vec4, T>::value ||

				std::is_same<glv::float32, T>::value ||std::is_same<glv::f32vec2, T>::value ||
				std::is_same<glv::f32vec3, T>::value ||std::is_same<glv::f32vec4, T>::value ||

				std::is_same<glv::float64, T>::value ||std::is_same<glv::f64vec2, T>::value ||
				std::is_same<glv::f64vec3, T>::value ||std::is_same<glv::f64vec4, T>::value ||

				std::is_same<glv::f32mat2, T>::value ||std::is_same<glv::f32mat2x3, T>::value ||std::is_same<glv::f32mat2x4, T>::value ||
				std::is_same<glv::f32mat3, T>::value ||std::is_same<glv::f32mat3x2, T>::value ||std::is_same<glv::f32mat3x4, T>::value ||
				std::is_same<glv::f32mat4, T>::value ||std::is_same<glv::f32mat4x2, T>::value ||std::is_same<glv::f32mat4x3, T>::value ||

				std::is_same<glv::f64mat2, T>::value ||std::is_same<glv::f64mat2x3, T>::value ||std::is_same<glv::f64mat2x4, T>::value ||
				std::is_same<glv::f64mat3, T>::value ||std::is_same<glv::f64mat3x2, T>::value ||std::is_same<glv::f64mat3x4, T>::value ||
				std::is_same<glv::f64mat4, T>::value ||std::is_same<glv::f64mat4x2, T>::value ||std::is_same<glv::f64mat4x3, T>::value
				, "T must be glv::i/ui/f32* or glv::f64* types.");
		}

        gl_vertex_attribute_descriptor _vertex_attribute_descriptor;
	    _vertex_attribute_descriptor.name = attribute_name;
		_vertex_attribute_descriptor.component_type = _get_component_type<typename T::value_type>();
        _vertex_attribute_descriptor.components_count = static_cast<std::uint32_t>(T::length());
		_vertex_attribute_descriptor.divisor = divisor;
		_vertex_attribute_descriptor.normalized = false;
		_vertex_attribute_descriptors.push_back(_vertex_attribute_descriptor);
	}

	template<typename T>
	void add_normalized_attribute_descriptor(const std::string& attribute_name, std::uint32_t divisor = 0)
	{
		{
			static_assert(
				std::is_same<glv::int32, T>::value ||std::is_same<glv::i32vec2, T>::value ||
				std::is_same<glv::i32vec3, T>::value ||std::is_same<glv::i32vec4, T>::value ||
				std::is_same<glv::uint32, T>::value ||std::is_same<glv::ui32vec2, T>::value ||
				std::is_same<glv::ui32vec3, T>::value ||std::is_same<glv::ui32vec4, T>::value
				, "T must be glv::i32* or glv::ui32* types.");
		}

        gl_vertex_attribute_descriptor _vertex_attribute_descriptor;
	    _vertex_attribute_descriptor.name = attribute_name;
        _vertex_attribute_descriptor.component_type = _get_component_type<typename T::value_type>();
        _vertex_attribute_descriptor.components_count = static_cast<std::uint32_t>(T::length());
        _vertex_attribute_descriptor.divisor = divisor;
        _vertex_attribute_descriptor.normalized = true;
        _vertex_attribute_descriptors.push_back(_vertex_attribute_descriptor);
	}

	const auto& get_attribute_descriptors() const { return _vertex_attribute_descriptors; }

private:

    template<typename T>
    gl_vertex_attribute_component::type _get_component_type()
    {
        return gl_vertex_attribute_component::type::UNKNOWN;
    }

    template<>
    gl_vertex_attribute_component::type _get_component_type<typename glv::i32vec4::value_type>()
    {
        return gl_vertex_attribute_component::type::INT;
    }

    template<>
    gl_vertex_attribute_component::type _get_component_type<typename glv::ui32vec4::value_type>()
    {
        return gl_vertex_attribute_component::type::UNSIGNED_INT;
    }

    template<>
    gl_vertex_attribute_component::type _get_component_type<typename glv::f32vec4::value_type>()
    {
        return gl_vertex_attribute_component::type::FLOAT;
    }

    template<>
    gl_vertex_attribute_component::type _get_component_type<typename glv::f64vec4::value_type>()
    {
        return gl_vertex_attribute_component::type::DOUBLE;
    }

};


class gl_vertex_array final : public gl_object
{
public:

	explicit gl_vertex_array(std::shared_ptr<gl_vertex_array_descriptor> descriptor);

    ~gl_vertex_array() override;

public:

    void allocate(const gl_vertex_array_descriptor& _vertex_array_descriptor)
    {

    }

    template<typename T>
    void update_attribute(const std::string& attribute_name, std::uint32_t attribute_index, const T& attribute) noexcept
    {
        try {
            _check(attribute_name, attribute_index);
        } catch (std::exception& e) {
            std::cout<<e.what()<<std::endl;
        }

        const auto _stream_ptr = reinterpret_cast<const std::uint8_t*>(glm::value_ptr(attribute));
        if(_stream_ptr)
            _update_attribute(attribute_name, attribute_index, _stream_ptr, sizeof(T));
    }

private:

    std::shared_ptr<gl_vertex_array_descriptor> _descriptor;

    std::shared_ptr<gl_buffer> _buffer;

    void _update_attribute(const std::string& attribute_name, std::uint32_t attribute_index, const std::vector<std::uint8_t>& stream)
    {}
    void _update_attribute(const std::string& attribute_name, std::uint32_t attribute_index, const std::uint8_t* stream_ptr, size_t size);

    void _check(const std::string& attribute_name, std::uint32_t attribute_index)
    {
        const auto& _attribute_descriptors = _descriptor->get_attribute_descriptors();
        bool found = false;
        for(const auto& _attribute_descriptor : _attribute_descriptors)
        {
            if(_attribute_descriptor.name == attribute_name) {

            }
        }



        throw std::exception("attribute_name not exist");
        throw std::exception("attribute_index not exist");
    }

    void _bind_buffer();

    void _unbind_buffer();

    void _fill();

public:

	void bind();

	void unbind();

	void enable_pointers();

	void disable_pointers();

public:
	// default false
	bool is_pointer_enabled(std::uint32_t index);
	// default is 4
	std::uint32_t get_attribute_components_num(std::uint32_t index);
	// default is GL_FLOAT
	std::string get_attribute_component_type(std::uint32_t index);

	void* get_mapped_data();

	const std::int32_t get_size() const;


};

#endif
