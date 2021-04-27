#include "MiniginPCH.h"
#include "HealthObserver.h"
#include "Health.h"
peach::HealthObserver::HealthObserver(int* pOwnerHealth, Subject* pSubject)
	:m_pOwnerHealth(pOwnerHealth)
	,m_Subject(pSubject)
{
	m_Subject->AddObserver(this);
}

void peach::HealthObserver::Notify(const GameObject& GameObject, Event event)
{
	switch (event)
	{
	case Event::OwnerDamaged:
		*(m_pOwnerHealth) = GameObject.GetComponent<Health>()->GetHealth();
		break;
		
	}
}
