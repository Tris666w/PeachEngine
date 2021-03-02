#pragma once
#include <vector>
namespace dae
{
	class GameObject;
	class Observer;

	enum class Event
	{
		OwnerDamaged,
		OwnerDied,
		ScoreIncreased
	};

	class Subject
	{
	public:
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
		void Notify(const GameObject& pGameObject, Event event);
	private:
		std::vector<Observer*>m_pObserverVector = {};
	};
}
