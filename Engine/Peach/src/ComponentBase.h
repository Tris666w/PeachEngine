#pragma once
namespace peach
{
	class GameObject;

	class ComponentBase
	{
	public:
		virtual void Initialize()
		{

		};
		virtual void FixedUpdate()
		{

		};
		virtual void Update()
		{

		};
		virtual void LateUpdate()
		{

		};
		virtual void Render()const
		{

		};

		ComponentBase() = default;
		virtual ~ComponentBase() = default;
		void SetParent(GameObject* pParent);
		GameObject* GetParent()const;

		ComponentBase(const ComponentBase&) = delete;
		ComponentBase(ComponentBase&&) = delete;
		ComponentBase& operator=(const ComponentBase&) = delete;
		ComponentBase& operator=(ComponentBase&&) = delete;

	private:
		GameObject* m_pParent = nullptr;
	};

	inline void ComponentBase::SetParent(GameObject* pParent)
	{
		m_pParent = pParent;
	}

	inline GameObject* ComponentBase::GetParent() const
	{
		return m_pParent;
	}
}
