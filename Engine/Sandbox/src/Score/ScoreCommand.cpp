#include "QbertPCH.h"

#include "ScoreCommand.h"

Qbert::ScoreCommand::ScoreCommand(Qbert::ScoreComponent* pScoreComponent, int addedScore)
	:m_pScoreComponent(pScoreComponent)
	, m_AmountOfAddedScore(addedScore)
{

}

void Qbert::ScoreCommand::Execute()
{
	m_pScoreComponent->IncreaseScore(m_AmountOfAddedScore);
}
