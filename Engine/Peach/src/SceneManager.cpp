#include "PeachPCH.h"
#include "SceneManager.h"
#include "Scene.h"

bool peach::SceneManager::Update()
{
	if (m_ActiveScene)
	{
		if (m_ActiveScene->RootUpdate())
			return false;
	}
	return true;
}

void peach::SceneManager::LateUpdate()
{
	if (m_ActiveScene)
	{
		m_ActiveScene->RootLateUpdate();
	}
}

void peach::SceneManager::Render()const
{
	if (m_ActiveScene)
	{
		m_ActiveScene->RootRender();
	}
}

const std::string& peach::SceneManager::GetActiveSceneName() const
{
	return m_ActiveScene->GetName();
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

void peach::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	const auto it = std::find(m_Scenes.begin(), m_Scenes.end(), scene);

	if (it == m_Scenes.end())
	{
		m_Scenes.push_back(scene);
		if (m_IsInitialized)
		{
			scene->RootInitialize();
			scene->RootPostInitialize();
		}
		if (m_ActiveScene == nullptr)
			m_ActiveScene = scene;
	}
}

void peach::SceneManager::RemoveScene(std::shared_ptr<Scene> scene)
{
	const auto it = std::find(m_Scenes.begin(), m_Scenes.end(), scene);

	if (it != m_Scenes.end())
		m_Scenes.erase(it);
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
		scene->RootInitialize();
	}
	m_IsInitialized = true;
}

void peach::SceneManager::PostInitialize()
{
	for (auto& scene : m_Scenes)
	{
		scene->RootPostInitialize();
	}
}

void peach::SceneManager::FixedUpdate()
{
	if (m_ActiveScene)
	{
		m_ActiveScene->RootFixedUpdate();
	}
}
