#include "pch.h"
#include "Window.h"
//#include <GLFW/glfw3.h>
#include "AlalbaEngine/Platform/Windows/GLFWWindow.h"
namespace Alalba 
{
	static Window* Create(const WindowSpecification& specification)
	{
		return new GLFWWindow(specification);
	}
	
}