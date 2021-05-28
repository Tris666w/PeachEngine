#include "PeachPCH.h"
#include "ScoreCommand.h"

ScoreCommand::ScoreCommand(peach::ScoreComponent* pScoreComponent, int addedScore)
	:m_pScoreComponent(pScoreComponent)
	,m_AmountOfAddedScore(addedScore)
{
	
}

void ScoreCommand::Execute()
{
	m_pScoreComponent->IncreaseScore(m_AmountOfAddedScore);
}
