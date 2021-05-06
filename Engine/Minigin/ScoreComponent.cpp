#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "Subject.h"

dae::ScoreComponent::ScoreComponent(GameObject* pOwner)
	:m_pOwner(pOwner)
	,m_ScoreSubject(std::make_unique<Subject>())
{
}

void dae::ScoreComponent::IncreaseScore(const int amount)
{
	m_Score += amount;
	m_ScoreSubject.get()->Notify(*(m_pOwner), Event::ScoreIncreased);
}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}

dae::Subject* dae::ScoreComponent::GetpSubject() const
{
	return m_ScoreSubject.get();
}
