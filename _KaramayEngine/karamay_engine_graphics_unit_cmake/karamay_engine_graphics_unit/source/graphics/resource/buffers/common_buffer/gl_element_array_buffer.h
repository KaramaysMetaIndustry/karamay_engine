#ifndef GL_ELEMENT_BUFFER_H
#define GL_ELEMENT_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"


enum class ElementType
{
    NONE,
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    UNSIGNED_INT = GL_UNSIGNED_INT
};

/*
* dynamic storage
*/
class ElementArrayBuffer final{
public:
    using ElementBufferWriter = std::function<void(void*, UInt32)>;
    using ElementBufferReader = std::function<void(const void*, UInt32)>;
    using ElementBufferHandler = std::function<void(void*, UInt32)>;


    ElementArrayBuffer() {}
    ElementArrayBuffer(ElementType Type, UInt32 ElementsNum, const void* InitialElements) :
        _Buffer(nullptr), 
        _ElementType(Type),
        _ElementSize(ElementsNum)
    {
        switch (Type)
        {
            case ElementType::UNSIGNED_BYTE: _ElementSize = sizeof(UInt8); break;
            case ElementType::UNSIGNED_SHORT: _ElementSize = sizeof(UInt16); break;
            case ElementType::UNSIGNED_INT: _ElementSize = sizeof(UInt32); break;
            default: break;
        }

        _Allocate(ElementsNum, InitialElements);
    }

    ElementArrayBuffer(const ElementArrayBuffer&) = delete;
    ElementArrayBuffer& operator=(const ElementArrayBuffer&) = delete;

    ~ElementArrayBuffer() = default;

public:
    
    UInt32 GetElementsNum() const { return _ElementsNum; }

    UInt32 GetElementSize() const { return _ElementSize; }

    ElementType GetElementType() const { return _ElementType; }

    void Reallocate(UInt32 ElementsNum, const void* InitialElements)
    {
        _ElementsNum = ElementsNum; 
        _Allocate(ElementsNum, InitialElements);
    }

    void WriteToElementBuffer(UInt32 ElementOffset, UInt32 ElementsNum, const ElementBufferWriter& Writer)
    {
        _Buffer->ExecuteMappedMemoryWriter(ElementOffset * _ElementSize, ElementsNum * _ElementSize,
            [&](UInt8* MappedMemory, Int64 BytesNum)
            {
                if (!MappedMemory) return;
                Writer(MappedMemory, BytesNum / _ElementSize);
            }
        );
    }

    void ReadFromElementBuffer(UInt32 ElementOffset, UInt32 ElementsNum, const ElementBufferReader& Reader)
    {
        _Buffer->ExecuteMappedMemoryReader(ElementOffset * _ElementSize, ElementsNum * _ElementSize, 
            [&](const UInt8* MappedMemory, Int64 BytesNum) 
            {
                if (!MappedMemory) return;
                Reader(MappedMemory, BytesNum / _ElementSize);
            }
        );
    }

    void HandleElementBuffer(UInt32 ElementOffset, UInt32 ElementsNum, const ElementBufferHandler& Handler)
    {
        _Buffer->ExecuteMappedMemoryHandler(ElementOffset * _ElementSize, ElementsNum * _ElementSize,
            [&](UInt8* MappedMemory, Int64 BytesNum)
            {
                if (!MappedMemory) return;
                Handler(MappedMemory, BytesNum / _ElementSize);
            }
        );
    }

    void SetPrimitiveRestartFlagElement(UInt32 ElementOffset)
    {

    }

    const std::vector<UInt32>& GetPrimitiveRestartFlagIndexOffsets() const 
    { 
        return _PrimitiveRestartFlagIndexOffsets; 
    }

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

public:

    Buffer* GetRaw()
    {
        return _Buffer.get();
    }

private:

    ElementType _ElementType;

    UInt32 _ElementSize, _ElementsNum;

    std::vector<UInt32> _PrimitiveRestartFlagIndexOffsets;

    UniquePtr<Buffer> _Buffer;

    void _Allocate(UInt32 ElementsNum, const void* InitialElements)
    {
        BufferStorageOptions _Options;
        _Options.ClientStorage = false;
        _Options.DynamicStorage = true;
        _Options.MapRead = true;
        _Options.MapWrite = true;
        _Options.MapCoherent = false;
        _Options.MapPersistent = false;
        _Buffer = std::make_unique<Buffer>(_Options, ElementsNum * _ElementSize);
    }

};


#endif
