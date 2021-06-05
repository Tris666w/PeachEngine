#pragma once
#include "ComponentBase.h"
namespace peach
{
	class FPS final : public ComponentBase
	{
	public:
		void Initialize() override;
		void Update() override;
		void Render() const override;

		int GetAverageFPS()const { return m_AverageFPS; }
	private:
		int m_AverageFPS{};
		int m_AmountOfPassedFrames{};
		float m_PassedTime{ 1.5f };
		const float m_PassTime{ 0.5f };
	};
}