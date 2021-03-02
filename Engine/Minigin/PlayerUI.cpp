#include "MiniginPCH.h"
#include "PlayerUI.h"
#include "Subject.h"
#include "imgui.h"
#include "HealthObserver.h"
#include "ScoreObserver.h"

dae::PlayerUI::PlayerUI(ImVec2 screenPos, const std::string& playerID, int playerScore, int playerHealth, Subject* pHealthSubject,Subject* pScoreSubject)
	:m_ScreenPos(screenPos)
	,m_PlayerID(playerID)
	,m_PlayerScore(playerScore)
	,m_RemainingHealth(playerHealth)
{
	m_pHealthObserver = std::make_unique<HealthObserver>(&m_RemainingHealth, pHealthSubject);
	m_pScoreObserver = std::make_unique<ScoreObserver>(&m_PlayerScore, pScoreSubject);
}

void dae::PlayerUI::Render() const
{
	const std::string windowTitle = "Player " + m_PlayerID;
	const std::string playerScore = "Score: " + std::to_string(m_PlayerScore);
	const std::string playerHealth = "Health: " + std::to_string(m_RemainingHealth);
	
	const ImVec2 windowSize = { 150,100 };
	ImGui::SetNextWindowSize(windowSize);
	ImGui::SetNextWindowPos(m_ScreenPos);

	
	ImGui::Begin(windowTitle.c_str());
	ImGui::Text(playerScore.c_str());
	ImGui::Text(playerHealth.c_str());
	
	if (m_RemainingHealth <= 0)
	{
		const std::string playerDied = "Player " + m_PlayerID + " has died";
		ImGui::Text(playerDied.c_str());
		
	}

	
	ImGui::End();
}
