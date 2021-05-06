#pragma once
#include "ComponentBase.h"

namespace peach
{
	class TextObject;
}
class FPS;

class FPSCounter final : public peach::ComponentBase
{
public:
	FPSCounter(peach::TextObject* pTextObject);

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
	peach::TextObject* m_pTextObject = nullptr;
	FPS* m_pFPS = nullptr;
};
