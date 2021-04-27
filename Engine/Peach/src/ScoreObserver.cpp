#include "MiniginPCH.h"
#include "ScoreObserver.h"

#include "ScoreComponent.h"

peach::ScoreObserver::ScoreObserver(int* pOwnerScore, Subject* pSubject)
	:m_pOwnerScore(pOwnerScore)
	,m_Subject(pSubject)
{
	m_Subject->AddObserver(this);
}

void peach::ScoreObserver::Notify(const GameObject& GameObject, Event event)
{
	switch (event)
	{
	case Event::ScoreIncreased:
		*(m_pOwnerScore) = GameObject.GetComponent<ScoreComponent>()->GetScore();
		break;
	}
}
