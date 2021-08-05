
#include "graphics/glo/gl_object.h"
#include "graphics/texture/texture_1d/gl_texture_1d.h"

class gl_image_1d : public gl_texture_1d
{	
public:

	gl_image_1d()
	{
		GLuint texture;
		//  GL_READ_ONLY, GL_WRITE_ONLY, or GL_READ_WRITE
		glBindImageTexture(GL_TEXTURE0, texture, 0, false, 1, GL_READ_ONLY, GL_RGBA32F);
	}



};