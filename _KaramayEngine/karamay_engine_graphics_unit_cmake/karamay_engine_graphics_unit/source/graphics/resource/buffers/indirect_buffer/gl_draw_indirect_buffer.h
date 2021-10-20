#ifndef GL_DRAW_INDIRECT_BUFFER_H
#define GL_DRAW_INDIRECT_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"

class gl_draw_indirect_buffer{
public:
	gl_draw_indirect_buffer()
	{

	}

	~gl_draw_indirect_buffer()
	{

	}


private:
	
	std::unique_ptr<gl_buffer> _buffer;

};


#endif
