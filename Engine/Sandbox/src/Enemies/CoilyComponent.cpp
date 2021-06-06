#include "QbertPCH.h"
#include "CoilyComponent.h"
#include "Level/LevelMovementComponent.h"
#include "QbertGameSettings.h"
#include "TextureComponent.h"
#include "Player/QbertComponent.h"
#include "Score/ScoreComponent.h"
#include "CoilyController.h"
#include "ServicesBase.h"

void Qbert::CoilyComponent::Spawn()
{
	GetParent()->SetIsActive(true);
	m_IsEgg = true;
	m_MovementTimer = 0.f;
	m_pMovementComponent->MoveImmediatelyToSpawnPos();
}

void Qbert::CoilyComponent::Remove() const
{
	GetParent()->SetIsActive(false);
}

void Qbert::CoilyComponent::PlayJumpSound()
{
	ServiceLocator::GetSoundSystem()->PlaySoundEffect(static_cast<SoundId>(m_SoundID));
}

void Qbert::CoilyComponent::SetMoveDir(MoveDirection moveDir)
{
	m_MoveDir = moveDir;
}

void Qbert::CoilyComponent::PostInitialize()
{
	//Players are initialized after the level!!
	auto qbertVector = GetParent()->GetScene()->GetObjectsWithTag(QbertGameSettings::qbert_tag);

	m_pQbert = qbertVector[0];

	m_pController = GetParent()->GetComponent<CoilyController>();
}

void Qbert::CoilyComponent::SetAnimTexture()
{
	auto textureDimensions = m_TextureComponent->GetTextureDimensions();

	auto spriteWidth = textureDimensions.w;
	if (m_IsEgg)
	{
		spriteWidth /= 2;
	}
	else
		spriteWidth /= 8;

	SDL_Rect srcRect = { 0,0,spriteWidth,textureDimensions.h };
	if (m_IsEgg)
	{
		if (m_pMovementComponent->GetIsMoving())
			srcRect.x = spriteWidth;
		else
			srcRect.x = 0;
	}
	else
		srcRect.x = (static_cast<int>(m_MoveDir) * 2 + static_cast<int>(m_pMovementComponent->GetIsMoving())) * spriteWidth;


	m_TextureComponent->SetSourceRect(srcRect);
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

	m_pMovementComponent->SetGridSpawnPos(1, QbertGameSettings::level_size - 3);
	m_pMovementComponent->MoveImmediatelyToSpawnPos();

	m_SoundID = ServiceLocator::GetSoundSystem()->AddSound("Resources/Sounds/jump2.wav");
}

void Qbert::CoilyComponent::Update()
{
	SetAnimTexture();
	if (m_pMovementComponent->GetIsMoving())
		return;

	//Check the move Timer
	m_MovementTimer += peach::GameTime::GetInstance().GetElapsedSec();
	if (m_MovementTimer < m_MoveWaitTime)
		return;

	if (m_IsEgg)
	{
		if (m_pMovementComponent->GetGridSpawnPos().y != 1)
		{
			if (rand() % 2 == 0)
				m_MoveDir = MoveDirection::DownLeft;
			else
				m_MoveDir = MoveDirection::DownRight;
		}
		else
		{
			m_IsEgg = false;
			m_TextureComponent->SetTexture("Resources/Images/Enemies/Coily/Snake.png");
			return;
		}
	}
	else
	{
		//Use controller for movement
		if (m_pController)
			return;

		auto const pos = m_pMovementComponent->GetGridPos();
		auto qbertpos = m_pQbert->GetComponent<LevelMovementComponent>()->GetGridPos();
		auto moveDirection = qbertpos - pos;

		if (m_pQbert->GetComponent<QbertComponent>()->GetIsOnDisc())
		{
			qbertpos = m_pQbert->GetComponent<LevelMovementComponent>()->GetGridPosBeforeOnDisk();
			moveDirection = qbertpos - pos;
			if ((moveDirection.x == 0 && abs(moveDirection.y) == 1) ||
				(abs(moveDirection.x) == 1 && moveDirection.y == 0))
			{
				Remove();
				m_pQbert->GetComponent<ScoreComponent>()->IncreaseScore(500);

			}
		}

		if (moveDirection.x != 0)
		{
			if (moveDirection.x > 0)
				m_MoveDir = MoveDirection::DownRight;
			else
				m_MoveDir = MoveDirection::UpLeft;
		}
		else
		{
			if (moveDirection.y > 0)
				m_MoveDir = MoveDirection::UpRight;

			else
				m_MoveDir = MoveDirection::DownLeft;
		}
	}
	PlayJumpSound();
	m_pMovementComponent->Move(m_MoveDir);
	m_MovementTimer = 0.f;
}

void Qbert::CoilyComponent::Render() const
{
}
