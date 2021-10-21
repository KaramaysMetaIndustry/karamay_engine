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

enum class gl_buffer_memory_barrier_flag
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
    bool is_map_read;
    bool is_map_write;
    bool is_dynamic_storage;
    bool is_client_storage;
    bool is_map_persistent;
    bool is_map_coherent;

    std::uint32_t bitfield() const
    {
        std::uint32_t _storage_flags = 0;
        if (is_map_read) _storage_flags |= GL_MAP_READ_BIT;
        if (is_map_write) _storage_flags |= GL_MAP_WRITE_BIT;
        if (is_map_persistent) _storage_flags |= GL_MAP_PERSISTENT_BIT;
        if (is_map_coherent) _storage_flags |= GL_MAP_COHERENT_BIT;
        if (is_client_storage) _storage_flags |= GL_CLIENT_STORAGE_BIT;
        if (is_dynamic_storage) _storage_flags |= GL_DYNAMIC_STORAGE_BIT;

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
    gl_buffer() = delete;
    explicit gl_buffer(gl_buffer_storage_options _storage_options, std::int64_t _size) :
        gl_object(gl_object_type::BUFFER_OBJ),
        storage_options(_storage_options), size(_size)
    {
        glCreateBuffers(1, &_handle);
        if (_handle != 0)
        {
            glNamedBufferStorage(_handle, size, nullptr, storage_options.bitfield());
        }
    }
    explicit gl_buffer(gl_buffer_storage_options _storage_options, std::int64_t _size, const std::uint8_t* initialization_data) :
        gl_object(gl_object_type::BUFFER_OBJ),
        storage_options(_storage_options), size(_size)
    {
        glCreateBuffers(1, &_handle);
        if (_handle != 0)
        {
            glNamedBufferStorage(_handle, size, initialization_data, storage_options.bitfield());
        }
    }
    
    gl_buffer(const gl_buffer&) = delete;
    gl_buffer& operator=(const gl_buffer&) = delete;

    ~gl_buffer() override 
    {
        glDeleteBuffers(1, &_handle);
    }

    const gl_buffer_storage_options storage_options;

    const std::int64_t size;

public:

    /*
    * write byte stream into buffer, this operation will affect GPU memory immediately
    */
    void write(std::int64_t offset, const std::uint8_t* data, std::int64_t data_size)
    {
        if (!storage_options.is_dynamic_storage) return; // 
        if (!data) return;
        if (offset < 0 || data_size < 0 || offset + data_size > size) return;

        glNamedBufferSubData(_handle, offset, data_size, data);
    }

    void read(std::int64_t offset, std::int64_t data_size, void* out_data)
    {
        if (offset < 0 || data_size < 0 || offset + data_size > size) return;

        glGetNamedBufferSubData(_handle, offset, data_size, out_data);
    }

public:

    using mapped_memory_handler = std::function<void(std::uint8_t*, std::int64_t)>;

    /*
    * advised for dispersed filling
     * execute a handler(which can read/write) on mapped memory (specified by offset and size)
     * mapped memory has valid content which come from GPU memory
     * also your bytes write into mapped memory can affect GPU memory
     * [ ] (std::uint8_t* data, std::int64_t size) { }
     * */
    void execute_mapped_memory_handler(std::int64_t offset, std::int64_t data_size, const mapped_memory_handler& handler, std::uint8_t should_async = false)
    {
        if (!storage_options.is_map_write && !storage_options.is_map_read) return;
        if (offset < 0 || data_size < 0 || offset + data_size > size) return;

        auto* _mapped_memory = reinterpret_cast<std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, data_size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_WRITE_BIT))
        );
        
        if (_mapped_memory) handler(_mapped_memory, data_size);

        glUnmapNamedBuffer(_handle);
    }

    template<typename GLSL_TRANSPARENT_T>
    using mapped_memory_handler_transparent_t = std::function<void(GLSL_TRANSPARENT_T*, std::int64_t)>;

    template<typename GLSL_TRANSAPRENT_T>
    void execute_mapped_memory_handler_transparent_t(std::int64_t offset, std::int64_t size, const mapped_memory_handler_transparent_t<GLSL_TRANSAPRENT_T>& handler, bool should_async = false)
    {

    }

    using mapped_memory_writer = std::function<void(std::uint8_t*, std::int64_t)>;

    /*
     * map a block of mutable memory, advised for whole block filling
     * then execute a handler you specified
     * @offset : mapped memory' offset to whole buffer
     * @size : mapped memory' size
     * @writer : [ ] (std::uint8_t* data, std::int64_t size) {}
     * @should_async : if true, this func will not ensure the operation to buffer will work when it end, if false ..
     * */
    void execute_mapped_memory_writer(std::int64_t offset, std::int64_t data_size, const mapped_memory_writer& writer, bool should_async = false)
    {
        if (!storage_options.is_map_write) return;
        if (offset <0 || data_size < 0 || offset + data_size > size) return;

        auto* _mapped_memory = reinterpret_cast<std::uint8_t*>(
            glMapNamedBufferRange(_handle, offset, data_size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_WRITE_BIT))
        );

        if (_mapped_memory) writer(_mapped_memory, data_size);

        glFlushMappedNamedBufferRange(_handle, offset, data_size);

        glUnmapNamedBuffer(_handle);
        
        //glMemoryBarrier();
        //glFinish();
    }

    using mapped_memory_reader = std::function<void(const std::uint8_t*, std::int64_t)>;

    /*
    * advised for whole block reading
     * map a block of immutable memory
     * then execute a handler you specified (can not do any modification)
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * [ ] (const std::uint8_t* data, std::int64_t size) { }
     * */
    void execute_mapped_memory_reader(std::int64_t offset, std::int64_t data_size, const mapped_memory_reader& reader, std::uint8_t should_async = false) const 
    {
        if (!storage_options.is_map_read) return;
        if (offset < 0 || data_size < 0 || offset + data_size > size) return;

        const auto* _mapped_memory = reinterpret_cast<const std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, data_size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_READ_BIT))
        );

        if (_mapped_memory) reader(_mapped_memory, data_size);

        glUnmapNamedBuffer(_handle);
    }

