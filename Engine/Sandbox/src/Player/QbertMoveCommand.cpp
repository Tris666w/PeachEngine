#include "QbertPCH.h"
#include "QbertMoveCommand.h"
#include "GameObject.h"
#include "Level/LevelMovementComponent.h"
#include "QbertComponent.h"

Qbert::QbertMoveCommand::QbertMoveCommand(peach::GameObject* pObject, MoveDirection direction)
	:Command(),
	m_MoveDirection(direction)
{
	m_pMovementComponent = pObject->GetComponent<LevelMovementComponent>();
	m_pQbertComponent = pObject->GetComponent<QbertComponent>();

	if (!m_pMovementComponent || !m_pQbertComponent)
		peach::Logger::LogWarning("MoveCommand::MoveCommand, one of the components was nullptr!");
}

void Qbert::QbertMoveCommand::Execute()
{
	if (m_pMovementComponent->GetParent()->GetIsActive())
	{
		m_pMovementComponent->Move(m_MoveDirection);
		m_pQbertComponent->SetMoveDir(m_MoveDirection);
		m_pQbertComponent->PlayJumpSound();
	}
}
