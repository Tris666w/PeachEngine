#include "QbertPCH.h"
#include "LossScreen.h"

#include "QuitCommand.h"
#include "TextComponent.h"
#include "TextureComponent.h"

Qbert::LossScreen::LossScreen() :Scene("LossScreen")
{
}

void Qbert::LossScreen::Initialize()
{
	auto windowDimensions = peach::Application::GetWindowDimensions();

	//Background
	auto go = new peach::GameObject();
	auto textureComp = new peach::TextureComponent("Resources/Images/background.jpeg", windowDimensions.x, windowDimensions.y);
	go->AddComponent(textureComp);
	Add(go);

	auto fontBig = peach::ResourceManager::GetInstance().LoadFont("Resources/Fonts/q-bert-original.ttf", 86);
	auto fontSmall = peach::ResourceManager::GetInstance().LoadFont("Resources/Fonts/q-bert-original.ttf", 32);

	SDL_Color color = { 255,119,0 };

	glm::vec2 drawPos = { 0.25f * windowDimensions.x , 0.33f * windowDimensions.y };
	go = new peach::GameObject();
	auto textComp = new peach::TextComponent("You Lose!", fontBig);
	textComp->SetColor(color);
	go->AddComponent(textComp);
	go->SetPosition(drawPos.x, drawPos.y);
	Add(go);

	drawPos.y += 86;
	go = new peach::GameObject();
	textComp = new peach::TextComponent("Press enter to quit", fontSmall);
	textComp->SetColor(color);
	go->AddComponent(textComp);
	go->SetPosition(drawPos.x, drawPos.y);
	Add(go);
	auto quitCommnad = std::make_shared<QuitCommand>();
	GetInputManager()->AddOrChangeCommand(SDLK_RETURN, quitCommnad, peach::CommandExecuteCause::ButtonDown);
}
