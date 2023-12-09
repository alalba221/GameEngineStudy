#include "pch.h"
#include "Engine.h"

namespace Alalba
{
	Engine::Engine()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Engine::~Engine()
	{
	}

	void Engine::PreInit()
	{
	}

	void Engine::Init()
	{
		m_Window->Init();
	}

	void Engine::PostInit()
	{
	}
}

