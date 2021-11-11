#ifndef H_GL_VERTEX_ARRAY
#define H_GL_VERTEX_ARRAY

#include "graphics/resource/glo/gl_object.h"
#include "graphics/glsl/interface_block/glsl_in_block.h"
#include "graphics/resource/buffers/common_buffer/gl_array_buffer.h"

class gl_attribute_component
{
public:
    enum class type : GLenum
    {
        UNKNOWN = 0,
        INT = GL_INT,
        UINT = GL_UNSIGNED_INT,
        FLOAT = GL_FLOAT,
        DOUBLE = GL_DOUBLE
    };

    static std::string to_string(type component_type)
    {
        switch(component_type)
        {
            case type::INT: return "INT";
            case type::UINT: return "UINT";
            case type::FLOAT: return "FLOAT";
            case type::DOUBLE: return "DOUBLE";
            default: return "UNKNOWN";
        }
    }

    static type to_enum(const std::string& component_type)
    {
        if(component_type == "INT") return type::INT;
        if(component_type == "UINT") return type::UINT;
        if(component_type == "FLOAT") return type::FLOAT;
        if(component_type == "DOUBLE") return type::DOUBLE;
        return type::UNKNOWN;
    }

    static GLenum to_GLenum(type component_type)
    {
        return static_cast<GLenum>(component_type);
    }

    static std::uint32_t get_size(type component_type)
    {
        switch (component_type) {
            case type::INT: return sizeof(std::int32_t);
            case type::UINT: return sizeof(std::uint32_t);
            case type::FLOAT: return sizeof(std::float_t);
            case type::DOUBLE: return sizeof(std::double_t);
            default: return 0;
        }
    }
};

class gl_attribute
{
    enum class type
    {
        UINT,UVEC2,UVEC3,UVEC4,
        INT,IVEC2,IVEC3,IVEC4,
        FLOAT,VEC2,VEC3,VEC4,
        DOUBLE,DVEC2,DVEC3,DVEC4,

        MAT2X2,MAT2X3,MAT2X4,MAT3X2,MAT3X3,MAT3X4,MAT4X2,MAT4X3,MAT4X4,
        DMAT2X2,DMAT2X3,DMAT2X4,DMAT3X2,DMAT3X3,DMAT3X4,DMAT4X2,DMAT4X3,DMAT4X4,
    };

    static std::pair<gl_attribute_component::type, std::uint32_t> get_component_layout(gl_attribute::type attribute_type)
    {
        switch (attribute_type) {

            case type::UINT:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::UVEC2:
                return std::make_pair(gl_attribute_component::type::UINT, 2);
            case type::UVEC3:
                return std::make_pair(gl_attribute_component::type::UINT, 3);
            case type::UVEC4:
                return std::make_pair(gl_attribute_component::type::UINT, 4);
            case type::INT:
                return std::make_pair(gl_attribute_component::type::INT, 1);
            case type::IVEC2:
                return std::make_pair(gl_attribute_component::type::INT, 2);
            case type::IVEC3:
                return std::make_pair(gl_attribute_component::type::INT, 3);
            case type::IVEC4:
                return std::make_pair(gl_attribute_component::type::INT, 4);
            case type::FLOAT:
                return std::make_pair(gl_attribute_component::type::FLOAT, 1);
            case type::VEC2:
                return std::make_pair(gl_attribute_component::type::FLOAT, 2);
            case type::VEC3:
                return std::make_pair(gl_attribute_component::type::FLOAT, 3);
            case type::VEC4:
                return std::make_pair(gl_attribute_component::type::FLOAT, 4);
            case type::DOUBLE:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 1);
            case type::DVEC2:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 2);
            case type::DVEC3:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 3);
            case type::DVEC4:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 4);
            case type::MAT2X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT2X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT2X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT3X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT3X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT3X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT4X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT4X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT4X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT2X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT2X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT2X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT3X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT3X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT3X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT4X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT4X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT4X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
        }
    }
};

enum class AttributeComponentType
{
    UINT,
    INT,
    FLOAT,
    UINT_TO_FLOAT,
    DOUBLE,
};

struct VertexAttributeDescriptor 
{
    std::string AttributeName; // BaseColor
    UInt64 AttributeSize; // sizeof(glm::vec4)
    UInt32 ComponentsNum; // 4
    AttributeComponentType ComponentType; // FLOAT
};

struct VertexDescriptor
{
    std::vector<VertexAttributeDescriptor> AttributeDescriptors;
};

struct InstanceAttributeDescriptor
{
    std::string AttributeName; // InstancePositionOffset
    UInt32 AttributeSize; // sizeof(glm::vec3)
    UInt32 ComponentsNum; // 3
    AttributeComponentType ComponentType; // FLOAT
    UInt32 AttributesNum; // 10
    UInt32 Divisor; // 3 每渲染3个instances换一个attribute，总共有10种可以换
};

