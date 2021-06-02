#pragma once
#include "ComponentBase.h"
#include "Peach.h"

namespace peach
{
	class LevelMovementComponent;
	class QbertController final :public ComponentBase
	{
	public:
		void Initialize() override;

	private:
		LevelMovementComponent* m_pMovementComponent = nullptr;
	};
}