#pragma once
#include "ComponentBase.h"
#include "Peach.h"

namespace Qbert
{
    class LevelComponent;
    class TileComponent final :public peach::ComponentBase
    {
    public:
        TileComponent(const std::vector<std::string>& textureVector, LevelComponent* pLevel, bool reverses = false);
        void QbertStepOn(peach::GameObject* pQbert);
        void GreenStepOn();

        bool GetIsFinished()const { return m_IsFinished; }

        void SetReverses(bool state);
        void SetTextureVector(const std::vector<std::string>& m_pTextureVector);


        void Initialize() override;
        void Update() override;
        void Render() const override;
    private:
        std::vector<std::string>m_pTextureVector;
        LevelComponent* m_pLevel;
        uint32_t m_CurrentStage;
        uint32_t m_MaxStages;
        bool m_Reverses;
        bool m_IsFinished;
    };
}