struct VertexArrayDescriptor
{
    UInt32 VerticesNum; // 1024
    VertexDescriptor VertexDesc; // {...}
    UInt32 InstancesNum; // 30
    std::vector<InstanceAttributeDescriptor> InstanceAttributeDescs; // {...}
};

/*
 * Dynamic Storage : if required capacity is not enough,
 *
 * [          ] [vertex*] [vertex*] [vertex*] [vertex*]
 * 
 * [InstanceAttribute*] [       ] [       ] [      ] [.......]
 * 
 * [InstanceAttribute*] [       ] [       ] [      ] [.......]
 * 
 *
 * Store Vertex Attributes & Instance Attributes
 *
 * */
class VertexArray final : public gl_object {
public:
    VertexArray(const VertexArrayDescriptor& Descriptor) : 
        gl_object(gl_object_type::VERTEX_ARRAY_OBJ)
    {
        glCreateVertexArrays(1, &_handle);

        // construct internal descriptor and intialize buffers
        _InternalDescriptor.InstancesNum = Descriptor.InstancesNum;
        _InternalDescriptor.VerticesNum = Descriptor.VerticesNum;
        
        // attribute index
        UInt32 _AttributeIndex = 0;

        // construct internal vertex descriptor
        UInt32 _VertexSize = 0;
        for (const auto& _VertexAttributeDesc : Descriptor.VertexDesc.AttributeDescriptors)
        {
            InternalVertexAttributeDescriptor _InternalVertexAttributeDesc;
            _InternalVertexAttributeDesc.AttributeIndex = _AttributeIndex;
            _InternalVertexAttributeDesc.InitialDesc = _VertexAttributeDesc;
            _InternalDescriptor.VertexDesc.AttributeDescs.push_back(_InternalVertexAttributeDesc);
            
            _VertexSize += _VertexAttributeDesc.AttributeSize;
            ++_AttributeIndex;
        }

        _InternalDescriptor.VertexDesc.VertexSize = _VertexSize;
        _InternalDescriptor.VertexDesc.Buffer = new ArrayBuffer(_VertexSize * _InternalDescriptor.VerticesNum);
        _AllocateVertices();
        
        // construct instance attribues
        for (const auto& _InstanceAttributeDesc : Descriptor.InstanceAttributeDescs)
        {
            InternalInstanceAttributeDescriptor _InternalInstanceAttributeDesc;
            _InternalInstanceAttributeDesc.AttributeIndex = _AttributeIndex;
            _InternalInstanceAttributeDesc.InitialDesc = _InstanceAttributeDesc;
            _InternalInstanceAttributeDesc.Buffer = new ArrayBuffer(_InstanceAttributeDesc.AttributeSize * _InstanceAttributeDesc.AttributesNum);
            _InternalDescriptor.InstanceAttributeDescs.push_back(_InternalInstanceAttributeDesc);
            _AllocateInstanceAttributes(_InternalInstanceAttributeDesc.AttributeIndex);
            
            ++_AttributeIndex;
        }

    }

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    ~VertexArray() override
    {
        glDeleteVertexArrays(1, &_handle);
    }

private:

    struct InternalVertexAttributeDescriptor
    {
        VertexAttributeDescriptor InitialDesc;
        UInt32 AttributeIndex;
    };

    struct InternalVertexDescriptor
    {
        std::vector<InternalVertexAttributeDescriptor> AttributeDescs;
        UInt32 VertexSize;
        ArrayBuffer* Buffer;
    };

    struct InternalInstanceAttributeDescriptor
    {
        InstanceAttributeDescriptor InitialDesc;
        UInt32 AttributeIndex;
        ArrayBuffer* Buffer;
    };

    struct InternalVertexArrayDescriptor
    {
        UInt32 VerticesNum;
        InternalVertexDescriptor VertexDesc;
        UInt32 InstancesNum;
        std::vector<InternalInstanceAttributeDescriptor> InstanceAttributeDescs;
    };

    InternalVertexArrayDescriptor _InternalDescriptor;

public:
   
    /*
    * so this func properly cause performance degradation
    */
    void ReallocateVertices(UInt32 VerticesNum) noexcept
    {
        if (VerticesNum == _InternalDescriptor.VerticesNum) return;
        _InternalDescriptor.VerticesNum = VerticesNum;
        _AllocateVertices();
    }

