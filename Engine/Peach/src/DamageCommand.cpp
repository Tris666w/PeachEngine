#include "MiniginPCH.h"
#include "DamageCommand.h"

DamageCommand::DamageCommand(peach::Health* pHealthComponent)
	:m_pHealth(pHealthComponent)
{
}

void DamageCommand::Execute()
{
	m_pHealth->DoDamage(1);
}
