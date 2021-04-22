#pragma once
#include "Public/STL.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

class WindowBase : public MetaObject
{
public:
	virtual void LoadContext();
	
	virtual void Tick(float DeltaTime);
	
	virtual std::pair<size_t, size_t> GetFramebufferSize();

public:
	virtual void Show() = 0;

	virtual void Hide() = 0;
	
	virtual void Maximize() = 0;
	
	virtual void Minimize() = 0;
	
	virtual void Restore() = 0;

	virtual void SwitchWindowed(int UpperLeftX, int UpperLeftY, int Width, int Height) = 0;
	
	virtual void SwitchFullScreen() = 0;
	
	virtual bool IsFullScreen();

protected:
	bool bFullScreen : 1;

};


class WindowFactory
{
public:
	virtual WindowBase* Create()
	{
		return nullptr;
	}
};
