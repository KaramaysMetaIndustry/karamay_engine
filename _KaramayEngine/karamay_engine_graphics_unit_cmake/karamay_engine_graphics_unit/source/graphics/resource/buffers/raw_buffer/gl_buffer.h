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
    MAP_FLUSH_EXPLICIT_BIT = GL_MAP_FLUSH_EXPLICIT_BIT, // if true, gl will flush data from client to server until you explicitly called glFlushMapRanage()
    MAP_UNSYNCHRONIZED_BIT = GL_MAP_UNSYNCHRONIZED_BIT // if true, do not sync when you map the buffer, the operation will be undefined
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
    bool map_read; // can exec map reader
    bool map_write; // can exec map writer
    bool dynamic_storage; // can immediatly write
    bool client_storage; // store at client
    bool map_persistent; //
    bool map_coherent; //

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
    bool map_read;
    bool map_write;
    bool map_presistent;
    bool map_coherent;
    bool map_invalidate_range;
    bool map_invalidate_buffer;
    bool map_flush_explicit;
    bool map_unsynchronized;

    std::uint32_t bitfield()
    {
        std::uint32_t _access_flags = 0;

        if (map_read) _access_flags |= GL_MAP_READ_BIT;
        if (map_write) _access_flags |= GL_MAP_WRITE_BIT;
        if (map_presistent) _access_flags |= GL_MAP_PERSISTENT_BIT;
        if (map_coherent) _access_flags |= GL_MAP_COHERENT_BIT;
        if (map_invalidate_range) _access_flags |= GL_MAP_INVALIDATE_RANGE_BIT;
        if (map_invalidate_buffer) _access_flags |= GL_MAP_INVALIDATE_BUFFER_BIT;
        if (map_flush_explicit) _access_flags |= GL_MAP_FLUSH_EXPLICIT_BIT;
        if (map_unsynchronized) _access_flags |= GL_MAP_UNSYNCHRONIZED_BIT;

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

    gl_buffer(gl_buffer_storage_options storage_options, int64 bytes_num, const void* initial_data = nullptr) : gl_object(gl_object_type::BUFFER_OBJ),
        _buffer_storage_options(storage_options), 
        _bytes_num(bytes_num)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferStorage(_handle, _bytes_num, initial_data, _buffer_storage_options.bitfield());
    }
        
    gl_buffer(const gl_buffer&) = delete;
    gl_buffer& operator=(const gl_buffer&) = delete;

    ~gl_buffer() override
    {
        glDeleteBuffers(1, &_handle);
    }

public:

    void reallocate(int64 bytes_num, const void* initial_data = nullptr)
    {
        uint32 _new_handle = 0;
        glCreateBuffers(1, &_handle);
        glNamedBufferStorage(_new_handle, bytes_num, initial_data, _buffer_storage_options.bitfield());
        glCopyNamedBufferSubData(_handle, _new_handle, 0, 0, bytes_num > _bytes_num ? _bytes_num : bytes_num);
        glDeleteBuffers(1, &_handle);
        _handle = _new_handle;
        _bytes_num = bytes_num;
    }

    void reallocate(gl_buffer_storage_options options, int64 bytes_num, const void* initial_data = nullptr)
    {
        uint32 _new_handle = 0;
        glCreateBuffers(1, &_handle);
        glNamedBufferStorage(_new_handle, bytes_num, initial_data, options.bitfield());
        glCopyNamedBufferSubData(_handle, _new_handle, 0, 0, bytes_num > _bytes_num ? _bytes_num : bytes_num);
        glDeleteBuffers(1, &_handle);
        _handle = _new_handle;
        _bytes_num = bytes_num;
        _buffer_storage_options = options;
    }


    /*
    * client [ N ] => server [ N ] 
    * write byte stream into buffer
    */
    std::shared_ptr<gl_fence> write(int64 byte_offset, const void* bytes, int64 bytes_num, bool syncable = false) noexcept
    {
        if (!_buffer_storage_options.dynamic_storage) return nullptr;
        if (!bytes) return nullptr;
        if (byte_offset < 0 || bytes_num < 0 || byte_offset + bytes_num > _bytes_num) return nullptr;

        glNamedBufferSubData(_handle, byte_offset, bytes_num, bytes);

        if (syncable)
            return std::make_shared<gl_fence>();
        return nullptr;
    }

    /*
    * server [ N ] => client [ N ]
    * read byte stream from buffer
    */
    std::shared_ptr<gl_fence> read(int64 byte_offset, int64 bytes_num, void* _out_data, bool syncable = false) const noexcept
    {
        if (byte_offset < 0 || bytes_num < 0 || byte_offset + bytes_num > _bytes_num) return nullptr;
        glGetNamedBufferSubData(_handle, byte_offset, bytes_num, _out_data);
        if (syncable)
            return std::make_shared<gl_fence>();
        return nullptr;
    }

