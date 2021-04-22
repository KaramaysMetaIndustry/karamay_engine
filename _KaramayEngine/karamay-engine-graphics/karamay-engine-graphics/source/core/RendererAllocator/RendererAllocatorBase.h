#pragma once
#include "Public/STL.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

class RendererAllocatorBase : public MetaObject
{
public:
	virtual void Initialize() = 0;
};

class RendererAllocatorFactory : public MetaObject
{
public:
	virtual RendererAllocatorBase* Create()
	{
		return nullptr;
	}
};

