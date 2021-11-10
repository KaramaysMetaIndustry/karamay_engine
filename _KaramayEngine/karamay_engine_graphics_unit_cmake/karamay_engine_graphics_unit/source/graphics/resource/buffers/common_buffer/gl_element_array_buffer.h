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

        //_Buffer->execute_mapped_memory_writer()
        
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

    std::unique_ptr<gl_buffer> _Buffer;

    void _Allocate(Int64 Size)
    {
        gl_buffer_storage_options _options;
        _options.is_client_storage = false;
        _options.is_dynamic_storage = true;
        _options.is_map_read = true;
        _options.is_map_write = true;
        _options.is_map_coherent = false;
        _options.is_map_persistent = false;
        _Buffer = std::make_unique<gl_buffer>(_options, Size);
    }

};


#endif
