#pragma once

#include <memory>

namespace Alalba{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		virtual void Init();
	
		virtual void Tick() { }

		virtual void Exit();
	

	private:
		static Application* s_Instance;

	
	// keep from Alalba_VK
	public:
		static inline Application& Get() { return *s_Instance; }
	
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
