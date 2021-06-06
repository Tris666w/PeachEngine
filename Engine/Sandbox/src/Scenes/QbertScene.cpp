#include "QbertPCH.h"

#include "QbertScene.h"
#include "QbertGameSettings.h"
#include "Player/QbertComponent.h"
#include "Player/QbertController.h"
#include "SoundSystems.h"
#include "TextureComponent.h"
#include "Level/LevelComponent.h"
#include "Level/LevelMovementComponent.h"
#include "Level/LevelEnemyManager.h"
#include "RectColliderComponent.h"
#include "Enemies/CoilyComponent.h"
#include "Enemies/SlickSamComponent.h"
#include "Health/Health.h"
#include "Score/ScoreComponent.h"
#include "Player/PlayerUI.h"

Qbert::QbertScene::QbertScene() :Scene("Qbert")
{
}

void Qbert::QbertScene::Initialize()
{
    using namespace peach;

    int const characterSize = 32;
    auto windowDimensions = peach::Application::GetWindowDimensions();

    auto go = new GameObject();
    auto textureComp = new TextureComponent("Resources/Images/background.jpeg", windowDimensions.x, windowDimensions.y);
    go->AddComponent(textureComp);
    Add(go);

    go = new GameObject();
    auto lc = new LevelComponent();
    go->AddComponent(lc);
    auto lvmC = new LevelEnemyManager();
    go->AddComponent(lvmC);
    Add(go);

    go->SetPosition(windowDimensions.x / 3.f, 2 * windowDimensions.y / 3.f);

    for (size_t i = 0; i < QbertGameSettings::GetInstance().GetAmountOfPlayers(); ++i)
    {
        go = new GameObject();
        textureComp = new TextureComponent("Resources/Images/Qbert.png", characterSize, characterSize);
        go->AddComponent(textureComp);
        auto moveComponent = new LevelMovementComponent();
        go->AddComponent(moveComponent);
        auto controllerComp = new QbertController(static_cast<bool>(i));
        go->AddComponent(controllerComp);
        SDL_Rect colliderRect = { characterSize / 4,characterSize / 4,characterSize / 2,characterSize / 2 };
        auto collider = new RectColliderComponent(colliderRect);
        std::function const lambda = [](GameObject* qBert, GameObject* pOther)
        {
            auto scoreComp = qBert->GetComponent<ScoreComponent>();
            if (strcmp(QbertGameSettings::green_enemy_tag.c_str(), pOther->GetTag().c_str()) == 0)
            {
                scoreComp->IncreaseScore(300);
                pOther->GetComponent<SlickSamComponent>()->Remove();
            }
            if (strcmp(QbertGameSettings::purple_enemy_tag.c_str(), pOther->GetTag().c_str()) == 0)
            {
                if (auto coilyComp = pOther->GetComponent<CoilyComponent>(); coilyComp)
                {
                    if (coilyComp->GetIsEgg())
                        return;
                }
                qBert->GetComponent<Health>()->DoDamage(1);
                qBert->GetComponent<LevelMovementComponent>()->MoveImmediatelyToSpawnPos();
            }
        };
        collider->SetCollisionCallback(lambda);
        go->AddComponent(collider);
        auto healthComp = new Health(3, 3);
        go->AddComponent(healthComp);
        auto scoreComp = new ScoreComponent();
        go->AddComponent(scoreComp);
        auto qbertComp = new QbertComponent(healthComp->GetpSubject());
        go->AddComponent(qbertComp);
        Add(go);

        go = new GameObject();
        go->SetTag(QbertGameSettings::ui_tag);
        const auto playerUi = new PlayerUi(std::to_string(i + 1), 0, 5, healthComp->GetpSubject(), scoreComp->GetpSubject());
        go->AddComponent(playerUi);
        go->SetPosition(0, (i + 1) * windowDimensions.y / 5);
        Add(go);
    }
}
