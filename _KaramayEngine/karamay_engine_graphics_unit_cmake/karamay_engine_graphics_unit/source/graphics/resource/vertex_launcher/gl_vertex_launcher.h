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

struct VertexLauncherDescriptor
{
	VertexArrayDescriptor VertexArrayDesc;
	UInt32 IndicesNum;
	UInt32 PrimitiveVerticesNum; // IndicesNum % PrimitiveVerticesNum == 0
	PrimitiveMode Mode;
};

class VertexLauncher 
{
public:
	VertexLauncher() {}
	VertexLauncher(const VertexLauncherDescriptor& Descriptor) :
		_PrimitiveMode(Descriptor.Mode),
		_PrimitiveVerticesNum(Descriptor.PrimitiveVerticesNum),
		_VertexArray(nullptr), _ElementArrayBuffer(nullptr)
	{
		VertexArrayDescriptor _Desc;
		_VertexArray = new VertexArray(_Desc);
		_ElementArrayBuffer = new ElementArrayBuffer();
	}

	VertexLauncher(const VertexLauncher&) = delete;
	VertexLauncher& operator=(const VertexLauncher&) = delete;

	~VertexLauncher()
	{
		delete _VertexArray;
		delete _ElementArrayBuffer;
	}

public:

	PrimitiveMode GetPrimitiveMode() const { return _PrimitiveMode; }

	UInt32 GetVerticesNum() const { return _VertexArray ? _VertexArray->GetVerticesNum() : 0; }

	UInt32 GetInstancesNum() const { return _VertexArray ?  _VertexArray->GetInstancesNum() : 0; }

public:

	// you must describe a vertex size
	// you can only respecify a new VerticesNum, cause VertexSize, Layout can not be modified
	// this action will consume quite time
	void ReallocateVertices(UInt32 VerticesNum) noexcept
	{
		if (!_VertexArray) return;

		_VertexArray->ReallocateVertices(VerticesNum);
	}

	// Offset unit is a Vertex Size
	void FillVertices(UInt32 VertexOffset, const UInt8* DataBytes, UInt32 VerticesNum) noexcept
	{
		if (!_VertexArray) return;

		_VertexArray->FillVertices(VertexOffset, DataBytes, VerticesNum);
	}

	// Get Vertices
	const UInt8* GetVertices(UInt32 VertexOffset, UInt32 VerticesNum) const 
	{
		return nullptr;
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
	void FillInstanceAttributes(UInt32 AttributeIndex, UInt32 InstanceAttributeOffset, UInt8* DataBytes, UInt32 InstanceAttributesNum) noexcept
	{
		if (!_VertexArray) return;

		_VertexArray->FillInstanceAttributes("", InstanceAttributeOffset, DataBytes, InstanceAttributesNum);
	}

	const UInt8* GetInstanceAttributes(UInt32 AttributeIndex, UInt32 InstanceAttributeOffset, UInt32 InstanceAttributesNum) const
	{
		return nullptr;
	}

public:

	// Indices only associates to PrimitiveMode
	// PrimitiveMode will never change once lancher constructed
	// IndicesNum % PrimitiveVerticesNum = 0
	void ReallocateIndices(UInt32 IndicesNum) noexcept
	{
		if (!_ElementArrayBuffer) return;
		if (IndicesNum % _PrimitiveVerticesNum != 0) return;
		
		_ElementArrayBuffer->Reallocate(IndicesNum);
	}

	// Fill indices
	void FillIndices(UInt32 IndexOffset, const UInt8* DataBytes, UInt32 IndicesNum) noexcept
	{
		if (!_ElementArrayBuffer) return;
		
		//_ElementArrayBuffer->Fill(IndexOffset, Indices);
	}

	// Get indices data bytes
	const UInt8* GetIndices(UInt32 IndexOffset, UInt32 IndicesNum) const noexcept
	{
		return nullptr;
	}

public:

	void Bind() const noexcept
	{
		_VertexArray->Bind();
		_ElementArrayBuffer->Bind();
	}

	void Unbind() const noexcept
	{
		_VertexArray->Unbind();
		_ElementArrayBuffer->Unbind();
	}

public:

	void DrawArrays(UInt32 VertexOffset, UInt32 VerticesNum, UInt32 InstancesNum, UInt32 InstanceOffset) const
	{
		glDrawArraysInstancedBaseInstance(static_cast<GLenum>(_PrimitiveMode), VertexOffset, VerticesNum, InstancesNum, InstanceOffset);
	}

	void DrawIndices(UInt32 InstancesNum, UInt32 VertexOffset, UInt32 InstanceOffset) const
	{
		glDrawElementsInstancedBaseVertexBaseInstance(static_cast<GLenum>(_PrimitiveMode), _PrimitiveVerticesNum, GL_UNSIGNED_INT, nullptr, InstancesNum, VertexOffset, InstanceOffset);
	}

	void DrawRangeIndices(UInt32 IndexOffset, UInt32 IndicesNum)
	{
		//glDrawRangeElementsBaseVertex(static_cast<GLenum>(_PrimitiveMode), IndexOffset, I)
	}

	void RestartPrimitiveIndex(UInt32 Index) const
	{
		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(Index);
		glDisable(GL_PRIMITIVE_RESTART);
	}

private:

	VertexArray* _VertexArray;

	ElementArrayBuffer* _ElementArrayBuffer;

	PrimitiveMode _PrimitiveMode;

	UInt32 _PrimitiveVerticesNum;

};


template<typename VertexT, typename IndexT>
class VertexLauncherProxy : protected VertexLauncher
{

public:

	VertexLauncherProxy() {}

	void FillVertices(UInt32 VertexOffset, const std::vector<VertexT>& Vertices) 
	{
		VertexLauncher::FillVertices(VertexOffset, Vertices.data(), Vertices.size());
	}

};


#endif