#ifndef GL_QUERY_H
#define GL_QUERY_H

#include "graphics/resource/glo/gl_object.h"
#include "../buffers/common_buffer/gl_query_buffer.h"

enum class gl_query_type
{
	SAMPLES_PASSED = GL_SAMPLES_PASSED, // samples passed
	ANY_SAMPLES_PASSED = GL_ANY_SAMPLES_PASSED, // any samples passes
	ANY_SAMPLES_PASSED_CONSERVATIVE = GL_ANY_SAMPLES_PASSED_CONSERVATIVE, // any samples passed conservative
	TIME_ELAPSED = GL_TIME_ELAPSED, // time elapsed
	TIMESTAMP = GL_TIMESTAMP, // time stamp
	PRIMITIVES_GENERATED = GL_PRIMITIVES_GENERATED, // primitive generated
	TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 
	// transform feedback primitives written
};

class gl_query final : public gl_object
{
public:
	gl_query(gl_query_type type) : gl_object(gl_object_type::QUERY_OBJ), _type(type)
	{		
		glCreateQueries(static_cast<GLenum>(type), 1, &_handle);
	}

	gl_query(const gl_query&) = delete;
	gl_query& operator=(const gl_query&) = delete;

	~gl_query()
	{
		glDeleteQueries(1, &_handle);
	}

private:

	gl_query_type _type;

public:

	gl_query_type get_type() const { return _type; }
	

};

#endif
