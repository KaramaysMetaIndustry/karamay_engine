#ifndef GL_BUFFER_H
#define GL_BUFFER_H

#include "graphics/resource/glo/gl_object.h"

enum class BufferType
{
    ARRAY_BUFFER = GL_ARRAY_BUFFER,
    ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
    UNIFORM_BUFFER = GL_UNIFORM_BUFFER,
    SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
    ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
    TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
    
    QUERY_BUFFER = GL_QUERY_BUFFER,
    TEXTURE_BUFFER = GL_TEXTURE_BUFFER,

    DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
    DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,

    COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
    COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
    PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
    PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER
};

enum class BufferStorageFlag : GLenum
{
    CLIENT_STORAGE_BIT = GL_CLIENT_STORAGE_BIT,
    DYNAMIC_STORAGE_BIT = GL_DYNAMIC_STORAGE_BIT,

    MAP_READ_BIT = GL_MAP_READ_BIT,
    MAP_WRITE_BIT = GL_MAP_WRITE_BIT,

    MAP_PERSISTENT_BIT = GL_MAP_PERSISTENT_BIT,
    MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT
};

enum class BufferMapAccessFlag : GLenum
{
    MAP_READ_BIT = GL_MAP_READ_BIT,
    MAP_WRITE_BIT = GL_MAP_WRITE_BIT,
    MAP_PERSISTENT = GL_MAP_PERSISTENT_BIT,
    MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT,
    MAP_INVALIDATE_RANGE_BIT = GL_MAP_INVALIDATE_RANGE_BIT,
    MAP_INVALIDATE_BUFFER_BIT = GL_MAP_INVALIDATE_BUFFER_BIT,
    MAP_FLUSH_EXPLICIT_BIT = GL_MAP_FLUSH_EXPLICIT_BIT,
    MAP_UNSYNCHRONIZED_BIT = GL_MAP_UNSYNCHRONIZED_BIT
};

enum class BufferMemoryBarrierFlag
{
    VERTEX_ATTRIB_ARRAY_BARRIER_BIT = GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT,
    ELEMENT_ARRAY_BARRIER_BIT = GL_ELEMENT_ARRAY_BARRIER_BIT,
    TRANSFORM_FEEDBACK_BARRIER_BIT = GL_TRANSFORM_FEEDBACK_BARRIER_BIT,
    UNIFORM_BARRIER_BIT = GL_UNIFORM_BARRIER_BIT,
    SHADER_STORAGE_BARRIER_BIT = GL_SHADER_STORAGE_BARRIER_BIT,
    ATOMIC_COUNTER_BARRIER_BIT = GL_ATOMIC_COUNTER_BARRIER_BIT,
    FRAMEBUFFER_BARRIER_BIT = GL_FRAMEBUFFER_BARRIER_BIT,
    TEXTURE_FETCH_BARRIER_BIT = GL_TEXTURE_FETCH_BARRIER_BIT,
    SHADER_IMAGE_ACCESS_BARRIER_BIT = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
    COMMAND_BARRIER_BIT = GL_COMMAND_BARRIER_BIT,
    PIXEL_BUFFER_BARRIER_BIT = GL_PIXEL_BUFFER_BARRIER_BIT,
    TEXTURE_UPDATE_BARRIER_BIT = GL_TEXTURE_UPDATE_BARRIER_BIT,
    BUFFER_UPDATE_BARRIER_BIT = GL_BUFFER_UPDATE_BARRIER_BIT
};

enum class BufferMemoryBarrierRegionFlag
{
    UNIFORM_BARRIER_BIT = GL_UNIFORM_BARRIER_BIT,
    SHADER_STORAGE_BARRIER_BIT = GL_SHADER_STORAGE_BARRIER_BIT,
    ATOMIC_COUNTER_BARRIER_BIT = GL_ATOMIC_COUNTER_BARRIER_BIT,
    FRAMEBUFFER_BARRIER_BIT = GL_FRAMEBUFFER_BARRIER_BIT,
    SHADER_IMAGE_ACCESS_BARRIER_BIT = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
    TEXTURE_FETCH_BARRIER_BIT = GL_TEXTURE_FETCH_BARRIER_BIT
};

struct BufferStorageOptions
{
    bool MapRead;
    bool MapWrite;
    bool DynamicStorage;
    bool ClientStorage;
    bool MapPersistent;
    bool MapCoherent;

    UInt32 Bitfield() const
    {
        UInt32 _StorageFlags = 0;
        if (MapRead) _StorageFlags |= GL_MAP_READ_BIT;
        if (MapWrite) _StorageFlags |= GL_MAP_WRITE_BIT;
        if (DynamicStorage) _StorageFlags |= GL_MAP_PERSISTENT_BIT;
        if (ClientStorage) _StorageFlags |= GL_MAP_COHERENT_BIT;
        if (MapPersistent) _StorageFlags |= GL_CLIENT_STORAGE_BIT;
        if (MapCoherent) _StorageFlags |= GL_DYNAMIC_STORAGE_BIT;
        return _StorageFlags;
    }
};

