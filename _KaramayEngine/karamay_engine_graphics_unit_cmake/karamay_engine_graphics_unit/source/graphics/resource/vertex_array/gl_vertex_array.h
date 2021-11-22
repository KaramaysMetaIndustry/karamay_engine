#ifndef H_GL_VERTEX_ARRAY
#define H_GL_VERTEX_ARRAY

#include "graphics/resource/glo/gl_object.h"
#include "graphics/glsl/interface_block/glsl_in_block.h"
#include "graphics/resource/buffers/common_buffer/gl_array_buffer.h"

enum class gl_attribute_component_type
{
    UINT,
    INT,
    FLOAT,
    UINT_TO_FLOAT,
    DOUBLE,
};

struct gl_vertex_attribute_descriptor 
{
    std::string attribute_name; // BaseColor
    uint32 attribute_size; // sizeof(glm::vec4)
    uint32 components_num; // 4
    gl_attribute_component_type component_type; // FLOAT
};

struct gl_vertex_descriptor
{
    std::vector<gl_vertex_attribute_descriptor> attribute_descriptors;
};

struct gl_instance_attribute_descriptor
{
    std::string attribute_name; // InstancePositionOffset
    uint32 attribute_size; // sizeof(glm::vec3)
    uint32 components_num; // 3
    gl_attribute_component_type component_type; // FLOAT
   uint32 attributes_num; // 10
   uint32 divisor; // 3 每渲染3个instances换一个attribute，总共有10种可以换
};

struct gl_vertex_array_descriptor
{
    uint32 vertices_num; // 1024
    gl_vertex_descriptor vertex_descriptor; // {...}
    std::vector<gl_instance_attribute_descriptor> instance_attribute_descriptors; // {...}
};

/*
 * Dynamic Storage :
 *
 * [          ] [vertex*] [vertex*] [vertex*] [vertex*]
 * 
 * [InstanceAttribute*] [       ] [       ] [      ] [.......]
 * 
 * [InstanceAttribute*] [       ] [       ] [      ] [.......]
 * 
 *
 * */
class gl_vertex_array final : public gl_object {
public:
    
    using vertex_slot_reader = std::function<void(const void*, uint32)>;
    using vertex_slot_writer = std::function<void(void*, uint32)>;
    using vertex_slot_handler = std::function<void(void*, uint32)>;
    using instance_attribute_slot_reader = std::function<void(const void*, uint32)>;
    using instance_attribute_slot_writer = std::function<void(void*, uint32)>;
    using instance_attribute_slot_handler = std::function<void(void*, uint32)>;

    gl_vertex_array(const gl_vertex_array_descriptor& descriptor) :
        gl_object(gl_object_type::VERTEX_ARRAY_OBJ)
    {
        glCreateVertexArrays(1, &_handle);

        _internal_descriptor.vertices_num = descriptor.vertices_num;
        
        uint32 _attribute_index = 0;
        uint32 _vertex_size = 0;

        for (const auto& _vertex_attribute_descriptor : descriptor.vertex_descriptor.attribute_descriptors)
        {
            gl_internal_vertex_attribute_descriptor _internal_vertex_attribute_descriptor;
            _internal_vertex_attribute_descriptor.attribute_index = _attribute_index;
            _internal_vertex_attribute_descriptor.initial_descriptor = _vertex_attribute_descriptor;
            _internal_descriptor.vertex_descriptor.attribute_descriptors.push_back(_internal_vertex_attribute_descriptor);
            
            _vertex_size += _vertex_attribute_descriptor.attribute_size;
            ++_attribute_index;
        }

        _internal_descriptor.vertex_descriptor.vertex_size = _vertex_size;
        _internal_descriptor.vertex_descriptor.vertex_buffer = new gl_array_buffer(_internal_descriptor.vertices_num * _vertex_size);
        _AllocateVertices();
        
        // InstanceAttributes
        for (const auto& _instance_attribute_descriptor : descriptor.instance_attribute_descriptors)
        {
            gl_internal_instance_attribute_descriptor _internal_instance_attribute_descriptor;
            _internal_instance_attribute_descriptor.attribute_index = _attribute_index;
            _internal_instance_attribute_descriptor.initial_descriptor = _instance_attribute_descriptor;
            _internal_instance_attribute_descriptor.instance_attribute_buffer = new gl_array_buffer(_instance_attribute_descriptor.attributes_num * _instance_attribute_descriptor.attribute_size);
            _internal_descriptor.instance_attribute_descriptors.push_back(_internal_instance_attribute_descriptor);
            _AllocateInstanceAttributes(_internal_instance_attribute_descriptor.attribute_index);
            
            ++_attribute_index;
        }
    }

    gl_vertex_array(const gl_vertex_array&) = delete;
    gl_vertex_array& operator=(const gl_vertex_array&) = delete;

    ~gl_vertex_array() override
    {
        glDeleteVertexArrays(1, &_handle);
    }

private:

