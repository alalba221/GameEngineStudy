#include "AlalbaEngine/Core/Renderer/Renderer.h"
#include "Window.h"
namespace Alalba
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		void PreInit();
		void Init();
		void PostInit();

		inline Window& GetWindow() { return *m_Window; }
	private:
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<Window> m_Window;

	};
}

