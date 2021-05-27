#pragma once


#ifdef P_PLATFORM_WINDOWS

extern peach::Application* peach::CreateApplication();

int main(int argc, char** argv)
{
	peach::Application* app = peach::CreateApplication();
	app->Run();
	delete app;
}


#endif