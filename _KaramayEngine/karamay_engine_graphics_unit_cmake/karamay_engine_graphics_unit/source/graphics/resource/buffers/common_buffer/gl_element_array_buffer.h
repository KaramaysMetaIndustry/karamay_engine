#ifndef GL_ELEMENT_BUFFER_H
#define GL_ELEMENT_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"


/*
* dynamic storage
*/
class ElementArrayBuffer final{
public:
    ElementArrayBuffer() {}
    ElementArrayBuffer(UInt32 IndicesNum) : 
        _Buffer(nullptr), _IndicesNum(IndicesNum)
    {
        _Allocate(IndicesNum * sizeof(UInt32));
    }

    ElementArrayBuffer(const ElementArrayBuffer&) = delete;
    ElementArrayBuffer& operator=(const ElementArrayBuffer&) = delete;

    ~ElementArrayBuffer() = default;

public:

    void Reallocate(UInt32 IndicesNum) 
    {
        _IndicesNum = IndicesNum;
        const Int64 Size = sizeof(UInt32) * IndicesNum;
        _Allocate(Size);
    }

    void Fill(UInt32 Offset, const std::vector<UInt32>& Indices) 
    {
        if (!_Buffer) return;
        if (Offset + Indices.size() > _IndicesNum) return;
        
    }

    UInt32 GetIndicesNum() const { return _IndicesNum; }

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

    UInt32 _IndicesNum;

    UniquePtr<Buffer> _Buffer;

    void _Allocate(Int64 Size)
    {
        BufferStorageOptions _Options;
        _Options.ClientStorage = false;
        _Options.DynamicStorage = true;
        _Options.MapRead = true;
        _Options.MapWrite = true;
        _Options.MapCoherent = false;
        _Options.MapPersistent = false;
        _Buffer = std::make_unique<Buffer>(_Options, Size);
    }

};


#endif
