#pragma once
#include "Singleton.h"
#include <chrono>

namespace peach
{
	class Time final : public Singleton<Time>
	{
	public:
		void SetElapsedSec(const float elapsedSec) {
			m_ElapsedSec = elapsedSec;
		}

		float GetElapsedSec()const { return m_ElapsedSec; }

	private:
		friend class Singleton<Time>;
		Time() = default;

		float m_ElapsedSec = 0.f;
	};
}
