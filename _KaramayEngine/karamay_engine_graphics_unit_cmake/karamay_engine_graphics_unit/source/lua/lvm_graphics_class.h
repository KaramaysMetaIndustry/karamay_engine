#ifndef LVM_GRAPHICS_CLASS_H
#define LVM_GRAPHICS_CLASS_H

class CTest
{
public:
	CTest() : value(0) {}

	~CTest() = default;

public:

	int getA() { return value; }

	void setA(int a) { value = a; }

	CTest* finishNewCTest(CTest* test) 
	{
		if (test) test->setA(test->getA());
		return test;
	}

	CTest* finishNewCTest(CTest* test, int i)
	{
		if (test) test->setA(10);
		return test;
	}

private:

	int value;

};

#include "graphics/renderer/gl_renderer.h"


#endif