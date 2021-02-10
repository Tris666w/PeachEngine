#pragma once
#include "Transform.h"
#include "SceneObject.h"

namespace dae
{
	class ComponentBase;
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:

		void Initialize()override;
		void FixedUpdate()override;
		void Update(float deltaTime)override;
		void LateUpdate()override;
		void Render() const override;

		void SetTexture(const std::string& filename);
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
		std::shared_ptr<Texture2D> m_Texture{};
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
