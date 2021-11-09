#ifndef GL_VERTEX_LAUNCHER_H
#define GL_VERTEX_LAUNCHER_H

#include "graphics/resource/vertex_array/gl_vertex_array.h"
#include "graphics/resource/buffers/common_buffer/gl_element_array_buffer.h"

enum class PrimitiveMode
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
using UInt32 = std::uint32_t;


class VertexLauncher final 
{
public:

	VertexLauncher() :
		_VertexArray(nullptr), _ElementArrayBuffer(nullptr), _PrimitiveMode(PrimitiveMode::TRIANGLES)
	{
		_VertexArray = new gl_vertex_array();
		_ElementArrayBuffer = new gl_element_array_buffer();
	}

	VertexLauncher(PrimitiveMode Mode) {}

	VertexLauncher(const VertexLauncher&) = delete;
	VertexLauncher& operator=(const VertexLauncher&) = delete;

	~VertexLauncher()
	{
		delete _VertexArray;
		delete _ElementArrayBuffer;
	}

private:

	gl_vertex_array* _VertexArray;
	gl_element_array_buffer* _ElementArrayBuffer;
	PrimitiveMode _PrimitiveMode;

public:

	PrimitiveMode GetPrimitiveMode() const { return _PrimitiveMode; }

public:
	//
	void ReallocateVertices(UInt32 VerticesNum)
	{
		if (_VertexArray)
		{

		}
	}

	void FillVertices() {}

public:

	void ReallocateInstanceAttributes() {}

	void FillInstanceAttributes() {}

public:

	// Indices only associates to PrimitiveMode
	// PrimitiveMode will never change once lancher constructed
	// IndicesNum % PrimitiveVerticesNum = 0
	void ReallocateIndices(UInt32 IndicesNum)
	{
		if (_ElementArrayBuffer && IndicesNum % 3 == 0)
		{
			_ElementArrayBuffer->reallocate(IndicesNum * sizeof(std::uint32_t));
		}
	}

	void FillIndices(UInt32 Offset, const std::vector<UInt32>& Indices)
	{

	}

public:

	bool Assembly() noexcept
	{
		return false;
	}

	void Bind() noexcept
	{

	}

	void Unbind() noexcept
	{
	}

};


#endif