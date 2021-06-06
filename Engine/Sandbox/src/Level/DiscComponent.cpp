#include "QbertPCH.h"
#include "DiscComponent.h"

#include "LevelMovementComponent.h"
#include "QbertGameSettings.h"
#include "TextureComponent.h"

void Qbert::DiscComponent::Initialize()
{
    GetParent()->SetTag(Qbert::QbertGameSettings::disc_tag);

    m_pTextureComponent = GetParent()->GetComponent<peach::TextureComponent>();
    m_pLevelMovementComponent = GetParent()->GetComponent<LevelMovementComponent>();

    m_ActivationTime = m_pLevelMovementComponent->GetMoveWaitTime();
}

void Qbert::DiscComponent::Update()
{
    if (m_StartedMoving && !m_pLevelMovementComponent->GetIsMoving())
    {
        m_pLevelMovementComponent->SetGridPos(-100, 0);
        m_pTransportingQbert->GetComponent<LevelMovementComponent>()->MoveImmediatelyToTopCube();

        GetParent()->SetIsActive(false);
    }
    m_AnimTimer += peach::GameTime::GetInstance().GetElapsedSec();
    if (m_AnimTimer > m_AnimWait)
    {
        m_AnimTimer = 0.f;

        m_CurrentSprite++;
        if (m_CurrentSprite >= m_AmountOfSprites)
            m_CurrentSprite = 0;


        auto const textureDimensions = m_pTextureComponent->GetTextureDimensions();
        auto const spriteWidth = textureDimensions.w / m_AmountOfSprites;

        SDL_Rect srcRect = { m_CurrentSprite * spriteWidth,0,spriteWidth,textureDimensions.h };

        m_pTextureComponent->SetSourceRect(srcRect);
    }

    if (!m_IsActive)
        return;

    m_ActivationTimer += peach::GameTime::GetInstance().GetElapsedSec();
    if (m_ActivationTimer > m_ActivationTime)
    {
        m_pTransportingQbert->GetComponent<LevelMovementComponent>()->MoveToTop();
        m_pLevelMovementComponent->MoveToTop();
        m_ActivationTimer = 0.f;
        m_StartedMoving = true;
    }
}

void Qbert::DiscComponent::Render() const
{
}

void Qbert::DiscComponent::Activate(peach::GameObject* pQbert)
{
    m_IsActive = true;
    m_pTransportingQbert = pQbert;
}

void Qbert::DiscComponent::Deactivate()
{
    GetParent()->SetIsActive(false);
}
