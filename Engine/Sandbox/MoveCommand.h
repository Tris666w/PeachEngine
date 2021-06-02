#pragma once
#include "Command.h"
#include "Level/LevelMovementComponent.h"

namespace peach
{
	class MoveCommand : public Command
	{
	public:
		MoveCommand(GameObject* pObject, MoveDirection direction);

		void Execute() override;
	private:
		LevelMovementComponent* m_pMovementComponent = nullptr;
		MoveDirection m_MoveDirection;
	};
}
