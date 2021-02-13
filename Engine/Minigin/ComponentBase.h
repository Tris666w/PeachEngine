#pragma once
namespace dae
{
	class ComponentBase
	{
	public:
		virtual void Initialize() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void Render() = 0;

		ComponentBase() = default;
		virtual ~ComponentBase() = default;

		ComponentBase(const ComponentBase&) = delete;
		ComponentBase(ComponentBase&&) = delete;
		ComponentBase& operator=(const ComponentBase&) = delete;
		ComponentBase& operator=(ComponentBase&&) = delete;
	};
}
