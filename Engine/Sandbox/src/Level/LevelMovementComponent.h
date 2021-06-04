#pragma once
#include "ComponentBase.h"
#include "Peach.h"

namespace Qbert
{
	class LevelComponent;
	enum class MoveDirection
	{
		UpLeft = 0,
		UpRight = 1,
		DownLeft = 2,
		DownRight = 3
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

		void Move(MoveDirection direction);
		void SetGridSpawnPos(int col, int row);
		glm::vec3 GetGridSpawnPos()const { return m_GridPos; }

		void MoveImmediatlyToSpawnPos();


		bool GetIsMoving()const { return m_IsMoving; }
		glm::vec3 GetGridPos()const { return m_GridPos; }

	private:
		glm::vec3 m_GridPos = { -1,-1,0 };
		glm::vec3 m_GridSpawnPos = { -1,-1,0 };
		bool m_IsMoving = false;
		LevelComponent* m_pLevel = nullptr;
		glm::vec3 m_TargetPos{};

		float const m_MoveTime = 0.5f;
		float m_MoveTimer = 0.f;
	};

}
