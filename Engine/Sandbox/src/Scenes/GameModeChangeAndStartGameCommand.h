#pragma once
#include "Command.h"
namespace Qbert
{
    enum class GameMode;
    class GameModeChangeAndStartGameCommand final : public peach::Command
    {
    public:
        GameModeChangeAndStartGameCommand(GameMode gameMode);
        void Execute() override;

    private:
        GameMode m_GameMode;
    };
}