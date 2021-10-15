#ifndef GL_BUFFER_H
#define GL_BUFFER_H

#include "graphics/glo/gl_object.h"
#include "graphics/glsl/glsl_class.h"

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
    MAP_READ_BIT = GL_MAP_READ_BIT,
    MAP_WRITE_BIT = GL_MAP_WRITE_BIT,
    DYNAMIC_STORAGE_BIT = GL_DYNAMIC_STORAGE_BIT,
    CLIENT_STORAGE_BIT = GL_CLIENT_STORAGE_BIT,
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

struct gl_buffer_storage_options
{
    std::uint8_t is_map_read;
    std::uint8_t is_map_write;
    std::uint8_t is_dynamic_storage;
    std::uint8_t is_client_storage;
    std::uint8_t is_map_persistent;
    std::uint8_t is_map_coherent;

    bool operator==(const gl_buffer_storage_options& other) const
    {
        return other.is_map_read == is_map_read &&
               other.is_map_write == is_map_write &&
               other.is_map_coherent == is_map_coherent &&
               other.is_map_persistent == is_map_persistent &&
               other.is_dynamic_storage == is_dynamic_storage &&
               other.is_client_storage == is_client_storage;
    }

    gl_buffer_storage_options() = default;
};

/*
* 目前认为将填充逻辑优化完全下放给特化buffer是较好的选择，在buffer层面无法做到较全面的具化（或控制粒度不够）
* 并且我认为buffer层仅需要保证好性能与基础同步即可，前几个版本的迭代中发现如果在buffer中做填充逻辑，会导致难以权衡性能
* buffer目前需要较完备的调度逻辑，但是内存重分配在特化buffer层面依然有分歧，
* 并且我不认为特化buffer应该继承自此，因为有大量的逻辑不具备让virtual函数展开，参数不同
*/
class gl_buffer final : public gl_object{
public:

    /*
    * GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
    * GL_DYNAMIC_STORAGE_BIT | GL_CLIENT_STORAGE_BIT
    */
    explicit gl_buffer(std::int64_t capacity, gl_buffer_storage_options storage_options) :
            _storage_options(storage_options)
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

    ~gl_buffer() override;


public:

    std::int64_t size() const
    {
        return _size;
    }

public:

    /*
    * write byte stream into buffer, this operation will affect GPU memory immediately
	*
    */
    inline void write(std::int64_t offset, const std::uint8_t* data, std::int64_t size)
    {
        if(offset < 0 || offset >= _size || offset + size > _size) return;
        glNamedBufferSubData(_handle, offset, size, data);
    }

    inline void read(std::int64_t offset, std::int64_t size, void* out_data)
    {
        glGetNamedBufferSubData(_handle, offset, size, out_data);
    }


public:

    /*
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     * */
    template<typename GLSL_T>
    inline void overwrite_by_unit(std::int64_t offset, std::int64_t size, const GLSL_T& unit)
    {
        glClearNamedBufferSubData(_handle, 0, offset, size, 0, 0, reinterpret_cast<const std::uint8_t*>(&unit));
    }

public:

    using mapped_memory_handler = std::function<void(std::uint8_t*, std::int64_t)>;

    using mapped_memory_writer = std::function<void(std::uint8_t*, std::int64_t)>;

    using mapped_memory_reader = std::function<void(const std::uint8_t*, std::int64_t)>;

