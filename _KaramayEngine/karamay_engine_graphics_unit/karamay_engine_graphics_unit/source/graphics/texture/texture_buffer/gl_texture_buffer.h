#pragma once
#include "graphics/texture/base/gl_texture_base.h"
#include "graphics/buffer/gl_buffer.h"


/**
 *  vec4 texelFetch(samplerBuffer s, int coord);
 * ivec4 texelFetch(isamplerBuffer s, int coord);
 * uvec4 texelFetch(usamplerBuffer s, int coord);
 * 
 * 
 * the texture can only access up to GL_MAX_TEXTURE_BUFFER_SIZE texels
 * The offset​ specifies a byte offset from the beginning of the buffer. It must be aligned to GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT
 * Buffer textures are not mip-mapped; they can only store a single image.
 * Buffer textures cannot be attached to Framebuffer Objects.
 */

class gl_texture_buffer : public gl_texture_base
{
public:
	
	gl_texture_buffer();
	
	virtual ~gl_texture_buffer();

public:
	
	void associate_buffer(std::shared_ptr<gl_buffer> buffer)
	{
		if (buffer && buffer->get_size() <= GL_MAX_TEXTURE_BUFFER_SIZE) 
		{
			glBindBuffer(GL_TEXTURE_BUFFER, _handle);
			glTexBuffer(GL_TEXTURE_BUFFER, static_cast<GLenum>(buffer->get_internal_format()), buffer->get_handle());
			glBindBuffer(GL_TEXTURE_BUFFER, 0);
		}
	}
	
	void associate_sub_buffer(std::shared_ptr<gl_buffer> buffer, std::size_t offset, std::size_t size)
	{
		if (buffer && buffer->get_size() <= GL_MAX_TEXTURE_BUFFER_SIZE)
		{
			//GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT
			glBindBuffer(GL_TEXTURE_BUFFER, _handle);
			glTexBufferRange(GL_TEXTURE_BUFFER, static_cast<GLenum>(buffer->get_internal_format()), buffer->get_handle(), offset, size);
			glBindBuffer(GL_TEXTURE_BUFFER, 0);
		}
		
	}

	void bind(std::uint32_t unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_BUFFER, _handle);
	}
	
	void unbind() {}

};

