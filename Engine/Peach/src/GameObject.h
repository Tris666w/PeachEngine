#pragma once
#include "Transform.h"

namespace peach
{
	class ComponentBase;
	class Texture2D;
	class GameObject final
	{
	public:

		void Initialize();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Component stuff
		void AddComponent(ComponentBase* newComponent);
		template<class T>
		T* GetComponent()const;

		//Getters
		Transform* GetpTransform() { return &m_Transform; }
	private:
		Transform m_Transform;
		std::vector<ComponentBase*> m_pComponents{};
	};

	template<class T>
	T* GameObject::GetComponent() const
	{
		for (ComponentBase* c : m_pComponents)
		{
			if (typeid(T) == typeid(*c))
			{
				return reinterpret_cast<T*>(c);
			}
		}
		return nullptr;
	}
}
