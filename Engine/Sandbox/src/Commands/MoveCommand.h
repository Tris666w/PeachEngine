#pragma once
#include "Command.h"
#include "Level/LevelMovementComponent.h"

namespace Qbert
{
	class MoveCommand : public peach::Command
	{
	public:
		MoveCommand(peach::GameObject* pObject, MoveDirection direction);

		void Execute() override;
	private:
		LevelMovementComponent* m_pMovementComponent = nullptr;
		MoveDirection m_MoveDirection;
	};
}
