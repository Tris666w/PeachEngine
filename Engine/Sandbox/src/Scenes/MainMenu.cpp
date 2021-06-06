#include "QbertPCH.h"
#include "MainMenu.h"

#include "TextComponent.h"
#include "TextureComponent.h"
#include "GameModeChangeAndStartGameCommand.h"
#include "QbertGameSettings.h"

Qbert::MainMenu::MainMenu() :Scene("MainMenu")
{
}

void Qbert::MainMenu::Initialize()
{
	auto windowDimensions = peach::Application::GetWindowDimensions();

	//Background
	auto go = new peach::GameObject();
	auto textureComp = new peach::TextureComponent("Resources/Images/background.jpeg", windowDimensions.x, windowDimensions.y);
	go->AddComponent(textureComp);
	Add(go);



	auto fontBig = peach::ResourceManager::GetInstance().LoadFont("Resources/Fonts/q-bert-original.ttf", 64);
	auto fontSmall = peach::ResourceManager::GetInstance().LoadFont("Resources/Fonts/q-bert-original.ttf", 32);
	SDL_Color color = { 255,119,0 };

	//Single Player
	glm::vec2 drawPos = { 1 * windowDimensions.x / 5.f, windowDimensions.y / 2.f };
	go = new peach::GameObject();
	auto textComp = new peach::TextComponent("Solo", fontBig);
	textComp->SetColor(color);
	go->AddComponent(textComp);
	go->SetPosition(drawPos.x, drawPos.y);
	Add(go);

	drawPos.y += 64;
	go = new peach::GameObject();
	textComp = new peach::TextComponent("Press 1", fontSmall);
	textComp->SetColor(color);
	go->AddComponent(textComp);
	go->SetPosition(drawPos.x, drawPos.y);
	Add(go);

	//Coop
	drawPos = { 2 * windowDimensions.x / 5.f, 3 * windowDimensions.y / 4.f };
	go = new peach::GameObject();
	textComp = new peach::TextComponent("Coop", fontBig);
	textComp->SetColor(color);
	go->AddComponent(textComp);
	go->SetPosition(drawPos.x, drawPos.y);
	Add(go);

	drawPos.y += 64;
	go = new peach::GameObject();
	textComp = new peach::TextComponent("Press 2", fontSmall);
	textComp->SetColor(color);
	go->AddComponent(textComp);
	go->SetPosition(drawPos.x, drawPos.y);
	Add(go);

	//Logo
	go = new peach::GameObject();
	textureComp = new peach::TextureComponent("Resources/Images/Game_icon.png");
	go->AddComponent(textureComp);
	go->SetPosition(drawPos.x, 0);
	Add(go);

	//Versus
	drawPos = { 3 * windowDimensions.x / 5.f, windowDimensions.y / 2.f };
	go = new peach::GameObject();
	textComp = new peach::TextComponent("Versus", fontBig);
	textComp->SetColor(color);
	go->AddComponent(textComp);
	go->SetPosition(drawPos.x, drawPos.y);
	Add(go);

	drawPos.y += 64;
	go = new peach::GameObject();
	textComp = new peach::TextComponent("Press 3", fontSmall);
	textComp->SetColor(color);
	go->AddComponent(textComp);
	go->SetPosition(drawPos.x, drawPos.y);
	Add(go);

	auto startCommand = std::make_shared<GameModeChangeAndStartGameCommand>(GameMode::SinglePlayer);
	GetInputManager()->AddOrChangeCommand('1', startCommand, peach::CommandExecuteCause::ButtonDown);

	startCommand = std::make_shared<GameModeChangeAndStartGameCommand>(GameMode::Coop);
	GetInputManager()->AddOrChangeCommand('2', startCommand, peach::CommandExecuteCause::ButtonDown);

	startCommand = std::make_shared<GameModeChangeAndStartGameCommand>(GameMode::Versus);
	GetInputManager()->AddOrChangeCommand('3', startCommand, peach::CommandExecuteCause::ButtonDown);
}
