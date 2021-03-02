#pragma once
#include "Observer.h"
namespace dae {
    class ScoreObserver final: public Observer
    {
    public:
        ScoreObserver(int* pOwnerScore, Subject* pSubject);
        void Notify(const GameObject& GameObject, Event event) override;
    private:
        int* m_pOwnerScore = nullptr;
        Subject* m_Subject = nullptr;
    };
}
