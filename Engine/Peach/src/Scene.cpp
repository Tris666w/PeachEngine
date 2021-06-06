#include "PeachPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace peach;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (auto go : m_pObjects)
		SafeDelete(go);
}

void Scene::Add(GameObject* object)
{
	object->SetScene(this);
	m_pObjects.push_back(object);
}

void Scene::Remove(GameObject* object)
{
	if (object)
	{
		std::_Erase_remove(m_pObjects, object);
	}
}

void Scene::RootInitialize()
{
	if (m_IsInitialized)
		return;

	m_pInputManager = std::make_shared<InputManager>();
	m_pInputManager->Init();

	Initialize();

	for (auto& object : m_pObjects)
	{
		object->Initialize();
	}

	m_IsInitialized = true;
}

void Scene::RootPostInitialize()
{
	PostInitialize();

	for (auto& object : m_pObjects)
	{
		object->PostInitialize();
	}
}

void Scene::RootFixedUpdate()
{
	FixedUpdate();

	for (auto& object : m_pObjects)
	{
		if (object->GetIsActive())
			object->FixedUpdate();
	}
}

void Scene::RootLateUpdate()
{
	LateUpdate();

	for (auto& object : m_pObjects)
	{
		if (object->GetIsActive())
			object->LateUpdate();
	}
}

bool Scene::RootUpdate()
{
	auto const shouldStop = !m_pInputManager->ProcessInput();

	Update();

	for (auto& object : m_pObjects)
	{
		if (object->GetIsActive())
			object->Update();
	}

	return shouldStop;
}

void Scene::RootRender() const
{
	Render();

	for (const auto& object : m_pObjects)
	{
		if (object->GetIsActive())
			object->Render();
	}
}

std::vector<GameObject*> Scene::GetObjectsWithTag(const std::string& tag)
{
	std::vector<GameObject*> vector{};
	for (const auto& object : m_pObjects)
	{
		if (strcmp(tag.c_str(), object->GetTag().c_str()) == 0)
			vector.push_back(object);
	}

	return vector;
}
