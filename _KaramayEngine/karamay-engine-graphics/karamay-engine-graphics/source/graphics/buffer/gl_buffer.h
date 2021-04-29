#pragma once
#include "graphics/glo/gl_object.h"

enum class gl_buffer_type : GLenum
{
	ARRAY_BUFFER = GL_ARRAY_BUFFER,
	ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,

	ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
	
	COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
	COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
	
	DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
	DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,
	
	PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
	PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
	
	QUERY_BUFFER = GL_QUERY_BUFFER,
	
	SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
	
	TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
	
	TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
	
	UNIFORM_BUFFER = GL_UNIFORM_BUFFER
};


enum class gl_buffer_flag : GLenum
{
	MAP_READ_BIT = GL_MAP_READ_BIT,
	MAP_WRITE_BIT = GL_MAP_WRITE_BIT,
	MAP_PERSISTENT_BIT = GL_MAP_PERSISTENT_BIT,
	MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT,
	CLIENT_STORAGE_BIT = GL_CLIENT_STORAGE_BIT

};

class gl_buffer_data_pack
{
public:
	static std::shared_ptr<gl_buffer_data_pack> construct() { return std::make_shared<gl_buffer_data_pack>(); }

	~gl_buffer_data_pack() 
	{
		delete data;
	}

private:
	gl_buffer_data_pack() {}


public:

	const void* data;
	unsigned int size;
};

template<typename T>
GLbitfield caculate()
{
	return 
}


template<typename T, typename... Ts>
GLbitfield caculate(T flag, Ts... flags)
{
	return caculate()
}


class gl_buffer final : public gl_object
{
public:
	static std::shared_ptr<gl_buffer> construct()
	{
		return std::make_shared<gl_buffer>();
	}

	~gl_buffer();

private:
	gl_buffer();

	gl_buffer_type _buffer_type;

	unsigned int _buffer_size;

public:
	void allocate(gl_buffer_type buffer_type, unsigned int buffer_size, std::vector<gl_buffer_flag> flags){
		if (buffer_size > GL_MAX_UNIFORM_BLOCK_SIZE) return;

		glNamedBufferStorage(_handle, static_cast<GLsizeiptr>(buffer_size), nullptr, static_cast<GLbitfield>(flags));
		
		_buffer_size = buffer_size;
		_buffer_type = buffer_type;
	}

	void fill(std::shared_ptr<gl_buffer_data_pack> data_pack, unsigned int offset = 0) {
		if (data_pack.get() && (offset + data_pack->size > _buffer_size)) {
			throw std::exception("do not have enough memory");
		}
		glNamedBufferSubData(_handle, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(data_pack->size), data_pack->data);
	}


	void clear(GLenum internal_format, GLenum format, GLenum type, const void* data);

	void clear(GLenum internal_format, GLenum format, GLenum type, const void* data, GLintptr offset, GLsizeiptr size);

	void copy_to(GLuint write_buffer_handle, GLintptr read_offset, GLintptr write_offset, GLsizeiptr size);

public:
	void* map(GLenum access);

	void* map(GLenum access, GLintptr offset, GLsizeiptr size);

	void flush_mapped_buffer(GLintptr offset, GLsizeiptr size);

	void unmap();

public:
	void bind();

	void unbind();

private:
	int get_buffer_size() const
	{
		GLint value;
		glGetBufferParameteriv(static_cast<GLenum>(_buffer_type), GL_BUFFER_SIZE, &value);
		return value;
	}

};


enum class GLUsage : GLenum
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

enum class GLInternalFormat : GLenum
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

enum class GLFormat : GLenum
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

enum class GLDataType : GLenum
{
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	BYTE = GL_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	SHORT = GL_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT,
	INT = GL_INT,
	HALF_FLOAT = GL_HALF_FLOAT,
	FLOAT = GL_FLOAT,
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