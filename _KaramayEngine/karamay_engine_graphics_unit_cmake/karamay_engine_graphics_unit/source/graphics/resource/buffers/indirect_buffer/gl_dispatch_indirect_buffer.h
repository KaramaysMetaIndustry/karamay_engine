#ifndef GL_DISPATCH_INDIRECT_BUFFER_H
#define GL_DISPATCH_INDIRECT_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"

class gl_dispatch_indirect_buffer final{
public:
	gl_dispatch_indirect_buffer()
	{}

	~gl_dispatch_indirect_buffer();

private:

	std::unique_ptr<gl_buffer> _buffer;

};

#endif