    /*
    * VertexOffset + VerticesNum <= _InternalDescriptor.VerticesNum - 1
    * 
    */
    void FillVertices(UInt32 VertexOffset, const UInt8* Data, UInt32 VerticesNum) noexcept
    {
        const auto& _VertexBuffer = _InternalDescriptor.VertexDesc.Buffer;
        if (!_VertexBuffer) return;
        if (VertexOffset + VerticesNum > _InternalDescriptor.VerticesNum) return;

        const UInt32 _VertexSize = _InternalDescriptor.VertexDesc.VertexSize;
        _VertexBuffer->Fill(VertexOffset * _VertexSize, Data, VerticesNum * _VertexSize);
    }

public:

    /*
    * This func wont trigger memory reallocate
    * instancesNum does not effect instanceAttributes memory
    */
    void ResetInstancesNum(UInt32 InstancesNum) noexcept
    {
        if (InstancesNum == _InternalDescriptor.InstancesNum) return;
        _InternalDescriptor.InstancesNum = InstancesNum;
    }

    /*
    * this func will trigger memory reallocation, every instance attribute are separated
    * so this wont cause performance degradation
    */
    void ReallocateInstanceAttributes(UInt32 AttributeIndex, UInt32 InstanceAttributesNum, UInt32 Divisor)
    {
        const auto* _InstanceAttributeDesc = _FindInstanceAttributeDescriptor(AttributeIndex);
        if (!_InstanceAttributeDesc || _InstanceAttributeDesc->Buffer) return;

        _AllocateInstanceAttributes(AttributeIndex);
    }

    void FillInstanceAttributes(UInt32 AttributeIndex, UInt32 AttributeOffset, const UInt8* Data, UInt32 AttributesNum)
    {
        if (!Data) return;
        const auto* _InstanceAttributeDesc = _FindInstanceAttributeDescriptor(AttributeIndex);
        if (!_InstanceAttributeDesc || _InstanceAttributeDesc->Buffer) return;
        _InstanceAttributeDesc->Buffer->Fill(
            AttributeOffset * _InstanceAttributeDesc->InitialDesc.AttributeSize,
            Data, 
            AttributesNum * _InstanceAttributeDesc->InitialDesc.AttributeSize
        );
    }

public:

    /*
    * if return -1, not exist
    */
    Int32 GetVertexAttributeIndex(const std::string& Name) const 
    {
        for (const auto& _AttributeDesc : _InternalDescriptor.VertexDesc.AttributeDescs)
        {
            if (_AttributeDesc.InitialDesc.AttributeName == Name) return _AttributeDesc.AttributeIndex;
        }
        return -1;
    }

    /*
    * if return -1, not exist
    */
    Int32 GetInstanceAttributeIndex(const std::string& AttributeName) const 
    {
        for (const auto& _AttributeDesc : _InternalDescriptor.InstanceAttributeDescs)
        {
            if (_AttributeDesc.InitialDesc.AttributeName == AttributeName) return _AttributeDesc.AttributeIndex;
        }
        return -1;
    }

    UInt32 GetVerticesNum() const
    {
        return _InternalDescriptor.VerticesNum;
    }

    UInt32 GetInstancesNum() const 
    {
        return _InternalDescriptor.InstancesNum;
    }

public:

    void Bind() const noexcept
    {
        glBindVertexArray(_handle);
    }

    void Unbind() const noexcept
    {
        glBindVertexArray(0);
    }

    void EnablePointers() const
    {
        for (const auto& _VertexAttributeDesc : _InternalDescriptor.VertexDesc.AttributeDescs)
            glEnableVertexAttribArray(_VertexAttributeDesc.AttributeIndex);

        for (const auto& _InstanceAttributeDesc : _InternalDescriptor.InstanceAttributeDescs)
            glEnableVertexAttribArray(_InstanceAttributeDesc.AttributeIndex);
    }

    void DisablePointers() const
    {
        for (const auto& _VertexAttributeDesc : _InternalDescriptor.VertexDesc.AttributeDescs)
            glDisableVertexAttribArray(_VertexAttributeDesc.AttributeIndex);

        for (const auto& _InstanceAttributeDesc : _InternalDescriptor.InstanceAttributeDescs)
            glDisableVertexAttribArray(_InstanceAttributeDesc.AttributeIndex);
    }

private:

    void _AllocateVertices()
    {
        // calc total memory demond
        UInt32 _TotalSize = _InternalDescriptor.VerticesNum * _InternalDescriptor.VertexDesc.VertexSize;
        const auto& _VertexAttributeDescs = _InternalDescriptor.VertexDesc.AttributeDescs;
        auto& _VertexBuffer = _InternalDescriptor.VertexDesc.Buffer;
        _VertexBuffer = new ArrayBuffer(_TotalSize);
        if (!_VertexBuffer) return;

        // set attribute pointers
        Bind();
        _VertexBuffer->Bind();
        UInt32 _AttributeOffset = 0;
        for (const auto& _VertexAttributeDesc : _VertexAttributeDescs)
        {
            _SetAttributePointer(_VertexAttributeDesc.AttributeIndex, 
                _VertexAttributeDesc.InitialDesc.ComponentsNum, 
                _VertexAttributeDesc.InitialDesc.ComponentType,
                _VertexAttributeDesc.InitialDesc.AttributeSize,
                _AttributeOffset);
            // calc attribute offset
            _AttributeOffset += _VertexAttributeDesc.InitialDesc.AttributeSize;
        }
        _VertexBuffer->Unbind();
        Unbind();
    }

