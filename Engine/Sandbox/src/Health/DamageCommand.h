#pragma once
#include "Command.h"
#include "Health.h"

namespace Qbert
{
	class DamageCommand final :public peach::Command
	{
	public:
		DamageCommand(peach::Health* pHealthComponent);
		void Execute() override;
	private:
		peach::Health* m_pHealth = nullptr;
	};
}