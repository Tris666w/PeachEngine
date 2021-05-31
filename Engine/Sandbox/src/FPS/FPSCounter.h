#pragma once
#include "ComponentBase.h"


namespace peach {
	class TextComponent;
	class FPS;

	class FPSCounter final : public ComponentBase
	{
	public:
		FPSCounter(TextComponent* pTextObject);

		~FPSCounter() override;
		void Initialize() override;
		void FixedUpdate() override;
		void Update() override;
		void LateUpdate() override;
		void Render() const override;

		FPSCounter(const FPSCounter& other) = delete;
		FPSCounter(FPSCounter&& other) = delete;
		FPSCounter& operator=(const FPSCounter& other) = delete;
		FPSCounter& operator=(FPSCounter&& other) = delete;

	private:
		TextComponent* m_pTextComp = nullptr;
		FPS* m_pFPS = nullptr;
	};

	
}

