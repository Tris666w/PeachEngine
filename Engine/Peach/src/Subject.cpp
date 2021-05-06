#include "PeachPCH.h"
#include "Subject.h"
#include "GameObject.h"
#include "Observer.h"

void peach::Subject::AddObserver(Observer* pObserver)
{
	m_pObserverVector.push_back(pObserver);
}

void peach::Subject::RemoveObserver(Observer* pObserver)
{
	m_pObserverVector.erase(std::remove(m_pObserverVector.begin(), m_pObserverVector.end(), pObserver),m_pObserverVector.end());
	
}

void peach::Subject::Notify(const GameObject& pGameObject,const Event event)
{
	for (Observer* observer : m_pObserverVector)
	{
			observer->Notify(pGameObject, event);
	}
}