    void _AllocateInstanceAttributes(UInt32 AttributeIndex)
    {
        auto* _InstanceAttributeDesc = _FindInstanceAttributeDescriptor(AttributeIndex);
        if (!_InstanceAttributeDesc) return;

        UInt32 _TotalSize = _InstanceAttributeDesc->InitialDesc.AttributeSize * _InstanceAttributeDesc->InitialDesc.AttributesNum;
        auto& _InstanceAttributeBuffer = _InstanceAttributeDesc->Buffer;
        _InstanceAttributeBuffer = new ArrayBuffer(_TotalSize);

        Bind();
        _InstanceAttributeBuffer->Bind();

        _SetAttributePointer(AttributeIndex, 
            _InstanceAttributeDesc->InitialDesc.ComponentsNum,
            _InstanceAttributeDesc->InitialDesc.ComponentType,
            _InstanceAttributeDesc->InitialDesc.AttributeSize,
            0);
        glVertexAttribDivisor(AttributeIndex, _InstanceAttributeDesc->InitialDesc.Divisor);

        _InstanceAttributeBuffer->Unbind();
        Unbind();
    }

    void _SetAttributePointer(UInt32 AttributeIndex, UInt32 ComponentsNum, AttributeComponentType ComponentType, UInt32 AttributeSize, UInt32 Offset)
    {
        switch (ComponentType) 
        {
            case AttributeComponentType::INT:
            {
                glVertexAttribIPointer(AttributeIndex, ComponentsNum, GL_INT, AttributeSize, reinterpret_cast<const void*>(Offset));
            }
            break;
            case AttributeComponentType::UINT:
            {
                glVertexAttribIPointer(AttributeIndex, ComponentsNum, GL_UNSIGNED_INT, AttributeSize, reinterpret_cast<const void*>(Offset));
            }
            break;
            case AttributeComponentType::FLOAT:
            {
                glVertexAttribPointer(AttributeIndex, ComponentsNum, GL_FLOAT, GL_FALSE, AttributeSize, reinterpret_cast<const void*>(Offset));
            }
            break;
            case AttributeComponentType::UINT_TO_FLOAT:
            {
                glVertexAttribPointer(AttributeIndex, ComponentsNum, GL_UNSIGNED_INT, GL_TRUE, AttributeSize, reinterpret_cast<const void*>(Offset));
            }
            break;
            case AttributeComponentType::DOUBLE:
            {
                glVertexAttribLPointer(AttributeIndex, ComponentsNum, GL_DOUBLE, AttributeSize, reinterpret_cast<const void*>(Offset));
            }
            break;
            default: break;
        }
    }

    InternalInstanceAttributeDescriptor* _FindInstanceAttributeDescriptor(UInt32 AttributeIndex)
    {
        for (auto& _InternalInstanceAttributeDesc : _InternalDescriptor.InstanceAttributeDescs)
        {
            if (_InternalInstanceAttributeDesc.AttributeIndex == AttributeIndex) return &_InternalInstanceAttributeDesc;
        }
        return nullptr;
    }

    bool is_pointer_enabled(std::uint32_t index)
    {
        Bind();
        GLint _is_enabled = GL_FALSE;
        glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &_is_enabled);
        Unbind();
        return _is_enabled;
    }

    std::uint32_t get_attribute_components_num(std::uint32_t index)
    {
        Bind();
        GLint _num = 0;
        glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &_num);
        Unbind();
        return _num;
    }

    std::string get_attribute_component_type(std::uint32_t index)
    {
        Bind();
        GLint _num = 0;
        glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &_num);
        Unbind();

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

public:

    std::uint8_t* data(std::int64_t offset, std::int64_t size)
    {
        return nullptr;
    }

    template<typename GLSL_TRANSPARENT_T>
    const GLSL_TRANSPARENT_T* attribute(std::uint32_t index)
    {
        const auto* _data = reinterpret_cast<const GLSL_TRANSPARENT_T*>(
            data(index * sizeof(GLSL_TRANSPARENT_T), sizeof(GLSL_TRANSPARENT_T))
            );
        return _data;
    }

};

#endif
