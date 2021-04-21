#include "gl_buffer.h"

void gl_buffer::allocate(gl_buffer_type type, GLsizeiptr size, const void* data, GLbitfield flags)
{
	if (size > GL_MAX_UNIFORM_BLOCK_SIZE) return;

	glNamedBufferStorage(_handle, size, data, flags);
	_type = static_cast<GLenum>(type);
}

void gl_buffer::fill(GLintptr offset, GLsizeiptr size, const void* data)
{
	glNamedBufferSubData(_handle, offset, size, data);
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

void* gl_buffer::map(GLenum access)
{
	return glMapNamedBuffer(_handle, access);
}

void* gl_buffer::map(GLenum access, GLintptr offset, GLsizeiptr size)
{
	return glMapNamedBufferRange(_handle, offset, size, access);
}

void gl_buffer::flush_mapped_buffer(GLintptr offset, GLsizeiptr size)
{
	glFlushMappedNamedBufferRange(_handle, offset, size);
}

void gl_buffer::unmap()
{
	glUnmapNamedBuffer(_handle);
}

void gl_buffer::bind()
{
	glBindBuffer(_type, _handle);
}

void gl_buffer::unbind()
{
	glBindBuffer(_type, 0);
}

gl_buffer::gl_buffer()
{
	glCreateBuffers(1, &_handle);
}

gl_buffer::~gl_buffer()
{
	glDeleteBuffers(1, &_handle);
}
