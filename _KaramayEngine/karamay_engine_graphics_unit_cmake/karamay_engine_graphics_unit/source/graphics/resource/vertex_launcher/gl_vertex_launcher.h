#ifndef GL_VERTEX_LAUNCHER_H
#define GL_VERTEX_LAUNCHER_H

#include "graphics/resource/vertex_array/gl_vertex_array.h"
#include "graphics/resource/buffers/common_buffer/gl_element_array_buffer.h"

enum class gl_primitive_mode
{
	POINTS = GL_POINTS,

	LINES = GL_LINES,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	LINE_LOOP = GL_LINE_LOOP,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINE_STRIP = GL_LINE_STRIP,

	TRIANGLES = GL_TRIANGLES,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,

	PATCHES = GL_PATCHES
};

struct gl_draw_arrays_indirect_command {
	uint32  count;
	uint32  primCount;
	uint32  first;
	uint32  baseInstance;
};

struct gl_draw_elements_indirect_command {
	uint32 count;
	uint32 primCount;
	uint32 firstIndex;
	uint32 baseVertex;
	uint32 baseInstance;
};


struct gl_vertex_launcher_descriptor
{
	gl_primitive_mode primitive_mode;
	uint32 primitive_vertices_num; // IndicesNum % PrimitiveVerticesNum == 0
	gl_vertex_array_descriptor vertex_array_descriptor;
	uint32 elements_num;
};

class gl_vertex_launcher 
{
public:
	using vertex_slot_reader = gl_vertex_array::vertex_slot_reader;
	using vertex_slot_writer = gl_vertex_array::vertex_slot_writer;
	using vertex_slot_handler = gl_vertex_array::vertex_slot_handler;
	using instance_attribute_slot_reader = gl_vertex_array::instance_attribute_slot_reader;
	using instance_attribute_slot_writer = gl_vertex_array::instance_attribute_slot_writer;
	using instance_attribute_slot_handler = gl_vertex_array::instance_attribute_slot_handler;
	using element_slot_reader = gl_element_array_buffer::element_buffer_reader;
	using element_slot_writer = gl_element_array_buffer::element_buffer_writer;
	using element_slot_handler = gl_element_array_buffer::element_buffer_handler;

	gl_vertex_launcher(const gl_vertex_launcher_descriptor& descriptor) :
		_primitive_mode(descriptor.primitive_mode),
		_primitive_vertices_num(descriptor.primitive_vertices_num),
		_vertex_array(nullptr), _element_array_buffer(nullptr)
	{}

	gl_vertex_launcher(const gl_vertex_launcher&) = delete;
	gl_vertex_launcher& operator=(const gl_vertex_launcher&) = delete;

	~gl_vertex_launcher() = default;
	
public:

	uint32 get_vertices_num() const { return _vertex_array ? _vertex_array->get_vertices_num() : 0; }

	uint32 get_vertex_size() const { return _vertex_array ? _vertex_array->get_vertex_size() : 0; }

	/*
	* you must describe a vertex size
	* you can only respecify a new VerticesNum, cause VertexSize, Layout can not be modified
	* this action will consume quite time
	*/
	void reallocate_vertex_slot(uint32 vertices_num, const void* initial_vertices = nullptr) noexcept
	{
		if (!_vertex_array) return;
		_vertex_array->reallocate_vertex_slot(vertices_num);
	}

	const void* read_vertex_slot(uint32 vertex_offset, uint32 vertices_num)
	{
		return _vertex_array ? _vertex_array->read_vertex_slot(vertex_offset, vertices_num) : nullptr;
	}

	void write_vertex_slot(uint32 vertex_offset, uint32 vertices_num, const void* vertices) 
	{
		if (!_vertex_array) return;

		_vertex_array->write_vertex_slot(vertex_offset, vertices_num, vertices);
 	}

	void execute_mapped_vertex_slot_reader(uint32 vertex_offset, uint32 vertices_num, const vertex_slot_reader& reader)
	{

	}

