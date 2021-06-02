#pragma once
#include "ComponentBase.h"
#include "Peach.h"

namespace peach
{
	class LevelComponent;
	enum class MoveDirection
	{
		UpLeft = 0,
		UpRight = 1,
		DownLeft = 2,
		DownRight = 3
	};
	class LevelMovementComponent final : public ComponentBase
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
	private:
		IVector2 m_GridPos = { -1,-1 };
		IVector2 m_GridSpawnPos = { -1,-1 };
		bool m_IsMoving = false;
		LevelComponent* m_pLevel = nullptr;


	};

}
