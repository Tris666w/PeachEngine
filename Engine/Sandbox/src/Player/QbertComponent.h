#pragma once
#include "ComponentBase.h"

namespace peach {
	class TextureComponent;
	class Subject;
}

namespace Qbert
{
	enum class MoveDirection;
	class LevelComponent;
	class LevelMovementComponent;
	class HealthObserver;

	class QbertComponent final : public peach::ComponentBase
	{
	public:
		explicit QbertComponent(peach::Subject* pHealthSubject);
		QbertComponent(const QbertComponent& other) = delete;
		QbertComponent(QbertComponent&& other) noexcept = delete;
		QbertComponent& operator=(const QbertComponent& other) = delete;
		QbertComponent& operator=(QbertComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void SetIsOnDisc(bool state) { m_IsOnDisc = state; }
		bool GetIsOnDisc()const { return m_IsOnDisc; }

		bool GetIsDead()const { return m_IsDead; }
		void UpdateAnimTexture();

		void PostInitialize() override;
		void SetMoveDir(MoveDirection moveDirection);
	private:
		bool m_IsOnDisc = false;
		bool m_IsDead = false;
		LevelComponent* m_pLevel = nullptr;
		MoveDirection m_MoveDir;
		LevelMovementComponent* m_pMovementComponent = nullptr;

		std::unique_ptr<HealthObserver> m_pHealthObserver = nullptr;
		peach::TextureComponent* m_TextureComponent;
	};

}

