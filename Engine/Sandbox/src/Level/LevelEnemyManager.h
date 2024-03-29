#pragma once
#include "ComponentBase.h"


namespace Qbert
{
	class CoilyComponent;
	class SlickSamComponent;
	class UggWrongwayComponent;

	class LevelEnemyManager final : public peach::ComponentBase
	{
	public:
		LevelEnemyManager(int charSize = 32);

		void Initialize() override;
		void PostInitialize() override;
		void Update() override;
		void Render() const override;
		void Reset();


	private:
		CoilyComponent* m_CoilyComponent = nullptr;
		SlickSamComponent* m_SamComponent = nullptr;
		SlickSamComponent* m_SlickComponent = nullptr;
		UggWrongwayComponent* m_Ugg = nullptr;
		UggWrongwayComponent* m_Wrongway = nullptr;


		CoilyComponent* CreateCoilyGameObject() const;
		SlickSamComponent* CreateSlickOrSamGameObject(bool isSlick) const;
		UggWrongwayComponent* CreateUggOrWrongwayGameObject(bool isUgg)const;

		int m_CharSize;

		float m_SpawnTimer = 0.f;
		float const m_SpawnTime = 2.5f;
		int m_amountOfEnemiesSpawned = 0;
		void SpawnRandomEnemy();
	};

}

