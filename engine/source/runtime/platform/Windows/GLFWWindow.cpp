#include "pch.h"
#include "GLFWWindow.h"
//#include "AlalbaEngine/Core/Events/Event.h"
//#include "AlalbaEngine/Core/Events/ApplicationEvent.h"
//#include "AlalbaEngine/Core/Events/KeyEvent.h"
//#include "AlalbaEngine/Core/Events/MouseEvent.h"
namespace Alalba
{

	Window* Window::Create(const WindowSpecification& specification)
	{
		return new GLFWWindow(specification);
	}

	GLFWWindow::GLFWWindow(const WindowSpecification& props)
		: m_Specification(props)
	{
	}

	static bool s_GLFWInitialized = false;

	GLFWWindow::~GLFWWindow()
	{
		Shutdown();
	}

	void GLFWWindow::Init()
	{
		m_Data.Title = m_Specification.Title;
		m_Data.Width = m_Specification.Width;
		m_Data.Height = m_Specification.Height;

		ALALBA_INFO("Creating window {0} ({1}, {2})", m_Specification.Title, m_Specification.Width, m_Specification.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			ALALBA_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}
		// GLFW was originally designed to create an OpenGL context,
		// we need to tell it to not create an OpenGL context
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);


		if (m_Specification.Fullscreen)
		{
			GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

			glfwWindowHint(GLFW_DECORATED, false);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			m_Window = glfwCreateWindow(mode->width, mode->height, m_Data.Title.c_str(), primaryMonitor, nullptr);
		}
		else
		{
			m_Window = glfwCreateWindow((int)m_Specification.Width, (int)m_Specification.Height, m_Data.Title.c_str(), nullptr, nullptr);
		}

		ALALBA_ASSERT(m_Window, "glfw creation failed");

		glfwSetWindowUserPointer(m_Window, &m_Data);

		bool isRawMouseMotionSupported = glfwRawMouseMotionSupported();
		if (isRawMouseMotionSupported)
			glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		else
			ALALBA_WARN("Platform", "Raw mouse motion not supported.");

		//// Set	GLFW callbacks
		//glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		//	{
		//		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		//		data->Width = width;
		//		data->Height = height;

		//		WindowResizeEvent event(width, height);
		//		data->EventCallback(event);
		//	}
		//);

		//glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		//	{
		//		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		//		WindowCloseEvent event;
		//		data->EventCallback(event);

		//	}
		//);

		//glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mode)
		//	{
		//		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		//		switch (action)
		//		{
		//		case GLFW_PRESS:
		//		{
		//			KeyPressedEvent event(key, 0);
		//			data->EventCallback(event);
		//			break;
		//		}
		//		case GLFW_RELEASE:
		//		{
		//			KeyReleasedEvent event(key);
		//			data->EventCallback(event);
		//			break;
		//		}
		//		case GLFW_REPEAT:
		//		{
		//			KeyPressedEvent event(key, 1);
		//			data->EventCallback(event);
		//			break;
		//		}
		//		}
		//	});
		//glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//		KeyTypedEvent event(keycode);
		//		data.EventCallback(event);
		//	});
		//glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		//		switch (action)
		//		{
		//		case GLFW_PRESS:
		//		{
		//			MouseButtonPressedEvent event(button);
		//			data.EventCallback(event);
		//			break;
		//		}
		//		case GLFW_RELEASE:
		//		{
		//			MouseButtonReleasedEvent event(button);
		//			data.EventCallback(event);
		//			break;
		//		}
		//		}
		//	});

		//glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		//		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		//		data.EventCallback(event);
		//	});

		//glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		//		MouseMovedEvent event((float)xPos, (float)yPos);
		//		data.EventCallback(event);
		//	});

		//// Update window size to actual size
		//{
		//	int width, height;
		//	glfwGetWindowSize(m_Window, &width, &height);
		//	m_Data.Width = width;
		//	m_Data.Height = height;
		//}
	}
	void GLFWWindow::ProcessEvents()
	{
		glfwPollEvents();
	}
	std::pair<float, float> GLFWWindow::GetWindowPos() const
	{
		int x, y;
		glfwGetWindowPos(m_Window, &x, &y);
		return { (float)x, (float)y };
	}
	void GLFWWindow::SetVSync(bool enabled)
	{
	}
	bool GLFWWindow::IsVSync() const
	{
		return false;
	}
	void GLFWWindow::SetResizable(bool resizable) const
	{
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
	}
	void GLFWWindow::Maximize()
	{
		glfwMaximizeWindow(m_Window);
	}
	void GLFWWindow::CenterWindow()
	{
		const GLFWvidmode* videmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int x = (videmode->width / 2) - (m_Data.Width / 2);
		int y = (videmode->height / 2) - (m_Data.Height / 2);
		glfwSetWindowPos(m_Window, x, y);
	}
	void GLFWWindow::SetTitle(const std::string& title)
	{
		m_Data.Title = title;
		glfwSetWindowTitle(m_Window, m_Data.Title.c_str());
	}
	void GLFWWindow::Shutdown()
	{
		// glfwDestroyWindow(m_Window);
		glfwTerminate();
		s_GLFWInitialized = false;
	}
}
