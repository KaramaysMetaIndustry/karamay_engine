#ifndef GL_QUERY_H
#define GL_QUERY_H

#include "graphics/resource/glo/gl_object.h"
#include "graphics/resource/buffers/common_buffer/gl_query_buffer.h"

enum class gl_query_type
{
	SAMPLES_PASSED = GL_SAMPLES_PASSED,
	ANY_SAMPLES_PASSED = GL_ANY_SAMPLES_PASSED,
	ANY_SAMPLES_PASSED_CONSERVATIVE = GL_ANY_SAMPLES_PASSED_CONSERVATIVE,
	TIME_ELAPSED = GL_TIME_ELAPSED,
	TIMESTAMP = GL_TIMESTAMP,
	PRIMITIVES_GENERATED = GL_PRIMITIVES_GENERATED,
	TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
};

class gl_query : public gl_object{
public:
	gl_query()
	{		
		//glCreateQueries()
	}
};


#endif // !GL_QUERY_H