public:

    /*
     * server [ N ] => client [ N ] 
     * advised for whole block reading
     * map a block of immutable memory
     * then execute a handler you specified (can not do any modification)
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * [ ] (const std::uint8_t* data, std::int64_t size) { }
     * */
    std::shared_ptr<gl_fence> execute_mapped_memory_reader(int64 byte_offset, int64 bytes_num, const mapped_memory_reader& reader, bool syncable = false) const
    {
        // if map_read is not set, this func can not be used
        if (!_buffer_storage_options.map_read) return nullptr;
        // check the parameters range
        if (byte_offset < 0 || byte_offset < 0 || byte_offset + byte_offset > _bytes_num) return nullptr;

        // construct the access options
        gl_buffer_map_access_options _access_options;
        _access_options.map_read = true;

        if (_buffer_storage_options.map_persistent)
        {
            // if persistent and not coherent, we should set memory barrier manually to make sure
            if (!_buffer_storage_options.map_coherent)
            {
                glMemoryBarrier(GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT);
            }
            // if server can write this buffer when mapped by client, you need to sync result when you want to read it
            auto sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0); //glFinish();
            //glWaitSync(sync, 0, 1000);
            //glClientWaitSync(sync, 0, 1000);
        }

        const void* _mapped_memory = glMapNamedBufferRange(_handle, byte_offset, bytes_num, _access_options.bitfield());

        if (_mapped_memory) 
        {
            reader(_mapped_memory, bytes_num);
        } 
        
        glUnmapNamedBuffer(_handle);

        if (syncable)
            return std::make_shared<gl_fence>();
        return nullptr;
    }

    /*
     * client [ N ] => server [ N ]
     * map a block of mutable memory, advised for whole block filling
     * then execute a handler you specified
     * @offset : mapped memory' offset to whole buffer
     * @size : mapped memory' size
     * @writer : [ ] (void* mapped_memory, int64 size) {}
     * @should_async : if true, this func will not ensure the operation to buffer will work when it end, if false ..
     * */
    std::shared_ptr<gl_fence> execute_mapped_memory_writer(int64 byte_offset, int64 bytes_num, const mapped_memory_writer& writer, bool syncable = false)
    {
        // if the buffer storage option does not have map_write true, this func can not use
        if (!_buffer_storage_options.map_write) return nullptr;
        // check the parameters range
        if (byte_offset < 0 || bytes_num < 0 || byte_offset + bytes_num > _bytes_num) return nullptr;

        // construct access options bitfield
        gl_buffer_map_access_options _access_options;
        _access_options.map_write = true;

        // if persistent and not coherent, we must manually set memory barrier to make sure next writing safe
        if (_buffer_storage_options.map_persistent && !_buffer_storage_options.map_coherent)
        {
            glMemoryBarrier(GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT);
        }

        // map the buffer memory from GPU
        void* _mapped_memory = glMapNamedBufferRange(_handle, byte_offset, bytes_num, _access_options.bitfield());

        // make sure the pointer is valid
        if (_mapped_memory) 
        {
            writer(_mapped_memory, bytes_num);
        }

        //glFlushMappedNamedBufferRange(_handle, byte_offset, bytes_num);
        // unmap the buffer memory
        glUnmapNamedBuffer(_handle);

        if (syncable)
            return std::make_shared<gl_fence>();
        return nullptr;
    }

    /*
     * server [ N ] => client [ N ]
     * client [ N ] => server [ N ]
     * advised for dispersed filling
     * execute a handler(which can read/write) on mapped memory (specified by offset and size)
     * mapped memory has valid content which come from GPU memory
     * also your bytes write into mapped memory can affect GPU memory
     * @Handler(std::function<void(UInt8* MappedMemory, Int64 BytesNum)>)
     * syncable : if true, return a fence to confirm whether this action has been finished, if false, return nullptr
     * */
    std::shared_ptr<gl_fence> execute_mapped_memory_handler(int64 byte_offset, int64 bytes_num, const mapped_memory_handler& handler, bool syncable = false)
    {
        if (!_buffer_storage_options.map_write || !_buffer_storage_options.map_read) return nullptr;
        if (byte_offset < 0 || bytes_num < 0 || byte_offset + bytes_num > _bytes_num) return nullptr;

        gl_buffer_map_access_options _access_options;
        _access_options.map_write = true;
        _access_options.map_read = true;

        if (_buffer_storage_options.map_persistent)
        {
            if (!_buffer_storage_options.map_coherent)
            {
                glMemoryBarrier(GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT);
            }
            if (!_buffer_storage_options.map_coherent)
            {
                glMemoryBarrier(GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT);
            }
        }

        auto* _mapped_memory = reinterpret_cast<void*>(
            glMapNamedBufferRange(_handle, byte_offset, bytes_num, _access_options.bitfield())
            );

        if (_mapped_memory) handler(_mapped_memory, bytes_num);

        glUnmapNamedBuffer(_handle);

        if (syncable) 
            return std::make_shared<gl_fence>();
        return nullptr;
    }

    /*
     * client [ 1 ] => server [ N ]
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     */
    std::shared_ptr<gl_fence> clear(int64 byte_offset, const void* mask, int64 bytes_num, bool syncable = false)
    {
        if (!mask) return nullptr;
        if (byte_offset < 0 || bytes_num < 0 || byte_offset + bytes_num > _bytes_num) return nullptr;
        if (bytes_num % _bytes_num != 0) return nullptr;
        
        glClearNamedBufferSubData(_handle, GL_R8UI, byte_offset, bytes_num, GL_RED, GL_UNSIGNED_BYTE, mask);
        if(syncable)
            return std::make_shared<gl_fence>();
        return nullptr;
    }
 
    /*
    * server => server
    * memcpy from src buffer
    */
    std::shared_ptr<gl_fence> memcpy(int64 destination_byte_offset, const gl_buffer* source, int64 source_byte_offset, int64 bytes_num, bool syncable = false)
    {
        if (!source) return nullptr;
        glCopyNamedBufferSubData(source->get_handle(), _handle, source_byte_offset, destination_byte_offset, bytes_num);

        if (syncable)
            return std::make_shared<gl_fence>();
        return nullptr;
    }

public:

    int64 get_bytes_num() const { return _bytes_num; }

    const gl_buffer_storage_options& get_buffer_storage_options() const { return _buffer_storage_options; }

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