public:

    /*
    * 
    */
    void clear(std::int64_t offset, const std::uint8_t* data, std::int64_t data_size)
    {
        if (!data) return;
        if (offset < 0 || data_size <0 || offset + data_size > size) return;
        if (size % data_size != 0) return;
        
        glClearNamedBufferSubData(_handle, GL_R8UI, offset, data_size, GL_RED, GL_UNSIGNED_BYTE, data);
    }

    /*
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     * */
    void copy(std::int64_t offset, const std::shared_ptr<gl_buffer>& source, std::int64_t source_offset, std::int64_t data_size)
    {
        if (!source) return;
        if (offset < 0 || source_offset < 0 || data_size < 0 || offset + data_size > size || source_offset + data_size > source->size) return;

        glCopyNamedBufferSubData(source->get_handle(), _handle, source_offset, offset, data_size);
    }    

private:

    /*
     * Invalidate the whole buffers, data in buffers will become undefined.
     * */
    inline void invalidate()
    {
        glInvalidateBufferData(_handle);
    }

    /*
     * grab another same buffers storage as new one
     * */
    inline void invalidate(std::int64_t offset, std::int64_t size)
    {
        glInvalidateBufferSubData(_handle, offset, size);
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

    const static std::int64_t THEORETICAL_MAX_CAPACITY;

    const static std::int64_t HARDWARE_MAX_CAPACITY;

    const static std::int64_t GPU_MAX_CAPACITY;

    const static std::int64_t BUFFER_AVAILABLE_MAX_CAPACITY;

};

class gl_dynamic_buffer final : public gl_object{
public:
    gl_dynamic_buffer() = default;
};



#endif
