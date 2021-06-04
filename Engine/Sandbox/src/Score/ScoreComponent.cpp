#include "QbertPCH.h"

#include "ScoreComponent.h"
#include "Subject.h"

Qbert::ScoreComponent::ScoreComponent(peach::GameObject* pOwner)
	:m_pOwner(pOwner)
	, m_ScoreSubject(std::make_unique<peach::Subject>())
{
}

void Qbert::ScoreComponent::IncreaseScore(const int amount)
{
	m_Score += amount;
	m_ScoreSubject.get()->Notify(*(m_pOwner), peach::Event::ScoreIncreased);
}

int Qbert::ScoreComponent::GetScore() const
{
	return m_Score;
}

peach::Subject* Qbert::ScoreComponent::GetpSubject() const
{
	return m_ScoreSubject.get();
}
