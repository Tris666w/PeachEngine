#include "QbertPCH.h"
#include "Peach.h"
#include "scenes/MainMenu.h"
#include "SoundSystems.h"

class SandboxApp final :public peach::Application
{
public:
	SandboxApp() :Application({ 1280,720 })
	{
		SetApplicationName("Qbert");
	}
	~SandboxApp() override
	{
		SafeDelete(ServiceLocator::GetSoundSystem());
	}
	void LoadGame() const override
	{
		auto* sdlss = new SDLMixerSoundSystem();
		ServiceLocator::RegisterSoundSystem(sdlss);

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
