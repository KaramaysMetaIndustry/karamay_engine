#include "RendererAllocator_OpenGL.h"

void RendererAllocator_OpenGL::Initialize()
{
}

GLuint RendererAllocator_OpenGL::GetTexture2DSlot()
{
	return SlotIndex++;
}

RendererAllocator_OpenGL::RendererAllocator_OpenGL()
{
	SlotIndex = 0;
}

RendererAllocator_OpenGL::~RendererAllocator_OpenGL()
{
	
}
