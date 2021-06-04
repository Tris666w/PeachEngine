#include "QbertPCH.h"
#include "CoilyComponent.h"
#include "Level/LevelMovementComponent.h"
#include "QbertGameSettings.h"
#include "TextureComponent.h"


Qbert::CoilyComponent::CoilyComponent()
	:ComponentBase()
{
}

void Qbert::CoilyComponent::Spawn()
{
	GetParent()->SetIsActive(true);
	m_IsEgg = true;
	m_MovementTimer = 0.f;
	m_pMovementComponent->MoveImmediatlyToSpawnPos();
}

void Qbert::CoilyComponent::Remove() const
{
	GetParent()->SetIsActive(false);
}

void Qbert::CoilyComponent::PostInitialize()
{
	//Players are initialized after the level!!

	auto qbertVector = GetParent()->GetScene()->GetObjectsWithTag(QbertGameSettings::qbert_tag);

	m_pQbert = qbertVector[0];
}

void Qbert::CoilyComponent::Initialize()
{
	GetParent()->SetTag(QbertGameSettings::purple_enemy_tag);
	GetParent()->SetIsActive(false);
	m_pMovementComponent = GetParent()->GetComponent<LevelMovementComponent>();
	m_TextureComponent = GetParent()->GetComponent<peach::TextureComponent>();

	if (!m_TextureComponent || !m_pMovementComponent)
	{
		peach::Logger::LogWarning("CoilyComponent::Initialize(), not texture or movement component!");
	}

	m_pMovementComponent->SetGridSpawnPos(0, QbertGameSettings::level_size - 1);
	m_pMovementComponent->MoveImmediatlyToSpawnPos();

}

void Qbert::CoilyComponent::Update()
{
	if (m_pMovementComponent->GetIsMoving())
		return;

	//Check the move Timer
	m_MovementTimer += peach::GameTime::GetInstance().GetElapsedSec();
	if (m_MovementTimer < m_MoveWaitTime)
		return;

	if (m_IsEgg)
	{
		if (m_pMovementComponent->GetGridSpawnPos().y != 0)
		{
			if (rand() % 2 == 0)
				m_pMovementComponent->Move(MoveDirection::DownLeft);
			else
				m_pMovementComponent->Move(MoveDirection::DownRight);
		}
		else
		{
			m_IsEgg = false;
			m_TextureComponent->SetTexture("Resources/Images/Enemies/Coily/Snake.png");
		}
	}
	else
	{
		auto const pos = m_pMovementComponent->GetGridPos();
		auto const qbertpos = m_pQbert->GetComponent<LevelMovementComponent>()->GetGridPos();
		auto const moveDirection = qbertpos - pos;

		if (moveDirection.x != 0)
		{
			if (moveDirection.x > 0)
				m_pMovementComponent->Move(MoveDirection::DownRight);
			else
				m_pMovementComponent->Move(MoveDirection::UpLeft);
		}
		else
		{
			if (moveDirection.y > 0)
				m_pMovementComponent->Move(MoveDirection::UpRight);

			else
				m_pMovementComponent->Move(MoveDirection::DownLeft);
		}
	}
	m_MovementTimer = 0.f;
}