    struct gl_internal_vertex_attribute_descriptor
    {
        gl_vertex_attribute_descriptor initial_descriptor;
        uint32 attribute_index;
    };

    struct gl_internal_vertex_descriptor
    {
        std::vector<gl_internal_vertex_attribute_descriptor> attribute_descriptors;
        uint32 vertex_size;
        gl_array_buffer* vertex_buffer;
    };

    struct gl_internal_instance_attribute_descriptor
    {
        gl_instance_attribute_descriptor initial_descriptor;
        uint32 attribute_index;
        gl_array_buffer* instance_attribute_buffer;
    };

    struct gl_internal_vertex_array_descriptor
    {
        uint32 vertices_num;
        gl_internal_vertex_descriptor vertex_descriptor;
        std::vector<gl_internal_instance_attribute_descriptor> instance_attribute_descriptors;
    };

    gl_internal_vertex_array_descriptor _internal_descriptor;

public:
   
    /*
    * so this func properly cause performance degradation
    * @VerticesNum(UInt32) : num of vertices you want to reallocate memory for, if it is the same as old num, just return.
    */
    void reallocate_vertex_slot(uint32 vertices_num) noexcept
    {
        if (vertices_num == _internal_descriptor.vertices_num) return;
        _internal_descriptor.vertices_num = vertices_num;
        _AllocateVertices();
    }

    void write_vertex_slot(uint32 vertex_offset, uint32 vertices_num, const void* vertices)
    {}

    const void* read_vertex_slot(uint32 vertex_offset, uint32 vertices_num)
    {}

    void execute_mapped_vertex_slot_writer() {}

    void execute_mapped_vertex_slot_reader() {}

    void execute_mapped_vertex_slot_handler() {}

public:

    /*
    * this func will trigger memory reallocation, every instance attribute are separated
    * so this wont cause performance degradation
    */
    void reallocate_instance_attribute_slot(uint32 attribute_index, uint32 attributes_num, uint32 divisor, const void* initial_attributes)
    {
        const auto* _instance_attribute_descriptor = _find_instance_attribute_descriptor(attribute_index);
        if (!_instance_attribute_descriptor || _instance_attribute_descriptor->instance_attribute_buffer) return;

    }

    void write_to_instance_attribute_slot(uint32 attribute_index, int64 bytes_offset)
    {}

    void read_from_instance_attribute_slot(uint32 attribute_index, int64 bytes_offset)
    {}

    void execute_mapped_instance_attribute_slot_writer()
    {

    }

    void execute_mapped_instance_attribute_slot_reader()
    {
        glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

    }

    void execute_mapped_instance_attribute_slot_handler()
    {
    }

public:

    bool try_to_get_vertex_attribute_index(const std::string& vertex_attribute_name, uint32& out_attribute_index) const 
    {
        for (const auto& _vertex_attribute_descriptor : _internal_descriptor.vertex_descriptor.attribute_descriptors)
        {
            if (_vertex_attribute_descriptor.initial_descriptor.attribute_name == vertex_attribute_name)
            {
                out_attribute_index = _vertex_attribute_descriptor.attribute_index; 
                return true;
            }
        }
        return false;
    }

    bool try_to_get_instance_attribute_index(const std::string& instance_attribute_name, uint32& out_attribute_index) const
    {
        for (const auto& _instance_attribute_descriptor : _internal_descriptor.instance_attribute_descriptors)
        {
            if (_instance_attribute_descriptor.initial_descriptor.attribute_name == instance_attribute_name)
            {
                out_attribute_index = _instance_attribute_descriptor.attribute_index;
                return true;
            }
        }
        return false;
    }

    uint32 get_vertices_num() const
    {
        return _internal_descriptor.vertices_num;
    }

    uint32 get_vertex_size() const
    {
        return _internal_descriptor.vertex_descriptor.vertex_size;
    }

public:

    void bind() const noexcept
    {
        glBindVertexArray(_handle);
    }

    void unbind() const noexcept
    {
        glBindVertexArray(0);
    }

    void enable_pointers() const
    {
        for (const auto& _vertex_attribute_descriptor : _internal_descriptor.vertex_descriptor.attribute_descriptors)
            glEnableVertexAttribArray(_vertex_attribute_descriptor.attribute_index);

        for (const auto& _instance_attribute_descriptor : _internal_descriptor.instance_attribute_descriptors)
            glEnableVertexAttribArray(_instance_attribute_descriptor.attribute_index);
    }

    void disable_pointers() const
    {
        for (const auto& _vertex_attribute_descriptor : _internal_descriptor.vertex_descriptor.attribute_descriptors)
            glDisableVertexAttribArray(_vertex_attribute_descriptor.attribute_index);

        for (const auto& _instance_attribute_descriptor : _internal_descriptor.instance_attribute_descriptors)
            glDisableVertexAttribArray(_instance_attribute_descriptor.attribute_index);
    }

private:

