#pragma once
#include "ComponentBase.h"

namespace peach
{
	class QbertComponent final : public ComponentBase
	{
	public:
		QbertComponent() = default;
		QbertComponent(const QbertComponent& other) = delete;
		QbertComponent(QbertComponent&& other) noexcept = delete;
		QbertComponent& operator=(const QbertComponent& other) = delete;
		QbertComponent& operator=(QbertComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;

	private:

	};

}

