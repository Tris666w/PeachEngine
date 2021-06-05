#pragma once
#include "Singleton.h"
namespace Qbert
{
	class QbertGameSettings :public peach::Singleton<QbertGameSettings>
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
		inline static std::string purple_enemy_tag = "Purple";
		inline static std::string green_enemy_tag = "Green";


		static int const level_size = 7;

	private:
		friend class peach::Singleton<QbertGameSettings>;
		QbertGameSettings() = default;

		uint32_t m_AmountOfPlayers = 1;
	};
}
