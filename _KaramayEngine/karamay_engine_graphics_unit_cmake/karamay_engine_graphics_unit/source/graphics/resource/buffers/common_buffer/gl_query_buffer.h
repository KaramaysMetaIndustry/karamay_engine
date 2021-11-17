#ifndef GL_QUERY_BUFFER_H
#define GL_QUERY_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"

class gl_query_buffer
{
public:
	gl_query_buffer() {}

	~gl_query_buffer() {}

public:

	gl_buffer* get_raw()
	{
		return _raw_buffer.get();
	}

	void bind()
	{
		glBindBuffer(GL_QUERY_BUFFER, _raw_buffer->get_handle());
	}

	void unbind()
	{
		glBindBuffer(GL_QUERY_BUFFER, 0);
	}


private:

	std::unique_ptr<gl_buffer> _raw_buffer;
};

#endif
