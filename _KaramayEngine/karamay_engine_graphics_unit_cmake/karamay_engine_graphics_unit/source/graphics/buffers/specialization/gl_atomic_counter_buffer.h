 #ifndef H_GL_ATOMIC_COUNTER_BUFFER
#define H_GL_ATOMIC_COUNTER_BUFFER

#include "graphics/buffers/buffer/gl_buffer.h"

struct gl_atomic_counter_buffer_binding_info
{
	std::string block_name;

	std::shared_ptr<gl_buffer> buffer;

	std::size_t offset;

	std::size_t size;
};

class gl_atomic_counter_buffer_descriptor
{

};


class gl_atomic_counter_buffer final
{
public:

	gl_atomic_counter_buffer(const std::shared_ptr<gl_atomic_counter_buffer_descriptor>& acbo_desc)
	{
		_desc = acbo_desc;
	}
	
	~gl_atomic_counter_buffer() {}

private:

	std::shared_ptr<gl_atomic_counter_buffer_descriptor> _desc;

	std::shared_ptr<gl_buffer> _ref_buffer;

	std::size_t _offset;

	std::size_t _size;

	std::string _template_code;

public:

	void fill(const std::vector<std::string>& variable_names)
	{
		// fill buffers
		//_size = sizeof(GLuint) * variable_names.size();
		//_ref_buffer->fill(_offset, _size, nullptr);
		
		//_generate_template_code(variable_names);
	}

	void bind(std::uint32_t binding)
	{
		glBindBufferRange(GL_ATOMIC_COUNTER_BUFFER, binding, _ref_buffer->get_handle(), 0, 100);
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

};

#endif