	void execute_mapped_vertex_slot_writer(uint32 vertex_offset, uint32 vertices_num, const vertex_slot_writer& writer)
	{}

	void execute_mapped_vertex_slot_handler(uint32 vertex_offset, uint32 vertices_num, const vertex_slot_handler& handler)
	{}

public:

	uint32 get_instance_attributes_num(const std::string& attribute_name) const {}

	uint32 get_instance_attribute_size(const std::string& attribute_name) const {}

	void reallocate_instance_attribute_slot(const std::string& attribute_name, uint32 attributes_num, uint32 divisor, const void* initial_attributes) noexcept
	{
		if (!_vertex_array) return;
		_vertex_array->reallocate_instance_attribute_slot(0, attributes_num, divisor, initial_attributes);
	}

	const void* read_instance_attribute_slot() {}

	void write_instance_attribute_slot() {}

	void execute_mapped_instance_attribute_slot_reader(const std::string& attribute_name, uint32 attribute_offset, uint32 attributes_num, const instance_attribute_slot_reader& reader)
	{}

	void execute_mapped_instance_attribute_slot_writer(const std::string& attribute_name, uint32 attribute_offset, uint32 attributes_num, const instance_attribute_slot_writer& writer)
	{}

	void execute_mapped_instance_attribute_slot_handler(const std::string& attribute_name, uint32 attribute_offset, uint32 attributes_num, const instance_attribute_slot_handler& handler)
	{}

public:

	uint32 get_elements_num() const { return _element_array_buffer ? _element_array_buffer->get_elements_num() : 0; }
	
	uint32 get_element_size() const { return _element_array_buffer ? _element_array_buffer->get_element_size() : 0; }

	gl_element_type get_element_type() const { return _element_array_buffer ? _element_array_buffer->get_element_type() : gl_element_type::NONE; }

	/*
	* Indices only associates to PrimitiveMode
	* PrimitiveMode will never change once lancher constructed
	* IndicesNum % PrimitiveVerticesNum = 0
	*/
	void reallocate_element_slot(uint32 elements_num, const void* initial_elements = nullptr) noexcept
	{
		if (!_element_array_buffer) return;
		if (elements_num % _primitive_vertices_num != 0) return;
		
		_element_array_buffer->reallocate(elements_num, initial_elements);
	}

	void execute_mapped_element_slot_reader(uint32 element_offset, uint32 elements_num, const element_slot_reader& reader)
	{
		if (!_element_array_buffer) return;
		_element_array_buffer->execute_mapped_element_buffer_reader(element_offset, elements_num, reader);
	}

	void execute_mapped_element_slot_writer(uint32 element_offset, uint32 elements_num, const element_slot_writer& writer)
	{
		if (!_element_array_buffer) return;
		_element_array_buffer->execute_mapped_element_buffer_writer(element_offset, elements_num, writer);
	}

	void execute_mapped_element_slot_handler(uint32 element_offset, uint32 elements_num, const element_slot_handler& handler)
	{
		if (!_element_array_buffer) return;
		_element_array_buffer->execute_mapped_element_buffer_handler(element_offset, elements_num, handler);
	}

	void set_primitive_restart_flag_element(uint32 element_offset)
	{
		if (!_element_array_buffer) return;

		_element_array_buffer->set_primitive_restart_flag_element(element_offset);
	}

	const std::vector<uint32>& get_primitive_restart_flag_element_indices() const
	{

	}

public:

	void bind() const noexcept
	{
		if(_vertex_array) _vertex_array->bind();
		if(_element_array_buffer) _element_array_buffer->bind();
	}

	void unbind() const noexcept
	{
		if (_vertex_array) _vertex_array->unbind();
		if (_element_array_buffer) _element_array_buffer->unbind();
	}

public:

	gl_primitive_mode get_primitive_mode() const { return _primitive_mode; }

private:

	gl_primitive_mode _primitive_mode;

	uint32 _primitive_vertices_num;

	std::unique_ptr<gl_vertex_array> _vertex_array;

	std::unique_ptr<gl_element_array_buffer> _element_array_buffer;
	
};


#endif