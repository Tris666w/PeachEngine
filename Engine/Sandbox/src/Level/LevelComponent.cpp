#include "QbertPCH.h"
#include "LevelComponent.h"

#include "DiscComponent.h"
#include "GameObject.h"
#include "TileComponent.h"
#include "TextureComponent.h"
#include "QbertGameSettings.h"
#include "LevelMovementComponent.h"
#include "RectColliderComponent.h"
#include "BinaryReader.h"
#include "Score/ScoreComponent.h"
#include "LevelEnemyManager.h"
#include "Player/QbertComponent.h"
#include "Scenes/LossScreen.h"
#include "Scenes/VictoryScreen.h"

void Qbert::LevelComponent::Initialize()
{

	bool reversible;
	std::vector<std::string> textureVect{};
	ReadAndMakeLevelLayout(textureVect, reversible);


	auto pos = glm::vec3{ 0,0,0 };
	for (int row = 0; row < QbertGameSettings::level_size; ++row)
	{
		std::vector<TileComponent*> pTiles{};
		for (int col = 0; col < QbertGameSettings::level_size - row; ++col)
		{
			auto go = new peach::GameObject();
			auto const tileComp = new TileComponent(textureVect, this, reversible);
			auto const textureComp = new peach::TextureComponent(textureVect[0], block_size, block_size);

			go->AddComponent(tileComp);
			go->AddComponent(textureComp);
			GetParent()->AddChild(go);
			go->SetPosition(pos.x + col * block_size, pos.y);
			pTiles.push_back(tileComp);
			if (row == 0 || col == 0 || col == QbertGameSettings::level_size - row - 1)
			{
				go->SetIsActive(false);
			}
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
	switch (amountOfPlayers)
	{
	case 1:
		moveComp->SetGridSpawnPos(1, QbertGameSettings::level_size - 3);
		moveComp->MoveImmediatelyToSpawnPos();
		break;
	case 2:
		moveComp = qbertGameObjects[0]->GetComponent<LevelMovementComponent>();
		moveComp->SetGridSpawnPos(1, 1);
		moveComp->MoveImmediatelyToSpawnPos();

		moveComp = qbertGameObjects[1]->GetComponent<LevelMovementComponent>();
		moveComp->SetGridSpawnPos(QbertGameSettings::level_size - 3, 1);
		moveComp->MoveImmediatelyToSpawnPos();

		break;
	default:
		peach::Logger::LogWarning("LevelComponent::PostInitialize(), only single player or 2 player supported");
		break;

	}


	for (int i = 0; i < m_pDiscGridPosVector.size(); ++i)
	{
		auto go = new peach::GameObject();
		auto discComp = new DiscComponent();
		go->AddComponent(discComp);
		auto textureComp = new peach::TextureComponent("Resources/Images/Disc.png", 32, 32);
		go->AddComponent(textureComp);
		auto lmc = new LevelMovementComponent();
		go->AddComponent(lmc);
		SDL_Rect rect = { 0,0,32,32 };
		auto collider = new peach::RectColliderComponent(rect);
		go->AddComponent(collider);
		GetParent()->AddChild(go);
		m_pDiscs.push_back(go);

		lmc->SetGridSpawnPos(static_cast<int>(m_pDiscGridPosVector[i].x), static_cast<int>(m_pDiscGridPosVector[i].y));
		lmc->MoveImmediatelyToSpawnPos();
	}


	m_pEnemyManager = GetParent()->GetComponent<LevelEnemyManager>();
	if (!m_pEnemyManager)
		peach::Logger::LogWarning("LevelComponent::PostInitialize(), m_pEnemyManager is nullptr");



}

void Qbert::LevelComponent::Update()
{
	if (m_IsFinished)
	{
		LoadNextLevel();
	}
}

void Qbert::LevelComponent::Render() const
{
}

glm::vec3 Qbert::LevelComponent::GetCubeTilePos(int col, int row)
{
	auto topTile = m_pTiles.at(row)[col];
	return topTile->GetParent()->GetpTransform()->GetPosition();
}

glm::vec3 Qbert::LevelComponent::GetTopCubeTilePos()
{
	auto topTile = m_pTiles.at(QbertGameSettings::level_size - 3)[1];
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

const std::vector<peach::GameObject*>& Qbert::LevelComponent::GetDiscs()
{
	return m_pDiscs;
}

void Qbert::LevelComponent::CheckForEnd()
{
	m_IsFinished = true;

	for (auto& tileRow : m_pTiles)
	{
		auto& vector = tileRow.second;
		if (std::find_if(vector.begin(), vector.end(),
			[](TileComponent* pTile) {
				if (pTile->GetIsFinished() || !pTile->GetParent()->GetIsActive())
					return false;
				return true; })
			!= tileRow.second.end())
		{
			m_IsFinished = false;
			break;
		}
	}

	auto players = GetParent()->GetScene()->GetObjectsWithTag(QbertGameSettings::qbert_tag);
	for (auto qbertObject : players)
	{
		if (!qbertObject->GetComponent<QbertComponent>()->GetIsDead())
		{
			return;
		}
	}


	//TODO: Go to loss screen

	GoToLossScreen();
}

void Qbert::LevelComponent::ReadAndMakeLevelLayout(std::vector<std::string>& textureVect, bool& reversible)
{
	std::string path = "Resources/LevelLayout/Level" + std::to_string(m_LevelID);

	std::ifstream input;
	input.open(path, std::ios::in | std::ios::binary);
	if (!input.is_open())
	{
		peach::Logger::LogError("Could not open");
	}

	uint32_t amountOfTexturesRead;
	BinaryReader::Read(input, amountOfTexturesRead);
	for (uint32_t i = 0; i < amountOfTexturesRead; ++i)
	{
		std::string texturePath;
		BinaryReader::Read(input, texturePath);
		textureVect.push_back(texturePath);
	}
	BinaryReader::Read(input, reversible);

	uint32_t amountOfDisksRead;
	m_pDiscGridPosVector.clear();
	BinaryReader::Read(input, amountOfDisksRead);
	for (uint32_t i = 0; i < amountOfDisksRead; ++i)
	{
		uint32_t col;
		uint32_t row;

		BinaryReader::Read(input, col);
		BinaryReader::Read(input, row);
		m_pDiscGridPosVector.push_back({ col,row,0 });
	}

}

void Qbert::LevelComponent::LoadNextLevel()
{
	CheckDiscPoints();
	m_pEnemyManager->Reset();
	m_IsFinished = false;
	++m_LevelID;

	if (m_LevelID >= m_AmountOfLevels)
	{
		GoToVictoryScreen();
		return;
	}

	bool reversible;
	std::vector<std::string> textureVect{};
	ReadAndMakeLevelLayout(textureVect, reversible);


	for (int row = 0; row < QbertGameSettings::level_size; ++row)
	{
		std::vector<TileComponent*> pTiles{};
		for (int col = 0; col < QbertGameSettings::level_size - row; ++col)
		{
			auto tile = m_pTiles[row][col];
			tile->SetReverses(reversible);
			tile->SetTextureVector(textureVect);
		}
		m_pTiles.insert({ row,pTiles });
	}

	auto qbertVector = GetParent()->GetScene()->GetObjectsWithTag(QbertGameSettings::qbert_tag);
	for (auto qbert : qbertVector)
	{
		qbert->GetComponent<LevelMovementComponent>()->MoveImmediatelyToSpawnPos();
	}

	for (int i = 0; i < m_pDiscGridPosVector.size(); ++i)
	{
		if (m_pDiscGridPosVector.size() <= m_pDiscs.size())
		{
			auto discComp = m_pDiscs[i]->GetComponent<DiscComponent>();
			discComp->Reset();
			auto moveComp = m_pDiscs[i]->GetComponent<LevelMovementComponent>();
			moveComp->SetGridSpawnPos(static_cast<int>(m_pDiscGridPosVector[i].x), static_cast<int>(m_pDiscGridPosVector[i].y));
			moveComp->MoveImmediatelyToSpawnPos();
		}
		else
		{
			auto go = new peach::GameObject();
			auto discComp = new DiscComponent();
			go->AddComponent(discComp);
			auto textureComp = new peach::TextureComponent("Resources/Images/Disc.png", 32, 32);
			go->AddComponent(textureComp);
			auto lmc = new LevelMovementComponent();
			go->AddComponent(lmc);
			SDL_Rect rect = { 0,0,32,32 };
			auto collider = new peach::RectColliderComponent(rect);
			go->AddComponent(collider);
			GetParent()->AddChild(go);
			m_pDiscs.push_back(go);

			lmc->SetGridSpawnPos(static_cast<int>(m_pDiscGridPosVector[i].x), static_cast<int>(m_pDiscGridPosVector[i].y));
			lmc->MoveImmediatelyToSpawnPos();
		}
	}
}

void Qbert::LevelComponent::CheckDiscPoints()
{
	auto qbertGameObjects = GetParent()->GetScene()->GetObjectsWithTag(QbertGameSettings::qbert_tag);

	for (auto element : m_pDiscs)
	{
		if (element->GetIsActive())
		{
			for (auto qbert : qbertGameObjects)
				qbert->GetComponent<ScoreComponent>()->IncreaseScore(50);
		}
	}
}

void Qbert::LevelComponent::GoToVictoryScreen()
{
	peach::SceneManager::GetInstance().AddScene(std::make_shared<VictoryScreen>());
	peach::SceneManager::GetInstance().SetActiveGameScene("VictoryScreen");

}

void Qbert::LevelComponent::GoToLossScreen()
{
	peach::SceneManager::GetInstance().AddScene(std::make_shared<LossScreen>());
	peach::SceneManager::GetInstance().SetActiveGameScene("LossScreen");
}
