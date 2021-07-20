#ifndef H_GL_ELEMENT_ARRAY_BUFFER
#define H_GL_ELEMENT_ARRAY_BUFFER

#include "graphics/buffers/buffer/gl_buffer.h"


class gl_element_array_buffer
{
public:

	gl_element_array_buffer() {}

	~gl_element_array_buffer() {}

private:

	std::shared_ptr<gl_buffer> _buffer;

public:


};


#endif
