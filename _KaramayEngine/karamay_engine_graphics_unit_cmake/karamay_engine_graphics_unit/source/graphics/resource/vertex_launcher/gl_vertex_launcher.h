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

struct DrawArraysIndirectCommand {
	UInt32  count;
	UInt32  primCount;
	UInt32  first;
	UInt32  baseInstance;
};

struct DrawElementsIndirectCommand {
	UInt32 count;
	UInt32 primCount;
	UInt32 firstIndex;
	UInt32 baseVertex;
	UInt32 baseInstance;
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

public:

	// you must describe a vertex size
	// you can only respecify a new VerticesNum, cause VertexSize, Layout can not be modified
	// this action will consume quite time
	void ReallocateVertexSlot(UInt32 VerticesNum) noexcept
	{
		if (!_VertexArray) return;
		_VertexArray->ReallocateVertices(VerticesNum);
	}

	// Offset unit is a Vertex Size
	void FillVertexSlot(UInt32 VertexOffset, const UInt8* DataBytes, UInt32 VerticesNum) noexcept
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

	// reallocate the name specified attributes, divisor decide the attributes' layout
	void ReallocateInstanceAttributeSlot(const std::string& InstanceAttributeName, UInt32 InstanceAttributesNum, UInt32 Divisor) noexcept
	{
		if (!_VertexArray) return;
		
		//_VertexArray->ReallocateInstanceAttributes(AttributeIndex, InstanceAttributesNum, Divisor);
	}

	// fill the instance attributes
	void FillInstanceAttributeSlot(const std::string& InstanceAttributeName, UInt32 InstanceAttributeOffset, UInt8* DataBytes, UInt32 InstanceAttributesNum) noexcept
	{
		if (!_VertexArray) return;

		_VertexArray->FillInstanceAttributes(InstanceAttributeName, InstanceAttributeOffset, DataBytes, InstanceAttributesNum);
	}

	const UInt8* GetInstanceAttributes(const std::string& InstanceAttributeName, UInt32 InstanceAttributeOffset, UInt32 InstanceAttributesNum) const
	{
		return nullptr;
	}

public:

	// Indices only associates to PrimitiveMode
	// PrimitiveMode will never change once lancher constructed
	// IndicesNum % PrimitiveVerticesNum = 0
	void ReallocateIndexSlot(UInt32 IndicesNum, const UInt32* InitializationIndices = nullptr) noexcept
	{
		if (!_ElementArrayBuffer) return;
		if (IndicesNum % _PrimitiveVerticesNum != 0) return;
		
		_ElementArrayBuffer->Reallocate(IndicesNum);
	}

	void FillIndexSlot(UInt32 IndexOffset, const UInt32* Indices, UInt32 IndicesNum) noexcept
	{
		if (!_ElementArrayBuffer) return;
		
		//_ElementArrayBuffer->Fill(IndexOffset, Indices);
	}

	// Get indices data bytes
	const UInt32* FetchIndices(UInt32 IndexOffset, UInt32 IndicesNum) const noexcept
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

	void DrawArrays(UInt32 VertexOffset, UInt32 VerticesNum) const
	{
		glDrawArrays(static_cast<GLenum>(_PrimitiveMode), VertexOffset, VerticesNum);
	}

	void DrawArrays(UInt32 VertexOffset, UInt32 VerticesNum, UInt32 InstancesNum, UInt32 InstanceOffset) const
	{
		//glDrawArraysInstanced();
		glDrawArraysInstancedBaseInstance(static_cast<GLenum>(_PrimitiveMode), VertexOffset, VerticesNum, InstancesNum, InstanceOffset);
	}

	void DrawArraysIndirect() const
	{}


	void DrawElements(UInt32 ElementOffset, UInt32 ElementsNum) const
	{
		glDrawElementsBaseVertex(static_cast<GLenum>(_PrimitiveMode), ElementsNum, static_cast<GLenum>(_ElementArrayBuffer->GetElementType()), nullptr, ElementOffset);
	}

	void DrawElements(UInt32 ElementOffset, UInt32 ElementsNum, UInt32 InstancesNum, UInt32 InstanceOffset) const
	{
		glDrawElementsInstancedBaseVertexBaseInstance(static_cast<GLenum>(_PrimitiveMode), ElementsNum, GL_UNSIGNED_INT, nullptr, InstancesNum, ElementOffset, InstanceOffset);
	}

	void DrawElementsIndirect() const {}


	void MultiDrawArrays(const std::vector<std::pair<UInt32, UInt32>>& IndexIndexCu)
	{
		glMultiDrawArrays(static_cast<GLenum>(_PrimitiveMode), nullptr, nullptr, 10);
	}

	void MultiDrawElements()
	{
		//glMultiDrawElementsIndirect()
	}

	void DrawRangeElements(UInt32 IndexOffset, UInt32 IndicesNum)
	{
		glDrawRangeElementsBaseVertex(static_cast<GLenum>(_PrimitiveMode), )
		
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