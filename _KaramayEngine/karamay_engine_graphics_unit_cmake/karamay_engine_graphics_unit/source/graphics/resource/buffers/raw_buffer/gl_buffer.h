#ifndef GL_BUFFER_H
#define GL_BUFFER_H

#include "graphics/resource/glo/gl_object.h"

enum class internal_format : GLenum
{
    R8 = GL_R8,
    R16 = GL_R16,
    R16F = GL_R16F,
    R32F = GL_R32F,
    R8I = GL_R8I,
    R16I = GL_R16I,
    R32I = GL_R32I,
    R8UI = GL_R8UI,
    R16UI = GL_R16UI,
    R32UI = GL_R32UI,
    RG8 = GL_RG8,
    RG16 = GL_RG16,
    RG16F = GL_RG16F,
    RG32F = GL_RG32F,
    RG8I = GL_RG8I,
    RG16I = GL_RG16I,
    RG32I = GL_RG32I,
    RG8UI = GL_RG8UI,
    RG16UI = GL_RG16UI,
    RG32UI = GL_RG32UI,
    RGB32F = GL_RGB32F,
    RGB32I = GL_RGB32I,
    RGB32UI = GL_RGB32UI,
    RGBA8 = GL_RGBA8,
    RGBA16 = GL_RGBA16,
    RGBA16F = GL_RGBA16F,
    RGBA32F = GL_RGBA32F,
    RGBA8I = GL_RGBA8I,
    RGBA16I = GL_RGBA16I,
    RGBA32I = GL_RGBA32I,
    RGBA8UI = GL_RGBA8UI,
    RGBA16UI = GL_RGBA16UI,
    RGBA32UI = GL_RGBA32UI
};

enum class format : GLenum
{
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    BGR = GL_BGR,
    RGBA = GL_RGBA,
    BGRA = GL_BGRA,
    RED_INTEGER = GL_RED_INTEGER,
    RG_INTEGER = GL_RG_INTEGER,
    RGB_INTEGER = GL_RGB_INTEGER,
    BGR_INTEGER = GL_BGR_INTEGER,
    RGBA_INTEGER = GL_RGBA_INTEGER,
    BGRA_INTEGER = GL_BGRA_INTEGER,
    STENCIL_INDEX = GL_STENCIL_INDEX,
    DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    DEPTH_STENCIL = GL_DEPTH_STENCIL
};

enum class data_type : GLenum
{
    HALF_FLOAT = GL_HALF_FLOAT,
    FLOAT = GL_FLOAT,

    BYTE = GL_BYTE,
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    SHORT = GL_SHORT,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    INT = GL_INT,
    UNSIGNED_INT = GL_UNSIGNED_INT,

    UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
    UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
    UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
    UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
    UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
    UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
    UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
    UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
    UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
};

enum class gl_buffer_type
{

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

enum class access : GLenum
{
    READ_WRITE = GL_READ_WRITE,
    READ_ONLY = GL_READ_ONLY,
    WRITE_ONLY = GL_WRITE_ONLY
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

/*
*
* 
*/
struct gl_buffer_storage_options
{
    std::uint8_t is_map_read;
    std::uint8_t is_map_write;
    std::uint8_t is_dynamic_storage;
    std::uint8_t is_client_storage;
    std::uint8_t is_map_persistent;
    std::uint8_t is_map_coherent;
};

/*
* 目前认为将填充逻辑优化完全下放给特化buffer是较好的选择，在buffer层面无法做到较全面的具化（或控制粒度不够）
* 并且我认为buffer层仅需要保证好性能与基础同步即可，前几个版本的迭代中发现如果在buffer中做填充逻辑，会导致难以权衡性能
* buffer目前需要较完备的调度逻辑，但是内存重分配在特化buffer层面依然有分歧，
* 并且我不认为特化buffer应该继承自此，因为有大量的逻辑不具备让virtual函数展开，参数不同
*/
class gl_buffer : public gl_object{
public:
    /*
    * GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
    * GL_DYNAMIC_STORAGE_BIT | GL_CLIENT_STORAGE_BIT
    */
    gl_buffer() = delete;
    explicit gl_buffer(std::int64_t capacity, gl_buffer_storage_options storage_options) : 
        gl_object(gl_object_type::BUFFER_OBJ),
        _storage_options(storage_options), _size(capacity)
    {
        glCreateBuffers(1, &_handle);
        if (_handle != 0)
        {
            std::uint32_t _storage_flags = 0;
            if (storage_options.is_map_read) _storage_flags |= GL_MAP_READ_BIT;
            if (storage_options.is_map_write) _storage_flags |= GL_MAP_WRITE_BIT;
            if (storage_options.is_map_persistent) _storage_flags |= GL_MAP_PERSISTENT_BIT;
            if (storage_options.is_map_coherent) _storage_flags |= GL_MAP_COHERENT_BIT;
            if (storage_options.is_client_storage) _storage_flags |= GL_CLIENT_STORAGE_BIT;
            if (storage_options.is_dynamic_storage) _storage_flags |= GL_DYNAMIC_STORAGE_BIT;

            glNamedBufferStorage(_handle, capacity, nullptr, _storage_flags);
        }
    }
    gl_buffer(const gl_buffer&) = delete;
    gl_buffer& operator=(const gl_buffer&) = delete;

