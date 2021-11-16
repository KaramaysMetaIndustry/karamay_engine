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

	using ElementSlotWriter = ElementArrayBuffer::ElementBufferWriter;
	using ElementSlotReader = ElementArrayBuffer::ElementBufferReader;
	using ElementSlotHandler = ElementArrayBuffer::ElementBufferHandler;


	VertexLauncher(const VertexLauncherDescriptor& Descriptor) :
		_PrimitiveMode(Descriptor.Mode),
		_PrimitiveVerticesNum(Descriptor.PrimitiveVerticesNum),
		_VertexArray(nullptr), _ElementArrayBuffer(nullptr)
	{
	}

	VertexLauncher(const VertexLauncher&) = delete;
	VertexLauncher& operator=(const VertexLauncher&) = delete;

	~VertexLauncher() = default;
	
public:

	UInt32 GetVerticesNum() const { return _VertexArray ? _VertexArray->GetVerticesNum() : 0; }

	UInt32 GetVertexSize() const { return _VertexArray ? _VertexArray->GetVertexSize() : 0; }

	/*
	* you must describe a vertex size
	* you can only respecify a new VerticesNum, cause VertexSize, Layout can not be modified
	* this action will consume quite time
	*/
	void ReallocateVertexSlot(UInt32 VerticesNum, const void* InitialVertices = nullptr) noexcept
	{
		if (!_VertexArray) return;
		_VertexArray->ReallocateVertexSlot(VerticesNum);
	}


	void WriteToVertexSlot(UInt32 VertexOffset, UInt32 VerticesNum, const VertexArray::VertexSlotWriter& Writer)
	{}

	void ReadFromVertexSlot(UInt32 VertexOffset, UInt32 VerticesNum, const VertexArray::VertexSlotReader& Reader)
	{}

	void HandleVertexSlot(UInt32 VertexOffset, UInt32 VerticesNum, const VertexArray::VertexSlotHandler& Handler)
	{}

public:

	UInt32 GetInstanceAttributesNum(const std::string& InstanceAttributeName) const {}

	UInt32 GetInstanceAttributeSize(const std::string& InstanceAttributeName) const {}

	/* reallocate the name specified attributes, divisor decide the attributes' layout */ 
	void ReallocateInstanceAttributeSlot(const std::string& InstanceAttributeName, UInt32 InstanceAttributesNum, UInt32 Divisor, const void* InitialInstanceAttributes) noexcept
	{
		if (!_VertexArray) return;

	}

	void WriteToInstanceAttributeSlot(const std::string& InstanceAttributeName, UInt32 InstanceAttributeOffset, UInt32 InstanceAttributesNum)
	{}

	void ReadFromInstanceAttributeSlot(const std::string& InstanceAttributeName, UInt32 InstanceAttributeOffset, UInt32 InstanceAttributesNum)
	{}

	void HandleInstanceAttributeSlot(const std::string& InstanceAttributeName, UInt32 InstanceAttributeOffset, UInt32 InstanceAttributesNum)
	{}

public:

	/* Get elements num.*/
	UInt32 GetElementsNum() const { return _ElementArrayBuffer ? _ElementArrayBuffer->GetElementsNum() : 0; }
	
	/* Get element size.*/
	UInt32 GetElementSize() const { return _ElementArrayBuffer ? _ElementArrayBuffer->GetElementSize() : 0; }

	/* Get element type.*/
	ElementType GetElementType() const { return _ElementArrayBuffer ? _ElementArrayBuffer->GetElementType() : ElementType::NONE; }

	/*
	* Indices only associates to PrimitiveMode
	* PrimitiveMode will never change once lancher constructed
	* IndicesNum % PrimitiveVerticesNum = 0
	*/
	void ReallocateElementSlot(UInt32 ElementsNum, const void* InitialElements = nullptr) noexcept
	{
		if (!_ElementArrayBuffer) return;
		if (ElementsNum % _PrimitiveVerticesNum != 0) return;
		
		_ElementArrayBuffer->Reallocate(ElementsNum, InitialElements);
	}

	void WriteToElementSlot(UInt32 ElementOffset, UInt32 ElementsNum, const ElementSlotWriter& Writer) 
	{
		if (!_ElementArrayBuffer) return;
		_ElementArrayBuffer->WriteToElementBuffer(ElementOffset, ElementsNum, Writer);
	}

	void ReadFromElementSlot(UInt32 ElementOffset, UInt32 ElementsNum, const ElementSlotReader& Reader) 
	{
		if (!_ElementArrayBuffer) return;
		_ElementArrayBuffer->ReadFromElementBuffer(ElementOffset, ElementsNum, Reader);
	}

	/*
	* Map the element slot as Client memory, it will copy data from Server, after handling over, then copy back to Server
	* ElementOffset(UInt32)
	* ElementsNum(UInt32)
	* Handler([](void* MappedMemory, UInt32 ElementsNum) {})
	*/
	void HandleElementSlot(UInt32 ElementOffset, UInt32 ElementsNum, const ElementSlotHandler& Handler) 
	{
		if (!_ElementArrayBuffer) return;

		_ElementArrayBuffer->HandleElementBuffer(ElementOffset, ElementsNum, Handler);
	}

	void SetPrimitiveRestartFlagElement(UInt32 ElementOffset)
	{
		if (!_ElementArrayBuffer) return;

		_ElementArrayBuffer->SetPrimitiveRestartFlagElement(ElementOffset);
	}

	const std::vector<UInt32>& GetPrimitiveRestartFlagElementIndices() const 
	{

	}

public:

	void Bind() const noexcept
	{
		if(_VertexArray) _VertexArray->Bind();
		if(_ElementArrayBuffer) _ElementArrayBuffer->Bind();
	}

	void Unbind() const noexcept
	{
		if (_VertexArray) _VertexArray->Unbind();
		if (_ElementArrayBuffer) _ElementArrayBuffer->Unbind();
	}

public:

	PrimitiveMode GetPrimitiveMode() const { return _PrimitiveMode; }

private:

	PrimitiveMode _PrimitiveMode;

	UInt32 _PrimitiveVerticesNum;

	UniquePtr<VertexArray> _VertexArray;

	UniquePtr<ElementArrayBuffer> _ElementArrayBuffer;
	
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