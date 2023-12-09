#include "pch.h"
#include "GLFWInput.h"
#include "AlalbaEngine/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Alalba
{
	Input* Input::s_Instance = new GLFWInput();

	bool GLFWInput::IsKeyPressedImpl(int keycode)
	{
		auto& Engine = Application::Get().GetEngine();
		auto window = static_cast<GLFWwindow*>(Engine.GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GLFWInput::IsMouseButtonPressedImpl(int button)
	{
		auto& Engine = Application::Get().GetEngine();
		auto window = static_cast<GLFWwindow*>(Engine.GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> GLFWInput::GetMousePositionImpl()
	{
		auto& Engine = Application::Get().GetEngine();
		auto window = static_cast<GLFWwindow*>(Engine.GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float GLFWInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float GLFWInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
