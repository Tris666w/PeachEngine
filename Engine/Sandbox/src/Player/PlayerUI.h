#pragma once
#include "imgui.h"
#include "ComponentBase.h"
namespace peach
{
	class TextComponent;
	class Subject;
}

namespace Qbert {
	class ScoreObserver;
	class HealthObserver;

	class PlayerUi : public peach::ComponentBase
	{
	public:
		PlayerUi(ImVec2 screenPos, const std::string& playerID, int playerScore, int playerHealth, peach::Subject* pHealthSubject, peach::Subject* pScoreSubject);

		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
		peach::TextComponent* m_pPlayerTextComponent = nullptr;
		peach::TextComponent* m_pHealthTextComponent = nullptr;
		peach::TextComponent* m_pScoreTextComponent = nullptr;

		ImVec2 m_ScreenPos = {};
		std::string m_PlayerID = {};
		int m_PlayerScore;
		int m_RemainingHealth;
		int const m_CharSize = 32;
		std::unique_ptr<HealthObserver> m_pHealthObserver = nullptr;
		std::unique_ptr<ScoreObserver> m_pScoreObserver = nullptr;
		bool m_ShouldUpdateText = false;

		std::shared_ptr<peach::Font> m_Font;
		SDL_Color m_TextColor = { 255,119,0 };
	};
}
