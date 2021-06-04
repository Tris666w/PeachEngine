#pragma once
#include "ComponentBase.h"


namespace Qbert
{
	class CoilyComponent;
	class LevelEnemyManager final : public peach::ComponentBase
	{
	public:
		void Initialize() override;
		void PostInitialize() override;
		void Update() override;


	private:
		CoilyComponent* m_CoilyComponent = nullptr;
		CoilyComponent* CreateCoilyGameObject() const;
	};

}

