#pragma once

#ifdef P_PLATFORM_WINDOWS

extern peach::Application* peach::CreateApplication();

int main(int argc, char** argv)
{
	auto app = peach::CreateApplication();
	app->LoadGame();
	app->Run();
	delete app;
}

#endif
