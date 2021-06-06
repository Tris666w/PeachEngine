#include "QbertPCH.h"
#include "CoilyMoveCommand.h"

#include "CoilyComponent.h"
#include "Level/LevelMovementComponent.h"

Qbert::CoilyMoveCommand::CoilyMoveCommand(peach::GameObject* pObject, MoveDirection direction)
	:Command(),
	m_MoveDirection(direction)
{
	m_pMovementComponent = pObject->GetComponent<LevelMovementComponent>();
	if (!m_pMovementComponent)
		peach::Logger::LogWarning("CoilyMoveCommand::CoilyMoveCommand, given game object has no level movement component");

	m_pCoilyComponent = pObject->GetComponent<CoilyComponent>();
	if (!m_pMovementComponent)
		peach::Logger::LogWarning("CoilyMoveCommand::CoilyMoveCommand, given game object has no coily component");
}


void Qbert::CoilyMoveCommand::Execute()
{
	if (!m_pCoilyComponent || !m_pMovementComponent)
	{
		peach::Logger::LogWarning("CoilyMoveCommand::Execute, one of the components is nullptr");
		return;
	}
	if (!m_pCoilyComponent->GetIsEgg() && m_pCoilyComponent->GetParent()->GetIsActive())
	{
		m_pMovementComponent->Move(m_MoveDirection);
		m_pCoilyComponent->SetMoveDir(m_MoveDirection);
		m_pCoilyComponent->PlayJumpSound();
	}
}
