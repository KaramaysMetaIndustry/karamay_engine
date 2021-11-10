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


class VertexLauncher final 
{
public:

	VertexLauncher(PrimitiveMode Mode) :
		_PrimitiveMode(Mode),
		_VertexArray(nullptr), _ElementArrayBuffer(nullptr)
	{
		VertexArrayDescriptor _Desc;
		_VertexArray = std::make_unique<VertexArray>(_Desc);
		_ElementArrayBuffer = std::make_unique<ElementArrayBuffer>();
	}

	VertexLauncher(const VertexLauncher&) = delete;
	VertexLauncher& operator=(const VertexLauncher&) = delete;

	~VertexLauncher()
	{}

private:

	std::unique_ptr<VertexArray> _VertexArray;

	std::unique_ptr<ElementArrayBuffer> _ElementArrayBuffer;
	
	PrimitiveMode _PrimitiveMode;

public:

	PrimitiveMode GetPrimitiveMode() const { return _PrimitiveMode; }

	UInt32 GetVerticesNum() const { return _VertexArray ? _VertexArray->GetVerticesNum() : 0; }

	UInt32 GetInstancesNum() const { return _VertexArray ?  _VertexArray->GetInstancesNum() : 0; }

public:

	// you must describ a vertex size
	// you can only respecify a new VerticesNum, cause VertexSize, Layout can not be modified
	// this action will consume quite time
	void ReallocateVertices(UInt32 VerticesNum) noexcept
	{
		if (!_VertexArray) return;
		_VertexArray->ReallocateVertices(VerticesNum);
	}

	// Offset unit is a Vertex Size
	void FillVertices(UInt32 VertexOffset, const UInt8* Data, UInt32 VerticesNum) noexcept
	{
		if (!_VertexArray) return;
		_VertexArray->FillVertices(VertexOffset, Data, VerticesNum);
	}

public:

	// reset num of instances, this decide instance attributes' layout
	void ResetInstancesNum(UInt32 InstancesNum) noexcept
	{
		if (!_VertexArray) return;
		_VertexArray->ResetInstancesNum(InstancesNum);
	}

	// reallocate the name specified attributes, divisor decide the attributes' layout
	void ReallocateInstanceAttributes(UInt32 AttributeIndex, UInt32 InstanceAttributesNum, UInt32 Divisor) noexcept
	{
		if (!_VertexArray) return;
		_VertexArray->ReallocateInstanceAttributes(AttributeIndex, InstanceAttributesNum, Divisor);
	}

	// fill the instance attributes
	// 
	void FillInstanceAttributes(UInt32 AttributeIndex, UInt32 Offset, UInt8* Data, UInt32 InstanceAttributesNum) noexcept
	{
		if (!_VertexArray) return;

	}

public:

	// Indices only associates to PrimitiveMode
	// PrimitiveMode will never change once lancher constructed
	// IndicesNum % PrimitiveVerticesNum = 0
	void ReallocateIndices(UInt32 IndicesNum)
	{
		const UInt32 PrimitiveVerticesNum = 3;

		if (!_ElementArrayBuffer) return;
		if (IndicesNum % PrimitiveVerticesNum != 0) return;
		
		_ElementArrayBuffer->Reallocate(IndicesNum);
	}

	void FillIndices(UInt32 Offset, const std::vector<UInt32>& Indices)
	{
		if (!_ElementArrayBuffer) return;
		
		_ElementArrayBuffer->Fill(Offset, Indices);
	}

public:

	void Bind() noexcept
	{
		_VertexArray->Bind();
		_ElementArrayBuffer->Bind();
	}

	void Unbind() noexcept
	{
		_VertexArray->Unbind();
		_ElementArrayBuffer->Unbind();
	}

};


#endif