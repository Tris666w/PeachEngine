#include "QbertPCH.h"
#include "TileComponent.h"
#include "TextureComponent.h"
#include "LevelComponent.h"

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

void Qbert::TileComponent::QbertStepOn()
{
	if (m_Reverses && m_CurrentStage == m_MaxStages)
	{
		--m_CurrentStage;
		m_IsFinished = false;
	}
	else
		++m_CurrentStage;

	if (m_CurrentStage == m_MaxStages && !m_IsFinished)
	{
		m_IsFinished = true;
		m_pLevel->CheckForEnd();
	}


	Clamp(m_CurrentStage, static_cast<uint32_t>(0), m_MaxStages);
	GetParent()->GetComponent<peach::TextureComponent>()->SetTexture(m_pTextureVector[m_CurrentStage]);
}
