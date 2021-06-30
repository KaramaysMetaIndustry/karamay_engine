#ifndef H_GL_VERTEX_ARRAY
#define H_GL_VERTEX_ARRAY

#include "graphics/glo/gl_object.h"
#include "graphics/variable/glv_types.h"

class gl_buffer;

namespace gl_attribute_component
{
    enum class type : GLenum
    {
        UNKNOWN = 0,
        INT = GL_INT,
        UINT = GL_UNSIGNED_INT,
        FLOAT = GL_FLOAT,
        DOUBLE = GL_DOUBLE
    };

    std::string to_string(gl_attribute_component::type component_type)
    {
        switch(component_type)
        {
            case gl_attribute_component::type::INT: return "INT";
            case gl_attribute_component::type::UINT: return "UINT";
            case gl_attribute_component::type::FLOAT: return "FLOAT";
            case gl_attribute_component::type::DOUBLE: return "DOUBLE";
            default: return "UNKNOWN";
        }
    }

    gl_attribute_component::type to_enum(const std::string& component_type)
    {
        if(component_type == "INT") return gl_attribute_component::type::INT;
        if(component_type == "UINT") return gl_attribute_component::type::UINT;
        if(component_type == "FLOAT") return gl_attribute_component::type::FLOAT;
        if(component_type == "DOUBLE") return gl_attribute_component::type::DOUBLE;
        return gl_attribute_component::type::UNKNOWN;
    }

    GLenum to_GLenum(gl_attribute_component::type component_type)
    {
        return static_cast<GLenum>(component_type);
    }

    std::uint32_t get_size(gl_attribute_component::type component_type)
    {
        switch (component_type) {
            case type::INT: return sizeof(std::int32_t);
            case type::UINT: return sizeof(std::uint32_t);
            case type::FLOAT: return sizeof(std::float_t);
            case type::DOUBLE: return sizeof(std::double_t);
            default: return 0;
        }
    }
}

class gl_vertex_attribute_descriptor
{
public:

    gl_vertex_attribute_descriptor(
            std::uint32_t component_count,
            gl_attribute_component::type component_type,
            const std::string& name
            ) :
            _name(name),
            _component_type(component_type),
            _components_count(component_count)
    {}

private:

    std::string _name;

    gl_attribute_component::type _component_type;

    std::uint32_t _components_count;

public:

    [[nodiscard]] const std::string& get_name() const {return _name;}

    [[nodiscard]] gl_attribute_component::type get_component_type() const {return _component_type;}

    [[nodiscard]] std::uint32_t get_component_count() const {return _components_count;}

};

class gl_instance_attribute_descriptor
{
public:

    gl_instance_attribute_descriptor(
            std::uint32_t component_count,
            gl_attribute_component::type component_name,
            const std::string& name,
            std::uint32_t count,
            std::uint32_t instance_divisor) :
            _name(name),
            _component_type(component_name),
            _components_count(component_count),
            _divisor(instance_divisor),
            _count(count)
    {}

private:

    std::string _name;

    gl_attribute_component::type _component_type;

    std::uint32_t _components_count;

    std::uint32_t _divisor;

    std::uint32_t _count;

public:

    [[nodiscard]] const std::string& get_name() const {return _name;}

    [[nodiscard]] gl_attribute_component::type get_component_type() const {return _component_type;}

    [[nodiscard]] std::uint32_t get_component_count() const {return _components_count;}

    [[nodiscard]] std::uint32_t get_divisor() const {return _divisor;}

    [[nodiscard]] std::uint32_t get_count() const {return _count;}

public:

    void set_divisor(std::uint32_t divisor);

    void set_count(std::uint32_t count);

};


class gl_vertex_array_descriptor final
{
public:
    gl_vertex_array_descriptor(
            const std::vector<gl_vertex_attribute_descriptor>& vertex_attribute_descriptors,
            std::uint32_t vertices_count,
            const std::vector<gl_instance_attribute_descriptor>& instance_attribute_descriptors,
            std::uint32_t instances_count) :
            _is_dirty(true),
            _vertex_attribute_descriptors(vertex_attribute_descriptors),
            _vertices_count(vertices_count),
            _instance_attribute_descriptors(instance_attribute_descriptors),
            _instances_count(instances_count)
    {
        std::uint32_t _index = 0;
        for(const auto& _vertex_attribute_descriptor : _vertex_attribute_descriptors)
        {
            _vertex_attribute_descriptors_map.emplace(_vertex_attribute_descriptor.get_name(), _index);
            ++_index;
        }

        _index = 0;
        for(const auto& _instance_attribute_descriptor : _instance_attribute_descriptors)
        {
            _instance_attribute_descriptors_map.emplace(_instance_attribute_descriptor.get_name(), _index);
            ++_index;
        }
    }

    gl_vertex_array_descriptor(
            const std::vector<gl_vertex_attribute_descriptor>& vertex_attribute_descriptors,
            std::uint32_t vertices_count) :
            _is_dirty(true),
            _vertex_attribute_descriptors(vertex_attribute_descriptors),
            _vertices_count(vertices_count),
            _instance_attribute_descriptors(),
            _instances_count(0)
    {}

public:

