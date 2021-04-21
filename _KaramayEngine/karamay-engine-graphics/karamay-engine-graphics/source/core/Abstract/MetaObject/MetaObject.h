#pragma once
#include "Public/STL.h"

class MetaObject
{
public:
	virtual std::string GetClassName();

public:
	MetaObject();
	virtual ~MetaObject();
};

