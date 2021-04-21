#include "WindowBase.h"
#include "Core/SpicesRendererGlobal.h"

void WindowBase::LoadContext()
{
}

void WindowBase::Tick(float DeltaTime)
{
}

std::pair<size_t, size_t> WindowBase::GetFramebufferSize()
{
	return std::pair<size_t, size_t>();
}

void WindowBase::Show()
{
}

void WindowBase::Hide()
{
}

void WindowBase::Maximize()
{
}

void WindowBase::Minimize()
{
}

void WindowBase::Restore()
{
}

bool WindowBase::IsFullScreen()
{
	return bFullScreen;
}
