#pragma once
#include "Observer.h"

namespace Qbert {
    class Health;

    class HealthObserver final:
        public peach::Observer
    {
    public:
        HealthObserver(int* pOwnerHeatlth, peach::Subject* pSubject);
        void Notify(const peach::GameObject& GameObject, peach::Event event) override;
    private:
        int* m_pOwnerHealth = nullptr;
        peach::Subject* m_Subject = nullptr;
    };
}
