#pragma once
#include "ComponentBase.h"
#include <memory>

namespace peach {
    class Subject;
    class GameObject;

    class Health final : public ComponentBase
    {
    public:
        Health(GameObject* m_pOwner, int maxHealth, int startHealth);
        ~Health() = default;

        void DoDamage(int damage);
        [[nodiscard]] int GetHealth() const;

        [[nodiscard]] Subject* GetpSubject()const;
    private:
        GameObject* m_pOwner = nullptr;
        bool m_PlayerIsDead = false;
        int m_MaxHealth = {};
        int m_CurrentHealth = {};
        std::unique_ptr<Subject> m_HealthSubject = nullptr;
    };

};