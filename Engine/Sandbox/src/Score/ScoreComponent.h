#pragma once
#include "ComponentBase.h"

namespace peach {
	class Subject;
	class GameObject;

	class ScoreComponent final :public ComponentBase
	{
	public:
		ScoreComponent(GameObject* pOwner);
		~ScoreComponent() = default;
		
		void IncreaseScore(int amount);

		[[nodiscard]] int GetScore() const;
        [[nodiscard]] Subject* GetpSubject()const;
	
	private:
		int m_Score = 0;
		GameObject* m_pOwner = nullptr;
		std::unique_ptr<Subject> m_ScoreSubject = nullptr;
	};
}
