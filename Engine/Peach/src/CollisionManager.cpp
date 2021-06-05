#include "PeachPCH.h"
#include "CollisionManager.h"

#include "GameObject.h"
#include "RectColliderComponent.h"
#include "Renderer.h"

peach::CollisionManager::~CollisionManager()
{
}

void peach::CollisionManager::CheckCollisions()
{
	for (size_t index = 0; index < m_pColliders.size(); ++index)
	{
		if (index + 1 >= m_pColliders.size())
			return;
		if (!m_pColliders[index]->GetParent()->GetIsActive())
			continue;

		for (size_t i = index + 1; i < m_pColliders.size(); ++i)
		{
			if (!m_pColliders[i]->GetParent()->GetIsActive())
				continue;

			auto const collider1 = m_pColliders[index];
			auto const collider2 = m_pColliders[i];

			if (CheckOverlap(collider1, collider2) &&
				collider1->GetParent()->GetScene() == collider2->GetParent()->GetScene())
			{
				collider1->Collide(collider2->GetParent());
				collider2->Collide(collider1->GetParent());
			}
		}
	}
}

void peach::CollisionManager::Render() const
{
	for (auto collider : m_pColliders)
	{
		auto shape = collider->GetWorldPosRect();
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 219, 73, 172, 0);
		SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &shape);
	}
}

void peach::CollisionManager::AddCollider(RectColliderComponent* pCollider)
{
	if (pCollider)
	{
		if (std::find(m_pColliders.begin(), m_pColliders.end(), pCollider) == m_pColliders.end())
			m_pColliders.push_back(pCollider);
	}
	else
		Logger::LogWarning("CollisionManager::AddCollider, given collider is nullptr");
}

void peach::CollisionManager::RemoveCollider(RectColliderComponent* pCollider)
{
	std::_Erase_remove(m_pColliders, pCollider);
}

peach::CollisionManager::CollisionManager()
{
}

bool peach::CollisionManager::CheckOverlap(RectColliderComponent* collider1, RectColliderComponent* collider2)
{
	SDL_Rect shape1 = collider1->GetWorldPosRect();
	SDL_Rect shape2 = collider2->GetWorldPosRect();

	if ((shape1.x + shape1.w) < shape2.x ||
		(shape2.x + shape2.w) < shape1.x)
		return false;

	if (shape1.y > (shape2.y + shape2.h) ||
		shape2.y > (shape1.y + shape1.h))
		return false;

	return true;
}
