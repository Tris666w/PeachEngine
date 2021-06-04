#pragma once
#include "Observer.h"
namespace Qbert {
    class ScoreObserver final: public peach::Observer
    {
    public:
        ScoreObserver(int* pOwnerScore, peach::Subject* pSubject);
        void Notify(const peach::GameObject& GameObject, peach::Event event) override;
    private:
        int* m_pOwnerScore = nullptr;
        peach::Subject* m_Subject = nullptr;
    };
}
