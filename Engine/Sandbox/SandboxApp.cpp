#include "QbertPCH.h"
#include "Peach.h"
#include "scenes/QbertScene.h"
#include "scenes/MainMenu.h"
#include "Scenes/VictoryScreen.h"

#ifdef _DEBUG
#include <vld.h>
#endif

class SandboxApp final :public peach::Application
{
public:
	SandboxApp() :Application({ 1280,720 })
	{
		SetApplicationName("Qbert");
	}
	~SandboxApp() override
	{

	}
	void LoadGame() const override
	{
		peach::SceneManager::GetInstance().AddScene(std::make_shared<Qbert::MainMenu>());
		peach::SceneManager::GetInstance().SetActiveGameScene("MainMenu");
	}
};

int main(int, char* [])
{
	SandboxApp engine{};
	engine.Run();
	return 0;
}
