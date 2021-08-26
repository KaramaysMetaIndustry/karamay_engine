#ifndef H_GL_TEXTURE_BUFFER
#define H_GL_TEXTURE_BUFFER

#include "graphics/texture/base/gl_texture.h"
class gl_buffer;

/**
 *  vec4 texelFetch(samplerBuffer s, int coord);
 * ivec4 texelFetch(isamplerBuffer s, int coord);
 * uvec4 texelFetch(usamplerBuffer s, int coord);
 * 
 * 
 * the texture can only access up to GL_MAX_TEXTURE_BUFFER_SIZE texels
 * The offset​ specifies a byte offset from the beginning of the buffers. It must be aligned to GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT
 * Buffer textures are not mip-mapped; they can only store a single image.
 * Buffer textures cannot be attached to Framebuffer Objects.
 */

struct gl_texture_buffer_descriptor
{
	std::shared_ptr<gl_buffer> buffer;
	gl_texture_pixel_format pixel_format;
	std::int32_t offset, length;

	gl_texture_buffer_descriptor()
	{}
};

class gl_texture_buffer : public gl_texture
{
public:
	
	gl_texture_buffer() = delete;
	gl_texture_buffer(const gl_texture_buffer_descriptor& descriptor) :
		gl_texture(gl_texture_type::TEXTURE_BUFFER),
		_descriptor(descriptor)
	{
		//GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT
		glTextureBufferRange(_handle, 
			static_cast<GLenum>(_descriptor.pixel_format), 
			_descriptor.buffer->get_handle(),
			_descriptor.offset, _descriptor.length
		);
	}
	
	~gl_texture_buffer() override = default;

private:

	gl_texture_buffer_descriptor _descriptor;

public:

	void bind(std::uint32_t unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_BUFFER, _handle);
	}
	
	void unbind() {}

};

#endif

