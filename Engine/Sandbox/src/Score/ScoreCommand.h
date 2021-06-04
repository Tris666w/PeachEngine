#pragma once
#include "Command.h"
#include "ScoreComponent.h"

namespace Qbert
{
	class ScoreCommand final : public peach::Command
	{
	public:
		ScoreCommand(ScoreComponent* pScoreComponent, int addedScore);
		void Execute() override;

	private:
		ScoreComponent* m_pScoreComponent = nullptr;
		int m_AmountOfAddedScore = 0;
	};
}