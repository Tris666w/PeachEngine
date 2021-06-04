#pragma once
#include "ComponentBase.h"

namespace Qbert
{
	class LevelMovementComponent;
	class QbertController final :public peach::ComponentBase
	{
	public:
		void Initialize() override;

	private:
		LevelMovementComponent* m_pMovementComponent = nullptr;
	};
}