    void _AllocateVertices()
    {
        int64 _total_size = _internal_descriptor.vertices_num * _internal_descriptor.vertex_descriptor.vertex_size;

        auto & _vertex_buffer = _internal_descriptor.vertex_descriptor.vertex_buffer;
        _vertex_buffer = new gl_array_buffer(_total_size);
        if (!_vertex_buffer) return;
        const auto& _vertex_attribute_descriptors = _internal_descriptor.vertex_descriptor.attribute_descriptors;

        // set attribute pointers
        bind();
        _vertex_buffer->bind();
        uint32 _attribute_offset = 0;
        for (const auto& _vertex_attribute_descriptor : _vertex_attribute_descriptors)
        {
            _set_attribute_pointer(_vertex_attribute_descriptor.attribute_index,
                _vertex_attribute_descriptor.initial_descriptor.components_num,
                _vertex_attribute_descriptor.initial_descriptor.component_type,
                _vertex_attribute_descriptor.initial_descriptor.attribute_size,
                _attribute_offset);

            _attribute_offset += _vertex_attribute_descriptor.initial_descriptor.attribute_size;
        }
        _vertex_buffer->unbind();
        unbind();
    }

    // allocate all instance attributes can only be used once
    void _AllocateInstanceAttributes(uint32 attribute_index)
    {
        auto* _instance_attribute_descriptor = _find_instance_attribute_descriptor(attribute_index);
        if (!_instance_attribute_descriptor) return;

        uint32 _total_size = _instance_attribute_descriptor->initial_descriptor.attribute_size * _instance_attribute_descriptor->initial_descriptor.attributes_num;
        auto& _instance_attribute_buffer = _instance_attribute_descriptor->instance_attribute_buffer;
        
        auto* _new_buffer = new gl_array_buffer(_total_size);
        //Data Safe memcpy
        //Buffer::Memcpy(NewBuffer->GetRaw(), 0, _InstanceAttributeBuffer->GetRaw(), 0, _InstanceAttributeBuffer->GetRaw()->GetBytesNum());
        _instance_attribute_buffer = _new_buffer;

        bind();
        _instance_attribute_buffer->bind();
        _set_attribute_pointer(attribute_index,
            _instance_attribute_descriptor->initial_descriptor.components_num,
            _instance_attribute_descriptor->initial_descriptor.component_type,
            _instance_attribute_descriptor->initial_descriptor.attribute_size,
            0);
        glVertexAttribDivisor(attribute_index, _instance_attribute_descriptor->initial_descriptor.divisor);
        _instance_attribute_buffer->unbind();
        unbind();
    }

    void _set_attribute_pointer(uint32 attribute_index, uint32 components_num, gl_attribute_component_type attribute_component_type, uint32 attribute_size, uint32 offset)
    {
        switch (attribute_component_type)
        {
            case gl_attribute_component_type::INT:
            {
                glVertexAttribIPointer(attribute_index, components_num, GL_INT, attribute_size, reinterpret_cast<const void*>(offset));
            }
            break;
            case gl_attribute_component_type::UINT:
            {
                glVertexAttribIPointer(attribute_index, components_num, GL_UNSIGNED_INT, attribute_size, reinterpret_cast<const void*>(offset));
            }
            break;
            case gl_attribute_component_type::FLOAT:
            {
                glVertexAttribPointer(attribute_index, components_num, GL_FLOAT, GL_FALSE, attribute_size, reinterpret_cast<const void*>(offset));
            }
            break;
            case gl_attribute_component_type::UINT_TO_FLOAT:
            {
                glVertexAttribPointer(attribute_index, components_num, GL_UNSIGNED_INT, GL_TRUE, attribute_size, reinterpret_cast<const void*>(offset));
            }
            break;
            case gl_attribute_component_type::DOUBLE:
            {
                glVertexAttribLPointer(attribute_index, components_num, GL_DOUBLE, attribute_size, reinterpret_cast<const void*>(offset));
            }
            break;
            default: break;
        }
    }

    gl_internal_instance_attribute_descriptor* _find_instance_attribute_descriptor(uint32 attribute_index)
    {
        for (auto& _instance_attribute_descriptor : _internal_descriptor.instance_attribute_descriptors)
        {
            if (_instance_attribute_descriptor.attribute_index == attribute_index) return &_instance_attribute_descriptor;
        }
        return nullptr;
    }

    bool is_pointer_enabled(std::uint32_t index)
    {
        bind();
        GLint _is_enabled = GL_FALSE;
        glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &_is_enabled);
        unbind();
        return _is_enabled;
    }

    std::uint32_t get_attribute_components_num(std::uint32_t index)
    {
        bind();
        GLint _num = 0;
        glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &_num);
        unbind();
        return _num;
    }

    std::string get_attribute_component_type(std::uint32_t index)
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
        }
    }

};

#endif
