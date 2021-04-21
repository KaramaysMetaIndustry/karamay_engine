#pragma once
#include "Public/STL.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

class ShaderAssemblageInfoBase;

class ShaderBase : public MetaObject
{
public:
	virtual void Assembly(ShaderAssemblageInfoBase* Info);
};

class ShaderFactory
{
public:
	virtual ShaderBase* CreateShader() = 0;
};

