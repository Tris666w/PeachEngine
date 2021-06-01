#pragma once
#include "Transform.h"
#include "Peach.h"
#include "Scene.h"

namespace peach
{
	class ComponentBase;
	class Texture2D;
	class GameObject final
	{
	public:

		void Initialize();
		void PostInitialize();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

		void SetPosition(float x, float y);

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void SetScene(Scene* scene) { m_pParentScene = scene; }
		Scene* GetScene()const { return m_pParentScene; }

		void AddChild(GameObject* object);
		void SetParent(GameObject* object);

		//Component stuff
		void AddComponent(ComponentBase* newComponent);
		template<class T>
		T* GetComponent()const;

		//Getters
		Transform* GetpTransform() { return &m_Transform; }

		const std::string& GetTag() const { return m_Tag; }
		void SetTag(const std::string& tag) { m_Tag = tag; }
	private:
		Transform m_Transform;
		std::vector<ComponentBase*> m_pComponents{};
		std::vector<GameObject*> m_pChildren{};

		GameObject* m_pParent = nullptr;
		Scene* m_pParentScene = nullptr;

		std::string m_Tag;
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
