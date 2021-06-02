#include "QbertPCH.h"
#include "LevelComponent.h"

#include "GameObject.h"
#include "TileComponent.h"
#include "TextureComponent.h"
#include "QbertGameSettings.h"
#include "LevelMovementComponent.h"

void peach::LevelComponent::Initialize()
{
	std::vector<std::string> textureVect = {};
	textureVect.push_back("Resources/Images/Level1/L1InactiveTile.png");
	auto pos = glm::vec3{ 0,0,0 };

	for (int row = 0; row < level_size; ++row)
	{
		std::vector<GameObject*> pGameObjects{};
		for (int col = 0; col < level_size - row; ++col)
		{
			auto go = new GameObject();
			auto tileComp = new TileComponent();
			auto textureComp = new TextureComponent(textureVect[0], block_size, block_size);
			tileComp->SetTextureVector(textureVect);
			go->AddComponent(tileComp);
			go->AddComponent(textureComp);

			GetParent()->AddChild(go);
			go->SetPosition(pos.x + col * block_size, pos.y);
			pGameObjects.push_back(go);
		}
		pos.x += block_size / 2.f;
		pos.y -= block_size * 0.75f;

		m_pTiles.insert({ row,pGameObjects });
	}

	GetParent()->SetTag(QbertGameSettings::level_tag);
}

void peach::LevelComponent::PostInitialize()
{
	auto scene = GetParent()->GetScene();
	auto qbertGameObjects = scene->GetObjectsWithTag(QbertGameSettings::qbert_tag);
	auto const amountOfPlayers = QbertGameSettings::GetInstance().GetAmountOfPlayers();

	if (amountOfPlayers != qbertGameObjects.size())
		Logger::LogWarning("LevelComponent::PostInitialize(), amount of players in the scene != amount of players in the game");

	auto moveComp = qbertGameObjects[0]->GetComponent<LevelMovementComponent>();
	auto player = qbertGameObjects[0];
	switch (amountOfPlayers)
	{
	case 1:
		player->SetPosition(GetTopCubeTilePos().x, GetTopCubeTilePos().y);
		if (moveComp)
			moveComp->SetGridSpawnPos(0, level_size - 1);
		else
			Logger::LogInfo("LevelComponent::PostInitialize(), no LevelMovementComponent was found");

		break;
	case 2:
		qbertGameObjects[0]->SetPosition(GetBottomLeftCubeTilePos().x, GetBottomLeftCubeTilePos().y);
		qbertGameObjects[1]->SetPosition(GetBottomRightCubeTilePos().x, GetBottomRightCubeTilePos().y);
		break;
	default:
		Logger::LogWarning("LevelComponent::PostInitialize(), only single player or 2 player supported");
		break;

	}
}

glm::vec3 peach::LevelComponent::GetTopCubeTilePos()
{
	auto topTile = m_pTiles.at(level_size - 1)[0];
	return topTile->GetpTransform()->GetPosition();
}

glm::vec3 peach::LevelComponent::GetBottomLeftCubeTilePos()
{
	auto leftBottom = m_pTiles.at(0)[0];
	return leftBottom->GetpTransform()->GetPosition();
}

glm::vec3 peach::LevelComponent::GetBottomRightCubeTilePos()
{
	auto rightBottom = m_pTiles.at(0)[level_size - 1];
	return rightBottom->GetpTransform()->GetPosition();
}

peach::GameObject* peach::LevelComponent::GetTile(uint32_t col, uint32_t row)
{
	if (row >= level_size || col >= level_size - row)
		return nullptr;

	return m_pTiles.at(row)[col];
}