    /*
     * execute a handler(which can read/write) on mapped memory (specified by offset and size)
     * mapped memory has valid content which come from GPU memory
     * also your bytes write into mapped memory can affect GPU memory
     * */
    void execute_mapped_memory_handler(std::int64_t offset, std::int64_t size, const mapped_memory_handler& handler, std::uint8_t should_async = false)
    {
        if (offset < 0 || size < 0 || offset + size > _size) return;
        auto* _mapped_memory = reinterpret_cast<std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_WRITE_BIT))
        );
        if (_mapped_memory) handler(_mapped_memory, size);
        glUnmapNamedBuffer(_handle);
    }

    /*
     * map a block of mutable memory
     * then execute a handler you specified
     * @offset : mapped memory' offset to whole buffer
     * @size : mapped memory' size
     * @writer : void(mapped_memory_block, mapped_memory_block_size)
     * @should_async : if true, this func will not ensure the operation to buffer will work when it end, if false ..
     * */
    void execute_mapped_memory_writer(std::int64_t offset, std::int64_t size, const mapped_memory_writer& writer, bool should_async = false)
    {
        if (offset <0 || size < 0 || offset + size > _size) return;

        auto* _mapped_memory = reinterpret_cast<std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, size, GL_MAP_WRITE_BIT)
        );

        if (_mapped_memory)
        {
            writer(_mapped_memory, size);
            glFlushMappedNamedBufferRange(_handle, offset, size);
            //glMemoryBarrier();
        } // make sure modification pushed to GPU

        glUnmapNamedBuffer(_handle);
    }

    /*
     * map a block of immutable memory
     * then execute a handler you specified (can not do any modification)
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * */
    void execute_mapped_memory_reader(std::int64_t offset, std::int64_t size, const mapped_memory_reader& reader, std::uint8_t should_async = false) const {
        if (offset < 0 || size < 0 || offset + size > _size) return;

        const auto* _mapped_memory = reinterpret_cast<const std::uint8_t*>(
                glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_READ_BIT))
        );

        if (_mapped_memory) reader(_mapped_memory, size);

        glUnmapNamedBuffer(_handle);
    }



public:

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

public:

    void copy()
    {}


private:

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

    std::int64_t _size;

    gl_buffer_storage_options _storage_options;

private:

    const static std::int64_t THEORETICAL_MAX_CAPACITY;

    const static std::int64_t HARDWARE_MAX_CAPACITY;

    const static std::int64_t GPU_MAX_CAPACITY;

    const static std::int64_t BUFFER_AVAILABLE_MAX_CAPACITY;

};

class gl_dynamic_buffer{
public:
    gl_dynamic_buffer();

};


enum class gl_uniform_buffer_memory_layout
{
    std140,
    shared,
    packed
};

enum class gl_uniform_buffer_matrix_layout
{
    row_major,
    column_major
};

struct gl_uniform_buffer_block_layout{
    std::uint32_t binding;
    std::int64_t offset;
    std::int64_t size;
    std::shared_ptr<glsl_uniform_block_t> block;
};

struct gl_uniform_buffer_block_state
{

};

struct gl_uniform_buffer_descriptor{
    gl_uniform_buffer_memory_layout memory_layout;
    gl_uniform_buffer_matrix_layout matrix_layout;
    std::vector<std::shared_ptr<glsl_uniform_block_t>> uniform_blocks;
    std::vector<std::shared_ptr<gl_uniform_buffer_block_state>> uniform_block_states;
};

class gl_uniform_buffer final{
public:
    struct gl_uniform_buffer_block_layout{
        std::uint32_t baked_binding;
        std::int64_t baked_offset;
        std::int64_t baked_size;
        std::shared_ptr<glsl_uniform_block_t> block;
    };

public:
    gl_uniform_buffer() = delete;
    explicit gl_uniform_buffer(const gl_uniform_buffer_descriptor& descriptor)
    {
        _initialize_ubo(descriptor);
    }
    gl_uniform_buffer(const gl_uniform_buffer&) = delete;
    gl_uniform_buffer& operator=(const gl_uniform_buffer&) = delete;

    ~gl_uniform_buffer() = default;

public:

    void bind() noexcept
    {
        if(!_buffer) return;

        for(const auto& _block_layout : _layouts)
        {
            glBindBufferRange(GL_UNIFORM_BUFFER, _block_layout.baked_binding, _buffer->get_handle(),_block_layout.baked_offset, _block_layout.baked_size);
        }
    }

