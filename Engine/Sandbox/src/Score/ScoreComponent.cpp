#include "QbertPCH.h"

#include "ScoreComponent.h"
#include "Subject.h"

peach::ScoreComponent::ScoreComponent(GameObject* pOwner)
	:m_pOwner(pOwner)
	, m_ScoreSubject(std::make_unique<Subject>())
{
}

void peach::ScoreComponent::IncreaseScore(const int amount)
{
	m_Score += amount;
	m_ScoreSubject.get()->Notify(*(m_pOwner), Event::ScoreIncreased);
}

int peach::ScoreComponent::GetScore() const
{
	return m_Score;
}

peach::Subject* peach::ScoreComponent::GetpSubject() const
{
	return m_ScoreSubject.get();
}
