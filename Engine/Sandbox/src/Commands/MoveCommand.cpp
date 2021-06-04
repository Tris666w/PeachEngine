#include "QbertPCH.h"
#include "MoveCommand.h"
#include "GameObject.h"
#include "Level/LevelMovementComponent.h"

Qbert::MoveCommand::MoveCommand(peach::GameObject* pObject, MoveDirection direction)
	:Command(),
	m_MoveDirection(direction)
{
	m_pMovementComponent = pObject->GetComponent<LevelMovementComponent>();
	if (!m_pMovementComponent)
		peach::Logger::LogWarning("MoveCommand::MoveCommand, given game object has no level movement component");
}

void Qbert::MoveCommand::Execute()
{
	if (m_pMovementComponent)
	{
		m_pMovementComponent->Move(m_MoveDirection);
	}
	else
		peach::Logger::LogWarning("MoveCommand::Execute, m_pMovementComponent is nullptr");
}
