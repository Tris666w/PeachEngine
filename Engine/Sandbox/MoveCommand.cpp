#include "QbertPCH.h"
#include "MoveCommand.h"
#include "GameObject.h"
#include "Level/LevelMovementComponent.h"

peach::MoveCommand::MoveCommand(GameObject* pObject, MoveDirection direction)
	:Command(),
	m_MoveDirection(direction)
{
	m_pMovementComponent = pObject->GetComponent<LevelMovementComponent>();
	if (!m_pMovementComponent)
		Logger::LogWarning("MoveCommand::MoveCommand, given game object has no level movement component");
}

void peach::MoveCommand::Execute()
{
	if (m_pMovementComponent)
	{
		m_pMovementComponent->Move(m_MoveDirection);
	}
	else
		Logger::LogWarning("MoveCommand::Execute, m_pMovementComponent is nullptr");
}
