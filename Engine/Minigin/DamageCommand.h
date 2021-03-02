#pragma once
#include "Command.h"
#include "Health.h"

class DamageCommand final :public Command
{
public:
	DamageCommand(dae::Health* pHealthComponent);
	void Execute() override;
private:
	dae::Health* m_pHealth = nullptr;
};

