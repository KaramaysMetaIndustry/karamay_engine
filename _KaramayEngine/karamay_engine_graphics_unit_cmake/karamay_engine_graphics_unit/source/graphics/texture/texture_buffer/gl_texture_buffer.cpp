#include "gl_texture_buffer.h"
#include "graphics/buffer/gl_buffer.h"

gl_texture_buffer::gl_texture_buffer()
{
	glCreateTextures(GL_TEXTURE_BUFFER, 1, &_handle);
}

gl_texture_buffer::~gl_texture_buffer()
{
	glDeleteTextures(1, &_handle);
}

void gl_texture_buffer::associate_buffer(std::shared_ptr<gl_buffer> buffer) {
    if (buffer && buffer->get_size() <= GL_MAX_TEXTURE_BUFFER_SIZE)
    {
        glBindBuffer(GL_TEXTURE_BUFFER, _handle);
        glTexBuffer(GL_TEXTURE_BUFFER, static_cast<GLenum>(buffer->get_internal_format()), buffer->get_handle());
        glBindBuffer(GL_TEXTURE_BUFFER, 0);
    }
}

void gl_texture_buffer::associate_sub_buffer(std::shared_ptr<gl_buffer> buffer, std::size_t offset, std::size_t size) {
    if (buffer && buffer->get_size() <= GL_MAX_TEXTURE_BUFFER_SIZE)
    {
        //GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT
        glBindBuffer(GL_TEXTURE_BUFFER, _handle);
        glTexBufferRange(GL_TEXTURE_BUFFER, static_cast<GLenum>(buffer->get_internal_format()), buffer->get_handle(), offset, size);
        glBindBuffer(GL_TEXTURE_BUFFER, 0);
    }
}
