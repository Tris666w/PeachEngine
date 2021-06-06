#pragma once
#include "Command.h"
namespace Qbert
{
	class QuitCommand final :public peach::Command
	{
		void Execute() override;
	};
}