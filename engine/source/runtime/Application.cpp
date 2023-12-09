#include "pch.h"
#include "Application.h"

namespace Alalba
{


	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		s_Instance = this;

	}

	void Application::Init()
	{
	
	}

	void Application::Exit()
	{
	}



	Application::~Application()
	{
	}

	void Application::Run()
	{
		Init();

		while(m_Running)
		{
			Tick();
			
		}
		Exit();
	}
}