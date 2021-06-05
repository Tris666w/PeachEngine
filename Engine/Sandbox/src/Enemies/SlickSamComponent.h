#pragma once
#include "ComponentBase.h"

namespace peach
{
	class TextureComponent;
}

namespace Qbert
{
	enum class MoveDirection;
	class LevelMovementComponent;

	class SlickSamComponent final : public peach::ComponentBase
	{
	public:
		explicit SlickSamComponent(bool isSlick);
		void Initialize() override;
		void Update() override;
		void Render() const override;

		void Spawn();
		void Remove() const;

	private:
		LevelMovementComponent* m_pMovementComponent = nullptr;
		peach::TextureComponent* m_TextureComponent = nullptr;

		float m_MovementTimer = 0.f;
		float const m_MoveWaitTime = 0.75f;

		bool m_IsSlick;
		MoveDirection m_MoveDir;

		void SetAnimTexture();
	};

}

