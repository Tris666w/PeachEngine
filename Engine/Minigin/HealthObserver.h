#pragma once
#include "Observer.h"
namespace dae {
    class Health;

    class HealthObserver final:
        public Observer
    {
    public:
        HealthObserver(int* pOwnerHeatlth, Subject* pSubject);
        void Notify(const GameObject& GameObject, Event event) override;
    private:
        int* m_pOwnerHealth = nullptr;
        Subject* m_Subject = nullptr;
    };
}
