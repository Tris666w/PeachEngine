#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "ComponentBase.h"

dae::GameObject::~GameObject()
{
	for (ComponentBase* pComponentBase : m_pComponents)
	{
		delete pComponentBase;
		pComponentBase = nullptr;
	}
};

void dae::GameObject::AddComponent(ComponentBase* newComponent)
{
	if (newComponent)
		m_pComponents.push_back(newComponent);
}

void dae::GameObject::Initialize()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->Initialize();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->FixedUpdate();
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (ComponentBase* element : m_pComponents)
	{
		element->Update(deltaTime);
	}
}

void dae::GameObject::LateUpdate()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->LateUpdate();
	}
}

void dae::GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);

	for (ComponentBase* element : m_pComponents)
	{
		element->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}