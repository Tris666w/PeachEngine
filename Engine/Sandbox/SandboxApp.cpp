#include <windows.h>


#include "Command.h"
#include "Health/DamageCommand.h"
#include "FPS/FPSCounter.h"
#include "Health/Health.h"
#include "InputManager.h"
#include "Peach.h"
#include "Player/PlayerUI.h"
#include "ResourceManager.h"
#include "Score/ScoreCommand.h"
#include "Score/ScoreComponent.h"
#include "ServicesBase.h"
#include "SoundSystems.h"
#include "TextObject.h"
class SandboxApp final :public peach::Application
{
public:
	SandboxApp() :Application()
	{

	}
	~SandboxApp() override
	{

	}

	void LoadGame() const override
	{
		using namespace peach;

		auto& scene = SceneManager::GetInstance().CreateScene("Demo");

		auto go = std::make_shared<GameObject>();
		go->SetTexture("background.jpg");
		scene.Add(go);

		go = std::make_shared<GameObject>();
		go->SetTexture("logo.png");
		go->SetPosition(216, 180);
		scene.Add(go);

		auto qBert1 = std::make_shared<GameObject>();
		qBert1->SetTexture("Qbert.png");
		qBert1->SetPosition(0, 100);
		Health* healthComponent1 = new Health(qBert1.get(), 5, 5);
		ScoreComponent* scoreComponent1 = new ScoreComponent(qBert1.get());

		std::shared_ptr<Command> const takeDamageCommand1 = std::make_shared<DamageCommand>(healthComponent1);
		std::shared_ptr<Command> const colorChangeScoreCommand1 = std::make_shared<ScoreCommand>(scoreComponent1, 25);
		std::shared_ptr<Command> const coilyScoreCommand1 = std::make_shared<ScoreCommand>(scoreComponent1, 500);
		std::shared_ptr<Command> const remainingDiscScoreCommand1 = std::make_shared<ScoreCommand>(scoreComponent1, 50);
		std::shared_ptr<Command> const catchScoreCommand1 = std::make_shared<ScoreCommand>(scoreComponent1, 300);

		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonLeftShoulder, takeDamageCommand1, CommandExecuteCause::ButtonDown);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonUp, colorChangeScoreCommand1, CommandExecuteCause::ButtonDown);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonLeft, coilyScoreCommand1, CommandExecuteCause::ButtonDown);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonRight, remainingDiscScoreCommand1, CommandExecuteCause::ButtonDown);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonDown, catchScoreCommand1, CommandExecuteCause::ButtonDown);

		qBert1->AddComponent(healthComponent1);
		qBert1->AddComponent(scoreComponent1);
		scene.Add(qBert1);

		const auto playerUi1 = std::make_shared<PlayerUI>(ImVec2(100, 150), "1", 0, 5, healthComponent1->GetpSubject(), scoreComponent1->GetpSubject());
		scene.Add(playerUi1);


		auto qBert2 = std::make_shared<GameObject>();
		qBert2->SetTexture("Qbert.png");
		qBert2->SetPosition(350, 100);
		Health* healthComponent2 = new Health(qBert2.get(), 5, 5);
		ScoreComponent* scoreComponent2 = new ScoreComponent(qBert2.get());

		std::shared_ptr<Command> const takeDamageCommand2 = std::make_shared<DamageCommand>(healthComponent2);
		std::shared_ptr<Command> const colorChangeScoreCommand2 = std::make_shared<ScoreCommand>(scoreComponent2, 25);
		std::shared_ptr<Command> const coilyScoreCommand2 = std::make_shared<ScoreCommand>(scoreComponent2, 500);
		std::shared_ptr<Command> const remainingDiscScoreCommand2 = std::make_shared<ScoreCommand>(scoreComponent2, 50);
		std::shared_ptr<Command> const catchScoreCommand2 = std::make_shared<ScoreCommand>(scoreComponent2, 300);

		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonRightShoulder, takeDamageCommand2, CommandExecuteCause::ButtonDown);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonY, colorChangeScoreCommand2, CommandExecuteCause::ButtonDown);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonX, coilyScoreCommand2, CommandExecuteCause::ButtonDown);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonB, remainingDiscScoreCommand2, CommandExecuteCause::ButtonDown);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonA, catchScoreCommand2, CommandExecuteCause::ButtonDown);

		qBert2->AddComponent(healthComponent2);
		qBert2->AddComponent(scoreComponent2);
		scene.Add(qBert2);
		const auto playerUi2 = std::make_shared<PlayerUI>(ImVec2(350, 150), "2", 0, 5, healthComponent2->GetpSubject(), scoreComponent2->GetpSubject());
		scene.Add(playerUi2);


		go = std::make_shared<GameObject>();
		go->SetTexture("ControllerScheme.png");
		go->SetPosition(0, 250);
		scene.Add(go);


		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
		to->SetPosition(90, 20);
		scene.Add(to);

		to = std::make_shared<TextObject>("X FPS", font);
		to->SetPosition(5.f, 20);
		FPSCounter* fpsCounter = new FPSCounter((to).get());
		to->AddComponent(fpsCounter);
		scene.Add(to);

		auto& t1 = ServiceLocator::GetSoundSystem();
		t1.PlaySoundEffect(5, 50);


		auto* sdlSs = new SDLMixerSoundSystem();
		ServiceLocator::RegisterSoundSystem(sdlSs);
		SoundEffectID const soundID = sdlSs->AddSound("../Data/Sound/Powerup.wav");
		MusicID const musicID = sdlSs->AddMusic("../Data/Sound/TWICE_Mix.wav");

		auto& ss = ServiceLocator::GetSoundSystem();
		ss.PlaySoundEffect(soundID, 50);
		ss.PlayMusic(musicID, 10);

		delete sdlSs;
	}
};

int main(int, char* [])
{
	SandboxApp engine{};
	engine.Run();
	return 0;
}
