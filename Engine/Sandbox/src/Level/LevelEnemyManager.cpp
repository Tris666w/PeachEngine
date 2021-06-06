#include "QbertPCH.h"
#include "LevelEnemyManager.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "Level/LevelMovementComponent.h"
#include "Enemies/CoilyComponent.h"
#include "Enemies/SlickSamComponent.h"
#include "Enemies/UggWrongwayComponent.h"
#include "RectColliderComponent.h"
#include "QbertGameSettings.h"
#include "Enemies/CoilyController.h"


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

	if (QbertGameSettings::GetInstance().GetGameMode() == GameMode::Versus)
	{
		m_CoilyComponent->Spawn();
		m_amountOfEnemiesSpawned = 1;
	}
}

void Qbert::LevelEnemyManager::PostInitialize()
{
}

void Qbert::LevelEnemyManager::Update()
{
	if (m_amountOfEnemiesSpawned < 5)
	{
		m_SpawnTimer += peach::GameTime::GetInstance().GetElapsedSec();
		if (m_SpawnTimer > m_SpawnTime)
		{
			SpawnRandomEnemy();
			m_SpawnTimer = 0.f;
		}
	}
}

void Qbert::LevelEnemyManager::Render() const
{
}

void Qbert::LevelEnemyManager::Reset()
{
	m_CoilyComponent->Remove();
	m_SlickComponent->Remove();
	m_SamComponent->Remove();
	m_Ugg->Remove();
	m_Wrongway->Remove();

	m_SpawnTimer = 0.f;
	m_amountOfEnemiesSpawned = 0;

	if (QbertGameSettings::GetInstance().GetGameMode() == GameMode::Versus)
	{
		m_CoilyComponent->Spawn();
		m_amountOfEnemiesSpawned = 1;
	}

}

Qbert::CoilyComponent* Qbert::LevelEnemyManager::CreateCoilyGameObject() const
{
	auto go = new peach::GameObject();

	auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Coily/Egg.png", static_cast<float>(m_CharSize), static_cast<float>(m_CharSize));
	go->AddComponent(textureComp);

	auto const moveComponent = new LevelMovementComponent();
	go->AddComponent(moveComponent);

	SDL_Rect colliderRect = { static_cast<int>(0.25 * m_CharSize),static_cast<int>(0.25 * m_CharSize),static_cast<int>(0.75 * m_CharSize), static_cast<int>(0.75 * m_CharSize) };
	auto const colliderComponent = new peach::RectColliderComponent(colliderRect);
	go->AddComponent(colliderComponent);

	if (QbertGameSettings::GetInstance().GetGameMode() == GameMode::Versus)
	{
		auto coilyController = new CoilyController();
		go->AddComponent(coilyController);
	}

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
		auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Slick/Slick.png", static_cast<float>(m_CharSize), static_cast<float>(m_CharSize));
		go->AddComponent(textureComp);
	}
	else
	{
		auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Sam/Sam.png", static_cast<float>(m_CharSize), static_cast<float>(m_CharSize));
		go->AddComponent(textureComp);
	}

	auto const moveComponent = new LevelMovementComponent();
	go->AddComponent(moveComponent);

	SDL_Rect colliderRect = { static_cast<int>(0.25 * m_CharSize),static_cast<int>(0.25 * m_CharSize),static_cast<int>(0.75 * m_CharSize), static_cast<int>(0.75 * m_CharSize) };
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
		auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Ugg/Ugg.png", static_cast<float>(m_CharSize), static_cast<float>(m_CharSize));
		go->AddComponent(textureComp);
	}
	else
	{
		auto const textureComp = new peach::TextureComponent("Resources/Images/Enemies/Wrongway/Wrongway.png", static_cast<float>(m_CharSize), static_cast<float>(m_CharSize));
		go->AddComponent(textureComp);
	}

	auto const moveComponent = new LevelMovementComponent();
	go->AddComponent(moveComponent);

	SDL_Rect colliderRect = { static_cast<int>(0.25 * m_CharSize),static_cast<int>(0.25 * m_CharSize),static_cast<int>(0.75 * m_CharSize), static_cast<int>(0.75 * m_CharSize) };
	auto const colliderComponent = new peach::RectColliderComponent(colliderRect);
	go->AddComponent(colliderComponent);


	auto const uggWrongwayComp = new UggWrongwayComponent(isUgg);
	go->AddComponent(uggWrongwayComp);

	GetParent()->AddChild(go);

	return uggWrongwayComp;
}

void Qbert::LevelEnemyManager::SpawnRandomEnemy()
{
	m_amountOfEnemiesSpawned++;

	while (true)
	{
		int random = rand() % 5;
		switch (random)
		{
		case 0:
			if (!m_CoilyComponent->GetParent()->GetIsActive())
			{
				m_CoilyComponent->Spawn();
				return;
			}
			break;
		case 1:
			if (!m_SamComponent->GetParent()->GetIsActive())
			{
				m_SamComponent->Spawn();
				return;
			}
			break;
		case 2:
		{
			if (!m_SlickComponent->GetParent()->GetIsActive())
			{
				m_SlickComponent->Spawn();
				return;
			}
			break;
		}
		case 3:
			if (!m_Ugg->GetParent()->GetIsActive())
			{
				m_Ugg->Spawn();
				return;
			}
			break;
		case 4:
			if (!m_Wrongway->GetParent()->GetIsActive())
			{
				m_Wrongway->Spawn();
				return;
			}
			break;
		}
	}
}
