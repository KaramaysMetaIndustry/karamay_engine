#ifndef H_GL_VERTEX_ARRAY
#define H_GL_VERTEX_ARRAY

#include "graphics/resource/glo/gl_object.h"
#include "graphics/glsl/interface_block/glsl_in_block.h"
#include "graphics/resource/buffers/common_buffer/gl_array_buffer.h"

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
    std::vector<InstanceAttributeDescriptor> InstanceAttributeDescs; // {...}
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
class VertexArray final : public gl_object {
public:
    VertexArray(const VertexArrayDescriptor& Descriptor) : 
        gl_object(gl_object_type::VERTEX_ARRAY_OBJ)
    {
        glCreateVertexArrays(1, &_handle);

        // construct internal descriptor and intialize buffers
        _InternalDescriptor.VerticesNum = Descriptor.VerticesNum;
        
        // allocate attribute indices
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
        _InternalDescriptor.VertexDesc.Buffer = new ArrayBuffer(_InternalDescriptor.VerticesNum * _VertexSize);
        _AllocateVertices();
        
        // construct instance attribues
        for (const auto& _InstanceAttributeDesc : Descriptor.InstanceAttributeDescs)
        {
            InternalInstanceAttributeDescriptor _InternalInstanceAttributeDesc;
            _InternalInstanceAttributeDesc.AttributeIndex = _AttributeIndex;
            _InternalInstanceAttributeDesc.InitialDesc = _InstanceAttributeDesc;
            _InternalInstanceAttributeDesc.Buffer = new ArrayBuffer(_InstanceAttributeDesc.AttributesNum * _InstanceAttributeDesc.AttributeSize);
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
        std::vector<InternalInstanceAttributeDescriptor> InstanceAttributeDescs;
    };

    InternalVertexArrayDescriptor _InternalDescriptor;

public:
   
    /*
    * so this func properly cause performance degradation
    * @VerticesNum(UInt32) : num of vertices you want to reallocate memory for, if it is the same as old num, just return.
    */
    void ReallocateVertices(UInt32 VerticesNum) noexcept
    {
        if (VerticesNum == _InternalDescriptor.VerticesNum) return;
        _InternalDescriptor.VerticesNum = VerticesNum;
        _AllocateVertices();
    }

    /*
    * VertexOffset + VerticesNum <= _InternalDescriptor.VerticesNum - 1
    * @VertexOffset(UInt32) : 
    * @Data(const UInt8*) :
    * @VerticesNum(UInt32) :
    */
    void FillVertices(UInt32 VertexOffset, const UInt8* Data, UInt32 VerticesNum) noexcept
    {
        const auto& _VertexBuffer = _InternalDescriptor.VertexDesc.Buffer;
        if (!_VertexBuffer) return;
        if (VertexOffset + VerticesNum > _InternalDescriptor.VerticesNum) return;

        const UInt32 _VertexSize = _InternalDescriptor.VertexDesc.VertexSize;
       // _VertexBuffer->Fill(VertexOffset * _VertexSize, Data, VerticesNum * _VertexSize);
    }

    void HandleMappedVertices(UInt32 VertexOffset, UInt32 VerticesNum, const std::function<void(UInt8* MappedVertices, UInt32 VerticesNum)>& Handler)
    {

    }

public:

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

    void FillInstanceAttributes(const std::string& InstanceAttributeName, UInt32 AttributeOffset, const UInt8* Data, UInt32 AttributesNum)
    {
        if (!Data) return;
        Int32 AttributeIndex = GetVertexAttributeIndex(InstanceAttributeName);
        if (AttributeIndex == -1) return;
        
        const auto* _InstanceAttributeDesc = _FindInstanceAttributeDescriptor(AttributeIndex);
        if (!_InstanceAttributeDesc || _InstanceAttributeDesc->Buffer) return;

       /* _InstanceAttributeDesc->Buffer->Fill(
            AttributeOffset * _InstanceAttributeDesc->InitialDesc.AttributeSize,
            Data, 
            AttributesNum * _InstanceAttributeDesc->InitialDesc.AttributeSize
        );*/
    }

    /*
    * @AttributeIndex(UInt32) : Index the InstanceAttribute
    * @AttributeOffset(UInt32) : 
    * @AttributesNum(UInt32) :
    * @Handler(const std::function<void(UInt8* MappedInstanceAttributes, UInt32 MappedInstancesAttributesNum)>&) : Memory Handler
    */
    void HandleMappedInstanceAttributes(UInt32 AttributeIndex, UInt32 AttributeOffset, UInt32 AttributesNum, const std::function<void(UInt8* MappedInstanceAttributes, UInt32 MappedInstancesAttributesNum)>& Handler)
    {

    }

public:

    Int32 GetVertexAttributeIndex(const std::string& VertexAttributeName) const 
    {
        for (const auto& _AttributeDesc : _InternalDescriptor.VertexDesc.AttributeDescs)
        {
            if (_AttributeDesc.InitialDesc.AttributeName == VertexAttributeName) return _AttributeDesc.AttributeIndex;
        }
        return -1;
    }

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

    UInt32 GetVertexSize() const
    {
        return _InternalDescriptor.VertexDesc.VertexSize;
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

    // allocate all instance attributes can only be used once
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