    ~gl_buffer() override 
    {
        glDeleteBuffers(1, &_handle);
    }

public:

    /*
    * write byte stream into buffer, this operation will affect GPU memory immediately
    */
    void write(std::int64_t offset, const std::uint8_t* data, std::int64_t size)
    {
        if (!_storage_options.is_dynamic_storage) return;
        if (!data || offset < 0 || offset >= _size || offset + size > _size) return;

        glNamedBufferSubData(_handle, offset, size, data);
    }

    void read(std::int64_t offset, std::int64_t size, void* out_data)
    {
        if (offset < 0 || offset >= _size || offset + size > _size) return;

        glGetNamedBufferSubData(_handle, offset, size, out_data);
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
    void execute_mapped_memory_handler(std::int64_t offset, std::int64_t size, const mapped_memory_handler& handler, std::uint8_t should_async = false)
    {
        if (!_storage_options.is_map_write || !_storage_options.is_map_read ) return;
        if (offset < 0 || size < 0 || offset + size > _size) return;

        auto* _mapped_memory = reinterpret_cast<std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_WRITE_BIT))
        );
        if (_mapped_memory) handler(_mapped_memory, size);
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
    void execute_mapped_memory_writer(std::int64_t offset, std::int64_t size, const mapped_memory_writer& writer, bool should_async = false)
    {
        if (!_storage_options.is_map_write) return;
        if (offset <0 || size < 0 || offset + size > _size) return;

        auto* _mapped_memory = reinterpret_cast<std::uint8_t*>(
            glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_WRITE_BIT))
        );

        if (_mapped_memory)
        {
            writer(_mapped_memory, size);
            glFlushMappedNamedBufferRange(_handle, offset, size);
            //glMemoryBarrier();
            // make sure modification pushed to GPU
        }
        //glFinish();
        glUnmapNamedBuffer(_handle);
    }

    using mapped_memory_reader = std::function<void(const std::uint8_t*, std::int64_t)>;

    /*
    * advised for whole block reading
     * map a block of immutable memory
     * then execute a handler you specified (can not do any modification)
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * [ ] (const std::uint8_t* data, std::int64_t size) { }
     * */
    void execute_mapped_memory_reader(std::int64_t offset, std::int64_t size, const mapped_memory_reader& reader, std::uint8_t should_async = false) const 
    {
        if (!_storage_options.is_map_read) return;
        if (offset < 0 || size < 0 || offset + size > _size) return;

        const auto* _mapped_memory = reinterpret_cast<const std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_READ_BIT))
        );

        if (_mapped_memory) reader(_mapped_memory, size);

        glUnmapNamedBuffer(_handle);
    }

public:

    void clear(std::int64_t buffer_offset, std::uint8_t* data, std::int64_t data_size)
    {
        //glClearNamedBufferSubData(_handle, GL_UNSIGNED_BYTE, buffer_offset, data_size, GL_UNSIGNED_BYTE, )
    }

    /*
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     * */
    static void buffer_copy()
    {}

public:

    std::int64_t size() const
    {
        return _size;
    }

private:

    const gl_buffer_storage_options _storage_options;
    
    const std::int64_t _size;

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

template<typename GLSL_TRANSPARENT_T>
class gl_transparent_buffer : public gl_buffer
{

};

class gl_dynamic_buffer final : public gl_object{
public:
    gl_dynamic_buffer() = default;
};



#endif
