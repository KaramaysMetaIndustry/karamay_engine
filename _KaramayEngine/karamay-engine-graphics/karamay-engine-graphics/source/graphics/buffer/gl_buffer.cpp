#include "gl_buffer.h"
	

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
	glBindBuffer(static_cast<GLenum>(_buffer_type), _handle);
}

void gl_buffer::unbind()
{
	glBindBuffer(static_cast<GLenum>(_buffer_type), 0);
}

gl_buffer::gl_buffer()
{
	glCreateBuffers(1, &_handle);
}

void gl_buffer::allocate(gl_buffer_type buffer_type, unsigned int buffer_size, GLbitfield flags)
{
	if (buffer_size > GL_MAX_UNIFORM_BLOCK_SIZE) return;

	glNamedBufferStorage(_handle, static_cast<GLsizeiptr>(buffer_size), nullptr, flags);

	_buffer_size = buffer_size;
	_buffer_type = buffer_type;
}

void gl_buffer::fill(std::shared_ptr<gl_buffer_data_pack> data_pack, unsigned int offset)
{
	if (data_pack.get() && (offset + data_pack->size > _buffer_size)) {
		throw std::exception("do not have enough memory");
	}
	glNamedBufferSubData(_handle, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(data_pack->size), data_pack->data);
}

gl_buffer::~gl_buffer()
{
	glDeleteBuffers(1, &_handle);
}
