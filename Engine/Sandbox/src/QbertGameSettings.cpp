#include "QbertPCH.h"
#include "QbertGameSettings.h"

void Qbert::QbertGameSettings::SetGameMode(GameMode gameMode)
{
	m_GameMode = gameMode;
	switch (m_GameMode)
	{
	case GameMode::SinglePlayer:
		m_AmountOfPlayers = 1;
		break;
	case GameMode::Coop:
		m_AmountOfPlayers = 2;
		break;
	case GameMode::Versus:
		m_AmountOfPlayers = 1;
		break;
	}
}
