#include "QbertPCH.h"

#include "QbertComponent.h"
#include "QbertGameSettings.h"
#include "TextureComponent.h"
#include "Health/HealthObserver.h"
#include "Level/LevelComponent.h"
#include "Level/LevelMovementComponent.h"
#include "SoundSystems.h"

Qbert::QbertComponent::QbertComponent(peach::Subject* pHealthSubject)
{
	m_pHealthObserver = std::make_unique<HealthObserver>(&m_IsDead, pHealthSubject);

}

void Qbert::QbertComponent::Initialize()
{
	GetParent()->SetTag(QbertGameSettings::qbert_tag);

	m_pMovementComponent = GetParent()->GetComponent<LevelMovementComponent>();
	m_TextureComponent = GetParent()->GetComponent<peach::TextureComponent>();

	if (!m_TextureComponent || !m_pMovementComponent)
	{
		peach::Logger::LogWarning("CoilyComponent::Initialize(), not texture or movement component!");
	}

	m_SoundID = ServiceLocator::GetSoundSystem()->AddSound("Resources/Sounds/Qbert/jump1.wav");


}


void Qbert::QbertComponent::UpdateAnimTexture()
{
	auto const textureDimensions = m_TextureComponent->GetTextureDimensions();
	auto const spriteWidth = textureDimensions.w / 8;

	SDL_Rect srcRect = { 0,0,spriteWidth,textureDimensions.h };

	srcRect.x = (static_cast<int>(m_MoveDir) * 2 + static_cast<int>(m_pMovementComponent->GetIsMoving())) * spriteWidth;
	m_TextureComponent->SetSourceRect(srcRect);

}

void Qbert::QbertComponent::PlayJumpSound()
{
	ServiceLocator::GetSoundSystem()->PlaySoundEffect(static_cast<MusicId>(m_SoundID));
}

void Qbert::QbertComponent::PostInitialize()
{
	auto level = GetParent()->GetScene()->GetObjectsWithTag(QbertGameSettings::level_tag);

	m_pLevel = level[0]->GetComponent<LevelComponent>();
	if (!m_pLevel)
		peach::Logger::LogWarning("Qbert::QbertComponent::Initialize(), m_pLevel is nullptr");
}

void Qbert::QbertComponent::SetMoveDir(MoveDirection moveDirection)
{
	m_MoveDir = moveDirection;
}

void Qbert::QbertComponent::Update()
{
	if (m_IsDead)
	{
		GetParent()->SetIsActive(false);
		m_pLevel->CheckForEnd();
	}
	UpdateAnimTexture();
}

void Qbert::QbertComponent::Render() const
{
}

