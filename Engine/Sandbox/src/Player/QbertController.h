#pragma once
#include "ComponentBase.h"

namespace Qbert
{
	class LevelMovementComponent;
	class QbertController final :public peach::ComponentBase
	{
	public:
		explicit QbertController(bool useController = true);

		void Initialize() override;
		void Update() override;
		void Render() const override;

	private:
		bool m_UseController;
	};
}