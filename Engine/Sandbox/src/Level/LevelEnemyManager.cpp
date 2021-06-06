#include "QbertPCH.h"
#include "LevelEnemyManager.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "Level/LevelMovementComponent.h"
#include "Enemies/CoilyComponent.h"
#include "Enemies/SlickSamComponent.h"
#include "Enemies/UggWrongwayComponent.h"
#include "RectColliderComponent.h"


Qbert::LevelEnemyManager::LevelEnemyManager(int charSize)
	:ComponentBase(),
	m_CharSize(charSize)
{
}

void Qbert::LevelEnemyManager::Initialize()
{
	m_CoilyComponent = CreateCoilyGameObject();
	m_SlickComponent = CreateSlickOrSamGameObject(true);
	m_SamComponent = CreateSlickOrSamGameObject(false);
	m_Ugg = CreateUggOrWrongwayGameObject(true);
	m_Wrongway = CreateUggOrWrongwayGameObject(false);

}

void Qbert::LevelEnemyManager::PostInitialize()
{
	m_CoilyComponent->Spawn();
	m_Ugg->Spawn();
	m_Wrongway->Spawn();
}

void Qbert::LevelEnemyManager::Update()
{
}

void Qbert::LevelEnemyManager::Render() const
{
}

Qbert::CoilyComponent* Qbert::LevelEnemyManager::CreateCoilyGameObject() const
{
	auto go = new peach::GameObject();

	auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Coily/Egg.png", static_cast<float>(m_CharSize), static_cast<float>(m_CharSize));
	go->AddComponent(textureComp);

	auto const moveComponent = new LevelMovementComponent();
	go->AddComponent(moveComponent);

	SDL_Rect colliderRect = { 0.25 * m_CharSize,0.25 * m_CharSize,0.75 * m_CharSize, 0.75 * m_CharSize };
	auto const colliderComponent = new peach::RectColliderComponent(colliderRect);
	go->AddComponent(colliderComponent);

	auto const coilyComponent = new CoilyComponent();
	go->AddComponent(coilyComponent);

	GetParent()->AddChild(go);

	return coilyComponent;
}

Qbert::SlickSamComponent* Qbert::LevelEnemyManager::CreateSlickOrSamGameObject(bool isSlick) const
{
	auto go = new peach::GameObject();

	if (isSlick)
	{
		auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Slick/Slick.png", m_CharSize, m_CharSize);
		go->AddComponent(textureComp);
	}
	else
	{
		auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Sam/Sam.png", m_CharSize, m_CharSize);
		go->AddComponent(textureComp);
	}

	auto const moveComponent = new LevelMovementComponent();
	go->AddComponent(moveComponent);

	SDL_Rect colliderRect = { 0.25 * m_CharSize,0.25 * m_CharSize,0.75 * m_CharSize, 0.75 * m_CharSize };
	auto const colliderComponent = new peach::RectColliderComponent(colliderRect);
	go->AddComponent(colliderComponent);


	auto const slickSamComp = new SlickSamComponent(isSlick);
	go->AddComponent(slickSamComp);

	GetParent()->AddChild(go);

	return slickSamComp;
}

Qbert::UggWrongwayComponent* Qbert::LevelEnemyManager::CreateUggOrWrongwayGameObject(bool isUgg) const
{
	auto go = new peach::GameObject();

	if (isUgg)
	{
		auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Ugg/Ugg.png", m_CharSize, m_CharSize);
		go->AddComponent(textureComp);
	}
	else
	{
		auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Wrongway/Wrongway.png", m_CharSize, m_CharSize);
		go->AddComponent(textureComp);
	}

	auto const moveComponent = new LevelMovementComponent();
	go->AddComponent(moveComponent);

	SDL_Rect colliderRect = { 0.25 * m_CharSize,0.25 * m_CharSize,0.75 * m_CharSize, 0.75 * m_CharSize };
	auto const colliderComponent = new peach::RectColliderComponent(colliderRect);
	go->AddComponent(colliderComponent);


	auto const uggWrongwayComp = new UggWrongwayComponent(isUgg);
	go->AddComponent(uggWrongwayComp);

	GetParent()->AddChild(go);

	return uggWrongwayComp;
}
