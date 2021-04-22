#include "MetaObject.h"

std::string MetaObject::GetClassName()
{
	const type_info& info = typeid(*this);
	std::string name(info.name());
	auto pos = name.find("class ");

	name.erase(pos, 6);
	return name;
}

MetaObject::MetaObject()
{
	
}

MetaObject::~MetaObject()
{
}
