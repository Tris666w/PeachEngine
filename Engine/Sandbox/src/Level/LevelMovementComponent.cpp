#include "QbertPCH.h"

#include "LevelMovementComponent.h"
#include "GameObject.h"
#include "QbertGameSettings.h"
#include "LevelComponent.h"
#include "TileComponent.h"

void Qbert::LevelMovementComponent::Initialize()
{
	m_pLevel = GetParent()->GetScene()->GetObjectsWithTag(QbertGameSettings::level_tag)[0]->GetComponent<LevelComponent>();
}

void Qbert::LevelMovementComponent::Update()
{
	if (!m_IsMoving)
		return;

	m_MoveTimer += peach::GameTime::GetInstance().GetElapsedSec();

	if (m_MoveTimer < m_MoveTime)
	{
		glm::vec3 pos = { GetParent()->GetpTransform()->GetPosition().x, GetParent()->GetpTransform()->GetPosition().y,0 };
		auto const newPos = Interpolate(pos, m_TargetPos, m_MoveTimer / m_MoveTime);

		GetParent()->SetPosition(newPos.x, newPos.y);
	}
	else
	{
		m_MoveTimer = 0.f;
		m_IsMoving = false;
		GetParent()->SetPosition(m_TargetPos.x, m_TargetPos.y);

	}
}

void Qbert::LevelMovementComponent::Move(MoveDirection direction)
{
	if (m_IsMoving)
		return;

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

	auto targetTile = m_pLevel->GetTile(static_cast<uint32_t>(m_GridPos.x), static_cast<uint32_t>(m_GridPos.y));
	if (targetTile == nullptr)
	{
		m_GridPos = m_GridSpawnPos;
		targetTile = m_pLevel->GetTile(static_cast<uint32_t>(m_GridPos.x), static_cast<uint32_t>(m_GridPos.y));
	}

	//TODO: Add Tile Offset as constant
	int const offset = 16;
	m_TargetPos = { targetTile->GetpTransform()->GetPosition().x + offset, targetTile->GetpTransform()->GetPosition().y ,0 };
	if (strcmp(GetParent()->GetTag().c_str(), QbertGameSettings::qbert_tag.c_str()) == 0)
	{
		auto tileComp = targetTile->GetComponent<TileComponent>();
		tileComp->QbertStepOn();
	}
}

void Qbert::LevelMovementComponent::SetGridSpawnPos(int col, int row)
{
	m_GridSpawnPos = { col,row ,0 };
	m_GridPos = { col, row ,0 };
}

void Qbert::LevelMovementComponent::MoveImmediatlyToSpawnPos()
{
	auto targetTile = m_pLevel->GetTile(static_cast<uint32_t>(m_GridPos.x), static_cast<uint32_t>(m_GridPos.y));
	m_TargetPos = { targetTile->GetpTransform()->GetPosition().x, targetTile->GetpTransform()->GetPosition().y, 0 };

	GetParent()->SetPosition(m_TargetPos.x, m_TargetPos.y);
}
