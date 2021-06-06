#pragma once
#include "ComponentBase.h"
#include <memory>

namespace peach
{
    class Subject;
    class GameObject;
}

namespace Qbert {

    class Health final : public peach::ComponentBase
    {
    public:
        Health(int maxHealth, int startHealth);
        ~Health() = default;

        void DoDamage(int damage);
        [[nodiscard]] int GetHealth() const;

        [[nodiscard]] peach::Subject* GetpSubject()const;
        void Initialize() override;
        void Update() override;
        void Render() const override;
    private:
        bool m_PlayerIsDead = false;
        int m_MaxHealth = {};
        int m_CurrentHealth = {};
        std::unique_ptr<peach::Subject> m_HealthSubject = nullptr;
    };

};