struct gl_buffer_map_access_options
{
    bool is_map_read;
    bool is_map_write;
    bool is_map_presistent;
    bool is_map_coherent;
    bool is_map_invalidate_range;
    bool is_map_invalidate_buffer;
    bool is_map_flush_explicit;
    bool is_map_unsynchronized;

    std::uint32_t bitfield()
    {
        std::uint32_t _access_flags = 0;

        if (is_map_read) _access_flags |= GL_MAP_READ_BIT;
        if (is_map_write) _access_flags |= GL_MAP_WRITE_BIT;
        if (is_map_presistent) _access_flags |= GL_MAP_PERSISTENT_BIT;
        if (is_map_coherent) _access_flags |= GL_MAP_COHERENT_BIT;
        if (is_map_invalidate_range) _access_flags |= GL_MAP_INVALIDATE_RANGE_BIT;
        if (is_map_invalidate_buffer) _access_flags |= GL_MAP_INVALIDATE_BUFFER_BIT;
        if (is_map_flush_explicit) _access_flags |= GL_MAP_FLUSH_EXPLICIT_BIT;
        if (is_map_unsynchronized) _access_flags |= GL_MAP_UNSYNCHRONIZED_BIT;

        return _access_flags;
    }
};

/*
*
*/
class Buffer : public gl_object{
public:
    
    Buffer(BufferStorageOptions StorageOptions, Int64 Size) :
        gl_object(gl_object_type::BUFFER_OBJ),
        _StorageOptions(StorageOptions), _BytesNum(Size)
    {
        glCreateBuffers(1, &_handle);
        if (_handle != 0)
        {
            glNamedBufferStorage(_handle, _BytesNum, nullptr, _StorageOptions.Bitfield());
        }

    }

    Buffer(BufferStorageOptions StorageOptions, Int64 Size, const UInt8* InitializationBytes) :
        gl_object(gl_object_type::BUFFER_OBJ),
        _StorageOptions(StorageOptions), _BytesNum(Size)
    {
        glCreateBuffers(1, &_handle);
        if (_handle != 0)
        {
            glNamedBufferStorage(_handle, _BytesNum, InitializationBytes, _StorageOptions.Bitfield());
        }
    }
        
    
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    ~Buffer() override
    {
        glDeleteBuffers(1, &_handle);
    }

public:

    Int64 GetBytesNum() const
    {
        return _BytesNum;
    }

public:

    /*
    * write byte stream into buffer, this operation will affect GPU memory immediately
    */
    void Write(Int64 ByteOffset, const UInt8* Bytes, Int64 BytesNum) noexcept
    {
        if (!_StorageOptions.DynamicStorage) return;
        if (!Bytes) return;
        if (ByteOffset < 0 || BytesNum < 0 || ByteOffset + BytesNum > _BytesNum) return;

        glNamedBufferSubData(_handle, ByteOffset, BytesNum, Bytes);
    }

    const void* Read(Int64 ByteOffset, Int64 BytesNum) const noexcept
    {
        if (ByteOffset < 0 || BytesNum < 0 || ByteOffset + BytesNum > _BytesNum) return nullptr;
        void* _OutData = nullptr;
        glGetNamedBufferSubData(_handle, ByteOffset, BytesNum, _OutData);
        return _OutData;
    }

public:

    using MappedMemoryHandler = std::function<void(UInt8*, Int64)>;

    /*
    * advised for dispersed filling
     * execute a handler(which can read/write) on mapped memory (specified by offset and size)
     * mapped memory has valid content which come from GPU memory
     * also your bytes write into mapped memory can affect GPU memory
     * @Handler(std::function<void(UInt8* MappedMemory, Int64 BytesNum)>)
     * */
    void ExecuteMappedMemoryHandler(Int64 ByteOffset, Int64 BytesNum, const MappedMemoryHandler& Handler)
    {
        if (!_StorageOptions.MapWrite && !_StorageOptions.MapRead) return;
        if (ByteOffset < 0 || BytesNum < 0 || ByteOffset + BytesNum > _BytesNum) return;
        auto* _MappedMemory = reinterpret_cast<std::uint8_t*>(
                glMapNamedBufferRange(_handle, ByteOffset, BytesNum, static_cast<GLenum>(BufferMapAccessFlag::MAP_WRITE_BIT))
        );
        if (_MappedMemory) Handler(_MappedMemory, BytesNum);
        glUnmapNamedBuffer(_handle);
    }

