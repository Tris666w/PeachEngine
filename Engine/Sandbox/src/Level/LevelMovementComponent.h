#pragma once
#include "ComponentBase.h"
#include "DiscComponent.h"
#include "Peach.h"

namespace Qbert
{
    class LevelComponent;
    enum class MoveDirection
    {
        UpRight = 0,
        UpLeft = 1,
        DownRight = 2,
        DownLeft = 3,
        Right = 4,
        Left = 5
    };
    enum class TilePosition
    {
        Top = 0,
        Left = 1,
        Right = 2
    };
    class LevelMovementComponent final : public peach::ComponentBase
    {
    public:
        LevelMovementComponent() = default;
        LevelMovementComponent(const LevelMovementComponent& other) = delete;
        LevelMovementComponent(LevelMovementComponent&& other) noexcept = delete;
        LevelMovementComponent& operator=(const LevelMovementComponent& other) = delete;
        LevelMovementComponent& operator=(LevelMovementComponent&& other) noexcept = delete;

        void Initialize() override;
        void Update() override;
        void Render() const override;

        void Move(MoveDirection direction);
        void SetGridSpawnPos(int col, int row);
        glm::vec3 GetGridSpawnPos()const { return m_GridPos; }

        void MoveImmediatelyToSpawnPos();
        void SetTilePosition(TilePosition pos);
        void SetWaitTime(float waitTime) { m_WaitTime = waitTime; }
        bool GetIsMoving()const { return m_IsMoving; }
        glm::vec3 GetGridPos()const { return m_GridPos; }
        void MoveToTop();
        float GetMoveWaitTime() { return m_MoveTime; }
        void SetGridPos(int i, int i1);
        void MoveImmediatelyToTopCube();

    private:
        glm::vec3 m_GridPos = { -1,-1,0 };
        glm::vec3 m_GridSpawnPos = { -1,-1,0 };
        bool m_IsMoving = false;

        LevelComponent* m_pLevel = nullptr;
        glm::vec3 m_TargetPos{};

        float const m_MoveTime = 0.5f;
        float m_MoveTimer = 0.f;

        float m_WaitTime = -1.f;
        float m_WaitTimer = 0.f;

        TilePosition m_TilePosition = TilePosition::Top;
        float const m_TileOffset = 16;

        void ResetTargetTile(peach::GameObject** pTargetTile);
    };

}
