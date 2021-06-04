#pragma once
#include "Command.h"
#include "Health.h"

namespace Qbert
{
	class DamageCommand final :public peach::Command
	{
	public:
		DamageCommand(Health* pHealthComponent);
		void Execute() override;
	private:
		Health* m_pHealth = nullptr;
	};
}