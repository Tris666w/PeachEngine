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
	class QbertComponent final : public ComponentBase
	{
	public:
		QbertComponent() = default;
		QbertComponent(const QbertComponent& other) = delete;
		QbertComponent(QbertComponent&& other) noexcept = delete;
		QbertComponent& operator=(const QbertComponent& other) = delete;
		QbertComponent& operator=(QbertComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;

	private:
		IVector2 m_GridPos = { -1,-1 };
		bool m_IsMoving = false;
		LevelComponent* m_pLevel;


		void Move(MoveDirection direction);
	};

}

