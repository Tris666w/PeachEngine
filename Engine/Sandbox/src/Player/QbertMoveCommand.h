#pragma once
#include "Command.h"
#include "Level/LevelMovementComponent.h"

namespace Qbert
{
	class QbertComponent;
	class QbertMoveCommand : public peach::Command
	{
	public:
		QbertMoveCommand(peach::GameObject* pObject, MoveDirection direction);

		void Execute() override;
	private:
		LevelMovementComponent* m_pMovementComponent = nullptr;
		MoveDirection m_MoveDirection;
		QbertComponent* m_pQbertComponent = nullptr;
	};
}