    using MappedMemoryWriter = std::function<void(UInt8*, Int64)>;

    /*
     * map a block of mutable memory, advised for whole block filling
     * then execute a handler you specified
     * @offset : mapped memory' offset to whole buffer
     * @size : mapped memory' size
     * @writer : [ ] (std::uint8_t* data, std::int64_t size) {}
     * @should_async : if true, this func will not ensure the operation to buffer will work when it end, if false ..
     * */
    void ExecuteMappedMemoryWriter(Int64 ByteOffset, Int64 BytesNum, const MappedMemoryWriter& Writer)
    {
        if (!_StorageOptions.MapWrite) return;
        if (ByteOffset <0 || BytesNum < 0 || ByteOffset + BytesNum > _BytesNum) return;
        auto* _MappedMemory = reinterpret_cast<std::uint8_t*>(
            glMapNamedBufferRange(_handle, ByteOffset, BytesNum, static_cast<GLenum>(BufferMapAccessFlag::MAP_WRITE_BIT))
        );
        if (_MappedMemory) Writer(_MappedMemory, BytesNum);
        glFlushMappedNamedBufferRange(_handle, ByteOffset, BytesNum);
        glUnmapNamedBuffer(_handle);
    }

    using MappedMemoryReader = std::function<void(const UInt8*, Int64)>;

    /*
    * advised for whole block reading
     * map a block of immutable memory
     * then execute a handler you specified (can not do any modification)
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * [ ] (const std::uint8_t* data, std::int64_t size) { }
     * */
    void ExecuteMappedMemoryReader(Int64 ByteOffset, Int64 BytesNum, const MappedMemoryReader& Reader) const
    {
        if (!_StorageOptions.MapRead) return;
        if (ByteOffset < 0 || BytesNum < 0 || ByteOffset + BytesNum > _BytesNum) return;
        const auto* _MappedMemory = reinterpret_cast<const std::uint8_t*>(
                glMapNamedBufferRange(_handle, ByteOffset, BytesNum, static_cast<GLenum>(BufferMapAccessFlag::MAP_READ_BIT))
        );
        if (_MappedMemory) Reader(_MappedMemory, BytesNum);
        glUnmapNamedBuffer(_handle);
    }

    void Clear(Int64 ByteOffset, const UInt8* BytesMask, Int64 BytesNum)
    {
        if (!BytesMask) return;
        if (ByteOffset < 0 || BytesNum <0 || ByteOffset + BytesNum > _BytesNum) return;
        if (BytesNum % BytesNum != 0) return;
        
        glClearNamedBufferSubData(_handle, GL_R8UI, ByteOffset, BytesNum, GL_RED, GL_UNSIGNED_BYTE, BytesMask);
    }

public:

    /*
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     * */
    static void Memcpy(const Buffer* Dest, Int64 DestByteOffset, const Buffer* Src, Int64 SrcByteOffset, Int64 BytesNum)
    {
        if (!Dest || !Src) return;
        glCopyNamedBufferSubData(Src->get_handle(), Dest->get_handle(), SrcByteOffset, DestByteOffset, BytesNum);
    }


private:

    /*
     * Invalidate the whole buffers, data in buffers will become undefined.
     * */
    void _Invalidate()
    {
        glInvalidateBufferData(_handle);
    }

    /*
     * grab another same buffers storage as new one
     * */
    void _Invalidate(Int64 ByteOffset, Int64 BytesNum)
    {
        glInvalidateBufferSubData(_handle, ByteOffset, BytesNum);
    }

    inline std::int64_t _get_buffer_size() const
    {
        std::int64_t _buffer_size = 0;
        glGetNamedBufferParameteri64v(_handle, GL_BUFFER_SIZE, &_buffer_size);
        return _buffer_size;
    }

    inline std::uint8_t _get_buffer_mapped_state() const
    {
        std::int32_t _buffer_mapped_state = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_MAPPED, &_buffer_mapped_state);
        return _buffer_mapped_state == GL_TRUE;
    }

    inline std::int32_t _get_buffer_access() const
    {
        std::int32_t _buffer_access = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_ACCESS, &_buffer_access);
        return _buffer_access;
    }

    inline std::int32_t _get_buffer_usage() const
    {
        std::int32_t _buffer_usage = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_USAGE, &_buffer_usage);
        return _buffer_usage;
    }

private:

    BufferStorageOptions _StorageOptions;

    Int64 _BytesNum;

    const static std::int64_t THEORETICAL_MAX_CAPACITY;

    const static std::int64_t HARDWARE_MAX_CAPACITY;

    const static std::int64_t GPU_MAX_CAPACITY;

    const static std::int64_t BUFFER_AVAILABLE_MAX_CAPACITY;

};



#endif
