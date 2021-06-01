#pragma once
#include <cstdint>
#include <string>

#include "Singleton.h"
namespace peach
{
	class QbertGameSettings :public Singleton<QbertGameSettings>
	{
	public:
		~QbertGameSettings() = default;
		QbertGameSettings(const QbertGameSettings& other) = delete;
		QbertGameSettings(QbertGameSettings&& other) noexcept = delete;
		QbertGameSettings& operator=(const QbertGameSettings& other) = delete;
		QbertGameSettings& operator=(QbertGameSettings&& other) noexcept = delete;

		uint32_t GetAmountOfPlayers()const { return m_AmountOfPlayers; }

		inline static std::string level_tag = "Level";
		inline static std::string qbert_tag = "Qbert";

	private:
		friend class Singleton<QbertGameSettings>;
		QbertGameSettings() = default;

		uint32_t m_AmountOfPlayers = 1;
	};
}
