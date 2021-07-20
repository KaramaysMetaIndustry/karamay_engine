#ifndef H_GL_TEXTURE_BUFFER
#define H_GL_TEXTURE_BUFFER

#include "graphics/texture/base/gl_texture_base.h"
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

class gl_texture_buffer : public gl_texture_base
{
public:
	
	gl_texture_buffer();
	
	virtual ~gl_texture_buffer();

public:
	
	void associate_buffer(std::shared_ptr<gl_buffer> buffer);
	
	void associate_sub_buffer(std::shared_ptr<gl_buffer> buffer, std::size_t offset, std::size_t size);

	void bind(std::uint32_t unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_BUFFER, _handle);
	}
	
	void unbind() {}

};

#endif

