#include "PeachPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void peach::SceneManager::Update()
{
	for (auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void peach::SceneManager::LateUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->LateUpdate();
	}
}

void peach::SceneManager::Render()const
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

peach::Scene& peach::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *m_Scenes.at((m_Scenes.size() - 1));
}

void peach::SceneManager::Initialize()
{
	for (auto& scene : m_Scenes)
	{
		scene->Initialize();
	}
}

void peach::SceneManager::FixedUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}
}