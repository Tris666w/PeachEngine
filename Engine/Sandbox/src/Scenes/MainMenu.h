#pragma once
#include "Scene.h"
namespace Qbert
{
	class MainMenu final :public peach::Scene
	{
	public:
		MainMenu();
		void Initialize() override;
	};
}