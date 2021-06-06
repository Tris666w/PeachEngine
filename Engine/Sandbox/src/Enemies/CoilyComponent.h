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
    class CoilyController;

    class CoilyComponent final :public peach::ComponentBase
    {
    public:
        ~CoilyComponent() override = default;

        void Initialize() override;
        void PostInitialize() override;
        void Update() override;
        void Render() const override;

        void Spawn();
        void Remove() const;

        void PlayJumpSound();

        void SetMoveDir(MoveDirection moveDir);
        bool GetIsEgg()const { return m_IsEgg; }
    private:
        LevelMovementComponent* m_pMovementComponent = nullptr;
        peach::TextureComponent* m_TextureComponent = nullptr;
        peach::GameObject* m_pQbert = nullptr;
        CoilyController* m_pController = nullptr;

        float m_MovementTimer = 0.f;
        float const m_MoveWaitTime = 0.75f;

        int m_SoundID = 0;

        bool m_IsEgg = true;
        MoveDirection m_MoveDir;

        void SetAnimTexture();
    };
}
