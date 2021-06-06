#include "QbertPCH.h"
#include "GameModeChangeAndStartGameCommand.h"

#include "QbertGameSettings.h"
#include "scenes/QbertScene.h"

Qbert::GameModeChangeAndStartGameCommand::GameModeChangeAndStartGameCommand(GameMode gameMode)
	:Command(),
	m_GameMode(gameMode)
{
}

void Qbert::GameModeChangeAndStartGameCommand::Execute()
{
	QbertGameSettings::GetInstance().SetGameMode(m_GameMode);
	if (strcmp(peach::SceneManager::GetInstance().GetActiveSceneName().c_str(), "Qbert") != 0)
	{
		peach::SceneManager::GetInstance().AddScene(std::make_shared<QbertScene>());
		peach::SceneManager::GetInstance().SetActiveGameScene("Qbert");
	}

}
