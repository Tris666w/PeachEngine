#pragma once
#include "Command.h"
#include "ScoreComponent.h"

class ScoreCommand final: public Command
{
public:
	ScoreCommand(peach::ScoreComponent* pScoreComponent, int addedScore);
	void Execute() override;
	
private:
	peach::ScoreComponent* m_pScoreComponent = nullptr;
	int m_AmountOfAddedScore = 0;
};

