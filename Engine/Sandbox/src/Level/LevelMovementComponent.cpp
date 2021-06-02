#include "QbertPCH.h"

#include "LevelMovementComponent.h"
#include "GameObject.h"
#include "QbertGameSettings.h"
#include "LevelComponent.h"

void peach::LevelMovementComponent::Initialize()
{
	m_pLevel = GetParent()->GetScene()->GetObjectsWithTag(QbertGameSettings::level_tag)[0]->GetComponent<LevelComponent>();
}

void peach::LevelMovementComponent::Update()
{
	if (!m_IsMoving)
		return;

	m_IsMoving = false;

	auto targetTile = m_pLevel->GetTile(m_GridPos.x, m_GridPos.y);
	if (targetTile == nullptr)
	{
		m_GridPos = m_GridSpawnPos;
		targetTile = m_pLevel->GetTile(m_GridPos.x, m_GridPos.y);
	}

	auto& targetPos = targetTile->GetpTransform()->GetPosition();
	GetParent()->SetPosition(targetPos.x, targetPos.y);
}

void peach::LevelMovementComponent::Move(MoveDirection direction)
{
	switch (direction)
	{
	case MoveDirection::UpLeft:
		++m_GridPos.y;
		--m_GridPos.x;
		break;
	case MoveDirection::DownRight:
		--m_GridPos.y;
		++m_GridPos.x;
		break;
	case MoveDirection::UpRight:
		++m_GridPos.y;;
		break;
	case MoveDirection::DownLeft:
		--m_GridPos.y;
		break;
	}

	m_IsMoving = true;
}

void peach::LevelMovementComponent::SetGridSpawnPos(int col, int row)
{
	m_GridSpawnPos = { col,row };
	m_GridPos = { col, row };
}
