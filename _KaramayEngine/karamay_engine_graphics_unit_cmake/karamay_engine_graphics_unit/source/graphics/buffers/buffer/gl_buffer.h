#ifndef H_GL_BUFFER
#define H_GL_BUFFER

#include "graphics/glo/gl_object.h"
#include "graphics/buffers/buffer/gl_buffer_tools.h"



using gl_buffer_sptr = std::shared_ptr<class gl_buffer>;

/*
* 目前认为将填充逻辑优化完全下放给特化buffer是较好的选择，在buffer层面无法做到较全面的具化（或控制粒度不够）
* 并且我认为buffer层仅需要保证好性能与基础同步即可，前几个版本的迭代中发现如果在buffer中做填充逻辑，会导致难以权衡性能
* buffer目前需要较完备的调度逻辑，但是内存重分配在特化buffer层面依然有分歧，
* 并且我不认为特化buffer应该继承自此，因为有大量的逻辑不具备让virtual函数展开，参数不同
*/
class gl_buffer final : public gl_object
{
private:

    const static std::int64_t THEORETICAL_MAX_CAPACITY;

    const static std::int64_t HARDWARE_MAX_CAPACITY;

    const static std::int64_t GPU_MAX_CAPACITY;

    const static std::int64_t BUFFER_AVAILABLE_MAX_CAPACITY;

public:

    static std::shared_ptr<gl_buffer> new_buffer(std::int64_t capacity, gl_buffer_storage_options storage_options)
    {
        return std::make_shared<gl_buffer>(capacity, storage_options);
    }

    static std::shared_ptr<gl_buffer> new_buffer(std::int64_t capacity)
    {
        return std::make_shared<gl_buffer>(capacity, gl_buffer_storage_options());
    }

public:

	/*
	* GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
	* GL_DYNAMIC_STORAGE_BIT | GL_CLIENT_STORAGE_BIT
	*/
    explicit gl_buffer(std::int64_t capacity, gl_buffer_storage_options storage_options) : 
		_capacity(capacity),
		_storage_options(storage_options)
    {
        //_allocate_buffer();
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
        _release_buffer();
    }

private:

    /*
    * write byte stream into buffer, this operation will affect GPU memory immediately
	* 
    */
    inline void write(std::int64_t offset, const std::uint8_t* byte_stream, std::int64_t byte_stream_size)
    {
        if(!_check_object_validation() || !_storage_options.is_dynamic_storage || !byte_stream || offset < 0 || offset + byte_stream_size > _capacity) return;
        glNamedBufferSubData(_handle, offset, byte_stream_size, byte_stream);
		glMemoryBarrier(0);
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
		if (offset < 0 || size < 0 || offset + size > _capacity) return;
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
	void execute_mapped_memory_writer(std::int64_t offset, std::int64_t size, const mapped_memory_writer& writer, std::uint8_t should_async = false)
	{
		if (offset <0 || size < 0 || offset + size > _capacity) return;

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
		if (offset < 0 || size < 0 || offset + size > _capacity) return;

		const auto* _mapped_memory = reinterpret_cast<const std::uint8_t*>(
			glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(gl_buffer_map_access_flag::MAP_READ_BIT))
			);

		if (_mapped_memory) reader(_mapped_memory, size);

		glUnmapNamedBuffer(_handle);
	}

	
public:

    /*
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     * */
    void overwrite_by_byte(std::int64_t offset, std::int64_t size);

    template<typename GLSL_T>
    inline void overwrite_by_unit(std::int64_t offset, std::int64_t size, const GLSL_T& unit)
    {
        glClearNamedBufferSubData(_handle, 0, offset, size, 0, 0, reinterpret_cast<const std::uint8_t*>(&unit));
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
        if(offset < 0 || size < 0 || offset + size > _capacity) return; // VALUE_INVALID
        glInvalidateBufferSubData(_handle, offset, size);
    }

public:

	inline void copy_from(int64_t offset, gl_buffer_sptr& source_buffer, int64_t source_offset, int64_t byte_stream_size) 
	{
//		if (source_buffer.get_capacity() == _capacity)
//		{
//			glCopyNamedBufferSubData(_handle, target_buffer.get_handle(), 0, 0, _capacity);
//			glMemoryBarrier(0);
//		}
	}

	inline void copy_from(gl_buffer_sptr& source_buffer) 
	{
//		if (self_offset + output_size <= _capacity && target_offset + output_size <= target.get_capacity())
//		{
//			glCopyNamedBufferSubData(_handle, target.get_handle(), self_offset, target_offset, output_size);
//		}
	}


	std::int64_t get_capacity() const { return _capacity; }

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

    inline bool _check_capacity(std::int64_t capacity) const
    {
        return capacity != _capacity && capacity < BUFFER_AVAILABLE_MAX_CAPACITY;
    }

    std::uint8_t _check_object_validation() const override { return glIsBuffer(_handle) == GL_TRUE; }

    void _allocate_buffer()
    {
        glCreateBuffers(1, &_handle);
        if(_handle == 0) throw std::exception("can not allocate a new buffer");
        std::uint32_t _storage_flags = 0;
        glNamedBufferStorage(_handle, _capacity, nullptr, _storage_flags);
    }

    void _release_buffer()
    {
        glDeleteBuffers(1, &_handle);
    }

public:

    template<typename T>
    void print()
    {
        execute_immutable_memory_handler(0, _required_capacity, [](const std::uint8_t* data, std::int64_t size){
            const auto _data = reinterpret_cast<const T*>(data);
            if(_data)
            {
                for(std::int32_t _index = 0; _index < size/ sizeof(T); ++_index)
                {
                    std::cout<<": "<<_data[_index] <<std::endl;

                }
            }
        });
    }

private:

    void _reallocate(std::int64_t new_capacity);

	//void _allocate()
	//{
	//	// search the suitable buffers
	//	auto _it = std::find_if(_buffer_pool.begin(), _buffer_pool.end(), [&](const gl_buffer_pool_element& element) {
	//		return _check_buffer_validation(capacity, storage_options);
	//		});

	//	// do not find one, create a new one
	//	if (_it == _buffer_pool.end())
	//	{
	//		glCreateBuffers(1, &_handle);
	//		if (_handle != 0)
	//		{
	//			if (storage_options.is_map_read) _storage_flags |= GL_MAP_READ_BIT;
	//			if (storage_options.is_map_write) _storage_flags |= GL_MAP_WRITE_BIT;
	//			if (storage_options.is_map_persistent) _storage_flags |= GL_MAP_PERSISTENT_BIT;
	//			if (storage_options.is_map_coherent) _storage_flags |= GL_MAP_COHERENT_BIT;
	//			if (storage_options.is_client_storage) _storage_flags |= GL_CLIENT_STORAGE_BIT;
	//			if (storage_options.is_dynamic_storage) _storage_flags |= GL_DYNAMIC_STORAGE_BIT;

	//			glNamedBufferStorage(_handle, capacity, nullptr, _storage_flags);
	//			_required_capacity = capacity;
	//		}
	//	}
	//	else { // find a suitable buffers
	//	   // fetch
	//		_handle = _it->handle;
	//		_required_capacity = capacity;
	//		_storage_options = _it->storage_options;
	//		_storage_flags = _it->storage_flags;
	//		_capacity = _it->capacity;

	//		//_buffer_pool.remove(*_it);
	//	}
	//}

private:

    std::int64_t _capacity;

    gl_buffer_storage_options _storage_options;
};




//using BufferSPtr = gl_buffer_sptr;

#endif
