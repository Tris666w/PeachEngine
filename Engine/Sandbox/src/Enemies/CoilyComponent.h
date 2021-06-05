#pragma once
#include "ComponentBase.h"

namespace peach
{
    class TextureComponent;
    class GameObject;
}
namespace Qbert
{
    enum class MoveDirection;
    class LevelMovementComponent;
    class CoilyComponent final :public peach::ComponentBase
    {
    public:
        CoilyComponent();
        ~CoilyComponent() override = default;

        void Initialize() override;
        void PostInitialize() override;
        void Update() override;
        void Render() const override;

        void Spawn();
        void Remove() const;
    private:
        LevelMovementComponent* m_pMovementComponent = nullptr;
        peach::TextureComponent* m_TextureComponent = nullptr;
        peach::GameObject* m_pQbert = nullptr;

        float m_MovementTimer = 0.f;
        float const m_MoveWaitTime = 0.75f;

        bool m_IsEgg = true;
        MoveDirection m_MoveDir;

        void SetAnimTexture();
    };
}
