#ifndef LVM_CLASS_EXAMPLE_H
#define LVM_CLASS_EXAMPLE_H

class CTest
{
public:
	CTest() : value(0) {}

	~CTest() = default;

	int getA();

	void setA(int a) { value = a; }

	CTest* finishNewCTest(CTest* test) 
	{
		if (test)
		{
			test->setA(10);
		}
		return test;
	}

private:
	int value;

};


#endif