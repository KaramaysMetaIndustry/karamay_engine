#ifndef H_GL_BUFFER
#define H_GL_BUFFER

#include "graphics/glo/gl_object.h"
#include "graphics/buffers/buffer/gl_buffer_tools.h"


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

    ~gl_buffer() override
    {
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

#endif
