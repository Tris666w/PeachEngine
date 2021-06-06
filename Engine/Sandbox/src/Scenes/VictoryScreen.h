#pragma once
#include "Scene.h"

namespace Qbert
{
    class VictoryScreen final :public peach::Scene
    {
    public:
        VictoryScreen();
        void Initialize() override;
    private:
    };

}

