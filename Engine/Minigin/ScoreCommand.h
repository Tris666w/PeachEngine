#pragma once
#include "Command.h"
#include "ScoreComponent.h"

class ScoreCommand final: public Command
{
public:
	ScoreCommand(dae::ScoreComponent* pScoreComponent, int addedScore);
	void Execute() override;
	
private:
	dae::ScoreComponent* m_pScoreComponent = nullptr;
	int m_AmountOfAddedScore = 0;
};