    void set_vertices_count(std::uint32_t vertices_count);

    void set_instances_count(std::uint32_t instances_count);

    void set_instance_attribute_divisor(const std::string& attribute_name, std::uint32_t divisor);

    void set_instance_attribute_count(const std::string& attribute_name, std::uint32_t count);

private:

    std::uint8_t _is_dirty;

private:

    std::uint32_t _vertices_count;

    std::uint32_t _instances_count;

    std::vector<gl_vertex_attribute_descriptor> _vertex_attribute_descriptors;

    std::vector<gl_instance_attribute_descriptor> _instance_attribute_descriptors;

private:

    std::unordered_map<std::string, std::uint32_t> _vertex_attribute_descriptors_map;

    std::unordered_map<std::string, std::uint32_t> _instance_attribute_descriptors_map;

    std::unordered_map<std::string, std::pair<std::uint32_t, std::uint32_t>> _memory_layout;

    std::size_t _memory_demand;

public:

    [[nodiscard]] std::uint8_t is_dirty() const { return _is_dirty; }

public:

    [[nodiscard]] std::uint32_t get_vertices_count() const {return _vertices_count;}

    [[nodiscard]] std::uint32_t get_instance_count() const {return _instances_count;}

    [[nodiscard]] const std::vector<gl_vertex_attribute_descriptor>& get_vertex_attribute_descriptors() const {return _vertex_attribute_descriptors;}

    [[nodiscard]] const std::vector<gl_instance_attribute_descriptor>& get_instance_attribute_descriptors() const {return _instance_attribute_descriptors;}

public:

    [[nodiscard]] std::size_t get_memory_demand() const {return _memory_demand;}

    std::pair<std::uint32_t, std::uint32_t> get_memory_layout(const std::string attribute_name, std::uint32_t attribute_index)
    {

    }


private:

    inline auto _find_vertex_attribute_descriptor(const std::string& attribute_name)
    {
        return std::find(_vertex_attribute_descriptors.begin(), _vertex_attribute_descriptors.end(), [&attribute_name](gl_vertex_attribute_descriptor& descriptor){return descriptor.get_name() == attribute_name;});
    }

};


class gl_vertex_array final : public gl_object
{
public:

	explicit gl_vertex_array(const gl_vertex_array_descriptor& descriptor)
    {
        _descriptor = descriptor;
        glCreateVertexArrays(1, &_handle);
    }

    ~gl_vertex_array() override;

private:

    gl_vertex_array_descriptor _descriptor;

    std::shared_ptr<gl_buffer> _buffer;

public:

    [[nodiscard]] const gl_vertex_array_descriptor& get_vertex_array_descriptor() const {return _descriptor;}

public:

    void set_vertices_count(std::uint32_t vertices_count)
    {
       _descriptor.set_vertices_count(vertices_count);
    }

    void set_instances_count(std::uint32_t instances_count)
    {
        _descriptor.set_instances_count(instances_count);
    }

    void set_instance_attribute_divisor(const std::string& attribute_name, std::uint32_t divisor)
    {
        _descriptor.set_instance_attribute_divisor(attribute_name, divisor);
    }

    void set_instance_attribute_count(const std::string& attribute_name, std::uint32_t count)
    {
        _descriptor.set_instance_attribute_count(attribute_name, count);
    }

public:

    template<typename T>
    void update_attribute(const std::string& attribute_name, std::uint32_t attribute_index, const T& value) noexcept
    {
        const auto _stream_ptr = reinterpret_cast<const std::uint8_t*>(glm::value_ptr(value));

        if(_stream_ptr)
        {
            try {
                _update_attribute(attribute_name, attribute_index, _stream_ptr, sizeof(T));
            }catch (std::exception& e)
            {
                std::cout<<e.what()<<std::endl;
            }
        }
    }

private:

    void _reallocate();

    void _update_attribute(const std::string& attribute_name, std::uint32_t vertex_index, const std::uint8_t* stream_ptr, size_t size);

    void _fill();

    void _bind_buffer();

    void _unbind_buffer();

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

	[[nodiscard]] const std::int32_t get_size() const;


private:

    template<typename T>
    gl_attribute_component::type _get_component_type()
    {
        return gl_attribute_component::type::UNKNOWN;
    }

    template<>
    gl_attribute_component::type _get_component_type<typename glv::i32vec4::value_type>()
    {
        return gl_attribute_component::type::INT;
    }

    template<>
    gl_attribute_component::type _get_component_type<typename glv::ui32vec4::value_type>()
    {
        return gl_attribute_component::type::UINT;
    }

    template<>
    gl_attribute_component::type _get_component_type<typename glv::f32vec4::value_type>()
    {
        return gl_attribute_component::type::FLOAT;
    }

    template<>
    gl_attribute_component::type _get_component_type<typename glv::f64vec4::value_type>()
    {
        return gl_attribute_component::type::DOUBLE;
    }


};

#endif
