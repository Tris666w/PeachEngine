#pragma once
#include "Command.h"
#include "ScoreComponent.h"

namespace Qbert
{
	class ScoreCommand final : public peach::Command
	{
	public:
		ScoreCommand(peach::ScoreComponent* pScoreComponent, int addedScore);
		void Execute() override;

	private:
		peach::ScoreComponent* m_pScoreComponent = nullptr;
		int m_AmountOfAddedScore = 0;
	};
}