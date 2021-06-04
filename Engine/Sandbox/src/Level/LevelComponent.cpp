#include "QbertPCH.h"
#include "LevelComponent.h"

#include "GameObject.h"
#include "TileComponent.h"
#include "TextureComponent.h"
#include "QbertGameSettings.h"
#include "LevelMovementComponent.h"

void Qbert::LevelComponent::Initialize()
{
	std::vector<std::string> textureVect = {};
	textureVect.push_back("Resources/Images/Level1/L1InactiveTile.png");
	textureVect.push_back("Resources/Images/Level1/L1ActiveTile.png");

	auto pos = glm::vec3{ 0,0,0 };

	for (int row = 0; row < QbertGameSettings::level_size; ++row)
	{
		std::vector<TileComponent*> pTiles{};
		for (int col = 0; col < QbertGameSettings::level_size - row; ++col)
		{
			auto go = new peach::GameObject();
			auto const tileComp = new TileComponent(textureVect, this, false);
			auto const textureComp = new peach::TextureComponent(textureVect[0], block_size, block_size);

			go->AddComponent(tileComp);
			go->AddComponent(textureComp);

			GetParent()->AddChild(go);
			go->SetPosition(pos.x + col * block_size, pos.y);
			pTiles.push_back(tileComp);
		}
		pos.x += block_size / 2.f;
		pos.y -= block_size * 0.75f;

		m_pTiles.insert({ row,pTiles });
	}

	GetParent()->SetTag(QbertGameSettings::level_tag);
}

void Qbert::LevelComponent::PostInitialize()
{
	auto scene = GetParent()->GetScene();
	auto qbertGameObjects = scene->GetObjectsWithTag(QbertGameSettings::qbert_tag);
	auto const amountOfPlayers = QbertGameSettings::GetInstance().GetAmountOfPlayers();

	if (amountOfPlayers != qbertGameObjects.size())
		peach::Logger::LogWarning("LevelComponent::PostInitialize(), amount of players in the scene != amount of players in the game");

	auto moveComp = qbertGameObjects[0]->GetComponent<LevelMovementComponent>();
	auto player = qbertGameObjects[0];
	switch (amountOfPlayers)
	{
	case 1:
		player->SetPosition(GetTopCubeTilePos().x, GetTopCubeTilePos().y);
		if (moveComp)
			moveComp->SetGridSpawnPos(0, QbertGameSettings::level_size - 1);
		else
			peach::Logger::LogInfo("LevelComponent::PostInitialize(), no LevelMovementComponent was found");

		break;
	case 2:
		qbertGameObjects[0]->SetPosition(GetBottomLeftCubeTilePos().x, GetBottomLeftCubeTilePos().y);
		qbertGameObjects[1]->SetPosition(GetBottomRightCubeTilePos().x, GetBottomRightCubeTilePos().y);
		break;
	default:
		peach::Logger::LogWarning("LevelComponent::PostInitialize(), only single player or 2 player supported");
		break;

	}
}

glm::vec3 Qbert::LevelComponent::GetTopCubeTilePos()
{
	auto topTile = m_pTiles.at(QbertGameSettings::level_size - 1)[0];
	return topTile->GetParent()->GetpTransform()->GetPosition();
}

glm::vec3 Qbert::LevelComponent::GetBottomLeftCubeTilePos()
{
	auto leftBottom = m_pTiles.at(0)[0];
	return leftBottom->GetParent()->GetpTransform()->GetPosition();
}

glm::vec3 Qbert::LevelComponent::GetBottomRightCubeTilePos()
{
	auto rightBottom = m_pTiles.at(0)[QbertGameSettings::level_size - 1];
	return rightBottom->GetParent()->GetpTransform()->GetPosition();
}

peach::GameObject* Qbert::LevelComponent::GetTile(uint32_t col, uint32_t row)
{
	if (row >= QbertGameSettings::level_size || col >= QbertGameSettings::level_size - row)
		return nullptr;

	return m_pTiles.at(row)[col]->GetParent();
}

void Qbert::LevelComponent::CheckForEnd()
{
	m_IsFinished = true;

	for (auto& tileRow : m_pTiles)
	{
		auto& vector = tileRow.second;
		if (std::find_if(vector.begin(), vector.end(),
			[](TileComponent* pTile) {
				if (pTile->GetIsFinished())
					return false;
				return true; })
			!= tileRow.second.end())
		{
			m_IsFinished = false;
			break;
		}
	}

	if (m_IsFinished)
	{
		peach::Logger::LogError("LEVEL FINISHED BITCHES");
	}

}
