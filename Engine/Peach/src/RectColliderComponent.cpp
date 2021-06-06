#include "PeachPCH.h"
#include "RectColliderComponent.h"
#include "CollisionManager.h"

#include "GameObject.h"

peach::RectColliderComponent::~RectColliderComponent()
{
}

peach::RectColliderComponent::RectColliderComponent(SDL_Rect rect)
	:ComponentBase(),
	m_Rect(rect)
{
}

void peach::RectColliderComponent::Initialize()
{
	CollisionManager::GetInstance().AddCollider(this);
}

void peach::RectColliderComponent::SetCollisionCallback(CollisionCallback callback)
{
	m_CollisionCallback = callback;
}

void peach::RectColliderComponent::Collide(GameObject* pOther)
{
	if (m_CollisionCallback)
	{
		m_CollisionCallback(GetParent(), pOther);
	}
}

SDL_Rect peach::RectColliderComponent::GetWorldPosRect() const
{
	SDL_Rect rect = m_Rect;
	rect.x += static_cast<int>(GetParent()->GetpTransform()->GetPosition().x);
	rect.y += static_cast<int>(GetParent()->GetpTransform()->GetPosition().y);
	return rect;
}

void peach::RectColliderComponent::Update()
{
}

void peach::RectColliderComponent::Render() const
{
}


