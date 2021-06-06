#pragma once
#include "Singleton.h"
namespace Qbert
{
	enum class GameMode
	{
		SinglePlayer = 0,
		Coop = 1,
		Versus = 2
	};
	class QbertGameSettings :public peach::Singleton<QbertGameSettings>
	{
	public:
		~QbertGameSettings() = default;
		QbertGameSettings(const QbertGameSettings& other) = delete;
		QbertGameSettings(QbertGameSettings&& other) noexcept = delete;
		QbertGameSettings& operator=(const QbertGameSettings& other) = delete;
		QbertGameSettings& operator=(QbertGameSettings&& other) noexcept = delete;

		uint32_t GetAmountOfPlayers()const { return m_AmountOfPlayers; }


		void SetGameMode(GameMode gameMode);
		GameMode GetGameMode()const { return m_GameMode; }

		inline static std::string level_tag = "Level";
		inline static std::string qbert_tag = "Qbert";
		inline static std::string purple_enemy_tag = "Purple";
		inline static std::string green_enemy_tag = "Green";
		inline static std::string disc_tag = "Disc";
		inline static std::string ui_tag = "Ui";



		static int const level_size = 10;

	private:
		friend class peach::Singleton<QbertGameSettings>;
		QbertGameSettings() = default;

		GameMode m_GameMode = GameMode::Versus;
		uint32_t m_AmountOfPlayers = 1;
	};
}
