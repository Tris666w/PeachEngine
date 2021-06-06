#pragma once
#include <map>
#include <vector>
#include "ComponentBase.h"


namespace Qbert
{
	class DiscComponent;
	class TileComponent;
	class LevelEnemyManager;
	class LevelComponent final : public peach::ComponentBase
	{
	public:
		void Initialize() override;
		void PostInitialize() override;
		void Update() override;
		void Render() const override;

		glm::vec3 GetCubeTilePos(int col, int row);
		glm::vec3 GetTopCubeTilePos();
		glm::vec3 GetBottomLeftCubeTilePos();
		glm::vec3 GetBottomRightCubeTilePos();

		peach::GameObject* GetTile(uint32_t col, uint32_t row);
		const std::vector<peach::GameObject*>& GetDiscs();

		void CheckForEnd();
		static int const block_size = 64;

	private:
		bool m_IsFinished = false;
		int const m_AmountOfLevels = 3;
		using row = uint32_t;
		std::map<row, std::vector<TileComponent*>> m_pTiles;
		std::vector<peach::GameObject*> m_pDiscs;
		std::vector<glm::vec3>m_pDiscGridPosVector;
		int m_LevelID = 1;
		int m_SoundID = 1;

		LevelEnemyManager* m_pEnemyManager = nullptr;

		void ReadAndMakeLevelLayout(std::vector<std::string>& textureVect, bool& reversible);
		void LoadNextLevel();
		void CheckDiscPoints();
		void GoToVictoryScreen();
		void GoToLossScreen();
		void PlaySound();

	};
}
