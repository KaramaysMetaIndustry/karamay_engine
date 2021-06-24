#include "gl_buffer.h"
	

void gl_buffer::allocate(std::size_t size, bool is_map_persistent, bool is_map_coherent, bool is_map_read, bool is_map_write, bool is_dynamic_storage, bool is_client_storage)
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
}

void gl_buffer::fill(std::size_t offset, std::size_t size, const void* data)
{
	if (data && offset + size <= get_size())
	{
		glNamedBufferSubData(_handle, offset, size, data);
	}
}

void gl_buffer::clear(GLenum internal_format, GLenum format, GLenum type, const void* data)
{
	glClearNamedBufferData(_handle, internal_format, format, type, data);
}

void gl_buffer::clear(GLenum internal_format, GLenum format, GLenum type, const void* data, GLintptr offset, GLsizeiptr size)
{
	glClearNamedBufferSubData(_handle, internal_format, offset, size, format, type, data);
}

void gl_buffer::copy_to(GLuint write_buffer_handle, GLintptr read_offset, GLintptr write_offset, GLsizeiptr size)
{
	glCopyNamedBufferSubData(_handle, write_buffer_handle, read_offset, write_offset, size);
}

void* gl_buffer::map(gl_buffer_enum::access access)
{
	return glMapNamedBuffer(_handle, static_cast<GLenum>(access));
}

void* gl_buffer::map(gl_buffer_enum::access access, std::size_t offset, std::size_t size)
{
	return glMapNamedBufferRange(_handle, offset, size, static_cast<GLenum>(access));
}

void gl_buffer::flush_mapped_buffer(std::size_t offset, std::size_t size)
{
	glFlushMappedNamedBufferRange(_handle, offset, size);
}

void gl_buffer::unmap()
{
	glUnmapNamedBuffer(_handle);
}


gl_buffer::gl_buffer()
{
	glCreateBuffers(1, &_handle);
}

gl_buffer::~gl_buffer()
{
	glDeleteBuffers(1, &_handle);
}
