#include "QbertPCH.h"
#include "TileComponent.h"
#include "TextureComponent.h"
#include "LevelComponent.h"
#include "Score/ScoreComponent.h"

Qbert::TileComponent::TileComponent(const std::vector<std::string>& textureVector, LevelComponent* pLevel, bool reverses)
	:ComponentBase(),
	m_pTextureVector(textureVector),
	m_pLevel(pLevel),
	m_Reverses(reverses),
	m_MaxStages(static_cast<uint32_t>(textureVector.size() - 1)),
	m_CurrentStage(static_cast<uint32_t>(0)),
	m_IsFinished(false)

{

}

void Qbert::TileComponent::QbertStepOn(peach::GameObject* pQbert)
{
	if (m_Reverses && m_CurrentStage == m_MaxStages)
	{
		--m_CurrentStage;
		m_IsFinished = false;
	}
	else if (m_CurrentStage < m_MaxStages)
	{
		++m_CurrentStage;

		auto scoreComp = pQbert->GetComponent<ScoreComponent>();
		if (!scoreComp)
			peach::Logger::LogError("TileComponent::QbertStepOn, no scoreComponent was found on the game object");
		scoreComp->IncreaseScore(25);
	}

	if (m_CurrentStage == m_MaxStages && !m_IsFinished)
	{
		m_IsFinished = true;
		m_pLevel->CheckForEnd();
	}


	Clamp(m_CurrentStage, static_cast<uint32_t>(0), m_MaxStages);
	GetParent()->GetComponent<peach::TextureComponent>()->SetTexture(m_pTextureVector[m_CurrentStage]);
}

void Qbert::TileComponent::GreenStepOn()
{
	if (m_CurrentStage != 0)
	{
		--m_CurrentStage;
		Clamp(m_CurrentStage, static_cast<uint32_t>(0), m_MaxStages);
		GetParent()->GetComponent<peach::TextureComponent>()->SetTexture(m_pTextureVector[m_CurrentStage]);
	}
}

void Qbert::TileComponent::SetReverses(bool state)
{
	m_Reverses = state;
}

void Qbert::TileComponent::SetTextureVector(const std::vector<std::string>& pTextureVector)
{
	m_pTextureVector = pTextureVector;
	m_MaxStages = static_cast<uint32_t>(pTextureVector.size() - 1);
	m_CurrentStage = static_cast<uint32_t>(0);
	GetParent()->GetComponent<peach::TextureComponent>()->SetTexture(m_pTextureVector[m_CurrentStage]);

	m_IsFinished = false;
}

void Qbert::TileComponent::Initialize()
{
}

void Qbert::TileComponent::Update()
{
}

void Qbert::TileComponent::Render() const
{
}
