#pragma once
namespace peach
{
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
		virtual void Render()
		{
			
		};

		ComponentBase() = default;
		virtual ~ComponentBase() = default;

		ComponentBase(const ComponentBase&) = delete;
		ComponentBase(ComponentBase&&) = delete;
		ComponentBase& operator=(const ComponentBase&) = delete;
		ComponentBase& operator=(ComponentBase&&) = delete;
	};
}
