#include "QbertPCH.h"
#include "UggWrongwayComponent.h"

#include "QbertGameSettings.h"
#include "Level/LevelMovementComponent.h"
#include "TextureComponent.h"

Qbert::UggWrongwayComponent::UggWrongwayComponent(bool isUgg)
	:ComponentBase(),
	m_IsUgg(isUgg),
	m_MoveDir()
{
}

void Qbert::UggWrongwayComponent::Initialize()
{
	GetParent()->SetTag(QbertGameSettings::purple_enemy_tag);
	GetParent()->SetIsActive(false);
	m_pMovementComponent = GetParent()->GetComponent<LevelMovementComponent>();
	m_TextureComponent = GetParent()->GetComponent<peach::TextureComponent>();

	if (!m_TextureComponent || !m_pMovementComponent)
	{
		peach::Logger::LogWarning("CoilyComponent::Initialize(), not texture or movement component!");
	}
	if (m_IsUgg)
	{
		m_pMovementComponent->SetGridSpawnPos(0, 0);
		m_pMovementComponent->SetTilePosition(TilePosition::Right);

	}
	else
	{
		m_pMovementComponent->SetGridSpawnPos(QbertGameSettings::level_size - 1, 0);
		m_pMovementComponent->SetTilePosition(TilePosition::Left);
	}


	m_pMovementComponent->MoveImmediatelyToSpawnPos();
}

void Qbert::UggWrongwayComponent::Update()
{
	if (m_pMovementComponent->GetIsMoving())
		return;

	SetAnimTexture();
	//Check the move Timer
	m_MovementTimer += peach::GameTime::GetInstance().GetElapsedSec();
	if (m_MovementTimer < m_MoveWaitTime)
		return;


	if (rand() % 2 == 0)
	{
		if (m_IsUgg)
			m_MoveDir = MoveDirection::Right;
		else
			m_MoveDir = MoveDirection::Left;

	}
	else
	{
		if (m_IsUgg)
			m_MoveDir = MoveDirection::UpRight;
		else
			m_MoveDir = MoveDirection::UpLeft;
	}


	m_pMovementComponent->Move(m_MoveDir);
	m_MovementTimer = 0.f;

	SetAnimTexture();
}

void Qbert::UggWrongwayComponent::Render() const
{
}

void Qbert::UggWrongwayComponent::Spawn()
{
	GetParent()->SetIsActive(true);
	m_MovementTimer = 0.f;
	m_pMovementComponent->MoveImmediatelyToSpawnPos();
}

void Qbert::UggWrongwayComponent::Remove() const
{
	GetParent()->SetIsActive(false);
}

void Qbert::UggWrongwayComponent::SetAnimTexture()
{
	auto textureDimensions = m_TextureComponent->GetTextureDimensions();
	auto spriteWidth = textureDimensions.w / 4;

	SDL_Rect srcRect = { 0,0,spriteWidth,textureDimensions.h };


	m_TextureComponent->SetSourceRect(srcRect);
}
