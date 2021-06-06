#include "QbertPCH.h"

#include "LevelMovementComponent.h"

#include "DiscComponent.h"
#include "GameObject.h"
#include "QbertGameSettings.h"
#include "LevelComponent.h"
#include "TileComponent.h"
#include "Health/Health.h"
#include "Player/QbertComponent.h"

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

void Qbert::LevelMovementComponent::Render() const
{
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
    case MoveDirection::Right:
        ++m_GridPos.x;
        break;
    case MoveDirection::Left:
        --m_GridPos.x;
        break;

    }

    m_IsMoving = true;

    auto targetTile = m_pLevel->GetTile(static_cast<uint32_t>(m_GridPos.x), static_cast<uint32_t>(m_GridPos.y));
    if (targetTile == nullptr)
        ResetTargetTile(&targetTile);
    else if (strcmp(GetParent()->GetTag().c_str(), QbertGameSettings::qbert_tag.c_str()) == 0)
    {
        bool onDisk = false;
        auto discVector = m_pLevel->GetDiscs();
        for (auto disc : discVector)
        {
            auto moveComp = disc->GetComponent<LevelMovementComponent>();
            if (moveComp->GetGridPos() == m_GridPos)
            {
                onDisk = true;
                disc->GetComponent<DiscComponent>()->Activate(GetParent());
                break;
            }
        }
        if (!onDisk && (m_GridPos.x == 0 || m_GridPos.y == 0 || m_GridPos.x == QbertGameSettings::level_size - m_GridPos.y - 1))
            ResetTargetTile(&targetTile);
    }
    else if (strcmp(GetParent()->GetTag().c_str(), QbertGameSettings::disc_tag.c_str()) != 0 &&
        (m_GridPos.x == 0 || m_GridPos.y == 0 || m_GridPos.x == QbertGameSettings::level_size - m_GridPos.y - 1))
    {
        ResetTargetTile(&targetTile);
    }

    switch (m_TilePosition)
    {
    case TilePosition::Top:
        m_TargetPos = { targetTile->GetpTransform()->GetPosition().x + m_TileOffset, targetTile->GetpTransform()->GetPosition().y  ,0 };
        break;
    case TilePosition::Left:
        m_TargetPos = { targetTile->GetpTransform()->GetPosition().x , targetTile->GetpTransform()->GetPosition().y + 1.5f * m_TileOffset  ,0 };
        break;
    case TilePosition::Right:
        m_TargetPos = { targetTile->GetpTransform()->GetPosition().x + 2 * m_TileOffset, targetTile->GetpTransform()->GetPosition().y + 1.5f * m_TileOffset ,0 };
        break;
    }

    if (strcmp(GetParent()->GetTag().c_str(), QbertGameSettings::qbert_tag.c_str()) == 0)
    {
        auto tileComp = targetTile->GetComponent<TileComponent>();
        tileComp->QbertStepOn(GetParent());
    }
    else if (strcmp(GetParent()->GetTag().c_str(), QbertGameSettings::green_enemy_tag.c_str()) == 0)
    {
        auto tileComp = targetTile->GetComponent<TileComponent>();
        tileComp->GreenStepOn();
    }
}

void Qbert::LevelMovementComponent::SetGridSpawnPos(int col, int row)
{
    m_GridSpawnPos = { col,row ,0 };
    m_GridPos = { col, row ,0 };
}

void Qbert::LevelMovementComponent::MoveImmediatelyToSpawnPos()
{
    m_GridPos = m_GridSpawnPos;
    auto targetTile = m_pLevel->GetTile(static_cast<uint32_t>(m_GridSpawnPos.x), static_cast<uint32_t>(m_GridSpawnPos.y));

    switch (m_TilePosition)
    {
    case TilePosition::Top:
        m_TargetPos = { targetTile->GetpTransform()->GetPosition().x + m_TileOffset, targetTile->GetpTransform()->GetPosition().y  ,0 };
        break;
    case TilePosition::Left:
        m_TargetPos = { targetTile->GetpTransform()->GetPosition().x , targetTile->GetpTransform()->GetPosition().y + 1.5f * m_TileOffset  ,0 };
        break;
    case TilePosition::Right:
        m_TargetPos = { targetTile->GetpTransform()->GetPosition().x + 2 * m_TileOffset, targetTile->GetpTransform()->GetPosition().y + 1.5f * m_TileOffset ,0 };
        break;

    }
    GetParent()->SetPosition(m_TargetPos.x, m_TargetPos.y);
}

void Qbert::LevelMovementComponent::SetTilePosition(TilePosition pos)
{
    m_TilePosition = pos;
}

void Qbert::LevelMovementComponent::MoveToTop()
{
    int col = {};
    if (m_GridPos.x == 0)
        col = 0;
    else
        col = 1;

    m_TargetPos = m_pLevel->GetCubeTilePos(col, QbertGameSettings::level_size - 2);

    m_IsMoving = true;
    m_GridPos = { col,QbertGameSettings::level_size - 2 ,0 };
}

void Qbert::LevelMovementComponent::SetGridPos(int i, int i1)
{
    m_GridPos = { i,i1 ,0 };
}

void Qbert::LevelMovementComponent::MoveImmediatelyToTopCube()
{
    m_GridPos = { 1,QbertGameSettings::level_size - 3 ,0 };
    m_IsMoving = false;

    auto targetTilePos = m_pLevel->GetTopCubeTilePos();

    switch (m_TilePosition)
    {
    case TilePosition::Top:
        m_TargetPos = { targetTilePos.x + m_TileOffset, targetTilePos.y  ,0 };
        break;
    case TilePosition::Left:
        m_TargetPos = { targetTilePos.x , targetTilePos.y + 1.5f * m_TileOffset  ,0 };
        break;
    case TilePosition::Right:
        m_TargetPos = { targetTilePos.x + 2 * m_TileOffset, targetTilePos.y + 1.5f * m_TileOffset ,0 };
        break;

    }
    GetParent()->SetPosition(m_TargetPos.x, m_TargetPos.y);

}

void Qbert::LevelMovementComponent::ResetTargetTile(peach::GameObject** pTargetTile)
{
    m_GridPos = m_GridSpawnPos;
    *pTargetTile = m_pLevel->GetTile(static_cast<uint32_t>(m_GridPos.x), static_cast<uint32_t>(m_GridPos.y));

    if (strcmp(GetParent()->GetTag().c_str(), QbertGameSettings::qbert_tag.c_str()) == 0)
    {
        auto health = GetParent()->GetComponent<Health>();
        health->DoDamage(1);
    }
}
