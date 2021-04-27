#pragma once
#include "Command.h"
#include "Health.h"

class DamageCommand final :public Command
{
public:
	DamageCommand(peach::Health* pHealthComponent);
	void Execute() override;
private:
	peach::Health* m_pHealth = nullptr;
};

