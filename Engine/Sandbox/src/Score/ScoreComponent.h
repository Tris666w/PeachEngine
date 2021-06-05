#pragma once
#include "ComponentBase.h"

namespace peach
{
	class Subject;
	class GameObject;
}

namespace Qbert {

	class ScoreComponent final :public peach::ComponentBase
	{
	public:
		ScoreComponent(peach::GameObject* pOwner);
		~ScoreComponent() = default;

		void IncreaseScore(int amount);

		[[nodiscard]] int GetScore() const;
		[[nodiscard]] peach::Subject* GetpSubject()const;

	private:
		int m_Score = 0;
		peach::GameObject* m_pOwner = nullptr;
		std::unique_ptr<peach::Subject> m_ScoreSubject = nullptr;
	};
}
