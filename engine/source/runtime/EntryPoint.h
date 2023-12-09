#pragma once

extern Alalba::Application* Alalba::CreateApplication();

int main(int argc, char** argv)
{

	auto app = Alalba::CreateApplication();
	app->Run();
	delete app;
	return 0;
}