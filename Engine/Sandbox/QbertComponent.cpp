#include "QbertPCH.h"

#include "QbertComponent.h"
#include "QbertGameSettings.h"
#include "Level/LevelComponent.h"
#include "Level/TileComponent.h"

void peach::QbertComponent::Initialize()
{
	GetParent()->SetTag(QbertGameSettings::qbert_tag);
}

void peach::QbertComponent::Update()
{
}

