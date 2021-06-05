#pragma once
#include <map>
#include <vector>
#include "ComponentBase.h"

namespace Qbert
{
	class TileComponent;
	class LevelComponent final : public peach::ComponentBase
	{
	public:
		void Initialize() override;
		void PostInitialize() override;
		void Update() override;
		void Render() const override;

		glm::vec3 GetTopCubeTilePos();
		glm::vec3 GetBottomLeftCubeTilePos();
		glm::vec3 GetBottomRightCubeTilePos();

		peach::GameObject* GetTile(uint32_t col, uint32_t row);

		void CheckForEnd();
		static int const block_size = 64;

	private:
		bool m_IsFinished = false;
		using row = uint32_t;
		std::map<row, std::vector<TileComponent*>> m_pTiles;
	};
}
