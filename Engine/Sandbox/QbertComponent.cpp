#include "QbertComponent.h"

#include "QbertGameSettings.h"
#include "Level/LevelComponent.h"
#include "Level/TileComponent.h"

void peach::QbertComponent::Initialize()
{
	m_pLevel = GetParent()->GetScene()->GetObjectsWithTag(QbertGameSettings::level_tag)[0]->GetComponent<LevelComponent>();

}

void peach::QbertComponent::Update()
{
	if (!m_IsMoving)
		return;

	auto targetPos = m_pLevel->GetTile(m_GridPos.x, m_GridPos.y)->GetpTransform()->GetPosition();

	GetParent()->SetPosition(targetPos.x, targetPos.y);

}

void peach::QbertComponent::Move(MoveDirection direction)
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

}
