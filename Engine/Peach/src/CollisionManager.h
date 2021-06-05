#pragma once
#include "Singleton.h"
namespace peach
{
	class RectColliderComponent;
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		~CollisionManager();

		void CheckCollisions();
		void Render()const;
		void ToggleDebugRendering(bool state) { m_DebugRender = state; }

		void AddCollider(RectColliderComponent* pCollider);
		void RemoveCollider(RectColliderComponent* pCollider);


	private:
		friend class Singleton<CollisionManager>;
		CollisionManager();

		std::vector<RectColliderComponent*> m_pColliders{};
		bool m_DebugRender = false;

		bool CheckOverlap(RectColliderComponent* collider1, RectColliderComponent* collider2);
	};
}
