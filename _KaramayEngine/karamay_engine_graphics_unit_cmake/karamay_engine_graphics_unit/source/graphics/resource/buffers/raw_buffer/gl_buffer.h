#ifndef GL_BUFFER_H
#define GL_BUFFER_H

#include "graphics/resource/glo/gl_object.h"

enum class gl_buffer_type
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

enum class gl_buffer_storage_flag : GLenum
{
    CLIENT_STORAGE_BIT = GL_CLIENT_STORAGE_BIT,
    DYNAMIC_STORAGE_BIT = GL_DYNAMIC_STORAGE_BIT,

    MAP_READ_BIT = GL_MAP_READ_BIT,
    MAP_WRITE_BIT = GL_MAP_WRITE_BIT,

    MAP_PERSISTENT_BIT = GL_MAP_PERSISTENT_BIT,
    MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT
};

enum class gl_buffer_map_access_flag : GLenum
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

enum class gl_buffer_memory_barrier_flag : GLenum
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

enum class gl_buffer_memory_barrier_region_flag
{
    UNIFORM_BARRIER_BIT = GL_UNIFORM_BARRIER_BIT,
    SHADER_STORAGE_BARRIER_BIT = GL_SHADER_STORAGE_BARRIER_BIT,
    ATOMIC_COUNTER_BARRIER_BIT = GL_ATOMIC_COUNTER_BARRIER_BIT,
    FRAMEBUFFER_BARRIER_BIT = GL_FRAMEBUFFER_BARRIER_BIT,
    SHADER_IMAGE_ACCESS_BARRIER_BIT = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
    TEXTURE_FETCH_BARRIER_BIT = GL_TEXTURE_FETCH_BARRIER_BIT
};

struct gl_buffer_storage_options
{
    bool map_read;
    bool map_write;
    bool dynamic_storage;
    bool client_storage;
    bool map_persistent;
    bool map_coherent;

    uint32 bitfield() const
    {
        uint32 _storage_flags = 0;
        if (map_read) _storage_flags |= GL_MAP_READ_BIT;
        if (map_write) _storage_flags |= GL_MAP_WRITE_BIT;
        if (dynamic_storage) _storage_flags |= GL_MAP_PERSISTENT_BIT;
        if (client_storage) _storage_flags |= GL_MAP_COHERENT_BIT;
        if (map_persistent) _storage_flags |= GL_CLIENT_STORAGE_BIT;
        if (map_coherent) _storage_flags |= GL_DYNAMIC_STORAGE_BIT;
        return _storage_flags;
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
class gl_buffer : public gl_object{
public:
    using mapped_memory_reader = std::function<void(const void*, int64)>;
    using mapped_memory_writer = std::function<void(void*, int64)>;
    using mapped_memory_handler = std::function<void(void*, int64)>;

    gl_buffer(gl_buffer_storage_options StorageOptions, int64 Size) :
        gl_object(gl_object_type::BUFFER_OBJ),
        _buffer_storage_options(StorageOptions), _bytes_num(Size)
    {
        glCreateBuffers(1, &_handle);
        if (_handle != 0)
        {
            glNamedBufferStorage(_handle, _bytes_num, nullptr, _buffer_storage_options.bitfield());
        }

    }

    gl_buffer(gl_buffer_storage_options StorageOptions, int64 Size, const uint8* InitializationBytes) :
        gl_object(gl_object_type::BUFFER_OBJ),
        _buffer_storage_options(StorageOptions), _bytes_num(Size)
    {
        glCreateBuffers(1, &_handle);
        if (_handle != 0)
        {
            glNamedBufferStorage(_handle, _bytes_num, InitializationBytes, _buffer_storage_options.bitfield());
        }
    }
        
    
    gl_buffer(const gl_buffer&) = delete;
    gl_buffer& operator=(const gl_buffer&) = delete;

    ~gl_buffer() override
    {
        glDeleteBuffers(1, &_handle);
    }

public:

    int64 get_bytes_num() const
    {
        return _bytes_num;
    }

    const gl_buffer_storage_options& get_buffer_storage_options() const { return _buffer_storage_options; }

public:

    /*
    * write byte stream into buffer, this operation will affect GPU memory immediately
    */
    void write(int64 byte_offset, const void* bytes, int64 bytes_num) noexcept
    {
        if (!_buffer_storage_options.dynamic_storage) return;
        if (!bytes) return;
        if (byte_offset < 0 || bytes_num < 0 || byte_offset + bytes_num > _bytes_num) return;

        glNamedBufferSubData(_handle, byte_offset, bytes_num, bytes);
    }

    const void* read(int64 byte_offset, int64 bytes_num) const noexcept
    {
        void* _out_data = nullptr;
        if (byte_offset < 0 || bytes_num < 0 || byte_offset + bytes_num > _bytes_num) return _out_data;
        glGetNamedBufferSubData(_handle, byte_offset, bytes_num, _out_data);
        return _out_data;
    }

public:

    /*
    * Server -> Client : Client -> Server
    * advised for dispersed filling
     * execute a handler(which can read/write) on mapped memory (specified by offset and size)
     * mapped memory has valid content which come from GPU memory
     * also your bytes write into mapped memory can affect GPU memory
     * @Handler(std::function<void(UInt8* MappedMemory, Int64 BytesNum)>)
     * */
    void execute_mapped_memory_handler(int64 byte_offset, int64 bytes_num, const mapped_memory_handler& handler)
    {
        if (!_buffer_storage_options.map_write && !_buffer_storage_options.map_read) return;
        if (byte_offset < 0 || bytes_num < 0 || byte_offset + bytes_num > _bytes_num) return;
        auto* _mapped_memory = reinterpret_cast<void*>(
                glMapNamedBufferRange(_handle, byte_offset, bytes_num, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_WRITE_BIT))
        );
        if (_mapped_memory) handler(_mapped_memory, bytes_num);
        glUnmapNamedBuffer(_handle);
    }

    /*
    * Client -> Server
     * map a block of mutable memory, advised for whole block filling
     * then execute a handler you specified
     * @offset : mapped memory' offset to whole buffer
     * @size : mapped memory' size
     * @writer : [ ] (std::uint8_t* data, std::int64_t size) {}
     * @should_async : if true, this func will not ensure the operation to buffer will work when it end, if false ..
     * */
    void execute_mapped_memory_writer(int64 byte_offset, int64 bytes_num, const mapped_memory_writer& writer)
    {
        if (!_buffer_storage_options.map_write) return;
        if (byte_offset <0 || bytes_num < 0 || byte_offset + bytes_num > _bytes_num) return;
        auto* _mapped_memory = reinterpret_cast<void*>(
            glMapNamedBufferRange(_handle, byte_offset, bytes_num, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_WRITE_BIT))
        );
        if (_mapped_memory) writer(_mapped_memory, bytes_num);
        glFlushMappedNamedBufferRange(_handle, byte_offset, bytes_num);
        glUnmapNamedBuffer(_handle);
    }

