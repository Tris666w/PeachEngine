#pragma once
#include "Command.h"

namespace Qbert
{
	class CoilyComponent;
	class LevelMovementComponent;
	enum class MoveDirection;

	class CoilyMoveCommand final:public peach::Command
    {
	public:
		CoilyMoveCommand(peach::GameObject* pObject, MoveDirection direction);
		void Execute() override;
		
	private:
		LevelMovementComponent* m_pMovementComponent = nullptr;
		MoveDirection m_MoveDirection;
		CoilyComponent* m_pCoilyComponent = nullptr;
    };
}