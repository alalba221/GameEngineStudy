#include <Alalba.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

class App : public Alalba::Application
{
public:
	App()
	{
		
	}
	~App()
	{
		
	}

	//virtual void Tick() override
	//{

	//}

	//virtual void Init() override
	//{
	//	ALALBA_INFO("Hello from dpa8090 OnInit");

	//
	//}

	//virtual void Exit() override
	//{
	//	

	//}



private:


};	


Alalba::Application* Alalba::CreateApplication()
{
	return new App();
}