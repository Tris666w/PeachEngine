#pragma once
#include "ComponentBase.h"
namespace peach
{
	class RectColliderComponent : public ComponentBase
	{
	public:
		typedef std::function<void(GameObject*)> CollisionCallback;
		~RectColliderComponent() override;
		explicit RectColliderComponent(SDL_Rect rect = { 0,0,10,10 });

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void SetCollisionCallback(CollisionCallback callback);
		void Collide(GameObject* pOther);

		SDL_Rect GetRect()const { return m_Rect; }
		SDL_Rect GetWorldPosRect()const;

	private:
		//Rect holding the offset and dimensions of the collider 
		SDL_Rect m_Rect;

		CollisionCallback m_CollisionCallback{};

	};
}
