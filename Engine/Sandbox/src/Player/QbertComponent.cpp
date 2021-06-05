#include "QbertPCH.h"

#include "QbertComponent.h"
#include "QbertGameSettings.h"
#include "Level/LevelComponent.h"
#include "Level/TileComponent.h"

void Qbert::QbertComponent::Initialize()
{
	GetParent()->SetTag(QbertGameSettings::qbert_tag);
}

void Qbert::QbertComponent::Update()
{
}

void Qbert::QbertComponent::Render() const
{
}

