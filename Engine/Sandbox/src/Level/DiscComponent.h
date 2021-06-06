#pragma once
#include "ComponentBase.h"

namespace peach
{
    class TextureComponent;
}

namespace Qbert
{
    class LevelMovementComponent;

    class DiscComponent final :public peach::ComponentBase
    {
    public:

        void Initialize() override;
        void Update() override;
        void Render() const override;

        void Activate(peach::GameObject* pQbert);
        void Deactivate();
    private:
        peach::TextureComponent* m_pTextureComponent = nullptr;
        LevelMovementComponent* m_pLevelMovementComponent = nullptr;
        peach::GameObject* m_pTransportingQbert = nullptr;
        int m_CurrentSprite = 0;
        float m_AnimTimer = 0.f;
        float const m_AnimWait = 0.25f;
        int const m_AmountOfSprites = 4;

        float m_ActivationTimer = 0.f;
        float m_ActivationTime = 0.f;
        bool m_IsActive = false;
        bool m_StartedMoving = false;
    };
}