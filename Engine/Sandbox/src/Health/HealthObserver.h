#pragma once
#include "Observer.h"

namespace Qbert {
    class Health;

    class HealthObserver final :
        public peach::Observer
    {
    public:
        HealthObserver(int* pOwnerHeatlth, bool* pTextUpdateBool, peach::Subject* pSubject);
        HealthObserver(bool* pIsDead, peach::Subject* pSubject);

        void Notify(const peach::GameObject& GameObject, peach::Event event) override;
    private:
        int* m_pOwnerHealth = nullptr;
        bool* m_pTextUpdateBool = nullptr;
        bool* m_pIsDead = nullptr;
        peach::Subject* m_Subject = nullptr;
    };
}
