#include "QbertPCH.h"

#include "DamageCommand.h"

Qbert::DamageCommand::DamageCommand(peach::Health* pHealthComponent)
	:m_pHealth(pHealthComponent)
{
}

void Qbert::DamageCommand::Execute()
{
	m_pHealth->DoDamage(1);
}
