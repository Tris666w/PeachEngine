#include "MiniginPCH.h"
#include "DamageCommand.h"

DamageCommand::DamageCommand(dae::Health* pHealthComponent)
	:m_pHealth(pHealthComponent)
{
}

void DamageCommand::Execute()
{
	m_pHealth->DoDamage(1);
}
