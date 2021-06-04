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

void Scene::Initialize()
{
	for (auto& object : m_pObjects)
	{
		object->Initialize();
	}
}

void Scene::PostInitialize()
{
	for (auto& object : m_pObjects)
	{
		object->PostInitialize();
	}
}

void Scene::FixedUpdate()
{
	for (auto& object : m_pObjects)
	{
		if (object->GetIsActive())
			object->FixedUpdate();
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_pObjects)
	{
		if (object->GetIsActive())
			object->LateUpdate();
	}
}

void Scene::Update()
{
	for (auto& object : m_pObjects)
	{
		if (object->GetIsActive())
			object->Update();
	}
}

void Scene::Render() const
{
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
