#include "QbertPCH.h"
#include "LevelEnemyManager.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "Level/LevelMovementComponent.h"
#include "Enemies/CoilyComponent.h"

void Qbert::LevelEnemyManager::Initialize()
{
	m_CoilyComponent = CreateCoilyGameObject();
}

void Qbert::LevelEnemyManager::PostInitialize()
{
	m_CoilyComponent->Spawn();
}

void Qbert::LevelEnemyManager::Update()
{
}

Qbert::CoilyComponent* Qbert::LevelEnemyManager::CreateCoilyGameObject() const
{
	auto go = new peach::GameObject();

	auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Coily/Egg.png", 32, 32);
	go->AddComponent(textureComp);

	auto const moveComponent = new LevelMovementComponent();
	go->AddComponent(moveComponent);

	auto const coilyComponent = new CoilyComponent();
	go->AddComponent(coilyComponent);

	GetParent()->AddChild(go);

	return coilyComponent;
}
