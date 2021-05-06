#pragma once
#include "ComponentBase.h"
class FPS final : public dae::ComponentBase
{
public:
	void Initialize() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	int GetAverageFPS()const { return m_AverageFPS; }
private:
	int m_AverageFPS{};
	int m_AmountOfPassedFrames{};
	float m_PassedTime{ 1.5f };
	const float m_PassTime{ 0.5f };
};
