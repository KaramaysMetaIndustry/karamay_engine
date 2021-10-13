#ifndef H_GL_ATOMIC_COUNTER_BUFFER
#define H_GL_ATOMIC_COUNTER_BUFFER

#include "graphics/glsl/opaque_t/glsl_atomic_counter_t.h"
#include "graphics/buffers/buffer/gl_buffer.h"

class gl_atomic_counter_buffer final{
public:
	gl_atomic_counter_buffer(const std::vector<std::shared_ptr<glsl_atomic_counter>>& counters) = default;

	~gl_atomic_counter_buffer() {}

public:

	void bind()
	{
        if(!_buffer) return;

		glBindBufferRange(GL_ATOMIC_COUNTER_BUFFER, 0, _buffer->get_handle(), 0, 4);
		glBindBufferRange(GL_ATOMIC_COUNTER_BUFFER, 1, _buffer->get_handle(), 4, 4);
		glBindBufferRange(GL_ATOMIC_COUNTER_BUFFER, 2, _buffer->get_handle(), 8, 4);
	}

	void unbind()
	{
		GLint MaxVertexAtomicCounterBuffers(0);
		GLint MaxControlAtomicCounterBuffers(0);
		GLint MaxEvaluationAtomicCounterBuffers(0);
		GLint MaxGeometryAtomicCounterBuffers(0);
		GLint MaxFragmentAtomicCounterBuffers(0);
		GLint MaxCombinedAtomicCounterBuffers(0);

		glGetIntegerv(GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS, &MaxVertexAtomicCounterBuffers);
		glGetIntegerv(GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS, &MaxControlAtomicCounterBuffers);
		glGetIntegerv(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS, &MaxEvaluationAtomicCounterBuffers);
		glGetIntegerv(GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS, &MaxGeometryAtomicCounterBuffers);
		glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS, &MaxFragmentAtomicCounterBuffers);
		glGetIntegerv(GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS, &MaxCombinedAtomicCounterBuffers);
	}

private:

    std::unique_ptr<gl_buffer> _buffer;


};

#endif

