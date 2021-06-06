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
		ScoreComponent();
		~ScoreComponent() = default;

		void IncreaseScore(int amount);

		[[nodiscard]] int GetScore() const;
		[[nodiscard]] peach::Subject* GetpSubject()const;

		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
		int m_Score = 0;
		std::unique_ptr<peach::Subject> m_ScoreSubject = nullptr;
	};
}
