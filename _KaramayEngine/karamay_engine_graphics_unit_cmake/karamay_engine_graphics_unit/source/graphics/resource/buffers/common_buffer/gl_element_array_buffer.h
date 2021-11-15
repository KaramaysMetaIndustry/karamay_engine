#ifndef GL_ELEMENT_BUFFER_H
#define GL_ELEMENT_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"


enum class ElementType
{
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    UNSIGNED_INT = GL_UNSIGNED_INT
};

/*
* dynamic storage
*/
class ElementArrayBuffer final{
public:
    ElementArrayBuffer() {}
    ElementArrayBuffer(ElementType Type, UInt32 IndicesNum) :
        _Buffer(nullptr), 
        _ElementType(Type),
        _IndicesNum(IndicesNum)
    {
        switch (Type)
        {
            case ElementType::UNSIGNED_BYTE: _IndexSize = sizeof(UInt8); break;
            case ElementType::UNSIGNED_SHORT: _IndexSize = sizeof(UInt16); break;
            case ElementType::UNSIGNED_INT: _IndexSize = sizeof(UInt32); break;
            default: break;
        }

        _Allocate(IndicesNum);
    }

    ElementArrayBuffer(const ElementArrayBuffer&) = delete;
    ElementArrayBuffer& operator=(const ElementArrayBuffer&) = delete;

    ~ElementArrayBuffer() = default;

public:

    void Reallocate(UInt32 IndicesNum, const void* Indices = nullptr)
    {
        _IndicesNum = IndicesNum; _Allocate(IndicesNum);
    }

    void Fill(UInt32 IndexOffset, const void* Indices, UInt32 IndicesNum) 
    {
        if (!_Buffer) return;
    }

    void FillPrimitiveRestartFlagIndex(UInt32 IndexOffset)
    {
        if (!_Buffer) return;

    }

    const std::vector<UInt32>& GetPrimitiveRestartFlagIndexOffsets() const 
    { 
        return _PrimitiveRestartFlagIndexOffsets; 
    }

    const void* FetchIndices(UInt32 IndexOffset, UInt32 IndicesNum) const
    {
        return nullptr;
    }

    UInt32 GetIndicesNum() const { return _IndicesNum; }

    UInt32 GetIndexSize() const { return _IndexSize; }

    ElementType GetElementType() const { return _ElementType; }

    void RestartPrimitive() const
    {
        if (_PrimitiveRestartFlagIndexOffsets.size() == 0) return;
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0xFFF);
        glDisable(GL_PRIMITIVE_RESTART);
    }

public:

    void Bind() const noexcept
    {
        if(!_Buffer) return;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Buffer->get_handle());
    }

    void Unbind() const noexcept
    {
        if(!_Buffer) return;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

private:

    ElementType _ElementType;

    UInt32 _IndexSize, _IndicesNum;

    std::vector<UInt32> _PrimitiveRestartFlagIndexOffsets;

    UniquePtr<Buffer> _Buffer;

    void _Allocate(UInt32 IndicesNum)
    {
        BufferStorageOptions _Options;
        _Options.ClientStorage = false;
        _Options.DynamicStorage = true;
        _Options.MapRead = true;
        _Options.MapWrite = true;
        _Options.MapCoherent = false;
        _Options.MapPersistent = false;
        _Buffer = std::make_unique<Buffer>(_Options, IndicesNum * _IndexSize);
    }

};


#endif
