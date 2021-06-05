#pragma once
#include "ComponentBase.h"

namespace Qbert
{
	class LevelMovementComponent;
	class QbertController final :public peach::ComponentBase
	{
	public:
		void Initialize() override;
		void Update() override;
		void Render() const override;

	private:
		LevelMovementComponent* m_pMovementComponent = nullptr;
	};
}