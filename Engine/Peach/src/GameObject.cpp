#include "PeachPCH.h"
#include "GameObject.h"

#include "ComponentBase.h"

peach::GameObject::~GameObject()
{
	for (ComponentBase* pComponentBase : m_pComponents)
		SafeDelete(pComponentBase);

	for (GameObject* childObj : m_pChildren)
		SafeDelete(childObj);
};

void peach::GameObject::AddChild(GameObject* object)
{
	object->SetParent(this);
	object->SetScene(m_pParentScene);
	object->Initialize();
	m_pChildren.push_back(object);

}

void peach::GameObject::SetParent(GameObject* object)
{
	m_pParent = object;
}

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
		element->Initialize();
	for (GameObject* child : m_pChildren)
		child->Initialize();

	if (m_pParent)
	{
		m_Transform.SetPosition(m_pParent->GetpTransform()->GetPosition() + m_Transform.GetPosition());
	}
}

void peach::GameObject::PostInitialize()
{
	for (ComponentBase* element : m_pComponents)
		element->PostInitialize();
	for (GameObject* child : m_pChildren)
		child->PostInitialize();
}

void peach::GameObject::FixedUpdate()
{
	for (ComponentBase* element : m_pComponents)
		element->FixedUpdate();
	for (GameObject* child : m_pChildren)
	{
		if (child->GetIsActive())
			child->FixedUpdate();
	}
}

void peach::GameObject::Update()
{
	for (ComponentBase* element : m_pComponents)
		element->Update();
	for (GameObject* child : m_pChildren)
	{
		if (child->GetIsActive())
			child->Update();
	}
}

void peach::GameObject::LateUpdate()
{
	for (ComponentBase* element : m_pComponents)
		element->LateUpdate();
	for (GameObject* child : m_pChildren)
	{
		if (child->GetIsActive())
			child->LateUpdate();
	}
}

void peach::GameObject::Render() const
{
	for (ComponentBase* element : m_pComponents)
		element->Render();
	for (GameObject* child : m_pChildren)
	{
		if (child->GetIsActive())
			child->Render();
	}
}

void peach::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);

	for (GameObject* child : m_pChildren)
		child->SetPosition(x, y);
}