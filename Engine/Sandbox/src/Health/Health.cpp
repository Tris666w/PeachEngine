#include "QbertPCH.h"
#include "Health.h"

#include "Subject.h"

Qbert::Health::Health(peach::GameObject* pOwner, int maxHealth, const int startHealth)
	:m_pOwner(pOwner)
	, m_MaxHealth(maxHealth)
	, m_CurrentHealth(startHealth)
	, m_HealthSubject(std::make_unique<peach::Subject>())
{
}
void Qbert::Health::DoDamage(const int damage)
{
	m_CurrentHealth -= damage;
	m_HealthSubject.get()->Notify(*(m_pOwner), peach::Event::OwnerDamaged);

	if (!m_PlayerIsDead && m_CurrentHealth <= 0)
	{
		m_PlayerIsDead = true;
		m_HealthSubject.get()->Notify(*(m_pOwner), peach::Event::OwnerDied);
	}
}

int Qbert::Health::GetHealth() const
{
	return m_CurrentHealth;
}

peach::Subject* Qbert::Health::GetpSubject() const
{
	return m_HealthSubject.get();
}
