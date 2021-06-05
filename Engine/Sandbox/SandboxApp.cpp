#include "QbertPCH.h"

#include "CollisionManager.h"
#include "FPS/FPSCounter.h"
#include "Peach.h"
#include "QbertGameSettings.h"
#include "ResourceManager.h"
#include "Player/QbertComponent.h"
#include "Player/QbertController.h"
#include "ServicesBase.h"
#include "SoundSystems.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Level/LevelComponent.h"
#include "Level/LevelMovementComponent.h"
#include "Level/LevelEnemyManager.h"
#include "RectColliderComponent.h"

#ifdef _DEBUG
#include <vld.h>
#endif

class SandboxApp final :public peach::Application
{
public:
	SandboxApp() :Application({ 1280,720 ,0 })
	{
		SetApplicationName("Qbert");
	}
	~SandboxApp() override
	{

	}
	void LoadGame() const override
	{
		using namespace peach;
		using namespace Qbert;

		auto windowDimensions = GetWindowDimensions();


		auto& scene = SceneManager::GetInstance().CreateScene("Qbert");
		SceneManager::GetInstance().SetActiveGameScene("Qbert");

		int const characterSize = 32;

		CollisionManager::GetInstance().ToggleDebugRendering(true);

		auto go = new GameObject();
		auto textureComp = new TextureComponent("Resources/Images/background.jpg", windowDimensions.x, windowDimensions.y);
		go->AddComponent(textureComp);
		scene.Add(go);

		go = new GameObject();
		auto lc = new LevelComponent();
		go->AddComponent(lc);
		auto lvmC = new LevelEnemyManager();
		go->AddComponent(lvmC);
		scene.Add(go);
		go->SetPosition(windowDimensions.x / 3.f, 2 * windowDimensions.y / 3.f);

		go = new GameObject();
		textureComp = new TextureComponent("Resources/Images/Qbert.png", characterSize, characterSize);
		go->AddComponent(textureComp);
		auto qbertComp = new QbertComponent();
		go->AddComponent(qbertComp);
		auto moveComponent = new LevelMovementComponent();
		go->AddComponent(moveComponent);
		auto controllerComp = new QbertController();
		go->AddComponent(controllerComp);
		SDL_Rect colliderRect = { 0,0,characterSize,characterSize };
		auto collider = new RectColliderComponent(colliderRect);
		go->AddComponent(collider);

		scene.Add(go);

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
