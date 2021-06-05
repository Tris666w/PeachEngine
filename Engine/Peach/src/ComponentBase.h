#pragma once
namespace peach
{
	class GameObject;

	class ComponentBase
	{
	public:
		virtual void Initialize() = 0;

		virtual void PostInitialize() {}
		virtual void FixedUpdate() {}
		virtual void Update() = 0;
		virtual void LateUpdate() {}
		virtual void Render()const = 0;

		ComponentBase() = default;
		virtual ~ComponentBase() = default;
		void SetParent(GameObject* pParent);
		GameObject* GetParent()const;

		ComponentBase(const ComponentBase&) = delete;
		ComponentBase(ComponentBase&&) = delete;
		ComponentBase& operator=(const ComponentBase&) = delete;
		ComponentBase& operator=(ComponentBase&&) = delete;

	private:
		bool m_IsInitialized = false;
		GameObject* m_pParent = nullptr;

		friend class GameObject;
		void RootInitialize();
	};

	inline void ComponentBase::SetParent(GameObject* pParent)
	{
		m_pParent = pParent;
	}

	inline GameObject* ComponentBase::GetParent() const
	{
		return m_pParent;
	}

	inline void ComponentBase::RootInitialize()
	{
		if (m_IsInitialized)
			return;


		Initialize();

		m_IsInitialized = true;
	}
}
