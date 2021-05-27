#pragma once
#include "graphics/glo/gl_object.h"

namespace gl_buffer_enum
{
	enum class target : GLenum
	{
		ARRAY_BUFFER = GL_ARRAY_BUFFER, //**
		ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER, // **

		UNIFORM_BUFFER = GL_UNIFORM_BUFFER, // **
		SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER, // **
		ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,

		DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,

		QUERY_BUFFER = GL_QUERY_BUFFER,
		PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
		PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,

		COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
		COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,

		DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
		
		TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
		TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER
	};

	enum class storage_flag : GLenum
	{
		MAP_READ_BIT = GL_MAP_READ_BIT,
		MAP_WRITE_BIT = GL_MAP_WRITE_BIT,

		DYNAMIC_STORAGE_BIT = GL_DYNAMIC_STORAGE_BIT,
		CLIENT_STORAGE_BIT = GL_CLIENT_STORAGE_BIT,

		MAP_PERSISTENT_BIT = GL_MAP_PERSISTENT_BIT,
		MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT
	};

	enum class usage : GLenum
	{
		STREAM_DRAW = GL_STREAM_DRAW,
		STREAM_READ = GL_STREAM_READ,
		STREAM_COPY = GL_STREAM_COPY,

		STATIC_DRAW = GL_STATIC_DRAW,
		STATIC_READ = GL_STATIC_READ,
		STATIC_COPY = GL_STATIC_COPY,

		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		DYNAMIC_READ = GL_DYNAMIC_READ,
		DYNAMIC_COPY = GL_DYNAMIC_COPY
	};

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
}

class gl_buffer : public gl_object
{
public:
	
	gl_buffer();

	virtual ~gl_buffer();

public:
	/**
	 * @size : bytes of size
	 * @is_dynamic_storage : if true,  
	 * @is_map_read : if true, you can read the map via mapping the buffer glMapBuffer/glMapNamedBuffer
	 * @is_map_persistent : if true, you can write the map via mapping the buffer
	 * @is_map_coherent :
	 * @is_client_storage :
	 */
	void allocate(std::size_t size, bool is_map_read = false, bool is_map_write = false, bool is_map_persistent = false, bool is_map_coherent= false, bool is_dynamic_storage = true, bool is_client_storage = true)
	{
		std::uint32_t flags = 0;
		if (is_dynamic_storage)
			flags = GL_DYNAMIC_STORAGE_BIT;
		if (is_map_read)
			flags = flags | GL_MAP_READ_BIT;
		if (is_map_write)
			flags = flags | GL_MAP_WRITE_BIT;
		if (is_map_persistent)
			flags = flags | GL_MAP_PERSISTENT_BIT;
		if (is_map_coherent)
			flags = flags | GL_MAP_COHERENT_BIT;
		if (is_client_storage)
			flags = flags | GL_CLIENT_STORAGE_BIT;

		glNamedBufferStorage(_handle, size, NULL, flags);
		_size = size;
	}

	void fill(std::size_t offset, std::size_t size, const void* data)
	{
		if (data && offset + size <= _size)
		{
			glNamedBufferSubData(_handle, offset, size, data);
		}
	}

	void clear(GLenum internal_format, GLenum format, GLenum type, const void* data);

	void clear(GLenum internal_format, GLenum format, GLenum type, const void* data, GLintptr offset, GLsizeiptr size);

	void copy_to(GLuint write_buffer_handle, GLintptr read_offset, GLintptr write_offset, GLsizeiptr size);

public:

	void* map(GLenum access);

	void* map(GLenum access, GLintptr offset, GLsizeiptr size);

	void flush_mapped_buffer(GLintptr offset, GLsizeiptr size);

	void unmap();

	void bind() {}

	void unbind() {}

private:
	
	int get_buffer_size() const
	{
		GLint value;
		glGetNamedBufferParameteriv(_handle, GL_BUFFER_SIZE, &value);
		return value;
	}

private:

	std::size_t _size;

	gl_buffer_enum::internal_format _internal_format;


public:
	const std::size_t get_size() const { return _size; }

	const gl_buffer_enum::internal_format get_internal_format() const { return _internal_format; }


};



class gl_buffer_referenece
{
public:

	std::shared_ptr<gl_buffer> _buffer;

	std::size_t _offset, _size;

public:

	void refer_to(std::size_t offset, std::size_t size, std::shared_ptr<gl_buffer> buffer)
	{
		_buffer = buffer;
		_offset = offset;
		_size = size;
	}

	void fill(const void* data)
	{
		if (_buffer)
		{
			_buffer->fill(_offset, _size, data);
		}
	}

	void release()
	{
		if (_buffer)
		{
			//_buffer->clear()
		}
	}

	std::uint32_t get_handle()
	{
		if (_buffer)
		{
			return _buffer->get_handle();
		}
	}

};




