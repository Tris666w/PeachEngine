#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "FPS/FPSCounter.h"
#include "Peach.h"
#include "QbertGameSettings.h"
#include "ResourceManager.h"
#include "ServicesBase.h"
#include "SoundSystems.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Level/LevelComponent.h"

#ifdef _DEBUG
#include <vld.h>
#endif

class SandboxApp final :public peach::Application
{
public:
	SandboxApp() :Application({ 1280,720 })
	{

	}
	~SandboxApp() override
	{

	}

	void LoadGame() const override
	{
		using namespace peach;

		auto windowDimensions = GetWindowDimensions();


		auto& scene = SceneManager::GetInstance().CreateScene("Qbert");
		SceneManager::GetInstance().SetActiveGameScene("Qbert");

		auto go = new GameObject();
		auto textureComp = new TextureComponent("Resources/Images/background.jpg", windowDimensions.x, windowDimensions.y);
		go->AddComponent(textureComp);
		scene.Add(go);

		go = new GameObject();
		auto lc = new LevelComponent();
		go->AddComponent(lc);
		scene.Add(go);
		go->SetPosition(windowDimensions.x / 3.f, 2 * windowDimensions.y / 3.f);

		go = new GameObject();
		textureComp = new TextureComponent("Resources/Images/Qbert.png", 32, 32);
		go->AddComponent(textureComp);
		scene.Add(go);
		go->SetTag(QbertGameSettings::qbert_tag);



		auto font = ResourceManager::GetInstance().LoadFont("Resources/Fonts/Lingua.otf", 36);
		go = new GameObject();
		auto to = new TextComponent("X FPS", font);
		go->SetPosition(5.f, 20);
		go->AddComponent(to);
		FPSCounter* fpsCounter = new FPSCounter(to);
		go->AddComponent(fpsCounter);
		scene.Add(go);

		/*	auto* sdlSs = new SDLMixerSoundSystem();
			ServiceLocator::RegisterSoundSystem(sdlSs);
			MusicID const musicID = sdlSs->AddMusic("Resources/Sound/If-it-means-a-lot-to-you.wav");
			auto& ss = ServiceLocator::GetSoundSystem();
			ss.PlayMusic(musicID, 10);
			delete sdlSs;*/
	}
};

int main(int, char* [])
{
	SandboxApp engine{};
	engine.Run();
	return 0;
}
