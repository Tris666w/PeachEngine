#include "MiniginPCH.h"
#include "ScoreCommand.h"

ScoreCommand::ScoreCommand(dae::ScoreComponent* pScoreComponent, int addedScore)
	:m_pScoreComponent(pScoreComponent)
	,m_AmountOfAddedScore(addedScore)
{
	
}

void ScoreCommand::Execute()
{
	m_pScoreComponent->IncreaseScore(m_AmountOfAddedScore);
}