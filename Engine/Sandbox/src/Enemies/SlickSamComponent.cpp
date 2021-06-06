#include "QbertPCH.h"
#include "SlickSamComponent.h"
#include "Level/LevelMovementComponent.h"
#include "QbertGameSettings.h"
#include "TextureComponent.h"

Qbert::SlickSamComponent::SlickSamComponent(bool isSlick)
	:ComponentBase(),
	m_IsSlick(isSlick)
{
}

void Qbert::SlickSamComponent::Initialize()
{
	GetParent()->SetTag(QbertGameSettings::green_enemy_tag);
	GetParent()->SetIsActive(false);
	m_pMovementComponent = GetParent()->GetComponent<LevelMovementComponent>();
	m_TextureComponent = GetParent()->GetComponent<peach::TextureComponent>();

	if (!m_TextureComponent || !m_pMovementComponent)
	{
		peach::Logger::LogWarning("CoilyComponent::Initialize(), not texture or movement component!");
	}

	m_pMovementComponent->SetGridSpawnPos(0, QbertGameSettings::level_size - 1);
	m_pMovementComponent->MoveImmediatelyToSpawnPos();
}

void Qbert::SlickSamComponent::Update()
{
	if (m_pMovementComponent->GetIsMoving())
		return;

	SetAnimTexture();
	//Check the move Timer
	m_MovementTimer += peach::GameTime::GetInstance().GetElapsedSec();
	if (m_MovementTimer < m_MoveWaitTime)
		return;

	if (rand() % 2 == 0)
		m_MoveDir = MoveDirection::DownLeft;
	else
		m_MoveDir = MoveDirection::DownRight;

	m_pMovementComponent->Move(m_MoveDir);
	m_MovementTimer = 0.f;

	SetAnimTexture();
}

void Qbert::SlickSamComponent::Render() const
{
}

void Qbert::SlickSamComponent::Spawn()
{
	GetParent()->SetIsActive(true);
	m_MovementTimer = 0.f;
	m_pMovementComponent->MoveImmediatelyToSpawnPos();
}

void Qbert::SlickSamComponent::Remove() const
{
	GetParent()->SetIsActive(false);

}

void Qbert::SlickSamComponent::SetAnimTexture()
{
	auto textureDimensions = m_TextureComponent->GetTextureDimensions();
	auto spriteWidth = textureDimensions.w / 4;

	SDL_Rect srcRect = { 0,0,spriteWidth,textureDimensions.h };
	if (m_MoveDir == MoveDirection::DownLeft)
		srcRect.x = static_cast<int>(m_pMovementComponent->GetIsMoving()) * spriteWidth;
	else
		srcRect.x = (static_cast<int>(m_pMovementComponent->GetIsMoving()) + 2) * spriteWidth;



	m_TextureComponent->SetSourceRect(srcRect);

}
