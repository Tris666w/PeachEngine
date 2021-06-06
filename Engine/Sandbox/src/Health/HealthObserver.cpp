#include "QbertPCH.h"

#include "HealthObserver.h"
#include "Health.h"

Qbert::HealthObserver::HealthObserver(int* pOwnerHealth, bool* pTextUpdateBool, peach::Subject* pSubject)
	:m_pOwnerHealth(pOwnerHealth),
	m_pTextUpdateBool(pTextUpdateBool),
	m_Subject(pSubject)
{
	m_Subject->AddObserver(this);
}

Qbert::HealthObserver::HealthObserver(bool* pIsDead, peach::Subject* pSubject)
	:m_pIsDead(pIsDead),
	m_Subject(pSubject)
{
	m_Subject->AddObserver(this);
}

void Qbert::HealthObserver::Notify(const peach::GameObject& GameObject, peach::Event event)
{
	
	switch (event)
	{
	case peach::Event::OwnerDamaged:
		if (m_pOwnerHealth && m_pTextUpdateBool)
		{
			*(m_pOwnerHealth) = GameObject.GetComponent<Health>()->GetHealth();
			*m_pTextUpdateBool = true;
		}
		break;
	case peach::Event::OwnerDied:
		if(m_pIsDead)
			*(m_pIsDead) = true;
		break;
	}
}
