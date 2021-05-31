#include "PeachPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "ComponentBase.h"

peach::GameObject::~GameObject()
{
	for (ComponentBase* pComponentBase : m_pComponents)
	{
		delete pComponentBase;
		pComponentBase = nullptr;
	}
};

void peach::GameObject::AddComponent(ComponentBase* newComponent)
{
	if (newComponent)
	{
		m_pComponents.push_back(newComponent);
		newComponent->SetParent(this);
	}
}

void peach::GameObject::Initialize()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->Initialize();
	}
}

void peach::GameObject::FixedUpdate()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->FixedUpdate();
	}
}

void peach::GameObject::Update()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->Update();
	}
}

void peach::GameObject::LateUpdate()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->LateUpdate();
	}
}

void peach::GameObject::Render() const
{
	for (ComponentBase* element : m_pComponents)
	{
		element->Render();
	}
}

void peach::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}