    /*
    * Server -> Client
    * advised for whole block reading
     * map a block of immutable memory
     * then execute a handler you specified (can not do any modification)
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * [ ] (const std::uint8_t* data, std::int64_t size) { }
     * */
    void execute_mapped_memory_reader(int64 byte_offset, int64 bytes_num, const mapped_memory_reader& reader) const
    {
        if (!_buffer_storage_options.map_read) return;
        if (byte_offset < 0 || byte_offset < 0 || byte_offset + byte_offset > _bytes_num) return;
        const auto* _mapped_memory = reinterpret_cast<const void*>(
                glMapNamedBufferRange(_handle, byte_offset, bytes_num, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_READ_BIT))
        );
        if (_mapped_memory) reader(_mapped_memory, bytes_num);
        glUnmapNamedBuffer(_handle);
    }

    void clear(int64 byte_offset, const void* mask, int64 bytes_num)
    {
        if (!mask) return;
        if (byte_offset < 0 || bytes_num <0 || byte_offset + bytes_num > _bytes_num) return;
        if (bytes_num % _bytes_num != 0) return;
        
        glClearNamedBufferSubData(_handle, GL_R8UI, byte_offset, bytes_num, GL_RED, GL_UNSIGNED_BYTE, mask);
    }

public:

    /*
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     * */
    static void memcpy(const gl_buffer* dest, int64 dest_byte_offset, const gl_buffer* src, int64 src_byte_offset, int64 bytes_num)
    {
        if (!dest || !src) return;
        glCopyNamedBufferSubData(src->get_handle(), dest->get_handle(), src_byte_offset, dest_byte_offset, bytes_num);
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
    void _Invalidate(int64 byte_offset, int64 bytes_num)
    {
        glInvalidateBufferSubData(_handle, byte_offset, bytes_num);
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

    gl_buffer_storage_options _buffer_storage_options;

    int64 _bytes_num;

};



#endif
