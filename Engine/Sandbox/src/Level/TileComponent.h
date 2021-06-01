#pragma once
#include "ComponentBase.h"
#include "Peach.h"

namespace peach
{
    class TileComponent final :public ComponentBase
    {
    public:
        TileComponent() = default;
        void SetTextureVector(std::vector<std::string> vector);
    private:
        std::vector<std::string>m_pTextureVector;
        int m_CurrentStage = 0;

    };
}

