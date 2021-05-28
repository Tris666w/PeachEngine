#pragma once
#include "Singleton.h"
#include <chrono>

namespace peach
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		void SetElapsedSec(const float elapsedSec) {
			m_ElapsedSec = elapsedSec;
		}

		float GetElapsedSec()const { return m_ElapsedSec; }

	private:
		friend class Singleton<GameTime>;
		GameTime() = default;

		float m_ElapsedSec = 0.f;
	};
}
