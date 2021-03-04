#include "MiniginPCH.h"
#include "Health.h"

#include "Subject.h"

dae::Health::Health(GameObject* pOwner, int maxHealth,const int startHealth)
	:m_pOwner(pOwner)
	,m_MaxHealth(maxHealth)
	,m_CurrentHealth(startHealth)
	,m_HealthSubject(std::make_unique<Subject>())
{
}
void dae::Health::DoDamage(const int damage)
{
	m_CurrentHealth -= damage;
	m_HealthSubject.get()->Notify(*(m_pOwner), Event::OwnerDamaged);
	
	if (!m_PlayerIsDead && m_CurrentHealth<= 0)
	{
		m_PlayerIsDead = true;
		m_HealthSubject.get()->Notify(*(m_pOwner), Event::OwnerDied);
	}
}

int dae::Health::GetHealth() const
{
	return m_CurrentHealth;
}

dae::Subject* dae::Health::GetpSubject() const
{
	return m_HealthSubject.get();
}