#include "QbertPCH.h"

#include "HealthObserver.h"
#include "Health.h"

Qbert::HealthObserver::HealthObserver(int* pOwnerHealth, peach::Subject* pSubject)
	:m_pOwnerHealth(pOwnerHealth)
	, m_Subject(pSubject)
{
	m_Subject->AddObserver(this);
}

void Qbert::HealthObserver::Notify(const peach::GameObject& GameObject, peach::Event event)
{
	switch (event)
	{
	case peach::Event::OwnerDamaged:
		*(m_pOwnerHealth) = GameObject.GetComponent<Health>()->GetHealth();
		break;

	}
}