    void unbind() noexcept
    {
        if(!_buffer) return;
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

public:

    void flush_dirty_blocks() noexcept
    {
        for(const auto& _layout : _layouts)
        {
            if(_layout.block && _layout.block->is_dirty())
            {
                if(!_layout.block->data()) return;
                _buffer->write(_layout.baked_offset, _layout.block->data(), _layout.baked_size);
                _layout.block->mark_dirty(false);
            }
        }
    }

    void read_back() noexcept
    {
        if(!_buffer) return;
        _buffer->execute_mapped_memory_reader(0, _buffer->size(),
                                              [this](const uint8_t* data, std::int64_t size){
                                                  for(const auto& _layout : _layouts)
                                                  {
                                                      std::memcpy(_layout.block->data(), data + _layout.baked_offset, _layout.baked_size);
                                                  }
                                              });
    }

private:

    std::unique_ptr<gl_buffer> _buffer;

    std::vector<gl_uniform_buffer_block_layout> _layouts;

private:
    // initialize ubo
    void _initialize_ubo(const gl_uniform_buffer_descriptor& descriptor)
    {
        switch (descriptor.memory_layout) {
            case gl_uniform_buffer_memory_layout::std140:
                _initialize_ubo_std140(descriptor.uniform_blocks);
                break;
            case gl_uniform_buffer_memory_layout::shared:
                _initialize_ubo_shared(descriptor.uniform_blocks);
                break;
            case gl_uniform_buffer_memory_layout::packed:
                _initialize_ubo_packed(descriptor.uniform_blocks);
                break;
        }
    }
    // default memory layout
    void _initialize_ubo_std140(const std::vector<std::shared_ptr<glsl_uniform_block_t>>& uniform_blocks)
    {
        std::int64_t _ubo_initialization_size = 0;
        std::int64_t _block_offset = 0;
        for(std::uint32_t _index = 0; _index < uniform_blocks.size(); ++_index)
        {
            const std::int64_t& _block_size = uniform_blocks[_index]->size();
            // generate layout
            _layouts.push_back({_index, _block_offset, _block_size, uniform_blocks[_index]});
            // calc offset/ total size
            const std::int64_t _raw_block_offset = _block_offset + _block_size;
            _block_offset += _raw_block_offset -
                             _raw_block_offset%GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT +
                             GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT;
            _ubo_initialization_size += _block_offset;
        }

        // create ubo
        gl_buffer_storage_options _options{
                true, true, true, true,
                false,false
        };
        _buffer = std::make_unique<gl_buffer>(_ubo_initialization_size, _options);
        if(_buffer)
        {
            // init, upload data to gpu
            _buffer->execute_mapped_memory_writer(0, _buffer->size(),[this](std::uint8_t * data, std::int64_t size){
                // set with zero
                std::memset(data, 0, size);
                // fill with blocks data
                for(const auto& _layout : _layouts)
                {
                    std::uint8_t* _src_data = _layout.block->data();
                    std::int64_t _src_size = _layout.block->size();
                    std::memcpy(data, _src_data, _src_size);
                    data += _layout.baked_offset;
                }
            });
        }
    }
    // TODO
    void _initialize_ubo_shared(const std::vector<std::shared_ptr<glsl_uniform_block_t>>& uniform_blocks){}
    // TODO
    void _initialize_ubo_packed(const std::vector<std::shared_ptr<glsl_uniform_block_t>>& uniform_blocks){}

};


enum class gl_shader_storage_buffer_memory_layout
{
    std140,
    std430
};

enum class gl_shader_storage_buffer_matrix_layout
{
    row_major,
    column_major
};

struct glsl_shader_storage_block_state
{

};

struct gl_shader_storage_buffer_descriptor{
    gl_shader_storage_buffer_memory_layout memory_layout;
    gl_shader_storage_buffer_matrix_layout matrix_layout;
    std::vector<std::shared_ptr<glsl_shader_storage_block_t>> shader_storage_blocks;
    std::vector<std::shared_ptr<glsl_shader_storage_block_state>> shader_storage_block_states;
};

class gl_shader_storage_buffer final{
public:
    gl_shader_storage_buffer() = default;
    explicit gl_shader_storage_buffer(const gl_shader_storage_buffer_descriptor& descriptor)
    {
        _initialize_ssbo(descriptor);
    }

public:

    void bind()
    {}

    void unbind();

    void flush_dirty_blocks()
    {

    }

private:

    void _generate_memory_layout()
    {

    }

    void _initialize_ssbo(const gl_shader_storage_buffer_descriptor& descriptor)
    {
        switch (descriptor.memory_layout) {
            case gl_shader_storage_buffer_memory_layout::std140:
                _initialize_ssbo_std140(descriptor);
                break;
            case gl_shader_storage_buffer_memory_layout::std430:
                _initialize_ssbo_std430(descriptor);
                break;
        }
    }

    void _initialize_ssbo_std140(const gl_shader_storage_buffer_descriptor& descriptor)
    {

    }

