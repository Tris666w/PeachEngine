#include "QbertPCH.h"

#include "ScoreObserver.h"

#include "ScoreComponent.h"

Qbert::ScoreObserver::ScoreObserver(int* pOwnerScore, bool* pTextUpdateBool, peach::Subject* pSubject)
	:m_pOwnerScore(pOwnerScore),
	m_pTextUpdateBool(pTextUpdateBool),
	m_Subject(pSubject)
{
	m_Subject->AddObserver(this);
}

void Qbert::ScoreObserver::Notify(const peach::GameObject& GameObject, peach::Event event)
{
	switch (event)
	{
	case peach::Event::ScoreIncreased:
		*(m_pOwnerScore) = GameObject.GetComponent<ScoreComponent>()->GetScore();
		*m_pTextUpdateBool = true;
		break;
	}
}
