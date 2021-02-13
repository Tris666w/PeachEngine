#pragma once
#include "ComponentBase.h"

namespace dae
{
	class TextObject;
}
class FPS;

class FPSCounter final : public dae::ComponentBase
{
public:
	FPSCounter(dae::TextObject* pTextObject);

	~FPSCounter();
	void Initialize() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	FPSCounter(const FPSCounter& other) = delete;
	FPSCounter(FPSCounter&& other) = delete;
	FPSCounter& operator=(const FPSCounter& other) = delete;
	FPSCounter& operator=(FPSCounter&& other) = delete;

private:
	dae::TextObject* m_pTextObject = nullptr;
	FPS* m_pFPS = nullptr;
};
