#pragma once
#include "imgui.h"
#include "ComponentBase.h"
namespace peach
{
	class Subject;
}

namespace Qbert {
	class ScoreObserver;
	class HealthObserver;

	class PlayerUI : public peach::ComponentBase
	{
	public:
		PlayerUI(ImVec2 screenPos, const std::string& playerID,int playerScore, int playerHealth, peach::Subject* pHealthSubject, peach::Subject* pScoreSubject);
		void Render() const override;
	private:
		ImVec2 m_ScreenPos = {};
		std::string m_PlayerID = {};
		int m_PlayerScore;
		int m_RemainingHealth;
		std::unique_ptr<HealthObserver> m_pHealthObserver = nullptr;
		std::unique_ptr<ScoreObserver> m_pScoreObserver = nullptr;
	};
}
