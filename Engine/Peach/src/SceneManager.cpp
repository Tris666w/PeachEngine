#include "PeachPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void peach::SceneManager::Update()
{
	if (m_ActiveScene)
	{
		m_ActiveScene->Update();
	}
}

void peach::SceneManager::LateUpdate()
{
	if (m_ActiveScene)
	{
		m_ActiveScene->LateUpdate();
	}
}

void peach::SceneManager::Render()const
{
	if (m_ActiveScene)
	{
		m_ActiveScene->Render();
	}
}

peach::Scene& peach::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);

	return *m_Scenes.at((m_Scenes.size() - 1));
}

std::shared_ptr<peach::Scene> peach::SceneManager::GetScene(const std::string& name)
{
	const auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(),
		[name](std::shared_ptr<Scene> scene)
		{
			return strcmp(scene->GetName().c_str(), name.c_str()) == 0;
		});

	if (it != m_Scenes.end())
		return *it;
	else
		return std::shared_ptr<Scene>();
}

void peach::SceneManager::SetActiveGameScene(const std::string& name)
{
	const auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(),
		[name](std::shared_ptr<Scene> scene)
		{
			return strcmp(scene->GetName().c_str(), name.c_str()) == 0;
		});

	if (it != m_Scenes.end())
	{
		m_ActiveScene = *it;
	}
}


void peach::SceneManager::Initialize()
{
	for (auto& scene : m_Scenes)
	{
		scene->Initialize();
	}
}

void peach::SceneManager::PostInitialize()
{
	for (auto& scene : m_Scenes)
	{
		scene->PostInitialize();
	}
}

void peach::SceneManager::FixedUpdate()
{
	if (m_ActiveScene)
	{
		m_ActiveScene->FixedUpdate();
	}
}