    void _initialize_ssbo_std430(const gl_shader_storage_buffer_descriptor& descriptor)
    {}


};


// 0xFC807e12026BedD66DD1f6e853fd93beBEA66558
struct gl_transform_feedback_buffer_descriptor{
    std::vector<glsl_vertex_stream> vertex_stream;
};

class gl_transform_feedback_buffer {
public:
    gl_transform_feedback_buffer() = delete;
    explicit gl_transform_feedback_buffer(const gl_transform_feedback_buffer_descriptor& descriptor)
    {

    }

    ~gl_transform_feedback_buffer() = default;

public:

    void bind(){
        if(!_buffer) return;
        glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0, _buffer->get_handle(), 0, 100);
    }

    void unbind(){
        if(!_buffer) return;
        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
    }

public:

    void flush(){}

    void read_back(){}

private:

    std::unique_ptr<gl_buffer> _buffer;

    void _initialize(const gl_transform_feedback_buffer_descriptor& descriptor)
    {
        gl_buffer_storage_options _options;
        _buffer = std::make_unique<gl_buffer>(100, _options);
        //_buffer->execute_mapped_memory_writer()
    }
};


struct gl_atomic_counter_buffer_descriptor{
    std::vector<std::shared_ptr<glsl_atomic_counter_t>> atomic_counters;
};

class gl_atomic_counter_buffer final{
    struct gl_atomic_counter_layout
    {
        std::uint32_t binding;
        std::int32_t offset;
        std::shared_ptr<glsl_atomic_counter_t> counter;
    };

public:
    gl_atomic_counter_buffer() = delete;
    explicit gl_atomic_counter_buffer(const gl_atomic_counter_buffer_descriptor& descriptor)
    {
        _initialize_acbo(descriptor);
    }

    ~gl_atomic_counter_buffer() = default;

public:

    void bind()
    {
        if(!_buffer) return;

        for(const auto& _layout: _layouts)
        {
            glBindBufferRange(GL_ATOMIC_COUNTER_BUFFER,
                              _layout.binding,
                              _buffer->get_handle(),_layout.offset, 4
            );
        }
    }

    void unbind()
    {
        if(!_buffer) return;

        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);

    }

private:

    std::unique_ptr<gl_buffer> _buffer;

    std::vector<gl_atomic_counter_layout> _layouts;

private:

    void _initialize_acbo(const gl_atomic_counter_buffer_descriptor& descriptor)
    {
        std::int64_t _acbo_initialization_size =
                static_cast<std::int64_t>(descriptor.atomic_counters.size() * sizeof (std::uint32_t));

        gl_buffer_storage_options _options{};
        _buffer = std::make_unique<gl_buffer>(_acbo_initialization_size, _options);
        if(!_buffer) return;

        _buffer->execute_mapped_memory_writer(0, _buffer->size(), [this](std::uint8_t* data, std::int64_t size){
            if(!data || size < 0) return;

            // no padding
            //std::memset(data,0, size);
            for(const auto& _layout : _layouts)
            {
                std::memcpy(data, &_layout.counter->data, 4);
                data += 4;
            }

        });
    }

};


struct gl_element_array_buffer_descriptor
{
    std::vector<std::uint32_t> primitives;
    std::uint32_t primitives_num;
};

class gl_element_array_buffer{
public:

    gl_element_array_buffer() = delete;
    explicit gl_element_array_buffer(const gl_element_array_buffer_descriptor& descriptor)
    {
        _initialize_ebo(descriptor);
    }

    ~gl_element_array_buffer() = default;

public:

    void bind()
    {
        if(!_buffer) return;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer->get_handle());
    }

    void unbind()
    {
        if(!_buffer) return;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

private:

    std::unique_ptr<gl_buffer> _buffer;

private:

    void _initialize_ebo(const gl_element_array_buffer_descriptor& descriptor)
    {
        std::int64_t _ebo_initialization_size = static_cast<std::int64_t>(descriptor.primitives.size() * sizeof (std::uint32_t));

        gl_buffer_storage_options _options{};
        _buffer = std::make_unique<gl_buffer>(_ebo_initialization_size, _options);

        _buffer->execute_mapped_memory_writer(0, _buffer->size(), [this](std::uint8_t* data, std::int64_t size){

        });
    }

};


#endif
