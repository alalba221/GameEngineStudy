#pragma once

#include <memory>

//#include "Events/ApplicationEvent.h"

#include "Engine.h"
#include "Timer.h"

namespace Alalba{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		virtual void Init();
	
		virtual void Tick() {}

		virtual void Exit();
	

	private:
		static Application* s_Instance;
		std::unique_ptr<Engine> m_Engine;
		std::unique_ptr<Timer> m_Timer;
	
	// keep from Alalba_VK
	public:
		static inline Application& Get() { return *s_Instance; }
		inline Engine& GetEngine() { return *m_Engine; }

	//	void OnEvent(Event& event);
	//private: 
	//	bool OnWindowClose(WindowCloseEvent& e);
	//	bool OnWindowResize(WindowResizeEvent& e);
	private:
		bool m_Running = true;
	
	};

	// to be defined in sandbox
	Application* CreateApplication();
}
