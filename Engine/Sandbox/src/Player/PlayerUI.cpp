#include "QbertPCH.h"

#include "PlayerUI.h"
#include "Subject.h"
#include "imgui.h"
#include "Health/HealthObserver.h"
#include "Score/ScoreObserver.h"
#include "TextComponent.h"

Qbert::PlayerUi::PlayerUi(const std::string& playerID, int playerScore, int playerHealth, peach::Subject* pHealthSubject, peach::Subject* pScoreSubject)
	:m_PlayerID(playerID)
	, m_PlayerScore(playerScore)
	, m_RemainingHealth(playerHealth)
{
	m_pHealthObserver = std::make_unique<HealthObserver>(&m_RemainingHealth, &m_ShouldUpdateText, pHealthSubject);
	m_pScoreObserver = std::make_unique<ScoreObserver>(&m_PlayerScore, &m_ShouldUpdateText, pScoreSubject);
}

void Qbert::PlayerUi::Render()const
{

}

void Qbert::PlayerUi::Initialize()
{
	m_Font = peach::ResourceManager::GetInstance().LoadFont("Resources/Fonts/q-bert-original.ttf", m_CharSize);

	m_pPlayerTextComponent = new peach::TextComponent("Player " + m_PlayerID, m_Font);
	m_pPlayerTextComponent->SetColor(m_TextColor);

	m_pHealthTextComponent = new peach::TextComponent("Health " + std::to_string(m_RemainingHealth), m_Font);
	m_pHealthTextComponent->SetPosition({ 0, static_cast<float>(m_CharSize) });
	m_pHealthTextComponent->SetColor(m_TextColor);

	m_pScoreTextComponent = new peach::TextComponent("Score " + std::to_string(m_PlayerScore), m_Font);
	m_pScoreTextComponent->SetPosition({ 0, static_cast<float>(2 * m_CharSize) });
	m_pScoreTextComponent->SetColor(m_TextColor);


	GetParent()->AddComponent(m_pPlayerTextComponent);
	GetParent()->AddComponent(m_pHealthTextComponent);
	GetParent()->AddComponent(m_pScoreTextComponent);

}

void Qbert::PlayerUi::Update()
{
	if (m_ShouldUpdateText)
	{
		m_pHealthTextComponent->SetText("Health " + std::to_string(m_RemainingHealth));
		m_pScoreTextComponent->SetText("Score " + std::to_string(m_PlayerScore));

	}
}
