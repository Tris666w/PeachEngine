#pragma once
#include <map>
#include <vector>
#include <glm/vec3.hpp>
#include "ComponentBase.h"
namespace peach
{
	class LevelComponent final : public ComponentBase
	{
	public:
		void Initialize() override;
		void PostInitialize() override;

		glm::vec3 GetTopCubeTilePos();
		glm::vec3 GetBottomLeftCubeTilePos();
		glm::vec3 GetBottomRightCubeTilePos();

		GameObject* GetTile(uint32_t col, uint32_t row);

		static int const level_size = 7;
		static int const block_size = 64;

		using row = uint32_t;
		std::map<row, std::vector<GameObject*>> m_pTiles;
	};
}
