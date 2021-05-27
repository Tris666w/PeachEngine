#include <Peach.h>

class SandboxApp final :public peach::Application
{
public:
	SandboxApp()
	{

	}
	~SandboxApp() override
	{

	}

};

peach::Application* peach::CreateApplication()
{
	return new SandboxApp();
}
