#pragma once
namespace peach
{
	class SceneObject
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
		virtual void Render() const
		{
			
		};

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};
}
