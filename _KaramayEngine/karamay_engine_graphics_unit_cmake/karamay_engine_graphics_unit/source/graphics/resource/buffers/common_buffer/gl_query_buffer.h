#ifndef GL_QUERY_BUFFER_H
#define GL_QUERY_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"

class QueryBuffer
{
public:
	QueryBuffer() {}

	~QueryBuffer() {}

public:

	Buffer* GetRaw()
	{
		return _Buffer.get();
	}

private:

	UniquePtr<Buffer> _Buffer;
};

#endif
