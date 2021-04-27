#pragma once
#include "imgui.h"
#include "SceneObject.h"

namespace peach {
	class ScoreObserver;
	class Subject;
	class HealthObserver;

	class PlayerUI : public peach::SceneObject
	{
	public:
		PlayerUI(ImVec2 screenPos, const std::string& playerID,int playerScore, int playerHealth,Subject* pHealthSubject,Subject* pScoreSubject);
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
