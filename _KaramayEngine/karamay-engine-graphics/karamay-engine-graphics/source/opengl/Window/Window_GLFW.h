#pragma once
#include "Public/OpenGL.h"
#include "Public/GLFW.h"
#include "Public/STL.h"
#include "Core/Window/WindowBase.h"

class Window_GLFW : public WindowBase
{
	using MonitorMode = std::pair<GLFWmonitor*, const GLFWvidmode*>;

public:
	virtual void LoadContext() override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual std::pair<size_t, size_t> GetFramebufferSize() override;

public:
	virtual void Show() override;

	virtual void Hide() override;
	
	virtual void Maximize() override;
	
	virtual void Minimize() override;
	
	virtual void Restore() override;
	
	void SwitchWindowed(int UpperLeftX, int UpperLeftY, int Width, int Height) override;
	
	void SwitchFullScreen() override;
	
	virtual bool IsFullScreen() override;

public:
	std::pair<size_t, size_t> GetPrimaryMonitorPhysicalSize();

private:
	void SetCallback();
	void SetInputMode();

	int FrameBufferWidth, FrameBufferHeight;

private:
	MonitorMode PrimaryMonitorMode;

	std::vector<MonitorMode> OtherMonitorModes;

	/** The main monitor. */
	//GLFWmonitor* PrimaryMonitor;
	/** The mode of main monitor. */
	//const GLFWvidmode* PrimaryMonitorMode;
	

	/** The window entity. */
	GLFWwindow* Window;
	/** The window title. */
	std::string Title;

	size_t WindowedWidth, WindowedHeight;

};

class WindowFactory_GLFW : public WindowFactory
{
public:
	virtual WindowBase* Create()
	{
		return new Window_GLFW();
	}
};

